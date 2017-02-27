.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

.. highlight:: sh

##################
Setting Up the SDK
##################

Prerequisites
=============

To use the |sdk-cpp|, you need:

* Visual Studio 2013 or later

  .. note:: Visual Studio 2013 does not provide default move constructors and operators. Later
      versions of Visual Studio provide a standards-compliant compiler.

* *or* GNU Compiler Collection (GCC) 4.9 or later
* *or* Clang 3.3 or later

* A minimum of 4 GB of RAM

  .. note:: You need 4 GB of RAM to build some of the larger AWS clients. The SDK may fail to
      build on |EC2| instance types *t2.micro*, *t2.small*, and other small instance types due to
      insufficient memory.


Additional Requirements for Linux Systems
-----------------------------------------

To compile on Linux, you must have the header files (``-dev`` packages) for *libcurl*, *libopenssl*,
*libuuid* and *zlib*. Typically, you'll find the packages in your system's package manager.

To install these packages on *Debian/Ubuntu-based systems*, use::

 sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev

On *Fedora-based systems*, use::

 sudo dnf install libcurl-devel openssl-devel libuuid-devel


.. _setup-with-nuget:

Getting the SDK Using NuGet with Visual C++
===========================================

You can use NuGet to manage dependencies for |sdk-cpp| projects that you develop with Microsoft
Visual C++. To use this procedure, you must have `NuGet website <nuget_>`_ installed on your system.

**To use the SDK with NuGet**

#. Open your project in Visual Studio.

#. In :guilabel:`Solution Explorer`, right-click your project name and choose :guilabel:`Manage
   NuGet Packages`.

#. Select the packages to use by searching for a particular service or library name. For example,
   you could use a search term such as :userinput:`aws s3 native` or, because |sdk-cpp| libraries
   are named consistently, use :samp:`AWSSDKCPP-{service name}` to add a library for a particular
   service to your project.

#. Choose :guilabel:`Install` to install the libraries you chose and add them to your project.

When you build your project, the correct binaries are automatically included for each
runtime/architecture configuration you use |mdash| you won't need to manage these dependencies
yourself.


.. _setup-from-source:

Building the SDK from Source
============================

If you don't use Visual Studio (or don't want to use NuGet), you can build the SDK from source to
set it up on your development system. This method also allows you to customize your SDK build
|mdash| see :doc:`cmake-params` for the available options.

**To build the SDK from source**

#. Download or clone the SDK source from :github:`aws/aws-sdk-cpp` on GitHub:

   * Direct download: :github:`aws/aws-sdk-cpp/archive/master.zip`

   * Clone with Git (HTTPS)::

      git clone https://github.com/aws/aws-sdk-cpp.git

   * Clone with Git (SSH)::

      git clone git@github.com:aws/aws-sdk-cpp.git

#. Install cmake_ (*v3.0+*) and the relevant build tools for your platform. Ensure these are
   available in your :envvar:`PATH`. If you are unable to install |cmake|, you can use |make| or
   |msbuild|.

#. Create a directory to create the buildfiles in, and generate the necessary buildfiles within
   it (referred to as an *out-of-source build*, the recommended approach)::

    mkdir sdk_build
    cd sdk_build
    cmake <path/to/sdk/source>

   Alternatively, you can create the build files directly in the SDK source directory::

    cd <path/to/sdk/source>
    cmake .

   If you don't have |cmake| installed, you can use these alternative commands to set up your build
   directory:

   * auto make: |make|
   * Visual Studio: :code:`msbuild ALL_BUILD.vcxproj`

#. Build and install the SDK by typing one of the following in the same location where you generated
   your build files:

   * For auto make systems::

      make
      sudo make install

   * For Visual Studio::

      msbuild INSTALL.vcxproj

.. tip:: Building the entire SDK can take awhile. To build only a particular client
   such as |S3|, you can use the |cmake| :paramname:`BUILD_ONLY` parameter. For example::

    cmake -DBUILD_ONLY="s3"

   See :doc:`cmake-params` for information about additional ways to modify the build output.


Building for Android
--------------------

To build for Android, add :code:`-DTARGET_ARCH=ANDROID` to your |cmake| command line. The |sdk-cpp|
includes a |cmake| toolchain file that should cover what's needed, assuming you have the appropriate
environment variables (:envvar:`ANDROID_NDK`) set.

Android on Windows
~~~~~~~~~~~~~~~~~~

Building for Android on Windows requires additional setup. In particular, you have to run |cmake|
from a Visual Studio developer command prompt (2013 or later). You'll also need the commands
:command:`git` and :command:`patch` in your path. If you have git installed on a Windows system,
then :command:`patch` is likely found in a sibling directory (:file:`.../Git/usr/bin/`).  Once
you've verified these requirements, your |cmake| command line will change slightly to use |nmake|::

 cmake -G "NMake Makefiles" `-DTARGET_ARCH=ANDROID` <other options> ..

Nmake builds targets in a serial fashion. To make things quicker, we recommend installing JOM as an
alternative to |nmake| and then changing the |cmake| invocation to::

 cmake -G "NMake Makefiles JOM" `-DTARGET_ARCH=ANDROID` <other options> ..


Creating Release Builds
-----------------------

To create a *release* build of the SDK, do one of the following:

* For auto make systems::

   cmake -DCMAKE_BUILD_TYPE=Release <path/to/sdk/source>
   make
   sudo make install

* For Visual Studio::

   cmake <path-to-root-of-this-source-code> -G "Visual Studio 12 Win64"
   msbuild INSTALL.vcxproj /p:Configuration=Release

Running Integration Tests
-------------------------

Several directories are appended with ``*integration-tests``. After building your project, you can
run these executables to ensure everything works correctly.

