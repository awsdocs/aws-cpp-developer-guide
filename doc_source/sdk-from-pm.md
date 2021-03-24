# Getting the AWS SDK for C\+\+ from a Package Manager<a name="sdk-from-pm"></a>

You can use the AWS SDK for C\+\+ in from your code by using a package manager to install the SDK\. The correct binaries are automatically included for each runtime/architecture configuration you use — you don’t need to manage these dependencies yourself\. 

Each package manager is independent and controls its own availability of versions\. There is a delay between when a version is released and when it is available through a package manager\. The most recent version is always available through [installing from source](sdk-from-source.md)\.

[vcpkg](https://github.com/Microsoft/vcpkg) is the supported package manager\. Nuget is no longer being updated with new versions and only provides up to version 1\.6 of the AWS SDK for C\+\+\.

## Getting the SDK using Vcpkg<a name="sdk-from-pm-vcpkg"></a>

Vcpkg is the recommended package manager\. You can use the vcpkg package manager to access AWS SDK for C\+\+ functionality for your project\. See instructions for:
+ [Installing vcpkg on Windows](setup-windows-vcpkg.md)
+ [Installing vcpkg on Linux/macOS](setup-linux-vcpkg.md)

Then you can create a simple application to use it:
+ ["Hello, S3\!" Starter Application](build-vcpkg.md)

## Getting the SDK using NuGet \(deprecated\)<a name="setupwin-with-nuget"></a>

**Important**  
You can only use NuGet to install AWS SDK for C\+\+ versions 1\.6 and earlier with Microsoft Visual Studio 2015 and 2017\.   
To install later versions, vcpkg is the recommended package manager\. For more information, see TBD\.

For AWS SDK for C\+\+ versions 1\.6 and earlier, and for Microsoft Visual Studio 2015 and 2017, you can use NuGet to manage dependencies for AWS SDK for C\+\+ projects that you develop with Microsoft Visual C\+\+\. To use this procedure, first install [NuGet](https://www.nuget.org/)

**To install the SDK with NuGet**

1. In Visual Studio, open your project\.

1. In **Solution Explorer**, right\-click your project name, and then choose **Manage NuGet Packages**\.

1. Select the packages to use by searching for a particular service or library name\. For example, you could use a search term such as `aws s3 native`\. Use the search term `AWSSDKCPP-service name ` to find a library for a particular service to your project\.

1. Choose **Install** to install the libraries and add them to your project\.