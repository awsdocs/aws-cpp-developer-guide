# CMake Parameters<a name="cmake-params"></a>

Use the [CMake](https://cmake.org/) parameters listed in this section to customize how your SDK builds\.

You can set these options with CMake GUI tools or the command line by using *\-D*\. For example:

```
cmake -DENABLE_UNITY_BUILD=ON -DREGENERATE_CLIENTS=1
```

## General CMake Variables and Options<a name="cmake-general-options"></a>

The following are general ** `cmake` ** variables and options that affect your SDK build\.

**Note**  
To use the *ADD\_CUSTOM\_CLIENTS* or *REGENERATE\_CLIENTS* variables, you must have [Python 2\.7](https://www.python.org/downloads/), Java \([JDK 1\.8\+](http://openjdk.java.net/install/)\), and [Maven](https://maven.apache.org/) installed and in your `PATH`\.

**Topics**
+ [ADD\_CUSTOM\_CLIENTS](#cmake-add-custom-clients)
+ [BUILD\_ONLY](#cmake-build-only)
+ [BUILD\_SHARED\_LIBS](#cmake-build-shared-libs)
+ [CPP\_STANDARD](#cmake-cpp-standard)
+ [CUSTOM\_MEMORY\_MANAGEMENT](#cmake-custom-memory-management)
+ [ENABLE\_RTTI](#cmake-enable-rtti)
+ [ENABLE\_TESTING](#cmake-enable-testing)
+ [ENABLE\_UNITY\_BUILD](#cmake-enable-unity-build)
+ [FORCE\_SHARED\_CRT](#cmake-force-shared-crt)
+ [G](#cmake-g)
+ [MINIMIZE\_SIZE](#cmake-minimize-size)
+ [NO\_ENCRYPTION](#cmake-no-encryption)
+ [NO\_HTTP\_CLIENT](#cmake-no-http-client)
+ [REGENERATE\_CLIENTS](#cmake-regenerate-clients)
+ [SIMPLE\_INSTALL](#cmake-simple-install)
+ [TARGET\_ARCH](#cmake-target-arch)

### ADD\_CUSTOM\_CLIENTS<a name="cmake-add-custom-clients"></a>

Builds any arbitrary clients based on the API definition\. Place your definition in the `code-generation/api-definitions` folder, and then pass this argument to ** `cmake` **\. The ** `cmake` ** configure step generates your client and includes it as a subdirectory in your build\. This is particularly useful to generate a C\+\+ client for using one of your [API Gateway](https://aws.amazon.com/api-gateway) services\. For example:

```
-DADD_CUSTOM_CLIENTS="serviceName=myCustomService,version=2015-12-21;serviceName=someOtherService,version=2015-08-15"
```

### BUILD\_ONLY<a name="cmake-build-only"></a>

Builds only the clients you want to use\. If set to a high\-level SDK such as `aws-cpp-sdk-transfer`, *BUILD\_ONLY* resolves any low\-level client dependencies\. It also builds integration and unit tests related to the projects you select, if they exist\. This is a list argument, with values separated by semicolon \(`;`\) characters\. For example:

```
-DBUILD_ONLY="s3;cognito-identity"
```

**Note**  
The core SDK module, `aws-sdk-cpp-core`, is *always* built, regardless of the value of the *BUILD\_ONLY* parameter\.

### BUILD\_SHARED\_LIBS<a name="cmake-build-shared-libs"></a>

A built\-in CMake option, re\-exposed here for visibility\. If enabled, it builds shared libraries; otherwise, it builds only static libraries\.

**Note**  
To dynamically link to the SDK, you must define the `USE_IMPORT_EXPORT` symbol for all build targets using the SDK\.

Values  
 *ON* \| *OFF* 

Default  
 *ON* 

### CPP\_STANDARD<a name="cmake-cpp-standard"></a>

Specifies a custom C\+\+ standard for use with C\+\+ 14 and 17 code bases\.

Values  
 *11* \| *14* \| *17* 

Default  
 *11* 

### CUSTOM\_MEMORY\_MANAGEMENT<a name="cmake-custom-memory-management"></a>

To use a custom memory manager, set the value to `1`\. You can install a custom allocator so that all STL types use the custom allocation interface\. If you set the value `0`, you still might want to use the STL template types to help with DLL safety on Windows\.

If static linking is enabled, custom memory management defaults to *off* \(`0`\)\. If dynamic linking is enabled, custom memory management defaults to *on* \(`1`\) and avoids cross\-DLL allocation and deallocation\.

**Note**  
To prevent linker mismatch errors, you must use the same value \(`0` or `1`\) throughout your build system\.

To install your own memory manager to handle allocations made by the SDK, you must set `-DCUSTOM_MEMORY_MANAGEMENT` and define `AWS_CUSTOM_MEMORY_MANAGEMENT` for all build targets that depend on the SDK\.

### ENABLE\_RTTI<a name="cmake-enable-rtti"></a>

Controls whether the SDK is built to enable run\-time type information \(RTTI\)\.

Values  
 *ON* \| *OFF* 

Default  
 *ON* 

### ENABLE\_TESTING<a name="cmake-enable-testing"></a>

Controls whether unit and integration test projects are built during the SDK build\.

Values  
 *ON* \| *OFF* 

Default  
 *ON* 

### ENABLE\_UNITY\_BUILD<a name="cmake-enable-unity-build"></a>

If enabled, most SDK libraries are built as a single, generated `.cpp` file\. This can significantly reduce static library size and speed up compilation time\.

Values  
 *ON* \| *OFF* 

Default  
 *OFF* 

### FORCE\_SHARED\_CRT<a name="cmake-force-shared-crt"></a>

If enabled, the SDK links to the C runtime *dynamically*; otherwise, it uses the *BUILD\_SHARED\_LIBS* setting \(sometimes necessary for backward compatibility with earlier versions of the SDK\)\.

Values  
 *ON* \| *OFF* 

Default  
 *ON* 

### G<a name="cmake-g"></a>

Generates build artifacts, such as Visual Studio solutions and Xcode projects\.

For example, on Windows:

```
-G "Visual Studio 12 Win64"
```

For more information, see the CMake documentation for your platform\.

### MINIMIZE\_SIZE<a name="cmake-minimize-size"></a>

A superset of [ENABLE\_UNITY\_BUILD](#cmake-enable-unity-build)\. If enabled, this option turns on *ENABLE\_UNITY\_BUILD* and additional binary size reduction settings\.

Values  
 *ON* \| *OFF* 

Default  
 *OFF* 

### NO\_ENCRYPTION<a name="cmake-no-encryption"></a>

If enabled, prevents the default platform\-specific cryptography implementation from being built into the library\. Turn this *ON* to inject your own cryptography implementation\.

Values  
 *ON* \| *OFF* 

Default  
 *OFF* 

### NO\_HTTP\_CLIENT<a name="cmake-no-http-client"></a>

If enabled, prevents the default platform\-specific HTTP client from being built into the library\. Turn this *ON* to inject your own HTTP client implementation\.

Values  
 *ON* \| *OFF* 

Default  
 *OFF* 

### REGENERATE\_CLIENTS<a name="cmake-regenerate-clients"></a>

This argument wipes out all generated code and generates the client directories from the `code-generation/api-definitions` folder\. For example:

```
-DREGENERATE_CLIENTS=1
```

### SIMPLE\_INSTALL<a name="cmake-simple-install"></a>

If enabled, the install process does not insert platform\-specific intermediate directories underneath `bin/` and `lib/`\. Turn *OFF* if you need to make multiplatform releases under a single install directory\.

Values  
 *ON* \| *OFF* 

Default  
 *ON* 

### TARGET\_ARCH<a name="cmake-target-arch"></a>

To cross\-compile or build for a mobile platform, you must specify the target platform\. By default, the build detects the host operating system and builds for the detected operating system\.

**Note**  
When *TARGET\_ARCH* is *ANDROID*, additional options are available\. See [Android CMake Variables and Options](#cmake-android-variables)\.

Values  
 *WINDOWS* \| *LINUX* \| *APPLE* \| *ANDROID* 

## Android CMake Variables and Options<a name="cmake-android-variables"></a>

Use the following variables when you are creating an Android build of the SDK \(when [TARGET\_ARCH](#cmake-target-arch) is set to *ANDROID*\)\.

**Topics**
+ [ANDROID\_ABI](#cmake-android-abi)
+ [ANDROID\_NATIVE\_API\_LEVEL](#cmake-android-native-api-level)
+ [ANDROID\_STL](#cmake-android-stl)
+ [ANDROID\_TOOLCHAIN\_NAME](#cmake-android-toolchain-name)
+ [DISABLE\_ANDROID\_STANDALONE\_BUILD](#cmake-disable-android-standalone-build)
+ [NDK\_DIR](#cmake-ndk-dir)

### ANDROID\_ABI<a name="cmake-android-abi"></a>

Controls which Application Binary Interface \(ABI\) to output code for\.

**Note**  
Not all valid Android ABI values are currently supported\.

Values  
 *arm64* \| *armeabi\-v7a* \| *x86\_64* \| *x86* \| *mips64* \| *mips* 

Default  
 *armeabi\-v7a* 

### ANDROID\_NATIVE\_API\_LEVEL<a name="cmake-android-native-api-level"></a>

Controls what API level the SDK builds against\. If you set [ANDROID\_STL](#cmake-android-stl) to *gnustl*, you can choose any API level\. If you use *libc\+\+*, you must use an API level of at least *21*\.

Default  
Varies by STL choice\.

### ANDROID\_STL<a name="cmake-android-stl"></a>

Controls what flavor of the C\+\+ standard library the SDK uses\.

**Important**  
Performance problems can occur within the SDK if the `gnustl` options are used; we strongly recommend using *libc\+\+\_shared* or *libc\+\+\_static*\.

Values  
 *libc\+\+\_shared* \| *libc\+\+\_static* \| *gnustl\_shared* \| *gnustl\_static* 

Default  
 *libc\+\+\_shared* 

### ANDROID\_TOOLCHAIN\_NAME<a name="cmake-android-toolchain-name"></a>

Controls which compiler is used to build the SDK\.

**Note**  
With GCC being deprecated by the Android NDK, we recommend using the default value\.

Default  
 *standalone\-clang* 

### DISABLE\_ANDROID\_STANDALONE\_BUILD<a name="cmake-disable-android-standalone-build"></a>

By default, Android builds use a standalone clang\-based toolchain constructed via NDK scripts\. To use your own toolchain, turn this option *ON*\.

Values  
 *ON* \| *OFF* 

Default  
 *OFF* 

### NDK\_DIR<a name="cmake-ndk-dir"></a>

Specifies an override path where the build system should find the Android NDK\. By default, the build system checks environment variables \(`ANDROID_NDK`\) if this variable is not set\.