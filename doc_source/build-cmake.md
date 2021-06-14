# "Hello S3" app<a name="build-cmake"></a>

 [CMake](https://cmake.org/) is a build tool that you use to manage your application’s dependencies and to create makefiles suitable for the platform you’re building on\. You can use CMake to create and build projects using the AWS SDK for C\+\+\.

This example reports the Amazon S3 buckets you own\. Having an Amazon S3 bucket in your AWS account is not required for this example, but it will be far more interesting if you have at least one\. See [Create a Bucket](https://docs.aws.amazon.com/AmazonS3/latest/userguide/creating-bucket.html) in the *Amazon Simple Storage Service Console User Guide* if you don't already have one\.

## Step 1: Write the code<a name="setting-up-a-cmake-project"></a>

This example consists of one folder containing one source file \(`main.cpp`\) and one `CMakeLists.txt` file\. The program uses Amazon S3 to report storage bucket information\.

You can set many options in a `CMakeLists.txt` build configuration file\. For more information, see the [CMake tutorial](https://cmake.org/cmake-tutorial/) on the CMake website\. 

**Note**  
Deep Dive: Setting CMAKE\_PREFIX\_PATH  
By default, the AWS SDK for C\+\+ on macOS, Linux, Android and other non\-Windows platforms is installed into `/usr/local` and on Windows is installed into `\Program Files (x86)\aws-cpp-sdk-all`\.  
CMake needs to know where to find several resources that result from building the SDK \([Windows](setup-windows.md), [Linux/macOS](setup-linux.md)\):  
the file `AWSSDKConfig.cmake` so that it can properly resolve the AWS SDK libraries that your application uses\.
\(for version 1\.8 and earlier\) the location of dependencies: `aws-c-event-stream`, `aws-c-common`, `aws-checksums`

**Note**  
Deep Dive: Runtime Libraries on Windows  
To run your program, several DLLs are required in your program's executable location: `aws-c-common.dll`, `aws-c-event-stream.dll`, `aws-checksums.dll`, `aws-cpp-sdk-core.dll`, as well as any specific DLLs based on the components of your program \(this example uses Amazon S3 and so also requires `aws-cpp-sdk-s3`\)\. If these DLLs are not in the executable location then runtime exceptions of 'file not found' occur\. The second `if` statement in the CMakeLists\.txt file copies these libraries from the installation location to the executable location to satisfy this requirement\.   
`AWSSDK_CPY_DYN_LIBS` is a macro defined by AWS SDK for C\+\+ that copies the SDK's DLLs from the installation location to the executable location of your program\. Review the two `AWSSDK_CPY_DYN_LIBS` lines and CHOOSE which pattern is accurate for your build environment\.

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

**To create the folder and source files**

1. Create a directory to hold your source files\.
**Note**  
This example can also be completed in Visual Studio: choose **Create New Project** and then choose **CMake Project**\.

1. Within that folder, add a `main.cpp` file that includes the following code, which reports the Amazon S3 buckets you own\.

1. Add a `CMakeLists.txt` file that specifies your project’s name, executables, source files, and linked libraries\. 

   ```
   cmake_minimum_required(VERSION 3.3)
   set(CMAKE_CXX_STANDARD 11)
   project(app LANGUAGES CXX)
   
   #Set the location of where Windows can find the installed libraries of the SDK.
   if(MSVC)
       string(REPLACE ";" "/aws-cpp-sdk-all;" SYSTEM_MODULE_PATH "${CMAKE_SYSTEM_PREFIX_PATH}/aws-cpp-sdk-all")
       list(APPEND CMAKE_PREFIX_PATH ${SYSTEM_MODULE_PATH})
   endif()
   
   message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
   set(BUILD_SHARED_LIBS ON CACHE STRING "Link to shared libraries by default.")
   
   #Load required services/packages: This basic example uses S3.
   find_package(AWSSDK REQUIRED COMPONENTS s3)
   add_executable(${PROJECT_NAME} "main.cpp") #Add app's main starting file.
   
   #Windows: This 'if' clause copies the SDK libraries from the installation location to the place where 
   #  this project's executable is located.  Without this you'll need to copy the install 
   #  /bin folder to the exe location (app.exe in this case) to prevent runtime errors.
   if(MSVC AND BUILD_SHARED_LIBS)
       target_compile_definitions(${PROJECT_NAME} PUBLIC "USE_IMPORT_EXPORT")
       add_definitions(-DUSE_IMPORT_EXPORT)
       # Copy relevant AWS SDK for C++ libraries into the current binary directory for running and debugging.
       list(APPEND SERVICE_LIST s3)
      
       #For IDE's like Xcode and Visual Studio this line will be ignored because Release/Debug 
       #  is switched internally, but this is necessary for non-IDE builds.
       set(CMAKE_BUILD_TYPE Debug) #TODO: Set to your build type
   	
       #TODO:Choose appropriate one of the following two lines, you want to copy to the same folder where your executables are.
       AWSSDK_CPY_DYN_LIBS(SERVICE_LIST "" ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})  #Choose this line if your executables are in /build/Debug
       #AWSSDK_CPY_DYN_LIBS(SERVICE_LIST "" ${CMAKE_CURRENT_BINARY_DIR})  #Choose this line for Visual Studio and possibly other IDEs
       
       message(STATUS ">>CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
       message(STATUS ">>CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
       message(STATUS ">>EXECUTABLE_OUTPUT_PATH : ${EXECUTABLE_OUTPUT_PATH}")
   endif()
   
   set_compiler_flags(${PROJECT_NAME})
   set_compiler_warnings(${PROJECT_NAME})
   target_link_libraries(${PROJECT_NAME} ${AWSSDK_LINK_LIBRARIES})
   ```

## Step 2: Build with CMake<a name="building-with-cmake"></a>

CMake uses the information in `CMakeLists.txt` to build an executable program\.

**To build the application**

1. Create a directory where ** `cmake` ** will build your application\.

   ```
   mkdir my_project_build
   ```

1. Change to the build directory and run ** `cmake` ** using the path to your project’s source directory\.

   ```
   cd my_project_build
   cmake ../
   ```

1. After ** `cmake` ** generates your build directory, you can use ** `make` ** \(or ** `nmake` ** on Windows\), or MSBUILD \(`"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" ALL_BUILD.vcxproj`\) to build your application\.

## Step 3: Run<a name="run-app"></a>

When you run this application, it displays console output that lists the total number of Amazon S3 buckets and the name of each bucket\.

**To run the program**

1. Change to the Debug directory where the result of the build was generated\. In this example, `app.exe` is in folder `my_project_build\Debug`\. 

   ```
   cd Debug
   ```

1. Run the program using the name of the executable\.

   ```
   app
   ```

For additional examples using the AWS SDK for C\+\+, see [ AWS SDK for C\+\+ code examples](programming-services.md)\.