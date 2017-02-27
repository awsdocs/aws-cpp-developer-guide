.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#############
Using the SDK
#############

To use the SDK, you should properly initialize it with :code:`Aws::InitAPI` before creating
service clients and using them. You should then shut down the SDK with
:code:`Aws::ShutdownAPI`.

Both of these functions take an instance of :aws-cpp-struct:`Aws::SDKOptions
<aws_1_1_s_d_k_options>`, which you can use to set additional run-time options for SDK calls.

.. _sdk-initializing:

Initializing and Shutting Down the SDK
======================================

A basic skeleton application looks like this:

.. code-block:: cpp

   #include <aws/core/Aws.h>
   int main(int argc, char** argv)
   {
      Aws::SDKOptions options;
      Aws::InitAPI(options);
      {
         // make your SDK calls here.
      }
      Aws::ShutdownAPI(options);
      return 0;
   }

.. admonition:: best practice

   To properly shut down / clean up any service clients that you may initialize before
   :code:`Aws::ShutdownAPI` is called, it's a *best practice* to make sure that all SDK calls
   are made within a pair of curly-braces as shown above, or within another function called between
   :code:`Aws::InitAPI` and :code:`Aws::ShutdownAPI`.

.. _sdk-setting-options:

Setting SDK options
===================

The :aws-cpp-struct:`Aws::SDKOptions <aws_1_1_s_d_k_options>` struct shown in
:ref:`sdk-initializing` provides a number of options you can set. You should send the same options
object to both :code:`Aws::InitAPI` and :code:`Aws::ShutdownAPI`.

A few examples:

* Turn logging on using the default logger:

  .. code-block:: cpp

     Aws::SDKOptions options
     options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
     Aws::InitAPI(options);
     {
         // make your SDK calls here.
     }
     Aws::ShutdownAPI(options);

* Install a custom memory manager:

  .. code-block:: cpp

     MyMemoryManager memoryManager;
     Aws::SDKOptions options
     options.memoryManagementOptions.memoryManager = &memoryManager;
     Aws::InitAPI(options);
     {
         // make your SDK calls here.
     }
     Aws::ShutdownAPI(options);

* Override the default HTTP client factory:

  .. code-block:: cpp

     Aws::SDKOptions options
     options.httpOptions.httpClientFactory_create_fn = [](){
             return Aws::MakeShared<MyCustomHttpClientFactory>(
                 "ALLOC_TAG", arg1);
         };
     Aws::InitAPI(options);
     {
         // make your SDK calls here.
     }
     Aws::ShutdownAPI(options);

.. note:: ``httpOptions`` takes a closure instead of a ``std::shared_ptr``. The SDK does this for
   all of its factory functions because the memory manager will not yet be installed at the time you
   will need to allocate this memory. Pass a closure to the SDK, and it will be called when it is
   safe to do so. This simplest way to do this is with a Lambda expression.

More Information
================

For further examples of |sdk-cpp| application code, view the topics in the
:doc:`programming-services` section. Each example contains a link to the full source code on GitHub,
which you can use as a starting point for your own applications.

