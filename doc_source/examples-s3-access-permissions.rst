.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

########################################################
Managing |S3| Access Permissions for Buckets and Objects
########################################################

.. meta::
   :description: How to retrieve or set the access control list for an Amazon S3 bucket or object.
   :keywords: AWS for C++ SDK code examples, bucket access permissions, object access permissions

You can use access control lists (ACLs) for |s3| buckets and objects for fine-grained control over
your |s3| resources.

.. include:: includes/examples-note.txt


Get the Access Control List for a Bucket
========================================

To get the ACL for an |s3| bucket, call the |s3client|'s :functionname:`GetBucketAcl` function with
a :aws-cpp-class:`GetBucketAclRequest <aws_1_1_s3_1_1_model_1_1_get_bucket_acl_request>`, providing
it with the *bucket name*.

Results are returned in an :aws-cpp-class:`GetBucketAclResult
<aws_1_1_s3_1_1_model_1_1_get_bucket_acl_result>` that you can use to get the list of
:aws-cpp-class:`Grants <aws_1_1_s3_1_1_model_1_1_grant>` by calling its :functionname:`GetGrants`
function.

**Includes**

.. literalinclude:: example_code/s3/get_acl.cpp
   :lines: 14-16, 18-19

**Code**

.. literalinclude:: example_code/s3/get_acl.cpp
   :lines: 46-72
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/get_acl.cpp>`.


Set the Access Control List for a Bucket
========================================

To set the ACL for a bucket, call the |s3client|'s :functionname:`PutBucketAcl` function, passing it
a :aws-cpp-class:`PutBucketAclRequest <aws_1_1_s3_1_1_model_1_1_put_bucket_acl_request>` object with
the bucket name and list of grantees and permissions within an :aws-cpp-class:`AccessControlPolicy
<aws_1_1_s3_1_1_model_1_1_access_control_policy>` object.

**Includes**

.. literalinclude:: example_code/s3/set_acl.cpp
   :lines: 14-18, 21-22

**Code**

.. literalinclude:: example_code/s3/set_acl.cpp
   :lines: 44-66
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/set_acl.cpp>`.


Get the Access Control List for an Object
=========================================

To get the ACL for an |s3| object, call the |s3client|'s :functionname:`GetObjectAcl` function with
a :aws-cpp-class:`GetObjectAclRequest <aws_1_1_s3_1_1_model_1_1_get_object_acl_request>`, providing
it with the *bucket name* and *object key*.

Results are returned in an :aws-cpp-class:`GetObjectAclResult
<aws_1_1_s3_1_1_model_1_1_get_object_acl_result>` that you can use to get the list of
:aws-cpp-class:`Grants <aws_1_1_s3_1_1_model_1_1_grant>` by calling its :functionname:`GetGrants`
function.

**Includes**

.. literalinclude:: example_code/s3/get_acl.cpp
   :lines: 14-15, 17-19

**Code**

.. literalinclude:: example_code/s3/get_acl.cpp
   :lines: 81-108
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/get_acl.cpp>`.


Set the Access Control List for an Object
=========================================

To set the ACL for an object, call the |s3client|'s :functionname:`PutObjectAcl` function, passing it
a :aws-cpp-class:`PutObjectAclRequest <aws_1_1_s3_1_1_model_1_1_put_object_acl_request>` object with
the object name and list of grantees and permissions within an :aws-cpp-class:`AccessControlPolicy
<aws_1_1_s3_1_1_model_1_1_access_control_policy>` object.

**Includes**

.. literalinclude:: example_code/s3/set_acl.cpp
   :lines: 14-16, 19-22

**Code**

.. literalinclude:: example_code/s3/set_acl.cpp
   :lines: 44-66
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/set_acl.cpp>`.


More Information
================

* :s3-api:`GET Bucket acl <RESTBucketGETacl>` in the |s3-api|
* :s3-api:`PUT Bucket acl <RESTBucketPUTacl>` in the |s3-api|
* :s3-api:`GET Object acl <RESTObjectGETacl>` in the |s3-api|
* :s3-api:`PUT Object acl <RESTObjectPUTacl>` in the |s3-api|

