# Getting started using the AWS SDK for C\+\+<a name="getting-started"></a>

AWS SDK for C\+\+ is a modularized, cross\-platform, open\-source library you can use to connect to Amazon Web Services\.

The AWS SDK for C\+\+ uses [CMake](https://cmake.org/) to support multiple platforms over multiple domains, including video games, systems, mobile, and embedded devices\. CMake is a build tool that you can use to manage your application’s dependencies and to create makefiles suitable for the platform you’re building on\. CMake removes the parts of the build that are not used for your platform or application\.

Before you run code to access AWS resources, you must establish your AWS user credentials in your environment\. 
+  [ Providing AWS credentials](credentials.md)

To use the AWS SDK for C\+\+ in your code, obtain the SDK executables by building the SDK source directly or by using a package manager\.
+  [ Getting the AWS SDK for C\+\+ from source code](sdk-from-source.md)
+  [ Getting the AWS SDK for C\+\+ from a package manager](sdk-from-pm.md)

If you run into build issues regarding CMake, see [Troubleshooting build issues](troubleshooting-cmake.md)\.