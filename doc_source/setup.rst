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

* Visual Studio 2015 or later
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

.. topic:: To install the packages on *CentOS-based systems*

   ::

      sudo yum install libcurl-devel openssl-devel libuuid-devel pulseaudio-libs-devel

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
      <https://docs.microsoft.com/en-us/cpp/vcpkg#installation>`_ per project or per user. 
      The command line shown below integrates vcpkg for the current user.
      ::

	      vcpkg integrate install

   #. Install the |sdk-cpp| package. The package compiles the entire SDK and its dependencies. It 
      can take a while.
      ::

	      vcpkg install aws-sdk-cpp[*]:x86-windows --recurse

      To reduce build time, build only the SDK packages needed. Specify the package names in 
      square brackets. Also include the SDK `core` package.
      ::

         vcpkg install aws-sdk-cpp[core,s3,ec2]:x86-windows
      
      A package name can be derived from the |sdk-cpp| repo directory name for the service.
      ::

         aws-sdk-cpp\aws-cpp-sdk-<packageName>   # Repo directory name and packageName
         aws-sdk-cpp\aws-cpp-sdk-s3              # Example: Package name is s3

   #. Open your project in Visual Studio.

   #. #include the |sdk-cpp| header files you want in your source code.

Like NuGet, when you build your project, the correct binaries are automatically included for each
runtime/architecture configuration you use.

.. _setup-from-source:

Building the SDK from Source
============================

If you don't use Visual Studio (or don't want to use NuGet), you can build 
the SDK from source using command-line tools. This method also enables you 
to customize your SDK build |mdash| see :doc:`cmake-params` for the available 
options.

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

   #. Install cmake_ (*v3.2 or later*) and the relevant build tools for your 
      platform. Ensure they are available in your :envvar:`PATH`.

   #. Recommended approach: Store the generated build files outside of the 
      SDK source directory. Create a new directory to store them in. Then 
      generate the build files by running |cmake|. Specify on the |cmake| 
      command line whether to build a `Debug` or `Release` version.
      ::

         sudo mkdir sdk_build
         cd sdk_build
         sudo cmake <path/to/sdk/source> -D CMAKE_BUILD_TYPE=[Debug | Release]

      Alternatively, create the build files directly in the SDK source 
      directory.
      ::

         cd <path/to/sdk/source>
         sudo cmake . -D CMAKE_BUILD_TYPE=[Debug | Release]

      Building the entire SDK can take a while. To build only a particular 
      service, use the |cmake| :paramname:`BUILD_ONLY` parameter. The example 
      shown below builds only the |S3| service. For more ways to modify the 
      build output, see :doc:`cmake-params`.
      ::

         sudo cmake -D CMAKE_BUILD_TYPE=[Debug | Release] -D BUILD_ONLY="s3"

   #. Build the SDK binaries by running one of the following operating 
      system-dependent commands. If you're building the entire SDK, the 
      operation can take one hour or longer.

      .. container:: option

         auto make (Linux/macOS)
            .. code-block:: sh

               sudo make

         Visual Studio (Windows)
            .. code-block:: doscon

               msbuild ALL_BUILD.vcxproj

   #. Install the SDK by running one of the following operating 
      system-dependent commands.

      .. container:: option

         auto make (Linux/macOS)
            .. code-block:: sh

               sudo make install

         Visual Studio (Windows)
            .. code-block:: doscon

               rem Run this command in a command shell running in ADMIN mode
               rem The SDK is installed in `\Program Files (x86)\aws-cpp-sdk-all\`
               msbuild INSTALL.vcxproj /p:Configuration=[Debug | Release | "Debug;Release"]


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
