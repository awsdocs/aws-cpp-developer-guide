.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

.. highlight:: sh

####################################
Building Your Application with CMake
####################################

.. meta::
    :description:
        Using CMake to build an application that uses the AWS SDK for C++.
    :keywords:

CMake_ is a build tool that can manage your application's dependencies and create native makefiles
suitable for the platform you're building on. It's an easy way to create and build projects using
the |sdk-cpp|.

Setting Up a CMake Project
==========================

.. topic:: To set up a CMake project for use with the |sdk-cpp|

   #. Create a directory to hold your source files.
      ::

        mkdir my_example_project

   #. Open the directory and add a :file:`CMakeLists.txt` file that specifies your project's name,
      executables, source files, and linked libraries. The following is a minimal example.

      .. literalinclude:: example_code/general/CMakeLists-minimal.txt
          :language: cmake

.. note:: You can set many options in your :file:`CMakeLists.txt` build configuration file. For an
   introduction to the file's features, see the `CMake tutorial
   <https://cmake.org/cmake-tutorial/>`_ on the CMake website.


Setting CMAKE_PREFIX_PATH (Optional)
====================================

By default, the AWS SDK for C++ on macOS, Linux, Android and other non-Windows platforms is installed
into :file:`/usr/local` and :file:`\Program Files (x86)\aws-cpp-sdk-all\` on Windows.

When you install the SDK into a non-default location, CMake needs to know where to find the file 
:file:`AWSSDKConfig.cmake` so that it can properly resolve the AWS SDK libraries that your 
application uses. You can find this file in the build directory that you used to 
:doc:`build the SDK <setup>`.

By adding the path to a list in :envvar:`CMAKE_PREFIX_PATH`, you won't need to type this path every 
time you rebuild your application.

You can set it on |unixes| like this.
::

   export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/path/to/sdk_install_dir

On Windows, use :code:`set` instead.
::

   set CMAKE_PREFIX_PATH=%CMAKE_PREFIX_PATH%;C:\path\to\sdk_install_dir


Building with CMake
===================

Create a directory into which :command:`cmake` will build your application.
::

   mkdir my_project_build

Open the directory and run :command:`cmake` using the path to your project's source directory.
::

   cd my_project_build
   cmake ../my_example_project

If you didn't set :envvar:`CMAKE_PREFIX_PATH`, you must add the path to the SDK's build directory
using :code:`-DAWSSDK_DIR`.
::

   cmake -DAWSSDK_DIR=/path/to/sdk_install_dir ../my_example_project

After :command:`cmake` generates your build directory, you can use :command:`make` (or
:command:`nmake` on Windows) to build your application.
::

   make
