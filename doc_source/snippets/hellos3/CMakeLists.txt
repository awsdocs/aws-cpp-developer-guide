cmake_minimum_required(VERSION 2.8)
project(hellos3)

# This will locate the aws sdk for c++ package so that we can use its targets
find_package(aws-sdk-cpp)

add_executable(hellos3 hellos3.cpp)

# Since we called find_package(), this will resolve all dependencies, header
# files, and cflags necessary #to build and link your executable.
target_link_libraries(hellos3 aws-cpp-sdk-s3)
