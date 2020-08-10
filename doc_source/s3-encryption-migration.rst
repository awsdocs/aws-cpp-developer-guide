.. Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#####################################
Amazon S3 Encryption Client Migration
#####################################

.. meta::
   :description: Describes how to migrate to the latest Amazon S3 encryption clients for |sdk-cpp|.

This topic shows how to migrate your applications from Version 1 (V1) of the Amazon Simple Storage Service (Amazon S3) encryption client 
to Version 2 (V2) and ensure application availability throughout the migration process.

Migration Overview
==================

This migration happens in two phases: 

1. **Update existing clients to read new formats.** First, deploy an updated version of the |sdk-cpp| 
to your application. This allows existing V1 encryption clients to decrypt objects written by the 
new V2 clients. If your application uses multiple AWS SDKs, you must upgrade each SDK separately. 

2. **Migrate encryption and decryption clients to V2.** Once all of your V1 encryption clients can 
read new formats, you can migrate your existing encryption and decryption clients to their respective 
V2 versions.

Update Existing Clients to Read New Formats
=========================================== 

You must first update your existing clients to the latest SDK release. After completing this step, 
your application’s V1 clients will be able to decrypt objects encrypted by V2 encryption clients 
without updating your application’s code base.

Build and Install the Latest Version of the |sdk-cpp| 
-----------------------------------------------------

**Applications Consuming the SDK from Vcpkg**

If your application uses `Vcpkg <https://github.com/microsoft/vcpkg>`_ to track SDK updates, simply use your existing Vcpkg 
upgrade method to upgrade the SDK to the latest version. For example, you could run the following command to upgrade package aws-sdk-cpp:

.. code-block:: cpp

 vcpkg upgrade aws-sdk-cpp

And verify the version of package aws-sdk-cpp:

.. code-block:: cpp

 vcpkg list aws-sdk-cpp

The version should be at least 1.8.24. 

**Applications Consuming the SDK from Source**

If you build and install AWS SDK for C++ artifacts from source, pull the latest code from the 
following GitHub repository: https://github.com/aws/aws-sdk-cpp. Then repeat your normal build and install steps.

