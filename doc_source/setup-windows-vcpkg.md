# AWS SDK for C\+\+ Setup using vcpkg on Windows<a name="setup-windows-vcpkg"></a>

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

## Getting the SDK using vcpkg<a name="setupwin-with-vcpkg"></a>

You can use the vcpkg package manager to access AWS SDK for C\+\+ functionality for your project\. To use this procedure, you must install [vcpkg](https://github.com/Microsoft/vcpkg) on your system\.

There is a delay between when a version is released and when it is available through a package manager\. The most recent version is always available through [installing from source](sdk-from-source.md)\.

**To install AWS SDK for C\+\+ with vcpkg**

1. Download and bootstrap [vcpkg](https://github.com/Microsoft/vcpkg) by following the instructions on the vcpkg GitHub Readme, substituting the following options when prompted:
   + 

     As part of those instructions, you are guided to enter:

     ```
     .\vcpkg\vcpkg install [packages to install]
     ```

     To install the entire SDK, enter `.\vcpkg\vcpkg install "aws-sdk-cpp[*]" --recurse` or indicate only specific services of the SDK to install by appending a package name in brackets, for example, `.\vcpkg\vcpkg install "aws-sdk-cpp[s3, ec2]" --recurse` 
   + Also as part of those instructions, proceed to integrate with whatever build environment you are using, such as `.\vcpkg\vcpkg integrate install` if you are using Visual Studio, or following the provided alternatives to use CMake, etc\.

   The output displays a messages similar to the following:

   ```
   All MSBuild C++ projects can now #include any installed libraries.
   Linking will be handled automatically.
   Installing new libraries will make them instantly available.
   
   CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake"
   ```

1. Copy the complete `-DCMAKE_TOOLCHAIN_FILE` command to use for CMake later\. The vcpkg GitHub Readme also instructs on where to use this for your toolset\.

1. You'll also need to note the build configuration type that you installed via vcpkg\. The console output shows the build configuration and the version of the SDK\.

   ```
   The following packages will be built and installed:
       aws-sdk-cpp[core,dynamodb,kinesis,s3]:x86-windows -> 1.8.126#6
   ```

This example output indicates the build configuration is "x86\-windows" and the AWS SDK for C\+\+ version installed is 1\.8\.