	.. Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

####################################
Building Your Application with CMake
####################################

.. contents::
    :local:
    :depth: 1

Setting up a CMake project
======================

	To set up a CMake project for use with the |sdk-cpp|:

1. Create a directory to hold your source-files::

    mkdir my_example_project

2. Enter the directory and add a :file:`CMakeLists.txt` file that specifies your project name, its
   executables, sourcefiles, and linked libraries. The following is a minimal example:

   .. literalinclude:: example_code/general/CMakeLists-minimal.txt
       :language: cmake

.. note:: There are many options that you can set in your :file:`CMakeLists.txt` build configuration file. For
an introduction to the file's features, see the `tutorial
<https://cmake.org/cmake-tutorial/>`_ on the CMake website.

(Optional) Setting CMAKE_PREFIX_PATH
================================

CMake needs to know the location of the :file:`aws-sdk-cpp-config.cmake` so that it can
properly resolve the AWS SDK libraries that your application uses. This file can be found in the build
directory that you used to :doc:`build the SDK <setup>`.

By setting the path in :envvar:`CMAKE_PREFIX_PATH`, you won't need to type this path every time you
rebuild your application.

You can set it on |unixes| like this::

 export CMAKE_PREFIX_PATH=/path/to/sdk_build_dir

On Windows, use :code:`set` instead::

 set CMAKE_PREFIX_PATH=C:\path\to\sdk_build_dir


Building with CMake
================

To build your application with :command:`cmake`, create a directory to build into::

 mkdir my_project_build

Enter the directory and run :command:`cmake` with the path to your project's source directory::

 cd my_project_build
 cmake ../my_example_project

If you did not set :envvar:`CMAKE_PREFIX_PATH`, then you must add the path to the SDK's build
directory using :code:`-Daws-sdk-cpp_DIR`::

 cmake -Daws-sdk-cpp_DIR=/path/to/sdk_build_dir ../my_example_project

Once :command:`cmake` generates your build directory, you can use :command:`make` (or
:command:`nmake` on Windows) to build your application::

 make



