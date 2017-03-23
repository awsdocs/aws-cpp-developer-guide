.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###########################
Working with |IAM| Policies
###########################

.. meta::
   :description: How to set, get, and delete a policy for an Amazon S3 bucket.
   :keywords: AWS for C++ SDK code examples, bucket policies

.. include:: includes/examples-note.txt

Creating a Policy
=================

To create a new policy, provide the policy's name and a JSON-formatted policy document in a
:aws-cpp-class:`CreatePolicyRequest <aws_1_1_i_a_m_1_1_model_1_1_create_policy_request>` to the
|iamclient|'s :functionname:`CreatePolicy` function.

**Includes:**

.. literalinclude:: example_code/iam/create_policy.cpp
   :lines: 14-18

**Code:**

.. literalinclude:: example_code/iam/create_policy.cpp
   :lines: 71-84
   :dedent: 8

|iam| policy documents are JSON strings with a :iam-ug:`well-documented syntax
<reference_policies_grammar>`. Here is an example that provides access to make particular requests
to |ddb|. It takes the policy ARN as a passed-in variable.

.. literalinclude:: example_code/iam/create_policy.cpp
   :lines: 20-52

See the :sdk-examples-cpp:`complete example <iam/create_policy.cpp>`.


Getting a Policy
================

To retrieve an existing policy, call the |iamclient|'s :functionname:`GetPolicy` function, providing the
policy's ARN within a :aws-cpp-class:`GetPolicyRequest
<aws_1_1_i_a_m_1_1_model_1_1_get_policy_request>` object.

**Includes:**

.. literalinclude:: example_code/iam/get_policy.cpp
   :lines: 14-18

**Code:**

.. literalinclude:: example_code/iam/get_policy.cpp
   :lines: 35-51
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/get_policy.cpp>`.

Deleting a Policy
=================

To delete a policy, provide the policy's ARN in a :aws-cpp-class:`DeletePolicyRequest
<aws_1_1_i_a_m_1_1_model_1_1_delete_policy_request>` to the |iamclient|'s :functionname:`DeletePolicy`
function.

**Includes:**

.. literalinclude:: example_code/iam/delete_policy.cpp
   :lines: 14-17

**Code:**

.. literalinclude:: example_code/iam/delete_policy.cpp
   :lines: 37-48
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/delete_policy.cpp>`.


Attaching a Policy
==================

You can attach a policy to an |IAM| :iam-ug:`role <id_roles>` by calling the |iamclient|'s
:functionname:`AttachRolePolicy` function, providing it with the role name and policy ARN in an
:aws-cpp-class:`AttachRolePolicyRequest <aws_1_1_i_a_m_1_1_model_1_1_attach_role_policy_request>`.

**Includes:**

.. literalinclude:: example_code/iam/attach_role_policy.cpp
   :lines: 14-19

**Code:**

.. literalinclude:: example_code/iam/attach_role_policy.cpp
   :lines: 24-65
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/attach_role_policy.cpp>`.


Listing Attached Policies
=========================

List attached policies on a role by calling the |iamclient|'s :functionname:`ListAttachedRolePolicies`
function. It takes a :aws-cpp-class:`ListAttachedRolePoliciesRequest
<aws_1_1_i_a_m_1_1_model_1_1_list_attached_role_policies_request>` object that contains the role
name to list the policies for.

Call :functionname:`GetAttachedPolicies` on the returned
:aws-cpp-class:`ListAttachedRolePoliciesResult
<aws_1_1_i_a_m_1_1_model_1_1_list_attached_role_policies_result>` object to get the list of attached
policies. Results may be truncated; if the :classname:`ListAttachedRolePoliciesResult` object's
:functionname:`GetIsTruncated` function returns :code-cpp:`true`, call the
:classname:`ListAttachedRolePoliciesRequest` object's :functionname:`SetMarker` function and use it
to call :functionname:`ListAttachedRolePolicies` again to get the next batch of results.

**Includes:**

.. literalinclude:: example_code/iam/list_policies.cpp
   :lines: 14-18

**Code:**

.. literalinclude:: example_code/iam/list_policies.cpp
   :lines: 31-66
   :dedent: 8

See the :sdk-examples-cpp:`complete example <iam/list_policies.cpp>`.


Detaching a Policy
==================

To detach a policy from a role, call the |iamclient|'s :functionname:`DetachRolePolicy` function,
providing it with the role name and policy ARN in a :aws-cpp-class:`DetachRolePolicyRequest
<aws_1_1_i_a_m_1_1_model_1_1_detach_role_policy_request>`.

**Includes:**

.. literalinclude:: example_code/iam/detach_role_policy.cpp
   :lines: 14-19

**Code:**

.. literalinclude:: example_code/iam/detach_role_policy.cpp
   :lines: 23, 58-71
   :dedent: 4

See the :sdk-examples-cpp:`complete example <iam/detach_role_policy.cpp>`.


More Information
================

* :iam-ug:`Overview of IAM Policies <access_policies>` in the |iam-ug|.
* :iam-ug:`AWS IAM Policy Reference <reference_policies>` in the |iam-ug|.
* :iam-api:`CreatePolicy` in the |iam-api|
* :iam-api:`GetPolicy` in the |iam-api|
* :iam-api:`DeletePolicy` in the |iam-api|
* :iam-api:`AttachGroupPolicy`, :iam-api:`AttachRolePolicy` and :iam-api:`AttachUserPolicy` in the
  |iam-api|
* :iam-api:`DetachGroupPolicy`, :iam-api:`DetachRolePolicy` and :iam-api:`DetachUserPolicy` in the
  |iam-api|
* :iam-api:`ListAttachedGroupPolicies`, :iam-api:`ListAttachedRolePolicies` and
  :iam-api:`ListAttachedUserPolicies` in the |iam-api|

