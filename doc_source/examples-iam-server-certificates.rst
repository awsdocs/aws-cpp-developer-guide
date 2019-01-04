.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

######################################
Working with |IAM| Server Certificates
######################################

.. meta::
   :description: How to manage AWS IAM server certificates.
   :keywords: iam

To enable HTTPS connections to your website or application on AWS, you need an SSL/TLS *server
certificate*. You can use a server certificate provided by |acmlong| or one that you obtained from
an external provider.

We recommend that you use |acm| to provision, manage, and deploy your server certificates. With
|acm| you can request a certificate, deploy it to your AWS resources, and let |acm| handle
certificate renewals for you. Certificates provided by |acm| are free. For more information about
|acm|, see the |acm-ug|_.

.. include:: includes/examples-note.txt

Retrieve a Server Certificate
=============================

You can retrieve a server certificate by calling the |iamclient|'s
:functionname:`GetServerCertificate` function, passing it a
:aws-cpp-class:`GetServerCertificateRequest
<aws_1_1_i_a_m_1_1_model_1_1_get_server_certificate_request>` with the certificate's name.

**Includes:**

.. literalinclude:: iam.cpp.get_server_cert.inc.txt

**Code:**

.. literalinclude:: iam.cpp.get_server_cert.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/get_server_cert.cpp>`.


List Server Certificates
========================

To list your server certificates, call the |iamclient|'s :functionname:`ListServerCertificates`
function with a :aws-cpp-class:`ListServerCertificatesRequest
<aws_1_1_i_a_m_1_1_model_1_1_list_server_certificates_request>`. It returns a
:aws-cpp-class:`ListServerCertificatesResult
<aws_1_1_i_a_m_1_1_model_1_1_list_server_certificates_result>`.

Call the returned :classname:`ListServerCertificateResult` object's
:functionname:`GetServerCertificateMetadataList` function to get a list of
:aws-cpp-class:`ServerCertificateMetadata <aws_1_1_i_a_m_1_1_model_1_1_server_certificate_metadata>`
objects that you can use to get information about each certificate.

Results may be truncated; if the :classname:`ListServerCertificateResult` object's
:functionname:`GetIsTruncated` function returns :code-cpp:`true`, call the
:classname:`ListServerCertificatesRequest` object's :functionname:`SetMarker` function and use it to
call :functionname:`listServerCertificates` again to get the next batch of results.

**Includes:**

.. literalinclude:: iam.cpp.list_server_certs.inc.txt

**Code:**

.. literalinclude:: iam.cpp.list_server_certs.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/list_server_certs.cpp>`.


Update a Server Certificate
===========================

You can update a server certificate's name or path by calling the |iamclient|'s
:functionname:`UpdateServerCertificate` function. It takes a
:aws-cpp-class:`UpdateServerCertificateRequest
<aws_1_1_i_a_m_1_1_model_1_1_update_server_certificate_request>` object set with the server
certificate's current name and either a new name or new path to use.

**Includes:**

.. literalinclude:: iam.cpp.update_server_cert.inc.txt

**Code:**

.. literalinclude:: iam.cpp.update_server_cert.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/update_server_cert.cpp>`.


Delete a Server Certificate
===========================

To delete a server certificate, call the |iamclient|'s :functionname:`DeleteServerCertificate`
function with a :aws-cpp-class:`DeleteServerCertificateRequest
<>` containing the certificate's
name.

**Includes:**

.. literalinclude:: iam.cpp.delete_server_cert.inc.txt

**Code:**

.. literalinclude:: iam.cpp.delete_server_cert.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/delete_server_cert.cpp>`.


More Information
================

* :iam-ug:`Working with Server Certificates <id_credentials_server-certs>` in the |iam-ug|
* :iam-api:`GetServerCertificate` in the |iam-api|
* :iam-api:`ListServerCertificates` in the |iam-api|
* :iam-api:`UpdateServerCertificate` in the |iam-api|
* :iam-api:`DeleteServerCertificate` in the |iam-api|
* |acm-ug|_

