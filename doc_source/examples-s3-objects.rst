.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#####################
Operations on Objects
#####################

An |S3| object represents a *file*, which is a collection of data. Every object must reside within a
:doc:`bucket <examples-s3-buckets>`.

.. include:: includes/examples-note.txt

.. contents::
    :local:

.. _upload-object:

Upload an Object
================

Use the |s3client| object :methodname:`PutObject` method, supplying it with a bucket name, key
name, and file to upload. *The bucket must exist or an error will result*.

**Includes**

.. literalinclude:: example_code/s3/put_object.cpp
   :lines: 14-18

**Code**

.. literalinclude:: example_code/s3/put_object.cpp
   :lines: 43-65
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/put_object.cpp>`.

.. _list-objects:

List Objects
============

To get a list of objects within a bucket, use the |s3client| object :methodname:`ListObjects`
method. Supply it with a :classname:`ListObjectsRequest` that you set with the name of a bucket
to list the contents of.

The :methodname:`ListObjects` method returns a :classname:`ListObjectsOutcome` object that you can
use to get a list of objects in the form of :classname:`Object` instances.

**Includes**

.. literalinclude:: example_code/s3/list_objects.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/s3/list_objects.cpp
   :lines: 38-60
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/list_objects.cpp>`.


.. _download-object:

Download an Object
==================

Use the |s3client| object :methodname:`GetObject` method, passing it a
:classname:`GetObjectRequest` that you set with the name of a bucket and the object key to download.
:methodname:`GetObject` returns a :classname:`GetObjectOutcome` object that you can use to
access
the S3 object's data.

The following example downloads an object from |S3| and saves its contents to a file (using the same
name as the object's key).

**Includes**

.. literalinclude:: example_code/s3/get_object.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/s3/get_object.cpp
   :lines: 41-61
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/get_object.cpp>`.


.. _delete-object:

Delete an Object
================

Use the |s3client| object's :methodname:`DeleteObject` method, passing it a
:classname:`DeleteObjectRequest` that you set with the name of a bucket and object to download.
*The specified bucket and object key must exist or an error will result*.

**Includes**

.. literalinclude:: example_code/s3/delete_object.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/s3/delete_object.cpp
   :lines: 43-60
   :dedent: 4

See the :sdk-examples-cpp:`complete example <s3/delete_object.cpp>`.

