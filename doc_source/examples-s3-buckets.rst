.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

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
    :description:
        Creating, listing, and deleting Amazon S3 buckets using the AWS SDK for C++.
    :keywords:

Every object (file) in |S3long| must reside within a *bucket*, which represents a collection
(container) of objects. Each bucket is known by a *key* (name), which must be unique. For detailed
information about buckets and their configuration, see :s3-dg:`Working with Amazon S3 Buckets
<UsingBucket>` in the |s3-dg|.

.. include:: common/s3-note-incomplete-upload-policy.txt

.. include:: includes/examples-note.txt

.. _create-bucket:

Create a Bucket
===============

Use the |s3client| object :functionname:`CreateBucket` method, passing it a
:classname:`CreateBucketRequest` with the bucket's name.

**Includes**

.. literalinclude:: example_code/s3/create_bucket.cpp
   :lines: 14-16

**Code**

.. literalinclude:: example_code/s3/create_bucket.cpp
   :lines: 42-58
   :dedent: 8

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

.. literalinclude:: example_code/s3/list_buckets.cpp
   :lines: 14-16

**Code**

.. literalinclude:: example_code/s3/list_buckets.cpp
   :lines: 26-46
   :dedent: 8

See the :sdk-examples-cpp:`complete example <s3/list_buckets.cpp>`.


.. _delete-bucket:

Delete a Bucket
===============

Use the |s3client| object :functionname:`DeleteBucket` method, passing it a
:classname:`DeleteBucketRequest` object that is set with the name of the bucket to delete. *The
bucket must be empty or an error will result*.

**Includes**

.. literalinclude:: example_code/s3/delete_bucket.cpp
   :lines: 14-16

**Code**

.. literalinclude:: example_code/s3/delete_bucket.cpp
   :lines: 49-67
   :dedent: 8

See the :sdk-examples-cpp:`complete example <s3/delete_bucket.cpp>`.

