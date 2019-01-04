.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

##############################################
Using Regions and Availability Zones for |EC2|
##############################################

.. meta::
   :description: How to list EC2 regions and availability zones using the AWS SDK for C++.
   :keywords: ec2

.. include:: includes/examples-note.txt

Describe Regions
================

To list the regions available to your account, call the |ec2client|'s
:functionname:`DescribeRegions` function with a :aws-cpp-class:`DescribeRegionsRequest
<aws_1_1_e_c2_1_1_model_1_1_describe_regions_request>`.

You will receieve a :aws-cpp-class:`DescribeRegionsResponse
<aws_1_1_e_c2_1_1_model_1_1_describe_regions_response>` in the outcome object. Call its
:functionname:`GetRegions` function to get a list of :aws-cpp-class:`Region
<aws_1_1_e_c2_1_1_model_1_1_region>` objects that represent each region.

**Includes**

.. literalinclude:: ec2.cpp.describe_regions.inc.txt

**Code**

.. literalinclude:: ec2.cpp.describe_regions.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <ec2/describe_regions_and_zones.cpp>`.


Describe Availability Zones
===========================

To list each availability zone available to your account, call the |ec2client|'s
:functionname:`DescribeAvailabilityZones` function with a
:aws-cpp-class:`DescribeAvailabilityZonesRequest
<aws_1_1_e_c2_1_1_model_1_1_describe_availability_zones_request>`.

You will receive a :aws-cpp-class:`DescribeAvailabilityZonesResponse
<aws_1_1_e_c2_1_1_model_1_1_describe_availability_zones_response>` in the outcome object. Call its
:functionname:`GetAvailabilityZones` function to get a list of :aws-cpp-class:`AvailabilityZone
<aws_1_1_e_c2_1_1_model_1_1_availability_zone>` objects that represent each availability zone.

**Includes**

.. literalinclude:: ec2.cpp.describe_zones.inc.txt

**Code**

.. literalinclude:: ec2.cpp.describe_zones.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <ec2/describe_regions_and_zones.cpp>`.


More Information
================

* :ec2-ug:`Regions and Availability Zones <using-regions-availability-zones>` in the |ec2-ug|
* :ec2-api:`DescribeRegions` in the |ec2-api|
* :ec2-api:`DescribeAvailabilityZones` in the |ec2-api|

