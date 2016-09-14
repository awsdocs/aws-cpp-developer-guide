.. Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

################
CMake Parameters
################

Use the CMake_ parameters listed in this section to customize how your SDK is built.

You can set these options either with CMake GUI tools or the command line using :paramname:`-D`. For
example::

 cmake -DENABLE_UNITY_BUILD=ON -DREGENERATE_CLIENTS=1

.. contents::
    :local:
    :depth: 1


.. _cmake-general-options:

General CMake variables and options
===================================

General :command:`cmake` variables and options that affect the your SDK build.

.. note:: To use the :paramname:`ADD_CUSTOM_CLIENTS` or :paramname:`REGENERATE_CLIENTS` variables
   you must have `Python 2.7 <https://www.python.org/downloads/>`_, Java (`JDK 1.8+
   <http://openjdk.java.net/install/>`_), and Maven_ installed and in your :envvar:`PATH`.

.. contents::
    :local:
    :depth: 1


.. _cmake-add-custom-clients:

ADD_CUSTOM_CLIENTS
------------------

Allows you to build any arbitrary clients based on the API definition. Place your definition
in the :file:`code-generation/api-definitions` folder, and then pass this argument to :command:`cmake`.
The :command:`cmake` configure step generates your client and includes it as a subdirectory in
your build. This is particularly useful if you want to generate a C++ client for using one of your
|ABP|_ services. For example::

 -DADD_CUSTOM_CLIENTS="serviceName=myCustomService;version=2015-12-21;serviceName=someOtherService;version=2015-08-15"


.. _cmake-build-only:

BUILD_ONLY
----------

Allows you to build only the clients you want to use. This will resolve any low-level client
dependencies if you set this to a high-level sdk such as ``aws-cpp-sdk-transfer``. This will also
build integration and unit tests related to the projects you select, if they exist. This is a list
argument, with values separated by semicolon (``;``) characters. For example::

 -DBUILD_ONLY="s3;cognito-identity"

.. note:: The core sdk module, ``aws-sdk-cpp-core``, is *always* built, regardless of the value of the
   :paramname:`BUILD_ONLY` parameter.


.. _cmake-build-shared-libs:

BUILD_SHARED_LIBS
-----------------

A built-in CMake option, re-exposed here for visibility. If enabled, shared libraries are built;
otherwise, only static libraries are built.

.. note:: To dynamically link to the SDK, you must define the ``USE_IMPORT_EXPORT`` symbol
   for all build targets using the SDK.

:Values: *ON* | *OFF*
:Default: *ON*


.. _cmake-cpp-standard:

CPP_STANDARD
------------

Allows you to specify a custom C++ standard for use with C++ 14 and 17 code bases.

:Values: *11* | *14* | *17*
:Default: *11*


.. _cmake-custom-memory-management:

CUSTOM_MEMORY_MANAGEMENT
------------------------

To use a custom memory manager, set the value to ``1``. You can install a custom allocator, and all
STL types will use the custom allocation interface. If the value is set to ``0``, you still might
want to use the STL template types to help with DLL safety on Windows.

If static linking is enabled, custom memory management defaults to *off* (``0``). If dynamic linking
is enabled, custom memory management defaults to *on* (``1``) and avoids cross-DLL allocation and
deallocation.

.. note:: To prevent linker mismatch errors, you must use the same value (``0`` or ``1``) throughout your
   build system.

   To install your own memory manager to handle allocations made by the SDK, you must
   set ``-DCUSTOM_MEMORY_MANAGEMENT`` and define ``AWS_CUSTOM_MEMORY_MANAGEMENT`` for all
   build targets that depend on the SDK.


.. _cmake-enable-rtti:

ENABLE_RTTI
-----------

Controls whether the SDK is built to enable run-time type information (RTTI).

:Values: *ON* | *OFF*
:Default: *ON*


.. _cmake-enable-testing:

ENABLE_TESTING
--------------

Controls whether unit and integration test projects are built during the SDK build.

:Values: *ON* | *OFF*
:Default: *ON*


.. _cmake-enable-unity-build:

ENABLE_UNITY_BUILD
------------------

If enabled, most SDK libraries are built as a single, generated :file:`.cpp` file. This can
significantly reduce static library size and speed up compilation time.

:Values: *ON* | *OFF*
:Default: *OFF*


.. _cmake-force-shared-crt:

FORCE_SHARED_CRT
----------------

