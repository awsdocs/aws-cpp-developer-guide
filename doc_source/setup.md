# Setting Up the AWS SDK for C\+\+<a name="setup"></a>

This section presents information about how to set up the AWS SDK for C\+\+ on your development platform\.

## Prerequisites<a name="prerequisites"></a>

To use the AWS SDK for C\+\+, you need:
+ Microsoft Visual Studio 2015 or later
+  *or* GNU Compiler Collection \(GCC\) 4\.9 or later
+  *or* Clang 3\.3 or later
+ A minimum of 4 GB of RAM
**Note**  
You need 4 GB of RAM to build some of the larger AWS clients\. The SDK might fail to build on Amazon EC2 instance types *t2\.micro*, *t2\.small*, and other small instance types due to insufficient memory\.

### Additional Requirements for Linux Systems<a name="additional-requirements-for-linux-systems"></a>

To compile on Linux, you must have the header files \(`-dev` packages\) for `libcurl`, `libopenssl`, `libuuid`, `zlib`, and, optionally, `libpulse` for Amazon Polly support\. The packages are typically found by using the system’s package manager\.

#### To install the packages on *Debian/Ubuntu\-based systems*<a name="w3aab7b9b5b7b5"></a>

```
sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev
```

#### To install the packages on *Redhat/Fedora\-based systems*<a name="w3aab7b9b5b7b7"></a>

```
sudo dnf install libcurl-devel openssl-devel libuuid-devel pulseaudio-devel
```

#### To install the packages on *CentOS\-based systems*<a name="w3aab7b9b5b7b9"></a>

```
sudo yum install libcurl-devel openssl-devel libuuid-devel pulseaudio-libs-devel
```

## Building the SDK from Source<a name="setup-from-source"></a>

If you don’t use Visual Studio \(or don’t want to or can’t use vcpkg or NuGet as described later in this topic\), you can build the SDK from source using command\-line tools\. This method also enables you to customize your SDK build—see [CMake Parameters](cmake-params.md) for the available options\.

**To build the SDK from source**

