.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###################################
Setting Visibility Timeout in |SQS|
###################################

.. meta::
   :description: How to set visibility timeout for Amazon SQS queues with the AWS SDK for C++.
   :keywords: AWS SDK for C++ code examples, Amazon SQS, visibility timeout

When a message is received in |SQS|, it remains on the queue until it's deleted in order to ensure
receipt. A message that was received, but not deleted, will be available in subsequent requests
after a given *visibility timeout* to help prevent the message from being received more than once
before it can be processed and deleted.

.. note:: When using :sqs-dg:`standard queues <standard-queues>`, visibility timeout isn't a
   guarantee against receiving a message twice. If you are using a standard queue, be sure that your
   code can handle the case where the same message has been delivered more than once.

.. _sqs-visibility-timeout-receipt:

Setting the Message Visibility Timeout upon Message Receipt
===========================================================

When you have received a message, you can modify its visibility timeout by passing its receipt
handle in a :aws-cpp-class:`ChangeMessageVisibilityRequest
<aws_1_1_s_q_s_1_1_model_1_1_change_message_visibility_request>` that you pass to the |sqsclient|
class' :methodname:`ChangeMessageVisibility` member function.

**Includes**

.. literalinclude:: example_code/sqs/change_message_visibility.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/sqs/change_message_visibility.cpp
   :lines: 27-68
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/change_message_visibility.cpp>`.

More Info
=========

* :sqs-dg:`Visibility Timeout <sqs-visibility-timeout>` in the |sqs-dg|
* :sqs-api:`SetQueueAttributes` in the |sqs-api|
* :sqs-api:`GetQueueAttributes` in the |sqs-api|
* :sqs-api:`ReceiveMessage` in the |sqs-api|
* :sqs-api:`ChangeMessageVisibility` in the |sqs-api|
* :sqs-api:`ChangeMessageVisibilityBatch` in the |sqs-api|

