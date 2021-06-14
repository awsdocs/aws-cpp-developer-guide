# Asynchronous methods<a name="async-methods"></a>

## Asynchronous SDK methods<a name="asynchronous-sdk-methods"></a>

For many methods, the SDK for C\+\+ provides both synchronous and asynchronous versions\. A method is asynchronous if it includes the `Async` suffix in its name\. For example, the Amazon S3 method `PutObject` is synchronous, while `PutObjectAsync` is asynchronous\.

Like all asynchronous operations, an asynchronous SDK method returns before its main task is finished\. For example, the `PutObjectAsync` method returns before it finishes uploading the file to the Amazon S3 bucket\. While the upload operation continues, the application can perform other operations, including calling other asynchronous methods\. The application is notified that an asynchronous operation has finished when an associated callback function is invoked\.

The following sections describe a code example that demonstrates calling an SDK asynchronous method\. Each section focuses on individual portions from the example’s [entire source file](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/put_object_async.cpp)\.

## Calling SDK asynchronous methods<a name="calling-sdk-asynchronous-methods"></a>

In general, the asynchronous version of an SDK method accepts the following arguments\.
+ A reference to the same Request\-type object as its synchronous counterpart\.
+ A reference to a response handler callback function\. This callback function is invoked when the asynchronous operation finishes\. One of the arguments contains the operation’s outcome\.
+ An optional `shared_ptr` to an `AsyncCallerContext` object\. The object is passed to the response handler callback\. It includes a UUID property that can be used to pass text information to the callback\.

The `put_s3_object_async` method shown below sets up and calls the SDK’s Amazon S3 `PutObjectAsync` method to asynchronously upload a file to an Amazon S3 bucket\.

The method initializes a `PutObjectRequest` object in the same manner as its synchronous counterpart\. In addition, a `shared_ptr` to an `AsyncCallerContext` object is allocated\. Its `UUID` property is set to the Amazon S3 object name\. For demonstration purposes, the response handler callback will access the property and output its value\.

The call to `PutObjectAsync` includes a reference argument to the response handler callback function `put_object_async_finished`\. This callback function is examined in more detail in the next section\.

```
bool AwsDoc::S3::PutObjectAsync(const Aws::S3::S3Client& s3Client,
    const Aws::String& bucketName,
    const Aws::String& objectName,
    const Aws::String& region)
{
    // Verify that the file exists.
    struct stat buffer;

    if (stat(objectName.c_str(), &buffer) == -1)
    {
        std::cout << "Error: PutObjectAsync: File '" <<
            objectName << "' does not exist." << std::endl;

        return false;
    }

    // Create and configure the asynchronous put object request.
    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bucketName);
    request.SetKey(objectName);

    const std::shared_ptr<Aws::IOStream> input_data =
        Aws::MakeShared<Aws::FStream>("SampleAllocationTag",
            objectName.c_str(),
            std::ios_base::in | std::ios_base::binary);

    request.SetBody(input_data);

    // Create and configure the context for the asynchronous put object request.
    std::shared_ptr<Aws::Client::AsyncCallerContext> context =
        Aws::MakeShared<Aws::Client::AsyncCallerContext>("PutObjectAllocationTag");
    context->SetUUID(objectName);

    // Make the asynchronous put object call. Queue the request into a 
    // thread executor and call the PutObjectAsyncFinished function when the 
    // operation has finished. 
    s3Client.PutObjectAsync(request, PutObjectAsyncFinished, context);

    return true;
}
```

The resources directly associated with an asynchronous operation must continue to exist until the operation finishes\. For example, the client object used to invoke an asynchronous SDK method must exist until the application receives notification that the operation has finished\. Similarly, the application itself cannot terminate until the asynchronous operation completes\.

For this reason, the `put_s3_object_async` method accepts a reference to an `S3Client` object instead of creating the client in a local variable\. In the example, the method returns to the caller immediately after beginning the asynchronous operation, enabling the caller to perform additional tasks while the upload operation is in progress\. If the client is stored in a local variable, it would go out of scope when the method returned\. However, the client object must continue to exist until the asynchronous operation finishes\.

## Notification of the Completion of an Asynchronous Operation<a name="notification-of-the-completion-of-an-asynchronous-operation"></a>

When an asynchronous operation finishes, an application response handler callback function is invoked\. This notification includes the outcome of the operation\. The outcome is contained in the same Outcome\-type class returned by the method’s synchronous counterpart\. In the code example, the outcome is in a `PutObjectOutcome` object\.

The example’s response handler callback function `put_object_async_finished` is shown below\. It checks whether the asynchronous operation succeeded or failed\. It uses a `std::condition_variable` to notify the application thread that the async operation has finished\.

```
// A mutex is a synchronization primitive that can be used to protect shared 
// data from being simultaneously accessed by multiple threads.
std::mutex upload_mutex;

// A condition_variable is a synchronization primitive that can be used to 
// block a thread, or multiple threads at the same time, until another 
// thread both modifies a shared variable (the condition) and 
// notifies the condition_variable. 
std::condition_variable upload_variable;
```

```
void PutObjectAsyncFinished(const Aws::S3::S3Client* s3Client, 
    const Aws::S3::Model::PutObjectRequest& request, 
    const Aws::S3::Model::PutObjectOutcome& outcome,
    const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context)
{
    if (outcome.IsSuccess()) {
        std::cout << "Success: PutObjectAsyncFinished: Finished uploading '" 
            << context->GetUUID() << "'." << std::endl;
    }
    else {
        std::cout << "Error: PutObjectAsyncFinished: " <<
            outcome.GetError().GetMessage() << std::endl;
    }

    // Unblock the thread that is waiting for this function to complete.
    upload_variable.notify_one();
}
```

With the asynchronous operation finished, the resources associated with it can be released\. The application can also terminate if it wishes\.

The following code demonstrates how the `put_object_async` and `put_object_async_finished` methods are used by an application\.

The `S3Client` object is allocated so it continues to exist until the asynchronous operation finishes\. After calling `put_object_async`, the application can perform whatever operations it wishes\. For simplicity, the example uses a `std::mutex` and `std::condition_variable` to wait until the response handler callback notifies it that the upload operation has finished\.

```
int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = "my-bucket";
        const Aws::String object_name = "my-file.txt";
        const Aws::String region = "us-east-1";

        // A unique_lock is a general-purpose mutex ownership wrapper allowing 
        // deferred locking, time-constrained attempts at locking, recursive 
        // locking, transfer of lock ownership, and use with 
        // condition variables.
        std::unique_lock<std::mutex> lock(upload_mutex);

        // Create and configure the Amazon S3 client. 
        // This client must be declared here, as this client must exist 
        // until the put object operation finishes.
        Aws::Client::ClientConfiguration config;

        if (!region.empty())
        {
            config.region = region;
        }

        Aws::S3::S3Client s3_client(config);

        if (AwsDoc::S3::PutObjectAsync(s3_client, bucket_name, object_name, region)) {

            std::cout << "main: Waiting for file upload attempt..." << 
                std::endl << std::endl;
            
            // While the put object operation attempt is in progress, 
            // you can perform other tasks.
            // This example simply blocks until the put object operation 
            // attempt finishes.
            upload_variable.wait(lock);

            std::cout << std::endl << "main: File upload attempt completed." 
                << std::endl;
        }
        else
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```