If you are upgrading |sdk-cpp| from a version earlier than 1.8.x, see this `CHANGELOG <https://github.com/aws/aws-sdk-cpp/blob/master/CHANGELOG.md>`_ for breaking changes 
introduced in each major version. For more information about how to build and install the |sdk-cpp|, see the README in our GitHub repository (https://github.com/aws/aws-sdk-cpp) 
or the AWS documentation (https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/setup.html).

Build, Install, and Deploy Your Applications
--------------------------------------------

If your application is statically linking against the |sdk-cpp|, code changes are not required in your application, but you must build your application again to 
consume the latest SDK changes. This step is not necessary for dynamic linking.

After upgrading your application’s dependency version and verifying application functionality, proceed to deploying your application to your fleet. Once 
application deployment is complete, you can proceed with the next phase for migrating your application to use the V2 encryption and decryption clients.

Migrate Encryption and Decryption Clients to V2
===============================================

The following steps show you how to successfully migrate your code from V1 to V2 of the Amazon S3 encryption client. Since code changes are required, you 
will need to rebuild your application regardless of whether it’s statically or dynamically linking against the |sdk-cpp|.

Using New Encryption Materials
------------------------------

With V2 Amazon S3 encryption clients and the V2 crypto configuration, the following encryption materials have been deprecated:

* ``SimpleEncryptionMaterials``
* ``KMSEncryptionMaterials``

They have been replaced with the following secure encryption materials:

* ``SimpleEncryptionMaterialsWithGCMAAD``
* ``KMSWithContextEncryptionMaterials``

The following code changes are required to construct a V2 S3 encryption client:

* If you are using ``KMSEncryptionMaterials`` when creating an S3 encryption client:
    * When creating a V2 S3 encryption client, replace ``KMSEncryptionMaterials`` with ``KMSWithContextEncryptionMaterials`` and specify it in the V2 crypto configuration.
    * When putting an object with V2 Amazon S3 encryption clients, you must explicitly provide a string-string context map as the KMS context for encrypting the CEK. This might be an empty map.
* If you are using ``SimpleEncryptionMaterials`` when creating an S3 encryption client:
    * When creating a V2 Amazon S3 encryption client, replace ``SimpleEncryptionMaterials`` with ``SimpleEncryptionMaterialsWithGCMAAD`` and specify it in the V2 crypto configuration.
    * When putting an object with V2 Amazon S3 encryption clients, you must explicitly provide an empty string-string context map, otherwise the SDK will return an error.

**Example: Using the KMS/KMSWithContext Key Wrap Algorithm**

*Pre-migration (KMS key wrap)*

.. code-block:: cpp

   auto materials = Aws::MakeShared<KMSEncryptionMaterials>("s3Encryption", CUSTOMER_MASTER_KEY_ID);
   CryptoConfiguration cryptoConfig;
   S3EncryptionClient encryptionClient(materials, cryptoConfig);
   // Code snippet here to setup the putObjectRequest object.
   encryptionClient.PutObject(putObjectRequest);

*Post-migration (KMSWithContext key wrap)*

.. code-block:: cpp

   auto materials = Aws::MakeShared<KMSWithContextEncryptionMaterials>("s3EncryptionV2", CUSTOMER_MASTER_KEY_ID);
   CryptoConfigurationV2 cryptoConfig(materials);
   S3EncryptionClientV2 encryptionClient(cryptoConfig);
   // Code snippet here to setup the putObjectRequest object.
   Aws::Map<Aws::String, Aws::String> kmsContextMap;
   kmsContextMap.emplace("client", "aws-sdk-cpp");
   kmsContextMap.emplace("version", "1.8.0");
   encryptionClient.PutObject(putObjectRequest, kmsContextMap /* could be empty as well */);

**Example:  Using the AES/AES-GCM Key Wrap Algorithm**

*Pre-migration (AES key wrap)*

.. code-block:: cpp

   auto materials = Aws::MakeShared<SimpleEncryptionMaterials>("s3Encryption", HashingUtils::Base64Decode(AES_MASTER_KEY_BASE64));
   CryptoConfiguration cryptoConfig;
   S3EncryptionClient encryptionClient(materials, cryptoConfig);
   // Code snippet here to setup the putObjectRequest object.
   encryptionClient.PutObject(putObjectRequest);

*Post-migration (AES-GCM key wrap)*

.. code-block:: cpp

   auto materials = Aws::MakeShared<SimpleEncryptionMaterialsWithGCMAAD>("s3EncryptionV2", HashingUtils::Base64Decode(AES_MASTER_KEY_BASE64));
   CryptoConfigurationV2 cryptoConfig(materials);
   S3EncryptionClientV2 encryptionClient(cryptoConfig);
   // Code snippet here to setup the putObjectRequest object.
   encryptionClient.PutObject(putObjectRequest, {} /* must be an empty map */);





Additional Examples
===================

The following examples demonstrate how to address specific use cases related to a migration from V1 to V2.

Decrypt Objects Encrypted by Legacy Amazon S3 Encryption Clients
----------------------------------------------------------------

By default, you can’t use the V2 Amazon S3 encryption client to decrypt objects that were encrypted with deprecated key wrap algorithms or deprecated content crypto schemas.

The following key wrap algorithms have been deprecated:

* ``KMS``
* ``AES_KEY_WRAP``

And the following content crypto schemas have been deprecated:

* ``CBC``
* ``CTR``

If you’re using legacy Amazon S3 encryption clients in the AWS SDK for C++ to encrypt the objects, you’re likely using the deprecated methods if:

* You used ``SimpleEncryptionMaterials`` or ``KMSEncryptionMaterials``.
* You used ``ENCRYPTION_ONLY`` as ``Crypto Mode`` in your crypto configuration.

To use the V2 Amazon S3 encryption client to decrypt objects that were encrypted by deprecated key wrap algorithms or deprecated content 
crypto schemas, you must override the default value of ``SecurityProfile`` in the V2 crypto configuration from ``V2`` to ``V2_AND_LEGACY``.

**Example**

*Pre-migration*

.. code-block:: cpp

   auto materials = Aws::MakeShared<KMSEncryptionMaterials>("s3Encryption", CUSTOMER_MASTER_KEY_ID);
   CryptoConfiguration cryptoConfig;
   S3EncryptionClient encryptionClient(materials, cryptoConfig);
   // Code snippet here to setup the getObjectRequest object.
   encryptionClient.GetObject(getObjectRequest);

*Post-migration*

.. code-block:: cpp

   auto materials = Aws::MakeShared<KMSWithContextEncryptionMaterials>("s3EncryptionV2", CUSTOMER_MASTER_KEY_ID);
   CryptoConfigurationV2 cryptoConfig(materials);
   cryptoConfig.SetSecurityProfile(SecurityProfile::V2_AND_LEGACY);
   S3EncryptionClientV2 encryptionClient(cryptoConfig);
   // Code snippet here to setup the getObjectRequest object.
   encryptionClient.GetObject(getObjectRequest);

Decrypt Objects with Range
--------------------------

With legacy Amazon S3 encryption clients, you can specify a range of bytes to receive when decrypting an S3 object. In the V2 Amazon S3 encryption client, this 
feature is ``DISABLED`` by default. Therefore you have to override the default value of ``RangeGetMode`` from ``DISABLED`` to ``ALL`` in the V2 crypto configuration.

**Example**

*Pre-migration*

.. code-block:: cpp

   auto materials = Aws::MakeShared<KMSEncryptionMaterials>("s3Encryption", CUSTOMER_MASTER_KEY_ID);
   CryptoConfiguration cryptoConfig;
   S3EncryptionClient encryptionClient(materials, cryptoConfig);
   // Code snippet here to setup the getObjectRequest object.
   getObjectRequest.WithRange("bytes=38-75");
   encryptionClient.GetObject(getObjectRequest);

*Post-migration*

.. code-block:: cpp

   auto materials = Aws::MakeShared<KMSWithContextEncryptionMaterials>("s3EncryptionV2", CUSTOMER_MASTER_KEY_ID);
   CryptoConfigurationV2 cryptoConfig(materials);
   cryptoConfig.SetUnAuthenticatedRangeGet(RangeGetMode::ALL);
   S3EncryptionClientV2 encryptionClient(cryptoConfig);
   // Code snippet here to setup the getObjectRequest object.
   getObjectRequest.WithRange("bytes=38-75");
   encryptionClient.GetObject(getObjectRequest);

Decrypt Objects with any CMK
----------------------------

When decrypting objects that were encrypted with ``KMSWithContextEncryptionMaterials``, V2 Amazon S3 encryption clients are capable 
of letting KMS to find the proper CMK by providing an empty master key. This feature is ``DISABLED`` by default. You have 
to configure it explicitly by calling ``SetKMSDecryptWithAnyCMK(true)`` for your KMS encryption materials.

**Example**

*Pre-migration*

.. code-block:: cpp

   auto materials = Aws::MakeShared<KMSEncryptionMaterials>("s3Encryption", ""/* provide an empty KMS Master Key*/);
   CryptoConfiguration cryptoConfig;
   S3EncryptionClient encryptionClient(materials, cryptoConfig);
   // Code snippet here to setup the getObjectRequest object.
   encryptionClient.GetObject(getObjectRequest);

*Post-migration*

.. code-block:: cpp

   auto materials = Aws::MakeShared<KMSWithContextEncryptionMaterials>("s3EncryptionV2", ""/* provide an empty KMS Master Key*/);
   materials.SetKMSDecryptWithAnyCMK(true);
   CryptoConfigurationV2 cryptoConfig(materials);
   S3EncryptionClientV2 encryptionClient(cryptoConfig);
   // Code snippet here to setup the getObjectRequest object.
   encryptionClient.GetObject(getObjectRequest);


For complete code examples for all of the migration scenarios mentioned in these docs, see https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3encryption.
