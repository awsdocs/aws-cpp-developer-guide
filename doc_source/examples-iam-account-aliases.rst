.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###########################
Using |IAM| Account Aliases
###########################

.. meta::
   :description: How to set, get, and delete a policy for an Amazon S3 bucket.
   :keywords: AWS for C++ SDK code examples, bucket policies

If you want the URL for your sign-in page to contain your company name or other friendly identifier
instead of your AWS account ID, you can create an alias for your AWS account.

.. note:: AWS supports exactly one account alias per account.

.. include:: includes/examples-note.txt

Creating an Account Alias
=========================

To create an account alias, call the |iamclient|'s :functionname:`CreateAccountAlias` function with a
:aws-cpp-class:`CreateAccountAliasRequest
<aws_1_1_i_a_m_1_1_model_1_1_create_account_alias_request>` object that contains the alias name.

**Includes:**

.. literalinclude:: example_code/iam/create_account_alias.cpp
   :lines: 14-17

**Code:**

.. literalinclude:: example_code/iam/create_account_alias.cpp
   :lines: 36-50
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/create_account_alias.cpp>`.


Listing Account Aliases
=======================

To list your account's alias, if any, call the |iamclient|'s :functionname:`ListAccountAliases`
function. It takes a :aws-cpp-class:`ListAccountAliasesRequest
<aws_1_1_i_a_m_1_1_model_1_1_list_account_aliases_request>` object.

.. note:: The returned :aws-cpp-class:`ListAccountAliasesResult
   <aws_1_1_i_a_m_1_1_model_1_1_list_account_aliases_result>` supports the same
   :functionname:`GetIsTruncated` and :functionname:`GetMarker` functions as other |sdk-cpp| *list*
   functions, but an AWS account can have only *one* account alias.

**Includes:**

.. literalinclude:: example_code/iam/list_account_aliases.cpp
   :lines: 14-19

**Code:**

.. literalinclude:: example_code/iam/list_account_aliases.cpp
   :lines: 29-69
   :dedent: 8

see the :sdk-examples-cpp:`complete example <iam/list_account_aliases.cpp>`.


Deleting an account alias
=========================

To delete your account's alias, call the |iamclient|'s :functionname:`DeleteAccountAlias` function.
When deleting an account alias, you must supply its name using a
:aws-cpp-class:`DeleteAccountAliasRequest
<aws_1_1_i_a_m_1_1_model_1_1_delete_account_alias_request>` object.

**Includes:**

.. literalinclude:: example_code/iam/delete_account_alias.cpp
   :lines: 14-17

**Code:**

.. literalinclude:: example_code/iam/delete_account_alias.cpp
   :lines: 36-51
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/delete_account_alias.cpp>`.


More Information
================

* :iam-ug:`Your AWS Account ID and Its Alias <console_account-alias>` in the |iam-ug|
* :iam-api:`CreateAccountAlias` in the |iam-api|
* :iam-api:`ListAccountAliases` in the |iam-api|
* :iam-api:`DeleteAccountAlias` in the |iam-api|

