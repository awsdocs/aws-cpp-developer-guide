.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#######################################
Creating, Listing, and Deleting Buckets
#######################################

.. meta::
    :description: Managing Amazon S3 buckets using the AWS SDK for C++.
    :keywords: s3

Every *object* or file in |S3long| must reside within a *bucket* which represents a folder
of objects. Each bucket is known by a name that must be globally unique within the AWS
ecosystem. For detailed information about buckets and their configuration, 
see :s3-dg:`Working with Amazon S3 Buckets<UsingBucket>` in the |s3-dg|.

.. include:: common/s3-note-incomplete-upload-policy.txt

.. include:: includes/examples-note.txt

.. _create-bucket:

Create a Bucket
===============

Use the |s3client| object :functionname:`CreateBucket` method, passing it a
:classname:`CreateBucketRequest` with the bucket's name. By default, buckets are
created in the *us-east-1* (N. Virginia) region. The code example demonstrates
how to create a bucket in any specified region.

**Includes**

.. literalinclude:: s3.cpp.create_bucket.inc.txt

**Code**

.. literalinclude:: s3.cpp.create_bucket.code.txt

See the :sdk-examples-cpp:`complete example <s3/create_bucket.cpp>`.


.. _list-buckets:

List Buckets
============

Use the |s3client| object :functionname:`ListBucket` method. If successful, the method returns a
:classname:`ListBucketOutcome` object, which contains a :classname:`ListBucketResult`
object.

Use the :classname:`ListBucketResult` object :functionname:`GetBuckets` method to get a list of
:classname:`Bucket` objects that contain information about each |S3| bucket in your account.

**Includes**

.. literalinclude:: s3.cpp.list_buckets.inc.txt

**Code**

.. literalinclude:: s3.cpp.list_buckets.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <s3/list_buckets.cpp>`.


.. _delete-bucket:

Delete a Bucket
===============

Use the |s3client| object :functionname:`DeleteBucket` method, passing it a
:classname:`DeleteBucketRequest` object that is set with the name of the bucket to delete. *The
bucket must be empty or an error will result*.

**Includes**

.. literalinclude:: s3.cpp.delete_bucket.inc.txt

**Code**

.. literalinclude:: s3.cpp.delete_bucket.code.txt

See the :sdk-examples-cpp:`complete example <s3/delete_bucket.cpp>`.

