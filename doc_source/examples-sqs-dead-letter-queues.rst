.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#################################
Using Dead Letter Queues in |SQS|
#################################

.. meta::
   :description: How to enable long polling for Amazon SQS message queues.
   :keywords: AWS SDK for C++ code examples, SQS, long polling, queue management

|SQS| provides support for *dead letter queues*. A dead letter queue is a queue that other (source)
queues can target for messages that can't be processed successfully. You can set aside and isolate
these messages in the dead letter queue to determine why their processing did not succeed.

To create a dead letter queue, you must first create a *redrive policy*, and then set the policy in
the queue's attributes.

.. important:: A dead letter queue must be the same type of queue (FIFO or standard) that the source
   queue is. It must also be created using the same AWS account and region as the source queue.


.. _sqs-dead-letter-queue-create-redrive-policy:

Creating a Redrive Policy
=========================

A redrive policy is specified in JSON. To create it, you can use the JSON utility class provided
with the |sdk-cpp|.

Here is an example function that creates a redrive policy by providing it with the ARN of your dead
letter queue and the maximum number of times the message can be received and not processed before
it's sent to the dead letter queue.

**Includes**

.. literalinclude:: example_code/sqs/dead_letter_queue.cpp
   :lines: 14-15

**Code**

.. literalinclude:: example_code/sqs/dead_letter_queue.cpp
   :lines: 20-33

See the :sdk-examples-cpp:`complete example <sqs/dead_letter_queue.cpp>`.


.. _sqs-dead-letter-queue-set-redrive-policy:

Setting the Redrive Policy on your Source Queue
===============================================

To finish setting up your dead letter queue, call the |sqsclient| class'
:methodname:`SetQueueAttributes` member function with a :aws-cpp-class:`SetQueueAttributesRequest
<aws_1_1_s_q_s_1_1_model_1_1_set_queue_attributes_request>` object for which you've set the
``RedrivePolicy`` attribute with your JSON redrive policy.

**Includes**

.. literalinclude:: example_code/sqs/dead_letter_queue.cpp
   :lines: 14, 16-17

**Code**

.. literalinclude:: example_code/sqs/dead_letter_queue.cpp
   :lines: 57-75
   :dedent: 8

More Info
=========

* :sqs-dg:`Using Amazon SQS Dead Letter Queues <sqs-dead-letter-queues>` in the |sqs-dg|
* :sqs-api:`SetQueueAttributes` in the |sqs-api|

