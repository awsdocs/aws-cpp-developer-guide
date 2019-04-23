.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.


####################
Asynchronous Methods
####################

.. meta::
   :description: How to use the asynchronous methods in the AWS SDK for C++.
   :keywords: asynchronous


Asynchronous SDK Methods
========================

For many methods, the |sdk-cpp| provides both synchronous and asynchronous 
versions. By default, a method is synchronous. An asynchronous version is 
designated with an ``Async`` suffix. For example, the Amazon S3 method 
``PutObject`` is synchronous and its asynchronous version is 
``PutObjectAsync``.

Like all asynchronous operations, an asynchronous SDK method returns before 
its main task is finished. For example, the ``PutObjectAsync`` method returns 
before it finishes uploading the file to the Amazon S3 bucket. While the 
upload operation continues, the application can perform other operations, 
including calling other asynchronous methods. The application is notified 
that an asynchronous operation has finished when an associated callback 
function is invoked.

The following sections describe a code example that demonstrates calling an 
SDK asynchronous method. Each section focuses on individual portions from the 
example's :sdk-examples-cpp:`entire source file <s3/put_object_async.cpp>`.


Calling SDK Asynchronous Methods
================================

In general, the asynchronous version of an SDK method accepts the following 
arguments.

* A reference to the same Request-type object as its synchronous counterpart.
* A reference to a response handler callback function. This callback function 
  is invoked when the asynchronous operation finishes. One of the arguments 
  contains the operation's outcome.
* An optional ``shared_ptr`` to an ``AsyncCallerContext`` object. The object 
  is passed to the response handler callback. It includes a UUID property 
  that can be used to pass text information to the callback.

The ``put_s3_object_async`` method shown below sets up and calls the SDK's 
Amazon S3 ``PutObjectAsync`` method to upload a file to an S3 bucket 
asynchronously.

The method initializes a ``PutObjectRequest`` object in the same manner as 
its synchronous counterpart. In addition, a ``shared_ptr`` to an 
``AsyncCallerContext`` object is allocated. Its ``UUID`` property is set to 
the Amazon S3 object name. For demonstration purposes, the response handler 
callback will access the property and output its value.

The call to ``PutObjectAsync`` includes a reference argument to the response 
handler callback function ``put_object_async_finished``. This callback 
function is examined in more detail in the next section.

.. literalinclude:: s3.cpp.put_object_async.code.txt

The resources directly associated with an asynchronous operation must 
continue to exist until the operation finishes. For example, the client 
object used to invoke an asynchronous SDK method must exist until the 
application receives notification that the operation has finished. Similarly, 
the application itself cannot terminate until the asynchronous operation 
completes.

For this reason, the ``put_s3_object_async`` method accepts a reference to 
an ``S3Client`` object instead of creating the client in a local variable. 
In the example, the method returns to the caller immediately after beginning 
the asynchronous operation, enabling the caller to perform additional tasks 
while the upload operation is in progress. If the client is stored in a local 
variable, it would go out of scope when the method returned. However, the 
client object must continue to exist until the asynchronous operation finishes.


Notification of the Completion of an Asynchronous Operation
===========================================================

When an asynchronous operation finishes, an application response handler 
callback function is invoked. This notification includes the outcome of the 
operation. The outcome is contained in the same Outcome-type class returned 
by the method's synchronous counterpart. In the code example, the outcome 
is in a ``PutObjectOutcome`` object.

The example's response handler callback function ``put_object_async_finished`` 
is shown below. It checks whether the asynchronous operation succeeded or 
failed. It uses a ``std::condition_variable`` to notify the application 
thread that the async operation has finished.

.. literalinclude:: s3.cpp.put_object_async.mutex_vars.txt

.. literalinclude:: s3.cpp.put_object_async_finished.code.txt

With the asynchronous operation finished, the resources associated 
with it can be released. The application can also terminate if it wishes.

The following code demonstrates how the ``put_object_async`` and 
``put_object_async_finished`` methods are used by an application.

The ``S3Client`` object is allocated so it continues to exist until the 
asynchronous operation finishes. After calling ``put_object_async``, the 
application can perform whatever operations it wishes. For simplicity, 
the example uses a ``std::mutex`` and ``std::condition_variable`` to wait 
until the response handler callback notifies it that the upload operation 
has finished.

.. literalinclude:: s3.cpp.put_object_async.invoke.code.txt
   :dedent: 8
