.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#####################
Using Service Clients
#####################

.. meta::
    :description:
        Using service clients like S3Client or IAMClient to connect to AWS with the AWS SDK for C++.
    :keywords:

AWS service client classes provide you with an interface to the AWS service that the class
represents. Service clients follow the namespace convention :samp:`Aws::{Service}::{Service}Client`.

For example, a client for |IAMlong| is constructed using the :classname:`Aws::IAM::IAMClient` class.
For an |S3long| client, use :classname:`Aws::S3::S3Client`.

When you use the client classes to instantiate a service client, you must supply AWS credentials.
You can do this by using the default credential provider chain, by manually passing credentials to
the client directly, or by using a custom credentials provider.

For more information about setting credentials, see :doc:`credentials`.


Using the Default Credential Provider Chain
-------------------------------------------

The following code shows how to create an |DDBlong| client by using a specialized client
configuration, default credential provider chain, and default HTTP client factory.

.. code-block:: cpp

    auto limiter = Aws::MakeShared<Aws::Utils::RateLimits::DefaultRateLimiter<>>(ALLOCATION_TAG, 200000);

    // Create a client
    ClientConfiguration config;
    config.scheme = Scheme::HTTPS;
    config.connectTimeoutMs = 30000;
    config.requestTimeoutMs = 30000;
    config.readRateLimiter = m_limiter;
    config.writeRateLimiter = m_limiter;

    auto client = Aws::MakeShared<DynamoDBClient>(ALLOCATION_TAG, config);


Passing Credentials Manually
----------------------------

The following code shows how to use the client constructor that takes three arguments, and use the
``Aws::Auth::AWSCredentials`` class to pass your credentials manually to the constructor.

.. code-block:: cpp

    auto client = Aws::MakeShared<DynamoDBClient>(
        ALLOCATION_TAG, AWSCredentials("access_key_id", "secret_key"), config);


Using a Custom Credentials Provider
-----------------------------------

The following code shows how to pass credentials to the ``Aws::MakeShared`` function and create a
client by using one of the credential providers in the ``Aws::Auth`` namespace.

.. code-block:: cpp

    auto client = Aws::MakeShared<DynamoDBClient>(
        ALLOCATION_TAG,
        Aws::MakeShared<CognitoCachingAnonymousCredentialsProvider>(
            ALLOCATION_TAG, "identityPoolId", "accountId"), config);


