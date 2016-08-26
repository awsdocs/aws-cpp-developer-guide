.. Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###########################################
Hello World - Building a Simple Application
###########################################

This topic will walk through the process of creating a simple AWS application with the |sdk-cpp|.

.. contents::
    :local:
    :depth: 1

Prerequisites
=============

This tutorial assumes that you've already taken these steps:

Installed the SDK
Set up AWS Credentials

If you haven't set up the SDK or your AWS credentials, you should go back and complete those steps
before proceeding with the rest of the walkthrough.

Create a project
================

The process for creating a project will depend on the development environment you choose.

.. contents::
    :local:
    :depth: 1

On the command-line with cmake:
-------------------------------

To create your project on the command-line for use with :command:`cmake`:

1. Open a terminal (command-line) window and create a new directory for your project's source files.
   For example::

       mkdir hello_s3

2. Enter the directory and create a :file:`CMakeLists.txt` file. Add the following contents::


