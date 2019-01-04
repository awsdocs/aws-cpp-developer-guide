.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###################################
Using Elastic IP Addresses in |EC2|
###################################

.. meta::
   :description: How to manage Elastic IP addresses for EC2 instances with the AWS SDK for C++.
   :keywords: ec2

.. include:: includes/examples-note.txt

Allocate an Elastic IP Address
==============================

To use an Elastic IP address, you first allocate one to your account, and then associate it with
your instance or a network interface.

To allocate an Elastic IP address, call the |ec2client|'s :functionname:`AllocateAddress` function
with an :aws-cpp-class:`AllocateAddressRequest
<aws_1_1_e_c2_1_1_model_1_1_allocate_address_request>` object containing the network type (classic
EC2 or VPC).

The :aws-cpp-class:`AllocateAddressResponse <aws_1_1_e_c2_1_1_model_1_1_allocate_address_response>`
class in the response object contains an allocation ID that you can use to associate the address
with an instance, by passing the allocation ID and instance ID in a
:aws-cpp-class:`AssociateAddressRequest <aws_1_1_e_c2_1_1_model_1_1_associate_address_request>` to
the |ec2client|'s :functionname:`AssociateAddress` function.

**Includes**

.. literalinclude:: ec2.cpp.allocate_address.inc.txt

**Code**

.. literalinclude:: ec2.cpp.allocate_address.code.txt
   :dedent: 4

See the :sdk-examples-cpp:`complete example <ec2/allocate_address.cpp>`.


Describe Elastic IP Addresses
=============================

To list the Elastic IP addresses assigned to your account, call the |ec2client|'s
:functionname:`DescribeAddresses` function. It returns an outcome object that contains a
:aws-cpp-class:`DescribeAddressesResponse <aws_1_1_e_c2_1_1_model_1_1_describe_addresses_response>`
which you can use to get a list of :aws-cpp-class:`Address <aws_1_1_e_c2_1_1_model_1_1_address>`
objects that represent the Elastic IP addresses on your account.

**Includes**

.. literalinclude:: ec2.cpp.describe_addresses.inc.txt

**Code**

.. literalinclude:: ec2.cpp.describe_addresses.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <ec2/describe_addresses.cpp>`.


Release an Elastic IP Address
=============================

To release an Elastic IP address, call the |ec2client|'s :functionname:`ReleaseAddress` function,
passing it a :aws-cpp-class:`ReleaseAddressRequest
<aws_1_1_e_c2_1_1_model_1_1_release_address_request>` containing the allocation ID of the Elastic IP
address you want to release.

**Includes**

.. literalinclude:: ec2.cpp.release_address.inc.txt

**Code**

.. literalinclude:: ec2.cpp.release_address.code.txt
   :dedent: 8

After you release an Elastic IP address, it is released to the AWS IP address pool and might be
unavailable to you afterward. Be sure to update your DNS records and any servers or devices that
communicate with the address. If you attempt to release an Elastic IP address that you already
released, you'll get an *AuthFailure* error if the address is already allocated to another AWS
account.

If you are using *EC2-Classic* or a *default VPC*, then releasing an Elastic IP address
automatically disassociates it from any instance that it's associated with. To disassociate an
Elastic IP address without releasing it, use the |ec2client|'s :functionname:`DisassociateAddress`
function.

If you are using a non-default VPC, you *must* use :functionname:`DisassociateAddress` to
disassociate the Elastic IP address before you try to release it. Otherwise, |EC2| returns an error
(*InvalidIPAddress.InUse*).

See the :sdk-examples-cpp:`complete example <ec2/release_address.cpp>`.


More Information
================

* :ec2-ug:`Elastic IP Addresses <elastic-ip-addresses-eip>` in the |ec2-ug|
* :ec2-api:`AllocateAddress` in the |ec2-api|
* :ec2-api:`DescribeAddresses` in the |ec2-api|
* :ec2-api:`ReleaseAddress` in the |ec2-api|

