# Getting started with the AWS SDK for C\+\+ code examples<a name="getting-started-code-examples"></a>

## Structure of the code examples<a name="structure"></a>

The [C\+\+ example folder](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code) on Github contains project folders for each AWS service\. Typically, individual \.cpp source files in the folders demonstrate a specific functionality or action for that service\. For example, for Amazon DynamoDB, *getting* an item from the database and *uploading* an item to the database are two different types of action, so there is a separate file for each in the DynamoDB folder: `get_item.cpp` and `put_item.cpp`\. Each \.cpp file contains a `main()` function as an entrypoint to a standalone executable\. The project executables are generated in a folder designated by your build system, and there is one executable file corresponding to each example source file\. The file name of the executable follows the conventions of the platform such as `{name}.exe` or just `{name}` and any custom prefix `CMakeLists.txt` applies such as `run_`\. 

**To run an example functionality**

1. Download the desired code example from the [AWS Code Examples Repository](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code) on GitHub\. 

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

## Using AWS for troubleshooting and diagnostics<a name="using-tools"></a>

As you learn to develop applications with the AWS SDK for C\+\+, it's also valuable to get comfortable in using both the AWS Management Console and the AWS CLI\. These tools can be used interchangeably for various troubleshooting and diagnostics \.

The following tutorial shows you an example of these troubleshooting and diagnostics tasks\. It focuses on the `Access denied` error, which can be encountered for several different reasons\. The tutorial shows an example of how you might determine the actual cause of the error\. It focuses on two of the possible causes: incorrect permissions for the current user and a resource that isn't available to the current user\.

**To get the project source and executables**

1. Download the Amazon S3 code example folder from [AWS Code Examples Repository](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code) on GitHub\. 

1. Open `delete_bucket.cpp` and notice that there are two methods: `main()` and `DeleteBucket()`\. `DeleteBucket()` uses the SDK to delete the bucket\. 

1. Also notice that there are two "TODO" blocks with instructions for updating the code\. Do **NOT** perform these updates yet; they will be performed later in the tutorial\.

1. Build the Amazon S3 example, using the same build steps explained in [Getting started using the AWS SDK for C\+\+](getting-started.md)\. The build process generates an executable for each source file\.

1. Open a command prompt to the folder where your build system generated your build executables\. Run the executable `run_create_bucket` \(your actual executable filename will differ based on your operating system\)\. This creates a bucket in your account \(so that you have one to delete\)\. 

1. In the command prompt, run the executable `run_delete_bucket`\. 

1. Confirm that you get an Access Denied error message\. *Getting an Access Denied error message leads you to question whether you created a user with full permissions for Amazon S3, which you'll verify next\.*

**To install the AWS CLI and find the **username** that is making calls to AWS**

