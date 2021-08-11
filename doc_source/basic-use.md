# Basic Use<a name="basic-use"></a>

Applications that use the AWS SDK for C\+\+ must initialize it\. Similarly, before the application terminates, the SDK must be shut down\. Both operations accept configuration options that affect the initialization and shutdown processes and subsequent calls to the SDK\.

## Initializing and Shutting Down the SDK<a name="sdk-initializing"></a>

All applications that use the AWS SDK for C\+\+ must include the file `aws/core/Aws.h`\.

The AWS SDK for C\+\+ must be initialized by calling `Aws::InitAPI`\. Before the application terminates, the SDK must be shut down by calling `Aws::ShutdownAPI`\. Each method accepts an argument of [https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html](https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html)\. All other calls to the SDK can be performed between these two method calls\.

Best practice requires all AWS SDK for C\+\+ calls performed between `Aws::InitAPI` and `Aws::ShutdownAPI` either to be contained within a pair of curly braces or be invoked by functions called between the two methods\.

A basic skeleton application is shown below\.

```
#include <aws/core/Aws.h>
int main(int argc, char** argv)
{
   Aws::SDKOptions options;
   Aws::InitAPI(options);
   {
      // make your SDK calls here.
   }
   Aws::ShutdownAPI(options);
   return 0;
}
```

## Setting SDK Options<a name="sdk-setting-options"></a>

The [https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html](https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html) struct contains SDK configuration options\.

An instance of [https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html](https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html) is passed to the `Aws::InitAPI` and `Aws::ShutdownAPI` methods\. The same instance should be sent to both methods\.

The following samples demonstrate some of the available options\.
+ Turn logging on using the default logger

  ```
  Aws::SDKOptions options;
  options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
  Aws::InitAPI(options);
  {
      // make your SDK calls here.
  }
  Aws::ShutdownAPI(options);
  ```
+ Override the default HTTP client factory

  ```
  Aws::SDKOptions options;
  options.httpOptions.httpClientFactory_create_fn = [](){
          return Aws::MakeShared<MyCustomHttpClientFactory>(
              "ALLOC_TAG", arg1);
      };
  Aws::InitAPI(options);
  {
      // make your SDK calls here.
  }
  Aws::ShutdownAPI(options);
  ```

**Note**  
 `httpOptions` takes a closure \(also called an anonymous function or lambda expression\) rather than a `std::shared_ptr`\. Each of the SDK factory functions operates in this manner because at the time at which the factory memory allocation occurs, the memory manager has not yet been installed\. By passing a closure to the method, the memory manager will be called to perform the memory allocation when it is safe to do so\. A simple technique to accomplish this procedure is by using a Lambda expression\.