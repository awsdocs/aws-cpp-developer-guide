.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#################################
Working with |SQS| Message Queues
#################################

.. meta::
   :description: How to create, list, delete, and get an Amazon SQS queue's URL with the AWS SDK for
                 C++.
   :keywords: C++, programming, AWS, Amazon SQS, queue, queue operations, create queue, list queue,
              delete queue, get queue URL

A *message queue* is the logical container used for sending messages reliably in |sqslong|. There
are two types of queues: *standard*, and *first-in, first-out* (FIFO). To learn more about queues
and the differences between these types, see the |sqs-dg|_.

This topic describes how to create, list, delete, and get a |SQS| queue's URL using the |sdk-cpp|.


.. _sqs-create-queue:

Creating Queues
===============

To create a new |SQS| queue, use the |sqsclient| class' :methodname:`CreateQueue` member function,
providing it with a :aws-cpp-class:`CreateQueueRequest
<aws_1_1_s_q_s_1_1_model_1_1_create_queue_request>` object that describes the queue parameters.

**Includes:**

.. literalinclude:: example_code/sqs/create_queue.cpp
   :lines: 14-17

**Code:**

.. literalinclude:: example_code/sqs/create_queue.cpp
   :lines: 36-47
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/create_queue.cpp>`.


.. _sqs-list-queues:

Listing Queues
==============

To list the |SQS| queues for your account, call the |sqsclient| class' :methodname:`ListQueues`
member function, passing it a :aws-cpp-class:`ListQueuesRequest
<class_aws_1_1_s_q_s_1_1_model_1_1_list_queues_request>` object.

**Includes:**

.. literalinclude:: example_code/sqs/list_queues.cpp
   :lines: 15-18

**Code:**

.. literalinclude:: example_code/sqs/list_queues.cpp
   :lines: 30-44
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/list_queues.cpp>`.


.. _sqs-get-queue-url:

Getting the Queue's URL
=======================

To get an existing |SQS| queue's URL, call the |sqsclient| class' :methodname:`GetQueueUrl` member
function.

**Includes:**

.. literalinclude:: example_code/sqs/get_queue_url.cpp
   :lines: 14-17

**Code:**

.. literalinclude:: example_code/sqs/get_queue_url.cpp
   :lines: 36-48
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/get_queue_url.cpp>`.


.. _sqs-delete-queue:

Deleting a Queue
================

To delete an |SQS| queue, provide its :ref:`URL <sqs-get-queue-url>` to the |sqsclient| class'
:methodname:`DeleteQueue` member function.

**Includes:**

.. literalinclude:: example_code/sqs/delete_queue.cpp
   :lines: 14-17

**Code:**

.. literalinclude:: example_code/sqs/delete_queue.cpp
   :lines: 37-53
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/delete_queue.cpp>`.


More Info
=========

* :sqs-dg:`How Amazon SQS Queues Work <sqs-how-it-works>` in the |sqs-dg|
* :sqs-api:`CreateQueue` in the |sqs-api|
* :sqs-api:`GetQueueUrl` in the |sqs-api|
* :sqs-api:`ListQueues` in the |sqs-api|
* :sqs-api:`DeleteQueues` in the |sqs-api|

