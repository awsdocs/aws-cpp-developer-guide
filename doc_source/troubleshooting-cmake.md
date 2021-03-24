# Troubleshooting Build Issues<a name="troubleshooting-cmake"></a>

**Topics**
+ [CMake Error: Could not find a package configuration file provided by "AWSSDK"](#could-not-find-package)
+ [CMake Error: Could not find load file](#could-not-load-file)
+ [Runtime Error: cannot proceed because X\.dll was not found](#dll-was-not-found)

## CMake Error: Could not find a package configuration file provided by "AWSSDK"<a name="could-not-find-package"></a>

CMake raises the following errorif it cannot find the installed SDK\.

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

To resolve this error, tell CMake where to find the installed SDK \(e\.g\. the folder that was generated as a result of the SDK install \([Windows](setup-windows.md), [Linux/macOS](setup-linux.md)\)\. Insert the following command before your first call to `find_package()` in your `CMakeLists.txt` file\. See [ "Hello S3" App](build-cmake.md) for an example\. 

```
list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\cmake")
```

## CMake Error: Could not find load file<a name="could-not-load-file"></a>

CMake raises the following error if it cannot find the installed SDK\.

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

To resolve this error, tell CMake where to find the installed SDK \(e\.g\. the folder that was generated as a result of the SDK install \([Windows](setup-windows.md), [Linux/macOS](setup-linux.md)\)\. Insert the following commands before your first call to `find_package()` in your `CMakeLists.txt` file\. See [ "Hello S3" App](build-cmake.md) for an example\. 

```
list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\aws-c-event-stream\\cmake")
list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\aws-c-common\\cmake")
list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\aws-checksums\\cmake")
```

## Runtime Error: cannot proceed because X\.dll was not found<a name="dll-was-not-found"></a>

CMake raises the following error if it cannot find a required DLL\.

```
The code execution cannot proceed because aws-cpp-sdk-[dynamodb].dll was not found. Reinstalling the program may fix this problem.
```

To resolve this error, copy the SDK build output in your executable location\. The specific DLL filename of the error will vary depending on which AWS services you are using\. Do one of the following:
+ Copy the contents of the `/bin` folder of the AWS SDK for C\+\+ install to your application's build folder\.
+ Add a call to `AWSSDK_CPY_DYN_LIBS(SERVICE_LIST "" ${CMAKE_CURRENT_BINARY_DIR})` or `AWSSDK_CPY_DYN_LIBS(SERVICE_LIST "" ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})` to your `CMakeLists.txt` file to use this macro to do the copying for you\. See [ "Hello S3" App](build-cmake.md) for an example\.