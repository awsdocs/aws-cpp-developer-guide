.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

.. highlight:: cpp

###########################
Using Alarm Actions in |CW|
###########################

.. meta::
   :description: How to enable or disable Amazon CloudWatch alarm actions using the AWS SDK for C++.
   :keywords: cloudwatch

Using |cw| alarm actions, you can create alarms that perform actions such as automatically stopping,
terminating, rebooting, or recovering |ec2| instances.

Alarm actions can be added to an alarm by using the :aws-cpp-class:`PutMetricAlarmRequest
<aws_1_1_cloud_watch_1_1_model_1_1_put_metric_alarm_request>`'s :functionname:`SetAlarmActions`
function when :doc:`creating an alarm <examples-cloudwatch-create-alarms>`.

.. include:: includes/examples-note.txt

Enable Alarm Actions
====================

To enable alarm actions for a |cw| alarm, call the |cwclient|'s :functionname:`EnableAlarmActions`
with a :aws-cpp-class:`EnableAlarmActionsRequest
<aws_1_1_cloud_watch_1_1_model_1_1_enable_alarm_actions_request>` containing one or more names of
alarms whose actions you want to enable.

**Includes**

.. literalinclude:: cw.cpp.enable_alarm_actions.inc.txt

**Code**

.. literalinclude:: cw.cpp.enable_alarm_actions.code.txt
   :dedent: 4

See the :sdk-examples-cpp:`complete example <cloudwatch/enable_alarm_actions.cpp>`.

Disable Alarm Actions
=====================

To disable alarm actions for a |cw| alarm, call the |cwclient|'s :functionname:`DisableAlarmActions`
with a :aws-cpp-class:`DisableAlarmActionsRequest
<aws_1_1_cloud_watch_1_1_model_1_1_disable_alarm_actions_request>` containing one or more names of
alarms whose actions you want to disable.

**Includes**

.. literalinclude:: cw.cpp.disable_alarm_actions.inc.txt

**Code**

.. literalinclude:: cw.cpp.disable_alarm_actions.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <cloudwatch/disable_alarm_actions.cpp>`.

More Information
================

* :cw-ug:`Create Alarms to Stop, Terminate, Reboot, or Recover an Instance <UsingAlarmActions>` in
  the |cw-ug|
* :cw-api:`PutMetricAlarm` in the |cw-api|
* :cw-api:`EnableAlarmActions` in the |cw-api|
* :cw-api:`DisableAlarmActions` in the |cw-api|

