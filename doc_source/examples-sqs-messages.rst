.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.


###############################################
Sending, Receiving, and Deleting |SQS| Messages
###############################################

.. meta::
   :description: How to manage Amazon SQS messages with the AWS SDK for C++.
   :keywords: sqs

Messages are always delivered using an :doc:`SQS queue <examples-sqs-message-queues>`. These C++
examples show you how to use the |sdk-cpp| to send, receive, and delete |SQS| messages from SQS
queues.

.. include:: includes/examples-note.txt

.. _sqs-message-send:

Send a Message
==============

You can add a single message to an |SQS| queue by calling the |sqsclient| class
:functionname:`SendMessage` member function. You provide :functionname:`SendMessage` with a
:aws-cpp-class:`SendMessageRequest <aws_1_1_s_q_s_1_1_model_1_1_send_message_request>` object
containing the queue's :ref:`URL <sqs-get-queue-url>`, the message body, and an optional delay value
(in seconds).

**Includes**

.. literalinclude:: sqs.cpp.send_message.inc.txt

**Code**

.. literalinclude:: sqs.cpp.send_message.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <sqs/send_message.cpp>`.


.. _sqs-messages-receive:

Receive Messages
================

Retrieve any messages that are currently in the queue by calling the |sqsclient| class
:functionname:`ReceiveMessage` member function, passing it the queue's URL. Messages are returned as a
list of :aws-cpp-class:`Message <aws_1_1_s_q_s_1_1_model_1_1_message>` objects.

**Includes**

.. literalinclude:: sqs.cpp.receive_message.inc.txt

**Code**

.. literalinclude:: sqs.cpp.receive_message.code.txt
   :dedent: 4

See the :sdk-examples-cpp:`complete example <sqs/receive_message.cpp>`.


.. _sqs-messages-delete:

Delete Messages after Receipt
-----------------------------

After receiving a message and processing its contents, delete the message from the queue by sending
the message's receipt handle and the queue URL to the |sqsclient| class :functionname:`DeleteMessage`
member function.

**Includes**

.. literalinclude:: sqs.cpp.delete_message.inc.txt

**Code**

.. literalinclude:: sqs.cpp.delete_message.code.txt
   :dedent: 4

See the :sdk-examples-cpp:`complete example <sqs/receive_message.cpp>`.

More Info
=========

* :sqs-dg:`How Amazon SQS Queues Work <sqs-how-it-works>` in the |sqs-dg|
* :sqs-api:`SendMessage` in the |sqs-api|
* :sqs-api:`SendMessageBatch` in the |sqs-api|
* :sqs-api:`ReceiveMessage` in the |sqs-api|
* :sqs-api:`DeleteMessage` in the |sqs-api|