1. To install the latest AWS CLI to your development machine, see [Installing the AWS CLI](https://docs.aws.amazon.com/https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-install.html) in the *AWS Command Line Interface User Guide*\.

1. To verify the AWS CLI is working, open a command prompt and run command `aws -\-version`

   ```
   $ aws -\-version
   aws-cli/2.1.29 Python/3.8.8 Windows/10 exe/AMD64 prompt/off
   ```

1. To obtain the username that is actually making the calls to AWS, run the AWS CLI command `aws sts get-caller-identity`\. In the following example output, that username is *userX*

   ```
   $ aws sts get-caller-identity
   {
       "UserId": "A12BCD34E5FGHI6JKLM",
       "Account": "1234567890987",
       "Arn": "arn:aws:iam::1234567890987:user/userX"
   }
   ```

   There are many ways to specify credentials, but if you followed the approach in [ Providing AWS credentials](credentials.md) then this username comes from your AWS shared credentials file\. During that procedure you granted your user **AmazonS3FullAccess** permissions\.
**Note**  
Generally, most AWS CLI commands follow the syntax structure of:  

   ```
   $ aws <command> <subcommand> [options and parameters]
   ```
where *command* is the service, and *subcommand* is the method being called on that service\. For more details, see [Command structure in the AWS CLI](https://docs.aws.amazon.com/cli/latest/userguide/cli-usage-commandstructure.html) in the *AWS Command Line Interface User Guide*\.

**To verify whether a user has permission to delete a bucket**

1. Open the [AWS Management Console](https://console.aws.amazon.com/) and log in\. For more details, see [Getting Started with the AWS Management Console](https://docs.aws.amazon.com/awsconsolehelpdocs/latest/gsg/getting-started.html)\. 

1. In the main navigation bar, for **Search for services\.\.\.**, enter **IAM** and select the IAM service from the results\.

1. From the **Dashboard** sidebar, or under **IAM Resources**, select **Users**\.

1. From the table of users available for your account, select the username obtained in the preceding procedure\.

1. Choose the **Permissions** tab of the **Summary** page, under the **Policy name** table, select **AmazonS3FullAccess**\.

1. Look at the **Policy summary** and the JSON data\. Verify that this user has full rights for the Amazon S3 service\.

   ```
               "Effect": "Allow",
               "Action": "s3:*",
               "Resource": "*"
   ```

This process of elimination is common in ruling *out* where the problem might be\. In this case, you've veriﬁed that the user does have the correct permissions, so the problem must be something else\. That is, since you have the correct permissions to access your buckets, the Access Denied error may mean that you are trying to access a bucket that isn't yours\. Next, review the bucket name in the code, which is "my\-bucket"\. Notice that a bucket with that name doesn't exist in your account, and thus, you cannot 'access' it\. 

**To update the code example so it runs successfully**

1. Back in `delete_bucket.cpp`'s `main()` function, change the Region, using the enum, to the Region of your account\. To find your Region of your account, log into the AWS Management Console, and locate the Region in the upper right\-hand corner\. Also in `main()`, change the bucket name to a bucket that **does** exist in your account\. There are several ways to find your current bucket names:
   + You can use the `run_list_buckets` executable that also exists in this code example's folder to programatically get the names of your buckets\.
   + Alternatively, you can also use the following AWS CLI command to list your Amazon S3 buckets\.

     ```
     $ aws s3 ls
     2022-01-05 14:27:48 my-bucket-28621ccd-4a48-45be-b660-5252f75635a4
     ```
   + Alternatively, you can also use the [AWS Management Console](https://console.aws.amazon.com/)\. In the main navigation bar, in **Search for services\.\.\.**, enter **S3**\. The Buckets page lists your account's buckets\.

1. Rebuild the code and run the updated executable `run_delete_bucket`\.

1. Using either the AWS Management Console or the AWS CLI, verify that the Amazon S3 bucket that you created earlier has been deleted\.

## Building and Debugging Code Examples in Visual Studio<a name="buildingOnVisualStudio"></a>

**Note**  
NuGet SDK packages are deprecated\. Even if you use Visual Studio, it is recommended to still get the latest source code from GitHub, and build the AWS SDK for C\+\+ from source following the instructions\.

**Building and running the Amazon S3 code example**

1. Obtain the Amazon S3 example source code\. This procedure uses the [ Amazon S3 code examples using the AWS SDK for C\+\+](examples-s3.md) code example to get up and running using Visual Studio\. 

1. In Windows Explorer, navigate to the `s3` folder \(e\.g\. `\aws-doc-sdk-examples\cpp\example_code\s3`\)\. 

1. Right click on the `s3` example folder and choose **Open with Visual Studio**\.  Visual Studio for CMake projects don’t have a 'project' file, rather, it is the whole folder\. 

1. In the **Configuration Selector** dropdown in the top menu of Visual Studio, ensure that the selected configuration matches the build type that you selected when building the SDK from source\.  E\.g\. a **Debug** configuration should be selected if you built from source using debug \(`-DCMAKE_BUILD_TYPE=Debug` in the CMake command line from the SDK installation instructions\)\. 

1. If you are on Windows, delete the file `list_buckets_disabling_dns_cache.cpp` before building the project because it relies on the curl `HttpClient` of Linux\.   This source file is not for Windows users\. 

1. Open file `CMakeLists.txt`\. 

1. Click **Save**\. Every time you click **Save** on the `CMakeLists.txt` file, Visual Studio refreshes the CMake\-generated files\.  If you have your **Output** tab displayed, you can see the resulting log messages from this generation\. 
   + There is a drop\-down box within the **Output** tab that says: "**Show output from:**" and **CMake** should be the option selected by default\. 
   + Last message output should say "**CMake generation finished\.**"  
   + If last message is not this, then the CMake file has issues\. Do not proceed to further steps until this is resolved\.  See [Troubleshooting build issues](troubleshooting-cmake.md)\. 
   + Note that the CMake cache is used by CMake for speed\. If you are working through CMake issues, you want to ensure a ‘clean slate’ so that the error messages you are given is actually reflective of your most recent changes\.  In the Solution Explorer, right\-click on `CMakeLists.txt` and choose **CMake Cache**, then choose **Delete Cache**\. Do this frequently when working progressively through CMake issues\. 

1. To build and run examples from within Visual Studio, Visual Studio places executables in a different folder structure than the command line\. To run the code, the SDK executables must be copied to the right place\.  Find the “`TODO`” line of the CMakeLists file \(\~line 40\) and choose the one commented for use in Visual Studio\. Visual Studio does not use a subfolder dedicated to the build type so this is not included\.  Switch the commented\-out line in the `CMakeLists.txt` file for Visual Studio use\. 

1. Delete the CMake cache \(as described above\), click in the `CMakeLists.txt` file to select/activate the tab, and choose **Save** on the `CMakeLists.txt` file again to initiate the CMake build files generation\. 

1. Open the source file of the ‘program’ you wish to run\.
   + For example, open `list_buckets.cpp`\.
   + The Amazon S3 example folder is coded so that each showcased ‘feature’ of Amazon S3 is demonstrated in a dedicated executable for just that feature\.  E\.g\. `list_buckets.cpp` will become an executable that only demonstrates the listing of buckets\. 

1. In the top menu, choose **Build**, then choose **Build All**\. 
   + The **Output** tab’s **Show output from** should reflect the selection of **Build**, and show all the building and linking messages\. 
   + The last output should be: "**Build All succeeded\.**" 
   + Now executables for each of the individual source files are generated\.  You can confirm this by looking in the build output directory \(e\.g\. `\aws-doc-sdk-examples\cpp\example_code\s3\out\build\x64-Debug`\)\.
   + Note that the executables are prefixed with “run\_” because the `CMakeLists.txt` file dictates this\. 

1. In the top menu, there is a **green arrow** and a **drop\-down selector** for **Debug Target**\.  Choose `run_list_buckets.exe`\. 

1. Click the **green arrow run button** to **Select Startup Item**\. 

1. A Visual Studio Debug Console window will open and display the output of the code\. 

1. Press a key to close the window, or manually close the window, to terminate the program\.  You can also set breakpoints in the code and when you click run again the breakpoints will be hit\. 