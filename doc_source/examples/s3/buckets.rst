######################################
Creating, Listing and Deleting Buckets
######################################

Every object (file) in |S3| must reside within a *bucket*, which represents a collection (container)
of objects. Each bucket is known by a *key* (name), which must be unique. For detailed information
about buckets and their configuration, see :s3-dg:`Working with Amazon S3 Buckets <UsingBucket>` in
the the |s3-dg|.

.. include:: ../examples-note.txt

.. contents::
    :local:

.. _create-bucket:

Create a bucket
===============

Use the |s3client| object's :methodname:`CreateBucket` method, passing it a
:classname:`CreateBucketRequest` with the bucket's name.

**Includes:**

.. literalinclude:: ../../example_code/s3/create_bucket.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: ../../example_code/s3/create_bucket.cpp
   :lines: 37-51
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/create_bucket.cpp>`.


.. _list-buckets:

List buckets
============

Use the |s3client| object's :methodname:`ListBucket` method. If successful, a
:classname:`ListBucketOutcome` object is returned, which contains a :classname:`ListBucketResult`
object.

Use the :classname:`ListBucketResult` object's :methodname:`GetBuckets` method to get a list of
:classname:`Bucket` objects that contain information about each |S3| bucket in your account.

**Includes:**

.. literalinclude:: ../../example_code/s3/list_buckets.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: ../../example_code/s3/list_buckets.cpp
   :lines: 26-43
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/list_buckets.cpp>`.


.. _delete-bucket:

Delete a bucket
===============

Use the |s3client| object's :methodname:`DeleteBucket` method, passing it a
:classname:`DeleteBucketRequest` object that is set with the name of the bucket to delete. *The
bucket must be empty, or an error will result*.

**Includes:**

.. literalinclude:: ../../example_code/s3/delete_bucket.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: ../../example_code/s3/delete_bucket.cpp
   :lines: 39-53
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/delete_bucket.cpp>`.
