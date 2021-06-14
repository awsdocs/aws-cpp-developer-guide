# Troubleshooting build issues<a name="troubleshooting-cmake"></a>

**Topics**
+ [CMake Error: Could not find a package configuration file provided by "AWSSDK"](#could-not-find-package)
+ [CMake Error: Could not find load file \(and you're on SDK version 1\.8\)](#could-not-load-file)
+ [CMake Error: Could not find load file](#could-not-load-file2)
+ [Runtime Error: cannot proceed because `aws-*.dll` was not found](#dll-was-not-found)

## CMake Error: Could not find a package configuration file provided by "AWSSDK"<a name="could-not-find-package"></a>

CMake raises the following error if it cannot find the installed SDK\.

```
1> [CMake] CMake Error at C:\CodeRepos\CMakeProject1\CMakeLists.txt:4 (find_package):
1> [CMake]   Could not find a package configuration file provided by "AWSSDK" with any
1> [CMake]   of the following names:
1> [CMake] 
1> [CMake]     AWSSDKConfig.cmake
1> [CMake]     awssdk-config.cmake
1> [CMake] 
1> [CMake]   Add the installation prefix of "AWSSDK" to CMAKE_PREFIX_PATH or set
1> [CMake]   "AWSSDK_DIR" to a directory containing one of the above files.  If "AWSSDK"
1> [CMake]   provides a separate development package or SDK, be sure it has been
1> [CMake]   installed.
```

To resolve this error, tell CMake where to find the installed SDK \(e\.g\. the folder that was generated as a result of the SDK install \([Windows](setup-windows.md), [Linux/macOS](setup-linux.md)\)\. Insert the following command before your first call to `find_package()` in your `CMakeLists.txt` file\. See [ "Hello S3" app](build-cmake.md) for an example\. 

```
list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\cmake")
```

## CMake Error: Could not find load file \(and you're on SDK version 1\.8\)<a name="could-not-load-file"></a>

CMake raises the following error if it cannot find the installed libraries\.

```
1> [CMake]   include could not find load file:
1> [CMake] 
1> [CMake]     C:/Program Files (x86)/aws-cpp-sdk-all/lib/aws-c-common/cmake/static/aws-c-common-targets.cmake

1> [CMake]   include could not find load file:
1> [CMake] 
1> [CMake]     C:/Program Files (x86)/aws-cpp-sdk-all/lib/aws-checksums/cmake/static/aws-checksums-targets.cmake
1> [CMake]   include could not find load file:
1> [CMake] 
1> [CMake]     C:/Program Files (x86)/aws-cpp-sdk-all/lib/aws-checksums/cmake/static/aws-checksums-targets.cmake
```

To resolve this error, tell CMake where to find the installed SDK \(e\.g\. the folder that was generated as a result of the SDK install \([Windows](setup-windows.md), [Linux/macOS](setup-linux.md)\)\. Insert the following commands before your first call to `find_package()` in your `CMakeLists.txt` file\. See [ "Hello S3" app](build-cmake.md) for an example\. 

```
#Set the location of where Windows can find the installed libraries of the SDK.
if(MSVC)
    string(REPLACE ";" "/aws-cpp-sdk-all;" SYSTEM_MODULE_PATH "${CMAKE_SYSTEM_PREFIX_PATH}/aws-cpp-sdk-all")
    list(APPEND CMAKE_PREFIX_PATH ${SYSTEM_MODULE_PATH})
endif()
```

This solution is only for v1\.8 of the SDK because these dependencies are handled differently in later versions\. Version 1\.9 addresses these issues by introducing an intermediate layer between the `aws-sdk-cpp` and `aws-c-*` libraries\. This new layer is called `aws-crt-cpp` , and is a git submodule of the SDK for C\+\+\. `aws-crt-cpp` also has the `aws-c-*` libraries \(including `aws-c-common`, `aws-checksums`,` aws-c-event-stream`, etc\.\) as its own git submodules\. This allows the SDK for C\+\+ to get all CRT libraries recursively and improves the build process\.

## CMake Error: Could not find load file<a name="could-not-load-file2"></a>

CMake raises the following error if it cannot find the installed libraries\.

```
CMake Error at C:/Program Files (x86)/aws-cpp-sdk-all/lib/aws-c-auth/cmake/aws-c-auth-config.cmake:11 
         (include):  include could not find load file:   
         C:/Program Files (x86)/aws-cpp-sdk-all/lib/aws-c-auth/cmake/static/aws-c-auth-targets.cmake
```

To resolve this error, tell CMake to build shared libraries\. Insert the following command before your first call to `find_package()` in your `CMakeLists.txt` file\. See [ "Hello S3" app](build-cmake.md) for an example\. 

```
set(BUILD_SHARED_LIBS ON CACHE STRING "Link to shared libraries by default.")
```

## Runtime Error: cannot proceed because `aws-*.dll` was not found<a name="dll-was-not-found"></a>

CMake raises an error similar to the following if it cannot find a required DLL\.

```
The code execution cannot proceed because aws-cpp-sdk-[dynamodb].dll was not found. Reinstalling the program may fix this problem.
```

This error occurs because the required libraries or executables for the SDK for C\+\+ are not available in the same folder as your application executables\. To resolve this error, copy the SDK build output in your executable location\. The specific DLL filename of the error will vary depending on which AWS services you are using\. Do *one* of the following:
+ Copy the contents of the `/bin` folder of the AWS SDK for C\+\+ install to your application's build folder\.
+ In your `CMakeLists.txt` file, use macro AWSSDK\_CPY\_DYN\_LIBS to copy these for you\.

  Add a call to either `AWSSDK_CPY_DYN_LIBS(SERVICE_LIST "" ${CMAKE_CURRENT_BINARY_DIR})` or `AWSSDK_CPY_DYN_LIBS(SERVICE_LIST "" ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})` to your `CMakeLists.txt` file to use this macro to do the copying for you\. See [ "Hello S3" app](build-cmake.md) for an example\.

  Choose the correct copy path for your build environment\. Building via command line frequently puts the build output into a subfolder \(`/Debug`\), but Visual Studio and other IDEs often do not\. Verify where your output executables are, and ensure the macro is copying to that location\. When making these types of changes, it is good practice to delete the contents of your build output directory so that you get a clean starting point for the next build\.