1. Download or clone the SDK source from [aws/aws\-sdk\-cpp](https://github.com/aws/aws-sdk-cpp) on GitHub\.
   + Direct download: [aws/aws\-sdk\-cpp/archive/master\.zip](https://github.com/aws/aws-sdk-cpp/archive/master.zip) 
   + Clone with Git:

------
#### [ HTTPS ]

     ```
     git clone https://github.com/aws/aws-sdk-cpp.git
     ```

------
#### [ SSH ]

     ```
     git clone git@github.com:aws/aws-sdk-cpp.git
     ```

------

1. Install [cmake](https://cmake.org/) \(*v3\.2 or later*\) and the relevant build tools for your platform\. Ensure they are available in your `PATH`\.

1. Recommended approach: Store the generated build files outside of the SDK source directory\. Create a new directory to store them in\. Then generate the build files by running cmake\. Specify on the cmake command line whether to build a *Debug* or *Release* version\.

   ```
   sudo mkdir sdk_build
   cd sdk_build
   sudo cmake <path/to/sdk/source> -DCMAKE_BUILD_TYPE=[Debug | Release]
   ```

   Alternatively, create the build files directly in the SDK source directory\.

   ```
   cd <path/to/sdk/source>
   sudo cmake . -DCMAKE_BUILD_TYPE=[Debug | Release]
   ```

   Building the entire SDK can take a while\. To build only a particular service, use the cmake *BUILD\_ONLY* parameter\. The example shown below builds only the Amazon S3 service\. For more ways to modify the build output, see [CMake Parameters](cmake-params.md)\.

   ```
   sudo cmake -DCMAKE_BUILD_TYPE=[Debug | Release] -D BUILD_ONLY="s3"
   ```

1. Build the SDK binaries by running one of the following operating system\-dependent commands\. If you’re building the entire SDK, the operation can take one hour or longer\.

------
#### [ auto make \(Linux/macOS\) ]

   ```
   sudo make
   ```

------
#### [ Visual Studio \(Windows\) ]

   ```
   msbuild ALL_BUILD.vcxproj
   ```

------

1. Install the SDK by running one of the following operating system\-dependent commands\. Administrator privileges required\.

------
#### [ auto make \(Linux/macOS\) ]

   ```
   sudo make install
   ```

------
#### [ Visual Studio \(Windows\) ]

   ```
   rem Run this command in a command shell running in ADMIN mode
   rem The SDK is installed in `\Program Files (x86)\aws-cpp-sdk-all\`
   msbuild INSTALL.vcxproj /p:Configuration=[Debug | Release | "Debug;Release"]
   ```

------

### Building for Android<a name="building-for-android"></a>

To build for Android, add `-DTARGET_ARCH=ANDROID` to your cmake command line\. The AWS SDK for C\+\+ includes a cmake toolchain file that should cover what’s needed, assuming you’ve set the appropriate environment variables \(`ANDROID_NDK`\)\.

#### Android on Windows<a name="android-on-windows"></a>

Building for Android on Windows requires additional setup\. In particular, you have to run cmake from a Visual Studio \(2013 or later\) developer command prompt\. You’ll also need the commands ** `git` ** and ** `patch` ** in your path\. If you have git installed on a Windows system, you’ll most likely find ** `patch` ** in a sibling directory \(`.../Git/usr/bin/`\)\. Once you’ve verified these requirements, your cmake command line will change slightly to use nmake\.:

```
cmake -G "NMake Makefiles" `-DTARGET_ARCH=ANDROID` <other options> ..
```

nmake builds targets in serially\. To make things go more quickly, we recommend installing JOM as an alternative to nmake, and then changing the cmake invocation as follows\.:

```
cmake -G "NMake Makefiles JOM" `-DTARGET_ARCH=ANDROID` <other options> ..
```

### Creating Release Builds<a name="creating-release-builds"></a>

------
#### [ auto make ]

```
cmake -DCMAKE_BUILD_TYPE=Release <path/to/sdk/source>
make
sudo make install
```

------
#### [ Visual Studio ]

```
cmake <path-to-root-of-this-source-code> -G "Visual Studio 12 Win64"
msbuild INSTALL.vcxproj /p:Configuration=Release
```

------

### Running Integration Tests<a name="running-integration-tests"></a>

Several directory names include the suffix `*integration-tests`\. After the project is built, the tests stored in these directories can be run to verify the project’s correct execution\.

## Getting the SDK Using Vcpkg with Visual C\+\+<a name="setup-with-vcpkg"></a>

You can use vcpkg to manage dependencies for AWS SDK for C\+\+ projects that you develop with Microsoft Visual C\+\+\. To use this procedure, you must have [vcpkg](https://github.com/Microsoft/vcpkg) installed on your system\.

**To use the SDK with vcpkg**

1. Open a Windows command prompt and navigate to the vcpkg directory\.

1. Integrate vcpkg into Visual Studio\. You can [integrate](https://docs.microsoft.com/en-us/cpp/vcpkg#installation) per project or per user\. The command line shown below integrates vcpkg for the current user\.

   ```
   vcpkg integrate install
   ```

1. Install the AWS SDK for C\+\+ package\. The package compiles the entire SDK and its dependencies\. It can take a while\.

   ```
   vcpkg install aws-sdk-cpp[*]:x86-windows --recurse
   ```

   To reduce build time, build only the SDK packages needed\. Specify the package names in square brackets\. Also include the SDK *core* package\.

   ```
   vcpkg install aws-sdk-cpp[core,s3,ec2]:x86-windows
   ```

   A package name can be derived from the AWS SDK for C\+\+ repo directory name for the service\.

   ```
   aws-sdk-cpp\aws-cpp-sdk-<packageName>   # Repo directory name and packageName
   aws-sdk-cpp\aws-cpp-sdk-s3              # Example: Package name is s3
   ```

1. Open your project in Visual Studio\.

1. \#include the AWS SDK for C\+\+ header files you want in your source code\.

When you build your project, the correct binaries are automatically included for each runtime/architecture configuration you use\.

## Getting the SDK Using NuGet with Visual C\+\+<a name="setup-with-nuget"></a>

You can use NuGet to manage dependencies for AWS SDK for C\+\+ projects that you develop with Microsoft Visual C\+\+\. To use this procedure, you must have [NuGet](https://www.nuget.org/) installed on your system\.

**Note**  
The following information applies only to AWS SDK for C\+\+ versions 1\.6 and earlier and to Microsoft Visual Studio 2015 and 2017\. For later versions of the AWS SDK for C\+\+ and Visual Studio, choose from the other setup options earlier in this topic\.

**To use the SDK with NuGet**

1. Open your project in Visual Studio\.

1. In **Solution Explorer**, right\-click your project name, and then choose **Manage NuGet Packages**\.

1. Select the packages to use by searching for a particular service or library name\. For example, you could use a search term such as `aws s3 native`\. Or, because AWS SDK for C\+\+ libraries are named consistently, use `AWSSDKCPP-service name ` to add a library for a particular service to your project\.

1. Choose **Install** to install the libraries and add them to your project\.

When you build your project, the correct binaries are automatically included for each runtime/architecture configuration you use — you won’t need to manage these dependencies yourself\.