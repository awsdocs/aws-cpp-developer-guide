.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.


################################
Managing |S3| Access Permissions
################################

.. meta::
   :description: How to manage access control lists for an Amazon S3 bucket or object.
   :keywords: s3

Access permissions for an |s3| bucket or object are defined in an access 
control list (ACL). The ACL specifies the owner of the bucket/object and a 
list of grants. Each grant specifies a user (or grantee) and the user's 
permissions to access the bucket/object, such as READ or WRITE access.


Manage an Object's Access Control List
======================================

The access control list for an object can be retrieved by calling the 
``S3Client`` method :functionname:`GetObjectAcl`. The method accepts the 
names of the object and its bucket. The return value includes the ACL's 
``Owner`` and list of ``Grants``.

.. literalinclude:: s3.cpp.get_put_object_acl.inc.txt

.. literalinclude:: s3.cpp.get_object_acl.code.txt
   :dedent: 4

The ACL can be modified by either creating a new ACL or changing the grants 
specified in the current ACL. The updated ACL becomes the new current ACL by 
passing it to the :functionname:`PutObjectAcl` method.

The following code uses the ACL retrieved by :functionname:`GetObjectAcl` 
and adds a new grant to it. The user or grantee is given READ permission for 
the object. The modified ACL is passed to :functionname:`PutObjectAcl`, making 
it the new current ACL. For further details, see 
:sdk-examples-cpp:`the example source file <s3/get_put_object_acl.cpp>`.

.. literalinclude:: s3.cpp.put_object_acl.code.txt
   :dedent: 4


Manage a Bucket's Access Control List
=====================================

In most cases, the preferred method for setting the access permissions of a 
bucket is to define a bucket policy. However, buckets also support access 
control lists for users who wish to use them.

Management of an access control list for a bucket is identical to that 
used for an object. The :functionname:`GetBucketAcl` method retrieves a 
bucket's current ACL and :functionname:`PutBucketAcl` applies a new ACL to 
the bucket.

The following code demonstrates getting and setting a bucket ACL. For details, 
see :sdk-examples-cpp:`the example source file <s3/get_put_bucket_acl.cpp>`.

.. literalinclude:: s3.cpp.get_put_bucket_acl.inc.txt

.. literalinclude:: s3.cpp.get_put_bucket_acl.code.txt
   :dedent: 4
