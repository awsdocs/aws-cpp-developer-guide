# Building the AWS SDK for C\+\+ on Windows<a name="setup-windows"></a>

To set up the AWS SDK for C\+\+, you can either build the SDK yourself directly from the source or download the libraries using a package manager\.



The SDK source is separated into individual packages by service\. Installing the entire SDK can take up to an hour\. Installing only the specific subset of services that your program uses decreases installation time and also reduces size on disk\. To choose which services to install, you need to know the package name of each service your program uses\. You can see the list of package directories at [https://github.com/aws/aws-sdk-cpp](https://github.com/aws/aws-sdk-cpp) on GitHub\. The package name is the suffix of the directory name for the service\. 

```
aws-sdk-cpp\aws-cpp-sdk-<packageName>   # Repo directory name and packageName
aws-sdk-cpp\aws-cpp-sdk-s3              # Example: Package name is s3
```

## Prerequisites<a name="prerequisites"></a>

You need a minimum of 4 GB of RAM to build some of the larger AWS clients\. The SDK might fail to build on Amazon EC2 instance types *t2\.micro*, *t2\.small*, and other small instance types due to insufficient memory\.

To use the AWS SDK for C\+\+, you need one of the following:
+ Microsoft Visual Studio 2015 or later, 
+  GNU Compiler Collection \(GCC\) 4\.9 or later, or
+  Clang 3\.3 or later\.

## Building the SDK for Windows with curl<a name="build-curl-id"></a>

On Windows, the SDK is built with [WinHTTP](https://msdn.microsoft.com/en-us/library/windows/desktop/aa382925%28v=vs.85%29.aspx) as the default HTTP client\. However, WinHTTP 1\.0 does not support HTTP/2 bidirectional streaming, which is required for some AWS services such as Amazon Transcribe and Amazon Lex\. Thus, it is sometimes necessary to build curl support with the SDK\. To view all available curl download options, see [curl Releases and Downloads](https://curl.se/download.html)\. One method for building the SDK with curl support is the following:

**To build the SDK with curl library support included**

1. Navigate to [curl for Windows](https://curl.se/windows/) and download the curl binary package for Microsoft Windows\. 

1. Unpack the package to a folder on your computer, for example, `C:\curl`\. 

1. Navigate to [CA certificates extracted from Mozilla](http://curl.haxx.se/docs/caextract.html) and download the `cacert.pem` file\. This Privacy Enhanced Mail \(PEM\) file contains a bundle of valid digital certificates that are used to verify the authenticity of secure websites\. The certificates are distributed by certificate authority \(CA\) companies such as GlobalSign and Verisign\. 

1. Move the `cacert.pem` file to the `bin` subfolder that you unpacked in a previous step, for example, `C:\curl\bin`\. Rename the file as `curl-ca-bundle.crt`\. 

Also, the Microsoft Build Engine \(MSBuild\) must be able to locate the curl `dll` in the procedure that follows\. Therefore, you should add the curl `bin` folder path to your Windows `PATH` environment variable, for example, `set PATH=%PATH%;C:\curl\bin`\. You must add this each time you open a new command prompt to build the SDK\. Alternatively, you can set the environment variable globally in your Windows system settings so that the setting is remembered\.

For alternative syntax required to build curl into your SDK, see Step 5 \(Generate build files\) in the *Building the SDK from source* procedure that follows\.

## Building the SDK from source<a name="setup-windows-from-source"></a>

You can build the SDK from source using command\-line tools\. Using this method, you can customize your SDK build\. For information about available options, see [CMake Parameters](cmake-params.md)\. There are three main steps\. First, you build the files using CMake\. Second, you use MSBuild to build the SDK binaries that work with your operating system and build toolchain\. Third, you install or copy the binaries into the correct location on the development machine\.

**To build the SDK from source**

1. Install [CMake](https://cmake.org/) \(minimum version 3\.2; *maximum version 3\.21*\) and the relevant build tools for your platform\. It is recommended to add `cmake` to your `PATH`\. To check your version of CMake, open a command prompt and run command **cmake \-\-version**

1. In a command prompt, navigate to a folder where you want to store the SDK\.

1. Get the latest source code\.

   Version 1\.9 simplifies dependencies by using git submodules to wrap external dependencies\.

   Download or clone the SDK source from [https://github.com/aws/aws-sdk-cpp](https://github.com/aws/aws-sdk-cpp) on GitHub:
   + Clone with Git: HTTPS

     ```
     git clone --recurse-submodules https://github.com/aws/aws-sdk-cpp
     ```
   + Clone with Git: SSH

     ```
     git clone --recurse-submodules git@github.com:aws/aws-sdk-cpp.git
     ```

1. We recommend you store the generated build files outside of the SDK source directory\. Create a new directory to store the build files in and navigate to that folder\.

   ```
   mkdir sdk_build
   cd sdk_build
   ```

1. Generate the build files by running `cmake`\. Specify on the `cmake` command line whether to build a *Debug* or *Release* version\. Choose `Debug` throughout this procedure to run a debug configuration of your application code\. Choose `Release` throughout this procedure to run a release configuration of your application code\. Command syntax: 

   `{path to cmake if not in PATH} {path to source location of aws-sdk-cpp} -DCMAKE_BUILD_TYPE=[Debug | Release]`

   For more ways to modify the build output, see [CMake Parameters](cmake-params.md)\.

   To generate the build files, do one of the following:
   + **Generate build files \(all AWS services\)**: To build the entire SDK, run cmake, specifying whether to build a *Debug* or *Release* version\. For example:

     ```
     "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" "..\aws-sdk-cpp" -DCMAKE_BUILD_TYPE=Debug
     ```

     
   + **Generate build files \(subset AWS services\)**: To build only a particular service or services package\(s\) for the SDK, add the CMake [BUILD\_ONLY](cmake-params.md#cmake-build-only) parameter\. The following example builds only the Amazon S3 service package:

     ```
     cmake ..\aws-sdk-cpp -DCMAKE_BUILD_TYPE=Debug -DBUILD_ONLY="s3"
     ```
   + **Generate build files \(with curl\)**: After completing the curl prerequisites, three additional cmake command line options are required to include curl support in the SDK: [FORCE\_CURL](cmake-params.md#cmake-force-curl), [CURL\_INCLUDE\_DIR](cmake-params.md#cmake-curl-include-dir), and [CURL\_LIBRARY](cmake-params.md#cmake-curl-library)\. For example: 

     ```
     cmake ..\aws-sdk-cpp -DCMAKE_BUILD_TYPE=Debug -DFORCE_CURL=ON -DCURL_INCLUDE_DIR='C:/curl/include'
           -DCURL_LIBRARY='C:/curl/lib/libcurl.dll.a'
     ```
**Note**  
If you get an error Failed to build third\-party libraries, check your version of CMake by running **cmake \-\-version**\. You must use CMake minimum version 3\.2, maximum version 3\.21\. 

1. Build the SDK binaries\. If you’re building the entire SDK, this step can take one hour or longer\. Command syntax: 

   `{path to MSBuild if not in PATH} ALL_BUILD.vcxproj -p:Configuration=[Debug | Release]`

   ```
   "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" ALL_BUILD.vcxproj  -p:Configuration=Debug
   ```
**Note**  
If you encounter the error The code execution cannot proceed \.\.\. dll not found\. Reinstalling the program may fix this problem\.", retry the `cmake` command again\.

1. Open a command prompt with administrator privileges to install the SDK\. This command installs the SDK in `\Program Files (x86)\aws-cpp-sdk-all\`\. Command syntax: 

   `msbuild INSTALL.vcxproj -p:Configuration=[Debug | Release]`

   ```
   msbuild INSTALL.vcxproj -p:Configuration=Debug
   ```

## Building for Android on Windows<a name="building-for-android"></a>

To build for Android, add `-DTARGET_ARCH=ANDROID` to your `cmake` command line\. The AWS SDK for C\+\+ includes a CMake toolchain file that includes what you need by referencing the appropriate environment variables \(`ANDROID_NDK`\)\.

To build the SDK for Android on Windows, you need to run `cmake` from a Visual Studio \(2015 or later\) developer command prompt\. You’ll also need NMAKE [NMAKE](https://docs.microsoft.com/en-us/cpp/build/reference/nmake-reference?view=msvc-160)installed and the commands ** `git` ** and ** `patch` ** in your path\. If you have git installed on a Windows system, you’ll most likely find ** `patch` ** in a sibling directory \(`.../Git/usr/bin/`\)\. Once you’ve verified these requirements, your `cmake` command line will change slightly to use NMAKE\.

```
cmake -G "NMake Makefiles" `-DTARGET_ARCH=ANDROID` <other options> ..
```

NMAKE builds serially\. To build more quickly, we recommend you install JOM as an alternative to NMAKE, and then change the `cmake` invocation as follows:

```
cmake -G "NMake Makefiles JOM" `-DTARGET_ARCH=ANDROID` <other options> ..
```

For an example application, see [Setting up an Android application with AWS SDK for C\+\+](https://aws.amazon.com/blogs/developer/setting-up-an-android-application-with-aws-sdk-for-c/)