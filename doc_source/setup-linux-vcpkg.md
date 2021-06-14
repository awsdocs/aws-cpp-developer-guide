# AWS SDK for C\+\+ Setup using vcpkg on Linux/macOS<a name="setup-linux-vcpkg"></a>

To set up the AWS SDK for C\+\+, you can either build the SDK yourself directly from the source or download the libraries using a package manager\.



The SDK source is separated into individual packages by service\. Installing the entire SDK can take up to an hour\. Installing only the specific subset of services that your program uses decreases installation time and also reduces size on disk\. To choose which services to install, you need to know the package name of each service your program uses\. You can see the list of package directories at [aws/aws\-sdk\-cpp](https://github.com/aws/aws-sdk-cpp) on GitHub\. The package name is the suffix of the directory name for the service\. 

```
aws-sdk-cpp\aws-cpp-sdk-<packageName>   # Repo directory name and packageName
aws-sdk-cpp\aws-cpp-sdk-s3              # Example: Package name is s3
```

## Prerequisites<a name="prerequisites"></a>

You need a minimum of 4 GB of RAM to build some of the larger AWS clients\. The SDK might fail to build on Amazon EC2 instance types *t2\.micro*, *t2\.small*, and other small instance types due to insufficient memory\.

To use the AWS SDK for C\+\+, you need one of the following:
+  GNU Compiler Collection \(GCC\) 4\.9 or later, or
+  Clang 3\.3 or later\.

## Getting the SDK Using Vcpkg<a name="setup-linux-vcpkg-with-vcpkg"></a>

You can use the vcpkg package manager to install AWS SDK for C\+\+\. To use this procedure, you must install [vcpkg](https://github.com/Microsoft/vcpkg) on your system\.

**To install AWS SDK for C\+\+ with vcpkg**

1. Download and bootstrap [vcpkg](https://github.com/Microsoft/vcpkg) by following the instructions on the vcpkg GitHub Readme, substituting the following options when prompted:
   + 

     As part of those instructions, you are guided to enter:

     ```
     ./vcpkg/vcpkg install [packages to install]
     ```

     To install the entire SDK, enter `./vcpkg/vcpkg install "aws-sdk-cpp[*]" --recurse` or indicate only specific services of the SDK to install by appending a package name in brackets, for example `./vcpkg/vcpkg install "aws-sdk-cpp[s3, ec2]" --recurse` 
   + Also as part of those instructions, proceed to integrate the build environment you are using, such as `./vcpkg/vcpkg integrate install` if you are using Visual Studio Code, or following the provided alternatives to use CMake, etc\.

   The output displays a messages similar to the following:

   ```
   Applied user-wide integration for this vcpkg root.
   
   CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=/local/home/username/vcpkg/scripts/buildsystems/vcpkg.cmake"
   ```

1. Copy the complete `-DCMAKE_TOOLCHAIN_FILE` command to use for CMake later\. The vcpkg GitHub Readme also describes where to use this for your toolset\.