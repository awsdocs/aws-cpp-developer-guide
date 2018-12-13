.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

.. highlight:: sh

########################
Setting Up the |sdk-cpp|
########################

.. meta::
    :description:
        |sdk-cpp| prerequisites and requirements to set up the SDK.
    :keywords:

This section presents information about how to set up the |sdk-cpp| on your development platform.
    
Prerequisites
=============

To use the |sdk-cpp|, you need:

* Visual Studio 2013 or later

  .. note:: Visual Studio 2013 doesn't provide default move constructors and operators. Later
     versions of Visual Studio provide a standards-compliant compiler.

* *or* GNU Compiler Collection (GCC) 4.9 or later
* *or* Clang 3.3 or later

* A minimum of 4 GB of RAM

  .. note:: You need 4 GB of RAM to build some of the larger AWS clients. The SDK might fail to
     build on |EC2| instance types *t2.micro*, *t2.small*, and other small instance types due to
     insufficient memory.


Additional Requirements for Linux Systems
-----------------------------------------

To compile on Linux, you must have the header files (``-dev`` packages) for :file:`libcurl`, 
:file:`libopenssl`, :file:`libuuid`, :file:`zlib`, and, optionally, :file:`libpulse` for 
|POLlong| support. The packages are typically found by using the system's package manager.

.. topic:: To install the packages on *Debian/Ubuntu-based systems*
   ::

      sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev

.. topic:: To install the packages on *Redhat/Fedora-based systems*
   ::

      sudo dnf install libcurl-devel openssl-devel libuuid-devel pulseaudio-devel


.. _setup-with-nuget:

Getting the SDK Using NuGet with Visual C++
===========================================

You can use NuGet to manage dependencies for |sdk-cpp| projects that you develop with Microsoft
Visual C++. To use this procedure, you must have `NuGet <nuget_>`_ installed on your system.

.. topic:: To use the SDK with NuGet

   #. Open your project in Visual Studio.

   #. In :guilabel:`Solution Explorer`, right-click your project name, and then choose :guilabel:`Manage
      NuGet Packages`.

   #. Select the packages to use by searching for a particular service or library name. For example,
      you could use a search term such as :userinput:`aws s3 native`. Or, because |sdk-cpp| libraries
      are named consistently, use :samp:`AWSSDKCPP-{service name}` to add a library for a particular
      service to your project.

   #. Choose :guilabel:`Install` to install the libraries and add them to your project.

When you build your project, the correct binaries are automatically included for each
runtime/architecture configuration you use |mdash| you won't need to manage these dependencies
yourself.

.. _setup-with-vcpkg:

Getting the SDK Using Vcpkg with Visual C++
===========================================
You can use vcpkg to manage dependencies for |sdk-cpp| projects that you develop with Microsoft
Visual C++. To use this procedure, you must have `vcpkg <https://github.com/Microsoft/vcpkg>`_
installed on your system.

.. topic:: To use the SDK with vcpkg

   #. Open a Windows command prompt and navigate to the vcpkg directory.

   #. Integrate vcpkg into Visual Studio. You can `integrate 
      <https://docs.microsoft.com/en-us/cpp/vcpkg#installation>`_ per project or per user 
      (shown below) to avoid manually editing Visual C++ directory paths.
      ::

	      vcpkg integrate install

   #. Install the |sdk-cpp| package. This package compiles the SDK and its dependencies. It can take a while.
      ::

	      vcpkg install aws-sdk-cpp:x86-windows

   #. Open your project in Visual Studio.

   #. #include |sdk-cpp| header files you want in your source code.

Like NuGet, when you build your project, the correct binaries are automatically included for each
runtime/architecture configuration you use.

.. _setup-from-source:

Building the SDK from Source
============================

If you don't use Visual Studio (or don't want to use NuGet), you can build the SDK from source to
set it up for your development system. This method also enables you to customize your SDK build
|mdash| see :doc:`cmake-params` for the available options.

.. topic:: To build the SDK from source

   #. Download or clone the SDK source from :github:`aws/aws-sdk-cpp` on GitHub.

      * Direct download: :github:`aws/aws-sdk-cpp/archive/master.zip`

      * Clone with Git:

        .. container:: option

           HTTPS
              .. code-block:: sh

                 git clone https://github.com/aws/aws-sdk-cpp.git

           SSH
              .. code-block:: sh

                 git clone git@github.com:aws/aws-sdk-cpp.git

   #. Install cmake_ (*v3.0+*) and the relevant build tools for your platform. Ensure these are
      available in your :envvar:`PATH`. If you're unable to install |cmake|, you can use |make| or
      |msbuild|.

   #. Create a directory in which to create your buildfiles, and generate the necessary buildfiles
      within it. This is the recommended approach, referred to as an *out-of-source build*.
      ::

         mkdir sdk_build
         cd sdk_build
         cmake <path/to/sdk/source>

      Alternatively, create the build files directly in the SDK source directory.
      ::

         cd <path/to/sdk/source>
         cmake .

      Building the entire SDK can take a while. To build only a particular client, such as |S3|, you 
      can use the |cmake| :paramname:`BUILD_ONLY` parameter demonstrated below. For more ways to 
      modify the build output, see :doc:`cmake-params`.
      ::

         cmake -DBUILD_ONLY="s3"

      If you don't have |cmake| installed, you can use these alternative commands to set up your build
      directory.

      .. container:: option

         auto make
            .. code-block:: sh

               make

         Visual Studio
            .. code-block:: doscon

               msbuild ALL_BUILD.vcxproj

   #. Build and install the SDK by typing one of the following in the same location where you generated
      your build files:

      .. container:: option

         auto make
            .. code-block:: sh

               make
               sudo make install

         Visual Studio
            .. code-block:: sh

               msbuild INSTALL.vcxproj


Building for Android
--------------------

To build for Android, add :code:`-DTARGET_ARCH=ANDROID` to your |cmake| command line. The |sdk-cpp|
includes a |cmake| toolchain file that should cover what's needed, assuming you've set the
appropriate environment variables (:envvar:`ANDROID_NDK`).

Android on Windows
~~~~~~~~~~~~~~~~~~

Building for Android on Windows requires additional setup. In particular, you have to run |cmake|
from a Visual Studio (2013 or later) developer command prompt. You'll also need the commands
:command:`git` and :command:`patch` in your path. If you have git installed on a Windows system,
you'll most likely find :command:`patch` in a sibling directory (:file:`.../Git/usr/bin/`).  Once
you've verified these requirements, your |cmake| command line will change slightly to use |nmake|.::

 cmake -G "NMake Makefiles" `-DTARGET_ARCH=ANDROID` <other options> ..

|nmake| builds targets in serially. To make things go more quickly, we recommend installing JOM as
an alternative to |nmake|, and then changing the |cmake| invocation as follows.::

 cmake -G "NMake Makefiles JOM" `-DTARGET_ARCH=ANDROID` <other options> ..


Creating Release Builds
-----------------------

.. container:: option

   auto make
      .. code-block:: sh

         cmake -DCMAKE_BUILD_TYPE=Release <path/to/sdk/source>
         make
         sudo make install

   Visual Studio
      .. code-block:: doscon

         cmake <path-to-root-of-this-source-code> -G "Visual Studio 12 Win64"
         msbuild INSTALL.vcxproj /p:Configuration=Release

Running Integration Tests
-------------------------

Several directory names include the suffix ``*integration-tests``. After the project is
built, the tests stored in these directories can be run to verify the project's correct 
execution.
