.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

####################
Managing |IAM| Users
####################

.. meta::
   :description: Get information about, create, list, and delete users.

.. include:: includes/examples-note.txt

Create a User
=============

To create an :iam-ug:`IAM User <id_users>`, first check to see if the username exists by calling the
|iamclient|.

**Includes:**

.. literalinclude:: example_code/iam/create_user.cpp
   :lines: 14-20

**Code:**

.. literalinclude:: example_code/iam/create_user.cpp
   :lines: 39-56
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/create_user>`.

Listing Users
=============

**Includes:**

.. literalinclude:: example_code/iam/list_users.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: example_code/iam/list_users.cpp
   :lines: 39-56
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/list_users>`.


Get Information about a Particular User
=======================================

**Includes:**

.. literalinclude:: example_code/iam/list_users.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: example_code/iam/list_users.cpp
   :lines: 39-56
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/list_users>`.


Update a User
=============

**Includes:**

.. literalinclude:: example_code/iam/update_user.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: example_code/iam/update_user.cpp
   :lines: 39-56
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/update_user>`.


Delete a User
=============

**Includes:**

.. literalinclude:: example_code/iam/delete_user.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: example_code/iam/delete_user.cpp
   :lines: 39-56
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/delete_user>`.

