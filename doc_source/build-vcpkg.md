# "Hello S3" app<a name="build-vcpkg"></a>

This example reports the Amazon S3 buckets you own\. Having an Amazon S3 bucket in your AWS account is not required for this example, but it will be far more interesting if you have at least one\. See [Create a Bucket](https://docs.aws.amazon.com/AmazonS3/latest/userguide/creating-bucket.html) in the *Amazon Simple Storage Service Console User Guide* if you don't already have one\.

You can use any IDE or C\+\+ tools to build your program\. This tutorial shows how to use Visual Studio, but it is not required for vcpkg\.

This example consists of one source file \(`main.cpp`\) and one `CMakeLists.txt` file\. The program uses Amazon S3 to report storage bucket information\.

**To create and run the application**

1. In Visual Studio, choose **Create New Project** and then choose **CMake Project**\.

1. Remove the generated \*\.cpp and \*\.h files that are created with the solution\.

1. Add a `main.cpp` file that includes the following code, which reports the Amazon S3 buckets you own\.

   ```
   #include <aws/core/Aws.h>
   #include <aws/core/utils/logging/LogLevel.h>
   #include <aws/s3/S3Client.h>
   #include <iostream>
   
   using namespace Aws;
   
   int main()
   {
       //The Aws::SDKOptions struct contains SDK configuration options.
       //An instance of Aws::SDKOptions is passed to the Aws::InitAPI and 
       //Aws::ShutdownAPI methods.  The same instance should be sent to both methods.
       SDKOptions options;
       options.loggingOptions.logLevel = Utils::Logging::LogLevel::Debug;
       
       //The AWS SDK for C++ must be initialized by calling Aws::InitAPI.
       InitAPI(options); 
       {
           S3::S3Client client;
   
           auto outcome = client.ListBuckets();
           if (outcome.IsSuccess()) {
               std::cout << "Found " << outcome.GetResult().GetBuckets().size() << " buckets\n";
               for (auto&& b : outcome.GetResult().GetBuckets()) {
                   std::cout << b.GetName() << std::endl;
               }
           }
           else {
               std::cout << "Failed with error: " << outcome.GetError() << std::endl;
           }
       }
   
       //Before the application terminates, the SDK must be shut down. 
       ShutdownAPI(options);
       return 0;
   }
   ```

1. Add a `CMakeLists.txt` file that specifies your project’s name, executables, source files, and linked libraries\. 

   ```
   # Minimal CMakeLists.txt for the AWS SDK for C++.
   cmake_minimum_required(VERSION 3.3)
   set(CMAKE_CXX_STANDARD 11)
   project(app LANGUAGES CXX)
   
   # Use shared libraries
   set(BUILD_SHARED_LIBS ON CACHE STRING "Link to shared libraries by default.")
   
   #Include in any AWS service packages your code will be using by service name
   find_package(AWSSDK REQUIRED COMPONENTS s3)
   add_executable(${PROJECT_NAME} "main.cpp") #add app's main sourcefile
   
   set_compiler_flags(${PROJECT_NAME})
   set_compiler_warnings(${PROJECT_NAME})
   target_link_libraries(${PROJECT_NAME} ${AWSSDK_LINK_LIBRARIES})
   ```

1. For the build configuration \(e\.g\. Debug vs\. Release\) in the toolbar, choose **Manage Configurations**\. This adds a `CMakeSettings.json` to your project\.

1. On the **CmakeSettings\.json** tab, choose **Configurations**, and add or choose the configuration that matches the SDK executables installed during the vcpkg installation step\. The output of the prior vcpkg install indicates the configuration \(like *x86\-windows*\)\.

1. On the **CmakeSettings\.json** tab, in the **General** section, for **CMake toolchain file** enter the CMAKE\_TOOLCHAIN\_FILE path obtained from the prior vcpkg install output\.

1. On either `CMakeLists.txt` and `CMakeSettings.json`, choose **Save**\. Saving either of these files automatically runs the CMake generation for your build configuration\. 

1. Confirm that CMake set up successfully by verifying that the last output is **CMake generation finished\.**

1. \(Optional\) If you have not already set up your AWS credentials in your environment, you can use the **AWS Explorer** within Visual Studio to load a **New Account Profile** based on your downloaded credentials file\. See [Adding a profile to the SDK Credential Store](https://docs.aws.amazon.com/toolkit-for-visual-studio/latest/user-guide/credentials.html) in the *AWS Toolkit for Visual Studio User Guide*\.

1. Open `main.cpp` so that it is your active tab\. 

1. Choose **Run**\.

    Visual Studio uses CMake to use the information in `CMakeLists.txt` and `CMakeSettings.json` to build an executable program\. 

1. Confirm that the console output lists the total number of Amazon S3 buckets and the name of each bucket\.

For additional examples using the AWS SDK for C\+\+, see [ AWS SDK for C\+\+ code examples](programming-services.md)\.