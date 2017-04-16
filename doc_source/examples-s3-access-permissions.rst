.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#######################################
Managing |S3| Bucket Access Permissions
#######################################

.. meta::
   :description: How to retrieve or set the access control list for an Amazon S3 bucket.
   :keywords: AWS for C++ SDK code examples, bucket access permissions

You can get or set the access control list for an Amazon S3 bucket.

.. include:: includes/examples-note.txt

Get the Current Bucket Access Control List
==========================================

**Includes**

.. literalinclude:: example_code/s3/get_acl.cpp
   :lines: 14-19

**Code**

.. literalinclude:: example_code/s3/get_acl.cpp
   :lines: 21-65

See the :sdk-examples-cpp:`complete example <s3/get_acl.cpp>`.

Set a Bucket Access Control List
================================

**Includes**

.. literalinclude:: example_code/s3/set_acl.cpp
   :lines: 14-22

**Code**

.. literalinclude:: example_code/s3/set_acl.cpp
   :lines: 24-64

See the :sdk-examples-cpp:`complete example <s3/set_acl.cpp>`.
