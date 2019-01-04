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
   :description: How to manage an Amazon SQS queue's URL with the AWS SDK for C++.
   :keywords: sqs

A *message queue* is the logical container you use to send messages reliably in |sqs|. There are two
types of queues: *standard* and *first-in, first-out* (FIFO). To learn more about queues and the
differences between these types, see the |sqs-dg|_.

These C++ examples show you how to use the |sdk-cpp| to create, list, delete, and get the URL of an |SQS|
queue.

.. include:: includes/examples-note.txt

.. _sqs-create-queue:

Create a Queue
==============

Use the |sqsclient| class :functionname:`CreateQueue` member function, and provide it with a
:aws-cpp-class:`CreateQueueRequest <aws_1_1_s_q_s_1_1_model_1_1_create_queue_request>` object that
describes the queue parameters.

**Includes**

.. literalinclude:: sqs.cpp.create_queue.inc.txt

**Code**

.. literalinclude:: sqs.cpp.create_queue.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/create_queue.cpp>`.


.. _sqs-list-queues:

List Queues
===========

To list |SQS| queues for your account, call the |sqsclient| class :functionname:`ListQueues` member
function, and pass it a :aws-cpp-class:`ListQueuesRequest
<class_aws_1_1_s_q_s_1_1_model_1_1_list_queues_request>` object.

**Includes**

.. literalinclude:: sqs.cpp.list_queues.inc.txt

**Code**

.. literalinclude:: sqs.cpp.list_queues.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/list_queues.cpp>`.


.. _sqs-get-queue-url:

Get the Queue's URL
===================

To get the URL for an existing |SQS| queue, call the |sqsclient| class :functionname:`GetQueueUrl`
member function.

**Includes**

.. literalinclude:: sqs.cpp.get_queue_url.inc.txt

**Code**

.. literalinclude:: sqs.cpp.get_queue_url.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/get_queue_url.cpp>`.


.. _sqs-delete-queue:

Delete a Queue
==============

Provide the :ref:`URL <sqs-get-queue-url>` to the |sqsclient| class :functionname:`DeleteQueue` member
function.

**Includes**

.. literalinclude:: sqs.cpp.delete_queue.inc.txt

**Code**

.. literalinclude:: sqs.cpp.delete_queue.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/delete_queue.cpp>`.


More Info
=========

* :sqs-dg:`How Amazon SQS Queues Work <sqs-how-it-works>` in the |sqs-dg|
* :sqs-api:`CreateQueue` in the |sqs-api|
* :sqs-api:`GetQueueUrl` in the |sqs-api|
* :sqs-api:`ListQueues` in the |sqs-api|
* :sqs-api:`DeleteQueues` in the |sqs-api|

