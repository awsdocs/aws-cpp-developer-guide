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

## Building the SDK from source<a name="setup-windows-from-source"></a>

You can build the SDK from source using command\-line tools\. Using this method, you can customize your SDK build\. For information about available options, see [CMake Parameters](cmake-params.md)\. There are three main steps\. First, you build the files using CMake\. Second, you use MSBuild to build the SDK binaries that work with your operating system and build toolchain\. Third, you install or copy the binaries into the correct location on the development machine\.

**To build the SDK from source**

1. Install [CMake](https://cmake.org/) \(*minimum version 3\.2; maximum version 3\.18*\) and the relevant build tools for your platform\. It is recommended to add `cmake` to your `PATH`\. To check your version of CMake, open a command prompt and run command **cmake \-\-version**

1. In a command prompt, navigate to a folder where you want to store the SDK\. This example uses a folder called `CodeRepos`\.

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

1. We recommend you store the generated build files outside of the SDK source directory\. Create a new directory to store the build files in\.

   ```
   mkdir sdk_build
   ```

1. Navigate to the newly created build folder\. Generate the build files by running `cmake`\. Specify on the `cmake` command line whether to build a *Debug* or *Release* version\. 

   To generate the build files, do one of the following:
   +  To build the entire SDK, run cmake, specifying whether to build a *Debug* or *Release* version\. Command syntax: 

     `{path to cmake if not in PATH} {path to source location of aws-sdk-cpp} -DCMAKE_BUILD_TYPE=[Debug | Release]`

     ```
     cd sdk_build
     "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" "C:\CodeRepos\aws-sdk-cpp\build\aws-sdk-cpp" -DCMAKE_BUILD_TYPE=Debug
     ```

     
   + To build only a particular service package, add the CMake *BUILD\_ONLY* parameter\. The following example builds only the Amazon S3 service package\. For more ways to modify the build output, see [CMake Parameters](cmake-params.md)\.

     ```
     cmake ..\aws-sdk-cpp -DCMAKE_BUILD_TYPE=[Debug | Release] -DBUILD_ONLY="s3"
     ```
**Note**  
If you get an error Failed to build third\-party libraries, check your version of CMake by running **cmake \-\-version**\. You must use CMake minimum version 3\.2, maximum version 3\.18\. 

1. Build the SDK binaries\. If you’re building the entire SDK, this step can take one hour or longer\. Command syntax: 

   `{path to MSBuild if not in PATH} ALL_BUILD.vcxproj`

   ```
   "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" ALL_BUILD.vcxproj  -p:Configuration=[Debug | Release]
   ```

1. If you encounter the error The code execution cannot proceed \.\.\. dll not found\. Reinstalling the program may fix this problem\.", retry the `cmake` command again\.

1. Open a command prompt with administrator privileges to install the SDK\. This command installs the SDK in `\Program Files (x86)\aws-cpp-sdk-all\`\.

   ```
   msbuild INSTALL.vcxproj -p:Configuration=[Debug | Release]
   ```

### Building for Android on Windows<a name="building-for-android"></a>

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