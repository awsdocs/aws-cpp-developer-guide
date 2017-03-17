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
   :keywords: AWS SDK for C++ code examples

A *message queue* is the logical container you use to send messages reliably in |sqs|. There are two
types of queues: *standard* and *first-in, first-out* (FIFO). To learn more about queues and the
differences between these types, see the |sqs-dg|_.

These C++ examples show you how to use the |sdk-cpp| to create, list, delete, and get the URL of an |SQS|
queue.


.. _sqs-create-queue:

Create a Queue
==============

Use the |sqsclient| class :methodname:`CreateQueue` member function, and provide it with a
:aws-cpp-class:`CreateQueueRequest <aws_1_1_s_q_s_1_1_model_1_1_create_queue_request>` object that
describes the queue parameters.

**Includes**

.. literalinclude:: example_code/sqs/create_queue.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/sqs/create_queue.cpp
   :lines: 34-45
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/create_queue.cpp>`.


.. _sqs-list-queues:

List Queues
===========

To list |SQS| queues for your account, call the |sqsclient| class :methodname:`ListQueues` member
function, and pass it a :aws-cpp-class:`ListQueuesRequest
<class_aws_1_1_s_q_s_1_1_model_1_1_list_queues_request>` object.

**Includes**

.. literalinclude:: example_code/sqs/list_queues.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/sqs/list_queues.cpp
   :lines: 28-42
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/list_queues.cpp>`.


.. _sqs-get-queue-url:

Get the Queue's URL
===================

To get the URL for an existing |SQS| queue, call the |sqsclient| class :methodname:`GetQueueUrl`
member function.

**Includes**

.. literalinclude:: example_code/sqs/get_queue_url.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/sqs/get_queue_url.cpp
   :lines: 34-46
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/get_queue_url.cpp>`.


.. _sqs-delete-queue:

Delete a Queue
==============

Provide the :ref:`URL <sqs-get-queue-url>` to the |sqsclient| class :methodname:`DeleteQueue` member
function.

**Includes**

.. literalinclude:: example_code/sqs/delete_queue.cpp
   :lines: 14-17

**Code**

.. literalinclude:: example_code/sqs/delete_queue.cpp
   :lines: 35-51
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/delete_queue.cpp>`.


More Info
=========

* :sqs-dg:`How Amazon SQS Queues Work <sqs-how-it-works>` in the |sqs-dg|
* :sqs-api:`CreateQueue` in the |sqs-api|
* :sqs-api:`GetQueueUrl` in the |sqs-api|
* :sqs-api:`ListQueues` in the |sqs-api|
* :sqs-api:`DeleteQueues` in the |sqs-api|

