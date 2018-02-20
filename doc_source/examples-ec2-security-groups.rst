.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#####################################
Working with Security Groups in |EC2|
#####################################

.. meta::
   :description: How to create, configure and delete EC2 security groups with the AWS SDK for C++.
   :keywords: AWS SDK for C++, code examples, EC2 security groups, create a security group, ingress
              rules, egress rules, IP permissions, EC2 access

.. include:: includes/examples-note.txt

Creating a Security Group
=========================

To create a security group, call the |ec2client|'s :functionname:`CreateSecurityGroup` function with
a :aws-cpp-class:`CreateSecurityGroupRequest
<aws_1_1_e_c2_1_1_model_1_1_create_security_group_request>` that contains the key's name.

**Includes**

.. literalinclude:: example_code/ec2/create_security_group.cpp
   :lines: 14-17, 19

**Code**

.. literalinclude:: example_code/ec2/create_security_group.cpp
   :lines: 48-65
   :dedent: 4

See the :sdk-examples-cpp:`complete example <ec2/create_security_group.cpp>`.


Configuring a Security Group
============================

A security group can control both inbound (ingress) and outbound (egress) traffic to your |EC2|
instances.

To add ingress rules to your security group, use the |ec2client|'s
:functionname:`AuthorizeSecurityGroupIngress` function, providing the name of the security group and
the access rules (:aws-cpp-class:`IpPermission <aws_1_1_e_c2_1_1_model_1_1_ip_permission>`) you want
to assign to it within an :aws-cpp-class:`AuthorizeSecurityGroupIngressRequest
<aws_1_1_e_c2_1_1_model_1_1_authorize_security_group_ingress_request>` object. The following example
shows how to add IP permissions to a security group.

**Includes**

.. literalinclude:: example_code/ec2/create_security_group.cpp
   :lines: 14-19

**Code**

.. literalinclude:: example_code/ec2/create_security_group.cpp
   :lines: 48, 69-71, 24-41, 73-85
   :dedent: 4

To add an egress rule to the security group, provide similar data in an
:aws-cpp-class:`AuthorizeSecurityGroupEgressRequest
<aws_1_1_e_c2_1_1_model_1_1_authorize_security_group_egress_request>` to the |ec2client|'s
:functionname:`AuthorizeSecurityGroupEgress` function.

See the :sdk-examples-cpp:`complete example <ec2/create_security_group.cpp>`.


Describing Security Groups
==========================

To describe your security groups or get information about them, call the |ec2client|'s
:functionname:`DescribeSecurityGroups` function with a :aws-cpp-class:`DescribeSecurityGroupsRequest
<aws_1_1_e_c2_1_1_model_1_1_describe_security_groups_request>`.


You will receive a :aws-cpp-class:`DescribeSecurityGroupsResponse
<aws_1_1_e_c2_1_1_model_1_1_describe_security_groups_response>` in the outcome object that you can
use to access the list of security groups by calling its :functionname:`GetSecurityGroups` function,
which returns a list of :aws-cpp-class:`SecurityGroup <aws_1_1_e_c2_1_1_model_1_1_security_group>`
objects.

**Includes**

.. literalinclude:: example_code/ec2/describe_security_groups.cpp
   :lines: 14-19

**Code**

.. literalinclude:: example_code/ec2/describe_security_groups.cpp
   :lines: 36-71
   :dedent: 8

See the :sdk-examples-cpp:`complete example <ec2/describe_security_groups.cpp>`.


Deleting a Security Group
=========================

To delete a security group, call the |ec2client|'s :functionname:`DeleteSecurityGroup` function,
passing it a :aws-cpp-class:`DeleteSecurityGroupRequest
<aws_1_1_e_c2_1_1_model_1_1_delete_security_group_request>` that contains the ID of the security
group to delete.

**Includes**

.. literalinclude:: example_code/ec2/delete_security_group.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/ec2/delete_security_group.cpp
   :lines: 35-50
   :dedent: 8

See the :sdk-examples-cpp:`complete example <ec2/delete_security_group.cpp>`.


More Information
================

* :ec2-ug:`Amazon EC2 Security Groups <ec2-key-pairs>` in the |ec2-ug|
* :ec2-ug:`Authorizing Inbound Traffic for Your Linux Instances <authorizing-access-to-an-instance>` in the |ec2-ug|
* :ec2-api:`CreateSecurityGroup` in the |ec2-api|
* :ec2-api:`DescribeSecurityGroups` in the |ec2-api|
* :ec2-api:`DeleteSecurityGroup` in the |ec2-api|
* :ec2-api:`AuthorizeSecurityGroupIngress` in the |ec2-api|

