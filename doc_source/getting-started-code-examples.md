# Getting started with the AWS SDK for C\+\+ code examples<a name="getting-started-code-examples"></a>

## Structure of the code examples<a name="structure"></a>

The [C\+\+ example folder](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code) on Github contains project folders for each AWS service\. Typically, individual \.cpp source files in the folders demonstrate a specific functionality or action for that service\. For example, for Amazon DynamoDB, *getting* an item from the database and *uploading* an item to the database are two different types of action, so there is a separate file for each in the DynamoDB folder: `get_item.cpp` and `put_item.cpp`\. Each \.cpp file contains a `main()` function as an entrypoint to a standalone executable\. The project executables are generated in a folder designated by your build system, and there is one executable file corresponding to each example source file\. The file name of the executable follows the conventions of the platform such as `{name}.exe` or just `{name}` and any custom prefix `CMakeLists.txt` applies such as `run_`\. 

**To run an example functionality**

1. Download the desired code example from the [AWS Code Examples Repository](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code) on GitHub\. 

1. Open a \.cpp file to explore its `main()` function and any called methods\. 

1. Build the project, as demonstrated with the starter example in [Getting started using the AWS SDK for C\+\+](getting-started.md)\. Note that building the project generates each executable for every source file in the project\.

1. Run the executable for the selected functionality\.
   + In a command prompt, run that program using the executable based on the name of the `*.cpp` file\.
   + If you are working within an IDE, choose the `.cpp` file of the functionality you want to demonstrate and select it as the startup option \(or startup object\)\.

### Unit tests<a name="unittest"></a>

Some examples include unit tests\. The unit tests are in the `tests` folder, and there is one test source file for each example source file\. Each test source file builds to its own executable that you can run by using the command line\.

### CMakeLists\.txt file<a name="CMakeLists"></a>

The folder for each service contains a file named `CMakeLists.txt` file\. Many of these files contain a construct similar to the following:

```
foreach(EXAMPLE IN LISTS EXAMPLES)
         add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
         target_link_libraries(${EXAMPLE} aws-cpp-sdk-email aws-cpp-sdk-core)
endforeach()
```

 For each \.cpp file in the folder, the `CMakeLists.txt` file builds an executable \(cmake: `add_executable`\) with a name based on the name of the source code file without the file extension\. 