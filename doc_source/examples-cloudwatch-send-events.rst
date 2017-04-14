.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

######################
Sending Events to |CW|
######################

.. meta::
   :description: How to add custom events, add rules and add targets to rules for Amazon Cloudwatch
                 using the AWS SDK for C++.
   :keywords: cloudwatch events, add events, add rules, add targets, code examples

.. include:: common/desc-cloudwatch-events.txt

.. include:: includes/examples-note.txt

Add Events
==========

To add custom |cw| events, call the |cweclient|'s :functionname:`PutEvents` function with a
:aws-cpp-class:`PutEventsRequest <aws_1_1_cloud_watch_events_1_1_model_1_1_put_events_request>`
object that contains one or more :aws-cpp-class:`PutEventsRequestEntry
<aws_1_1_cloud_watch_events_1_1_model_1_1_put_events_request_entry>` objects that provide details
about each event. You can specify several parameters for the entry such as the source and type of
the event, resources associated with the event, and so on.

.. note:: You can specify a maximum of 10 events per call to :functionname:`putEvents`.

**Includes**

.. literalinclude:: example_code/cloudwatch/put_events.cpp
   :lines: 15-19

**Code**

.. literalinclude:: example_code/cloudwatch/put_events.cpp
   :lines: 50-67
   :dedent: 8


Add Rules
=========

To create or update a rule, call the |cweclient|'s :functionname:`PutRule` function with a
:aws-cpp-class:`PutRuleRequest <aws_1_1_cloud_watch_events_1_1_model_1_1_put_rule_request>` with the
name of the rule and optional parameters such as the :cwe-ug:`event pattern
<CloudWatchEventsandEventPatterns>`, IAM role to associate with the rule, and a :cwe-ug:`scheduling
expression <ScheduledEvents>` that describes how often the rule is run.

**Includes**

.. literalinclude:: example_code/cloudwatch/put_rule.cpp
   :lines: 15-19

**Code**

.. literalinclude:: example_code/cloudwatch/put_rule.cpp
   :lines: 37-53
   :dedent: 8


Add Targets
===========

Targets are the resources that are invoked when a rule is triggered. Example targets include |ec2|
instances, |lam| functions, |ak| streams, |ecs| tasks, |sfn| state machines, and built-in targets.

To add a target to a rule, call the |cweclient|'s :functionname:`PutTargets` function with a
:aws-cpp-class:`PutTargetsRequest <aws_1_1_cloud_watch_events_1_1_model_1_1_put_targets_request>`
containing the rule to update and a list of targets to add to the rule.

**Includes**

.. literalinclude:: example_code/cloudwatch/put_targets.cpp
   :lines: 15-19

**Code**

.. literalinclude:: example_code/cloudwatch/put_targets.cpp
   :lines: 40-59
   :dedent: 8

See the :sdk-examples-cpp:`complete example <cloudwatch/put_targets.cpp>`.

More Information
================

* :cwe-ug:`Adding Events with PutEvents <AddEventsPutEvents>` in the |cwe-ug|
* :cwe-ug:`Schedule Expressions for Rules <ScheduledEvents>` in the |cwe-ug|
* :cwe-ug:`Event Types for CloudWatch Events <EventTypes>` in the |cwe-ug|
* :cwe-ug:`Events and Event Patterns <CloudWatchEventsandEventPatterns>` in the |cwe-ug|
* :cwe-api:`PutEvents` in the |cwe-api|
* :cwe-api:`PutTargets` in the |cwe-api|
* :cwe-api:`PutRule` in the |cwe-api|

