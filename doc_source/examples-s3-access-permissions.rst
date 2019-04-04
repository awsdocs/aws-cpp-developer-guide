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

Fine-grained access permissions for an |s3| bucket or object are defined in 
an access control list (ACL).


Get and Set an Object's Access Control List
===========================================

The access control list for an object can be retrieved by calling the AWS SDK 
for C++ ``S3Client`` method :functionname:`GetObjectAcl`. The method accepts 
the names of a bucket and object.

.. literalinclude:: s3.cpp.get_put_object_acl.inc.txt

.. literalinclude:: s3.cpp.get_object_acl.code.txt
   :dedent: 4

The returned result includes the ``Owner`` and ``Grants`` fields of the ACL. 
The ACL can be modified by creating a new ACL or changing the grants or 
permissions of the current ACL. The updated ACL is passed to the 
:functionname:`PutObjectAcl` method.

The following code adds a new grant to the current ACL. The grantee is 
assigned READ permission for the object.

.. literalinclude:: s3.cpp.put_object_acl.code.txt
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/get_put_object_acl.cpp>`.


Get and Set a Bucket's Access Control List
==========================================

In most cases, defining a bucket policy is the preferred method for setting 
a bucket's access permissions. However, buckets also support access control 
lists for users who wish to use them.

The access control list for a bucket can be retrieved by calling the AWS SDK 
for C++ ``S3Client`` method :functionname:`GetBucketAcl`. The method accepts 
a bucket name.

.. literalinclude:: s3.cpp.get_put_bucket_acl.inc.txt

.. literalinclude:: s3.cpp.get_bucket_acl.code.txt
   :dedent: 4

The returned result includes the ``Owner`` and ``Grants`` fields of the ACL. 
The ACL can be modified by creating a new ACL or changing the grants or 
permissions of the current ACL. The updated ACL is passed to the 
:functionname:`PutBucketAcl` method.

The following code adds a new grant to the current ACL. The grantee is 
assigned READ permission for the bucket.

.. literalinclude:: s3.cpp.put_bucket_acl.code.txt
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/get_put_bucket_acl.cpp>`.
