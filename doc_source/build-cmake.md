# Building Your Application with CMake<a name="build-cmake"></a>

 [CMake](https://cmake.org/) is a build tool that can manage your application’s dependencies and create native makefiles suitable for the platform you’re building on\. It’s an easy way to create and build projects using the AWS SDK for C\+\+\.

## Setting Up a CMake Project<a name="setting-up-a-cmake-project"></a>

**To set up a CMake project for use with the AWS SDK for C\+\+**

1. Create a directory to hold your source files\.

   ```
   mkdir my_example_project
   ```

1. Open the directory and add a `CMakeLists.txt` file that specifies your project’s name, executables, source files, and linked libraries\. The following is a minimal example\.

   ```
   # Minimal CMakeLists.txt for the AWS SDK for C++.
   cmake_minimum_required(VERSION 3.8)
   
   # Use shared libraries, which is the default for the AWS C++ SDK build.
   option(BUILD_SHARED_LIBS "Build shared libraries" ON)
   
   # "my-example" is just an example value.
   project(my-example)
   
   # Locate the AWS SDK for C++ package.
   # "s3" and "cloudtrail" are just example values.
   find_package(AWSSDK REQUIRED COMPONENTS s3 cloudtrail)
   
   # The executable name and its sourcefiles.
   add_executable(my-example my-example.cpp)
   
   # Build using the C++ standard version 11.
   target_compile_features(my-example PUBLIC cxx_std_11)
   
   # The libraries used by your executable.
   target_link_libraries(my-example ${AWSSDK_LINK_LIBRARIES})
   ```

**Note**  
You can set many options in your `CMakeLists.txt` build configuration file\. For an introduction to the file’s features, see the [CMake tutorial](https://cmake.org/cmake-tutorial/) on the CMake website\.

## Setting CMAKE\_PREFIX\_PATH \(Optional\)<a name="setting-cmake-prefix-path-optional"></a>

By default, the AWS SDK for C\+\+ on macOS, Linux, Android and other non\-Windows platforms is installed into `/usr/local` and `Program Files (x86)aws-cpp-sdk-all` on Windows\.

When you install the SDK into a non\-default location, CMake needs to know where to find the file `AWSSDKConfig.cmake` so that it can properly resolve the AWS SDK libraries that your application uses\. You can find this file in the build directory that you used to [build the SDK](setup.md)\.

By adding the path to a list in `CMAKE_PREFIX_PATH`, you won’t need to type this path every time you rebuild your application\.

You can set it on Linux, macOS, or Unix like this\.

```
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/path/to/sdk_install_dir
```

On Windows, use `set` instead\.

```
set CMAKE_PREFIX_PATH=%CMAKE_PREFIX_PATH%;C:\path\to\sdk_install_dir
```

## Building with CMake<a name="building-with-cmake"></a>

Create a directory into which ** `cmake` ** will build your application\.

```
mkdir my_project_build
```

Open the directory and run ** `cmake` ** using the path to your project’s source directory\.

```
cd my_project_build
cmake ../my_example_project
```

If you didn’t set `CMAKE_PREFIX_PATH`, you must add the path to the SDK’s build directory using `-DAWSSDK_DIR`\.

```
cmake -DAWSSDK_DIR=/path/to/sdk_install_dir ../my_example_project
```

After ** `cmake` ** generates your build directory, you can use ** `make` ** \(or ** `nmake` ** on Windows\) to build your application\.

```
make
```