.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###################
Using the |sdk-cpp|
###################

.. meta::
    :description:
        Initialize and set options to use the AWS SDK for C++.
    :keywords:

Applications that use the |sdk-cpp| must initialize it. Similarly, before the application 
terminates, the SDK must be shut down. Both operations accept configuration options that 
affect the initialization and shutdown processes and subsequent calls to the SDK.

.. _sdk-initializing:

Initializing and Shutting Down the SDK
======================================

All applications that use the |sdk-cpp| must include the file :file:`aws/core/Aws.h`.

The |sdk-cpp| must be initialized by calling :code:`Aws::InitAPI`. Before the application 
terminates, the SDK must be shut down by calling :code:`Aws::ShutdownAPI`. Each method accepts 
an argument of :aws-cpp-struct:`Aws::SDKOptions<aws_1_1_s_d_k_options>`. All other calls to the 
SDK can be performed between these two method calls.

Best practice requires all |sdk-cpp| calls performed between :code:`Aws::InitAPI` and
:code:`Aws::ShutdownAPI` either to be contained within a pair of curly braces or be invoked by 
functions called between the two methods.

A basic skeleton application is shown below.

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

.. _sdk-setting-options:

Setting SDK Options
===================

The :aws-cpp-struct:`Aws::SDKOptions <aws_1_1_s_d_k_options>` struct contains
SDK configuration options.

An instance of :aws-cpp-struct:`Aws::SDKOptions <aws_1_1_s_d_k_options>` is 
passed to the :code:`Aws::InitAPI` and :code:`Aws::ShutdownAPI` methods. The 
same instance should be sent to both methods.

The following samples demonstrate some of the available options.

* Turn logging on using the default logger

  .. code-block:: cpp

     Aws::SDKOptions options;
     options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
     Aws::InitAPI(options);
     {
         // make your SDK calls here.
     }
     Aws::ShutdownAPI(options);

* Install a custom memory manager

  .. code-block:: cpp

     MyMemoryManager memoryManager;
     Aws::SDKOptions options;
     options.memoryManagementOptions.memoryManager = &memoryManager;
     Aws::InitAPI(options);
     {
         // make your SDK calls here.
     }
     Aws::ShutdownAPI(options);

* Override the default HTTP client factory

  .. code-block:: cpp

     Aws::SDKOptions options;
     options.httpOptions.httpClientFactory_create_fn = [](){
             return Aws::MakeShared<MyCustomHttpClientFactory>(
                 "ALLOC_TAG", arg1);
         };
     Aws::InitAPI(options);
     {
         // make your SDK calls here.
     }
     Aws::ShutdownAPI(options);

.. note:: ``httpOptions`` takes a closure rather than a ``std::shared_ptr``. Each of the SDK 
    factory functions operates in this manner because at the time at which the factory memory 
    allocation occurs, the memory manager has not yet been installed. By passing a closure to the 
    method, the memory manager will be called to perform the memory allocation when it is safe to 
    do so. A simple technique to accomplish this procedure is by using a Lambda expression.

More Information
================

Examples of |sdk-cpp| application code are described in the section 
:doc:`programming-services`. Each example includes a link to the full source code on GitHub
which can be used as a starting point for your own applications.
