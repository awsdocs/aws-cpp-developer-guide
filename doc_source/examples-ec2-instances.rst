.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

########################
Managing |EC2| Instances
########################

.. meta::
   :description: How to create, start, stop, reboot, list and monitor EC2 instances using the AWS
                 SDK for C++.
   :keywords: AWS SDK for C++, code examples, EC2 instances, create instance, start instance, stop
              instance, reboot instance, monitor instance, list instances, describe instances

.. include:: includes/examples-note.txt

Creating an Instance
====================

Create a new |EC2| instance by calling the |ec2client|'s :functionname:`RunInstances` function,
providing it with a :aws-cpp-class:`RunInstancesRequest
<aws_1_1_e_c2_1_1_model_1_1_run_instances_request>` containing the :ec2-ug:`Amazon Machine Image
(AMI) <AMIs>` to use and an :ec2-ug:`instance type <instance-types>`.

**Includes**

.. literalinclude:: example_code/ec2/create_instance.cpp
   :lines: 14-19

**Code**

.. literalinclude:: example_code/ec2/create_instance.cpp
   :lines: 23-37
   :dedent: 4

See the :sdk-examples-cpp:`complete example <ec2/create_instance.cpp>`.


Starting an Instance
====================

To start an |EC2| instance, call the |ec2client|'s :functionname:`StartInstances` function, providing
it with a :aws-cpp-class:`StartInstancesRequest
<aws_1_1_e_c2_1_1_model_1_1_start_instances_request>` containing the ID of the instance to start.

**Includes**

.. literalinclude:: example_code/ec2/start_stop_instance.cpp
   :lines: 14-17, 20

**Code**

.. literalinclude:: example_code/ec2/start_stop_instance.cpp
   :lines: 24-48
   :dedent: 4

See the :sdk-examples-cpp:`complete example <ec2/start_stop_instance.cpp>`.


Stopping an Instance
====================

To stop an |EC2| instance, call the |ec2client|'s :functionname:`StopInstances` function, providing it
with a :aws-cpp-class:`StopInstancesRequest <aws_1_1_e_c2_1_1_model_1_1_stop_instances_request>`
containing the ID of the instance to stop.

**Includes**

.. literalinclude:: example_code/ec2/start_stop_instance.cpp
   :lines: 14-15, 18-20

**Code**

.. literalinclude:: example_code/ec2/start_stop_instance.cpp
   :lines: 53-76
   :dedent: 4

See the :sdk-examples-cpp:`complete example <ec2/start_stop_instance.cpp>`.


Rebooting an Instance
=====================

To reboot an |EC2| instance, call the |ec2client|'s :functionname:`RebootInstances` function,
providing it with a :aws-cpp-class:`RebootInstancesRequest
<aws_1_1_e_c2_1_1_model_1_1_reboot_instances_request>` containing the ID of the instance to reboot.

**Includes**

.. literalinclude:: example_code/ec2/reboot_instance.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/ec2/reboot_instance.cpp
   :lines: 21-45
   :dedent: 4

See the :sdk-examples-cpp:`complete example <ec2/reboot_instance.cpp>`.


Describing Instances
====================

To list your instances, create a :aws-cpp-class:`DescribeInstancesRequest
<aws_1_1_e_c2_1_1_model_1_1_describe_instances_request>` and call the |ec2client|'s
:functionname:`DescribeInstances` function. It will return a :aws-cpp-class:`DescribeInstancesResponse
<aws_1_1_e_c2_1_1_model_1_1_describe_instances_response>` object that you can use to list the |EC2|
instances for your account and region.

Instances are grouped by *reservation*. Each reservation corresponds to the call to
:functionname:`StartInstances` that launched the instance. To list your instances, you must first
call the :classname:`DescribeInstancesResponse` class' :functionname:`GetReservations` function, and
then call :functionname:`getInstances` on each returned Reservation object.

**Includes**

.. literalinclude:: example_code/ec2/describe_instances.cpp
   :lines: 14-18

**Code**

.. literalinclude:: example_code/ec2/describe_instances.cpp
   :lines: 29-93
   :dedent: 8

Results are paged; you can get further results by passing the value returned from the result
object's :functionname:`GetNextToken` function to your original request object's
:functionname:`SetNextToken` function, then using the same request object in your next call to
:functionname:`DescribeInstances`.

See the :sdk-examples-cpp:`complete example <ec2/describe_instances.cpp>`.


Enable Instance Monitoring
==========================

You can monitor various aspects of your |EC2| instances, such as CPU and network utilization,
available memory, and disk space remaining. To learn more about instance monitoring, see
:ec2-ug:`Monitoring Amazon EC2 <monitoring_ec2>` in the |ec2-ug|.

To start monitoring an instance, you must create a :aws-cpp-class:`MonitorInstancesRequest
<aws_1_1_e_c2_1_1_model_1_1_monitor_instances_request>` with the ID of the instance to monitor, and
pass it to the |ec2client|'s :functionname:`MonitorInstances` function.

**Includes**

.. literalinclude:: example_code/ec2/monitor_instance.cpp
   :lines: 14-17, 20

**Code**

.. literalinclude:: example_code/ec2/monitor_instance.cpp
   :lines: 24-48
   :dedent: 4

See the :sdk-examples-cpp:`complete example <ec2/monitor_instance.cpp>`.


Disable Instance Monitoring
===========================

To stop monitoring an instance, create an :aws-cpp-class:`UnmonitorInstancesRequest
<aws_1_1_e_c2_1_1_model_1_1_unmonitor_instances_request>` with the ID of the instance to stop
monitoring, and pass it to the |ec2client|'s :functionname:`UnmonitorInstances` function.

**Includes**

.. literalinclude:: example_code/ec2/monitor_instance.cpp
   :lines: 14-15, 18-20

**Code**

.. literalinclude:: example_code/ec2/monitor_instance.cpp
   :lines: 53-77
   :dedent: 4

See the :sdk-examples-cpp:`complete example <ec2/monitor_instance.cpp>`.


More Information
================

* :ec2-api:`RunInstances` in the |ec2-api|
* :ec2-api:`DescribeInstances` in the |ec2-api|
* :ec2-api:`StartInstances` in the |ec2-api|
* :ec2-api:`StopInstances` in the |ec2-api|
* :ec2-api:`RebootInstances` in the |ec2-api|
* :ec2-api:`DescribeInstances` in the |ec2-api|
* :ec2-api:`MonitorInstances` in the |ec2-api|
* :ec2-api:`UnmonitorInstances` in the |ec2-api|

