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

Use the |iamclient| :functionname:`CreateUser` function, passing it a
:aws-cpp-class:`CreateUserRequest <aws_1_1_i_a_m_1_1_model_1_1_create_user_request>` with the name
of the user to create.

**Includes:**

.. literalinclude:: example_code/iam/create_user.cpp
   :lines: 14-17

**Code:**

.. literalinclude:: example_code/iam/create_user.cpp
   :lines: 24, 39-47
   :dedent: 4

This call will fail if the user already exists. You can avoid this by first verifying if the user
exists or not by calling the |iamclient| :functionname:`GetUser` function. The function will fail
with :code-cpp:`Aws::IAM::IAMErrors::NO_SUCH_ENTITY` if the user doesn't already exist.

**Includes:**

.. literalinclude:: example_code/iam/create_user.cpp
   :lines: 14-15, 18-19

**Code:**

.. literalinclude:: example_code/iam/create_user.cpp
   :lines: 24-37
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/create_user>`.

Listing Users
=============

List the existing |IAM| users for your account by calling the |iamclient| :functionname:`ListUsers`
function, passing it a :aws-cpp-class:`ListUsersRequest
<aws_1_1_i_a_m_1_1_model_1_1_list_users_request>` object. The list of users is returned in a
:aws-cpp-class:`ListUsersResult <aws_1_1_i_a_m_1_1_model_1_1_list_users_result>` object that you can
use to get information about the users.

The result may be paginated; to check to see if there are more results available, check the value of
:code-cpp:`GetResult().GetIsTruncated()`. If :code-cpp:`true`, then set a marker on the request and
call :functionname:`ListUsers` again to get the next batch of users. This code demonstrates the
technique.

**Includes:**

.. literalinclude:: example_code/iam/list_users.cpp
   :lines: 14-17

**Code:**

.. literalinclude:: example_code/iam/list_users.cpp
   :lines: 31-65
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/list_users>`.


Update a User
=============

To update an existing user, create an :aws-cpp-class:`UpdateUserRequest
<aws_1_1_i_a_m_1_1_model_1_1_update_user_request>` and pass it to the |iamclient|
:functionname:`UpdateUser` member function.

**Includes:**

.. literalinclude:: example_code/iam/update_user.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: example_code/iam/update_user.cpp
   :lines: 37-51
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/update_user>`.


Delete a User
=============

To delete an existing user, call the |iamclient| :functionname:`DeleteUser` function, passing it a
:aws-cpp-class:`DeleteUserRequest <aws_1_1_i_a_m_1_1_model_1_1_delete_user_request>` object
containing the name of the user to delete.

**Includes:**

.. literalinclude:: example_code/iam/delete_user.cpp
   :lines: 14-16

**Code:**

.. literalinclude:: example_code/iam/delete_user.cpp
   :lines: 23, 40-49
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/delete_user>`.

