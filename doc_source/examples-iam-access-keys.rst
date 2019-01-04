.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

##########################
Managing |IAM| Access Keys
##########################

.. meta::
   :description: How to manage IAM access keys with the AWS SDK for C++.
   :keywords: iam

.. include:: includes/examples-note.txt


Create an Access Key
====================

To create an |IAM| access key, call the |iamclient|'s :functionname:`CreateAccessKey` function with
an :aws-cpp-class:`CreateAccessKeyRequest <aws_1_1_i_a_m_1_1_model_1_1_create_access_key_request>`
object.

You must set the user name using the :classname:`CreateAccessKeyRequest`'s
:functionname:`WithUserName` setter function before passing it to the
:functionname:`CreateAccessKey` function.

**Includes:**

.. literalinclude:: iam.cpp.create_access_key.inc.txt

**Code:**

.. literalinclude:: iam.cpp.create_access_key.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/create_access_key.cpp>`.


List Access Keys
================

To list the access keys for a given user, create a :aws-cpp-class:`ListAccessKeysRequest
<aws_1_1_i_a_m_1_1_model_1_1_list_access_keys_request>` object that contains the user name to list
keys for, and pass it to the |iamclient|'s :functionname:`ListAccessKeys` function.

.. note:: If you do not supply a user name to :functionname:`ListAccessKeys`, it will attempt to list
   access keys associated with the AWS account that signed the request.

**Includes:**

.. literalinclude:: iam.cpp.list_access_keys.inc.txt

**Code:**

.. literalinclude:: iam.cpp.list_access_keys.code.txt
   :dedent: 8

The results of :functionname:`ListAccessKeys` are paged (with a default maximum of 100 records per
call). You can call :functionname:`GetIsTruncated` on the returned
:aws-cpp-class:`ListAccessKeysResult <aws_1_1_i_a_m_1_1_model_1_1_list_access_keys_result>` object
to see if the query returned fewer results then are available. If so, then call
:functionname:`SetMarker` on the :classname:`ListAccessKeysRequest` and pass it back to the next
invocation of :functionname:`ListAccessKeys`.

See the :sdk-examples-cpp:`complete example <iam/list_access_keys.cpp>`.


Retrieve an Access Key's Last Used Time
=======================================

To get the time an access key was last used, call the |iamclient|'s
:functionname:`GetAccessKeyLastUsed` function with the access key's ID (which can be passed in using
a :aws-cpp-class:`GetAccessKeyLastUsedRequest
<aws_1_1_i_a_m_1_1_model_1_1_get_access_key_last_used_request>` object, or directly to the overload
that takes the access key ID directly.

You can then use the returned :aws-cpp-class:`GetAccessKeyLastUsedResult
<aws_1_1_i_a_m_1_1_model_1_1_get_access_key_last_used_result>` object to retrieve the key's last
used time.

**Includes:**

.. literalinclude:: iam.cpp.access_key_last_used.inc.txt

**Code:**

.. literalinclude:: iam.cpp.access_key_last_used.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/access_key_last_used.cpp>`.


.. _iam-access-keys-update:

Activate or Deactivate Access Keys
==================================

You can activate or deactivate an access key by creating an :aws-cpp-class:`UpdateAccessKeyRequest
<aws_1_1_i_a_m_1_1_model_1_1_update_access_key_request>` object, providing the access key ID,
optionally the user name, and the desired :classname:`Status Type`, then passing the request object
to the |iamclient|'s :functionname:`UpdateAccessKey` function.

**Includes:**

.. literalinclude:: iam.cpp.update_access_key.inc.txt

**Code:**

.. literalinclude:: iam.cpp.update_access_key.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/update_access_key.cpp>`.


Delete an Access Key
====================

To permanently delete an access key, call the |iamclient|'s :functionname:`DeleteKey` function,
providing it with a :aws-cpp-class:`DeleteAccessKeyRequest
<aws_1_1_i_a_m_1_1_model_1_1_delete_access_key_request>` containing the access key's ID and
username.

.. note:: Once deleted, a key can no longer be retrieved or used. To temporarily deactivate a key so
   that it can be activated again later, use :ref:`updateAccessKey <iam-access-keys-update>` function
   instead.

**Includes:**

.. literalinclude:: iam.cpp.delete_access_key.inc.txt

**Code:**

.. literalinclude:: iam.cpp.delete_access_key.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/delete_access_key.cpp>`.


More Information
================

* :iam-api:`CreateAccessKey` in the |iam-api|
* :iam-api:`ListAccessKeys` in the |iam-api|
* :iam-api:`GetAccessKeyLastUsed` in the |iam-api|
* :iam-api:`UpdateAccessKey` in the |iam-api|
* :iam-api:`DeleteAccessKey` in the |iam-api|

