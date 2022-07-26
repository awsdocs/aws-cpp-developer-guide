# Building the AWS SDK for C\+\+ on Linux/macOS<a name="setup-linux"></a>

To set up the AWS SDK for C\+\+, you can either build the SDK yourself directly from the source or download the libraries using a package manager\.



The SDK source is separated into individual packages by service\. Installing the entire SDK can take up to an hour\. Installing only the specific subset of services that your program uses decreases installation time and also reduces size on disk\. To choose which services to install, you need to know the package name of each service your program uses\. You can see the list of package directories at [https://github.com/aws/aws-sdk-cpp](https://github.com/aws/aws-sdk-cpp) on GitHub\. The package name is the suffix of the directory name for the service\. 

```
aws-sdk-cpp\aws-cpp-sdk-<packageName>   # Repo directory name and packageName
aws-sdk-cpp\aws-cpp-sdk-s3              # Example: Package name is s3
```

## Prerequisites<a name="prerequisites"></a>

You need a minimum of 4 GB of RAM to build some of the larger AWS clients\. The SDK might fail to build on Amazon EC2 instance types *t2\.micro*, *t2\.small*, and other small instance types due to insufficient memory\.

To use the AWS SDK for C\+\+, you need one of the following:
+  GNU Compiler Collection \(GCC\) 4\.9 or later, or
+  Clang 3\.3 or later\.

## Additional Requirements for Linux Systems<a name="additional-requirements-for-linux-systems"></a>

You must have the header files \(`-dev` packages\) for `libcurl`, `libopenssl`, `libuuid`, `zlib`, and, optionally, `libpulse` for Amazon Polly support\. You can find the packages by using your system’s package manager\.

**To install the packages on *Debian/Ubuntu\-based systems***
+ 

  ```
  sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev
  ```

**To install the packages on *Amazon Linux/Redhat/Fedora/CentOS\-based systems***
+ 

  ```
  sudo yum install libcurl-devel openssl-devel libuuid-devel pulseaudio-libs-devel
  ```

## Building the SDK from Source<a name="setup-linux-from-source"></a>

You can build the SDK from source using command\-line tools as an alternative to using vcpkg\. Using this method, you can customize your SDK build\. For information about available options, see [CMake Parameters](cmake-params.md)\.

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

   `{path to cmake if not in PATH} {path to source location of aws-sdk-cpp} -DCMAKE_BUILD_TYPE=[Debug | Release] -DCMAKE_PREFIX_PATH={path to install} -DCMAKE_INSTALL_PREFIX={path to install}`

   For more ways to modify the build output, see [CMake Parameters](cmake-params.md)\.

   To generate the build files, do one of the following:
   + **Generate build files \(all AWS services\)**: To build the entire SDK, run cmake, specifying whether to build a *Debug* or *Release* version\. For example:

     ```
     cmake ../aws-sdk-cpp -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/usr/local/ -DCMAKE_INSTALL_PREFIX=/usr/local/
     ```

     
   + **Generate build files \(subset AWS services\)**: To build only a particular service or services package\(s\) for the SDK, add the CMake [BUILD\_ONLY](cmake-params.md#cmake-build-only) parameter\. The following example builds only the Amazon S3 service package:

     ```
     cmake ../aws-sdk-cpp -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/usr/local/ -DCMAKE_INSTALL_PREFIX=/usr/local/ -DBUILD_ONLY="s3"
     ```
**Note**  
If you get an error Failed to build third\-party libraries, check your version of CMake by running **cmake \-\-version**\. You must use CMake minimum version 3\.2, maximum version 3\.21\. 

1. Build the SDK binaries\. If you’re building the entire SDK, the operation can take one hour or longer\. 

   ```
   make
   ```

1. Install the SDK\. You may need to escalate privileges depending on the location you chose to install to\.

   ```
   make install
   ```

## Building for Android on Linux<a name="building-for-android"></a>

To build for Android, add `-DTARGET_ARCH=ANDROID` to your `cmake` command line\. The AWS SDK for C\+\+ includes a CMake toolchain file that includes what you need by referencing the appropriate environment variables \(`ANDROID_NDK`\)\. For an example application, see [Setting up an Android application with AWS SDK for C\+\+](https://aws.amazon.com/blogs/developer/setting-up-an-android-application-with-aws-sdk-for-c/)