If enabled, the SDK links to the C runtime *dynamically*; otherwise, it uses the
:paramname:`BUILD_SHARED_LIBS` setting (sometimes necessary for backward compatibility with earlier
versions of the SDK).

:Values: *ON* | *OFF*
:Default: *ON*


.. _cmake-g:

G
-

Use this variable to generate build artifacts, such as Visual Studio solutions and Xcode projects.

For example, on Windows::

 -G "Visual Studio 12 Win64"

For more information, see the CMake documentation for your platform.


.. _cmake-minimize-size:

MINIMIZE_SIZE
-------------

A superset of :ref:`cmake-enable-unity-build`. If enabled, this option turns on
:paramname:`ENABLE_UNITY_BUILD` and some additional binary size reduction settings.

:Values: *ON* | *OFF*
:Default: *OFF*


.. _cmake-no-encryption:

NO_ENCRYPTION
-------------

If enabled, prevents the default platform-specific cryptography implementation from being built into
the library. Turn this ON to inject your own cryptography implementation.

:Values: *ON* | *OFF*
:Default: *OFF*


.. _cmake-no-http-client:

NO_HTTP_CLIENT
--------------

If enabled, prevents the default platform-specific HTTP client from being built into the library.
Turn this ON if you wish to inject your own HTTP client implementation.

:Values: *ON* | *OFF*
:Default: *OFF*


.. _cmake-regenerate-clients:

REGENERATE_CLIENTS
------------------

This argument wipes out all generated code and generates the client directories from the
:file:`code-generation/api-definitions` folder. For example::

 -DREGENERATE_CLIENTS=1


.. _cmake-simple-install:

SIMPLE_INSTALL
--------------

If enabled, the install process will not insert platform-specific intermediate directories
underneath :file:`bin/` and :file:`lib/`. Turn *OFF* if you need to make multiplatform releases
under a single install directory.

:Values: *ON* | *OFF*
:Default: *ON*


.. _cmake-target-arch:

TARGET_ARCH
-----------

To cross compile or build for a mobile platform, you must specify the target platform. By default
the build detects the host operating system and builds for the detected operating system.

.. note:: When :paramname:`TARGET_ARCH` is *ANDROID*, additional options are available. See
   :ref:`cmake-android-variables`.

:Values: *WINDOWS* | *LINUX* | *APPLE* | *ANDROID*



.. _cmake-android-variables:

Android CMake variables and options
===================================

The following variables are used when creating an Android build of the SDK (when :ref:`cmake-target-arch` is
set to *ANDROID*).

.. contents::
    :local:
    :depth: 1


.. _cmake-android-abi:

ANDROID_ABI
-----------

Controls which Application Binary Interface (ABI) to output code for.

.. note:: Not all valid Android ABI values are currently supported.

:Values: *arm64* | *armeabi-v7a* | *x86_64* | *x86* | *mips64* | *mips*
:Default: *armeabi-v7a*


.. _cmake-android-native-api-level:

ANDROID_NATIVE_API_LEVEL
------------------------

Controls what API level the SDK is built against. If you set :ref:`cmake-android-stl` to
*gnustl*, you can choose any API level. If you use *libc++*, you must use
an API level of at least *21*.

:Default: Varies by STL choice.


.. _cmake-android-stl:

ANDROID_STL
-----------

Controls what flavor of the C++ standard library the SDK will use.

.. important:: Performance problems can occur within the SDK if the ``gnustl`` options are used; we
   strongly recommend using *libc++_shared* or *libc++_static*.

:Values: *libc++_shared* | *libc++_static* | *gnustl_shared* | *gnustl_static*
:Default: *libc++_shared*


.. _cmake-android-toolchain-name:

ANDROID_TOOLCHAIN_NAME
----------------------

Controls which compiler is used to build the SDK.

.. note:: With GCC being deprecated by the Android NDK, we recommend using the default value.

:Default: *standalone-clang*


.. _cmake-disable-android-standalone-build:

DISABLE_ANDROID_STANDALONE_BUILD
--------------------------------

By default, Android builds use a standalone clang-based toolchain constructed via NDK scripts. To use your own toolchain, turn this option *ON*.

:Values: *ON* | *OFF*
:Default: *OFF*

.. _cmake-ndk-dir:

NDK_DIR
-------

An override path where the build system should find the Android NDK. By default, the build
system will check environment variables (:envvar:`ANDROID_NDK`) if this variable is not set.

