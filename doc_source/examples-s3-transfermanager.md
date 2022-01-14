# Using TransferManager for Amazon S3 operations<a name="examples-s3-transfermanager"></a>

You can use the AWS SDK for C\+\+ `TransferManager` class to reliably transfer files from the local environment to Amazon S3 and to copy objects from one Amazon S3 location to another\. `TransferManager` can get the progress of a transfer and pause or resume uploads and downloads\.

**Note**  
To avoid being charged for incomplete or partial uploads, we recommend that you enable the [AbortMultipartUpload](https://docs.aws.amazon.com/AmazonS3/latest/API/API_AbortMultipartUpload.html) lifecycle rule on your Amazon S3 buckets\.  
This rule directs Amazon S3 to abort multipart uploads that don’t complete within a specified number of days after being initiated\. When the set time limit is exceeded, Amazon S3 aborts the upload and then deletes the incomplete upload data\.   
For more information, see [Setting lifecycle configuration on a bucket](https://docs.aws.amazon.com/AmazonS3/latest/userguide/how-to-set-lifecycle-configuration-intro.html) in the Amazon S3 User Guide\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Upload and download of object using `TransferManager`<a name="stream"></a>

This example demonstrates how [https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_transfer_1_1_transfer_manager.html](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_transfer_1_1_transfer_manager.html) transfers large object in memory\. `UploadFile` and `DownloadFile` methods are both called asynchronously and return a `TransferHandle` to manage the status of your request\. If the object uploaded is larger than `bufferSize` then a multipart upload will be performed\. The `bufferSize` defaults to 5MB, but this can be configured via [https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_transfer_1_1_transfer_manager_configuration.html](https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_transfer_1_1_transfer_manager_configuration.html)\. 

```
        auto s3_client = Aws::MakeShared<Aws::S3::S3Client>("S3Client");
        auto executor = Aws::MakeShared<Aws::Utils::Threading::PooledThreadExecutor>("executor", 25);
        Aws::Transfer::TransferManagerConfiguration transfer_config(executor.get());
        transfer_config.s3Client = s3_client;

        auto transfer_manager = Aws::Transfer::TransferManager::Create(transfer_config);

        auto uploadHandle = transfer_manager->UploadFile(LOCAL_FILE, BUCKET, KEY, "text/plain", Aws::Map<Aws::String, Aws::String>());
        uploadHandle->WaitUntilFinished();
        bool success = uploadHandle->GetStatus() == Transfer::TransferStatus::COMPLETED; 
      
        if (!success)
        {
            auto err = uploadHandle->GetLastError();           
            std::cout << "File upload failed:  "<< err.GetMessage() << std::endl;
        }
        else
        {
            std::cout << "File upload finished." << std::endl;

            // Verify that the upload retrieved the expected amount of data.
            assert(uploadHandle->GetBytesTotalSize() == uploadHandle->GetBytesTransferred());
            g_file_size = uploadHandle->GetBytesTotalSize();

            // Create buffer to hold data received by the data stream. 
            Aws::Utils::Array<unsigned char> buffer(BUFFER_SIZE);
            auto downloadHandle = transfer_manager->DownloadFile(BUCKET,
                KEY,
                [&]() { //Define a lambda expression for the callback method parameter to stream back the data.
                    return Aws::New<MyUnderlyingStream>("TestTag", Aws::New<Stream::PreallocatedStreamBuf>("TestTag", buffer.GetUnderlyingData(), BUFFER_SIZE));
                });
            downloadHandle->WaitUntilFinished();// Block calling thread until download is complete.
            auto downStat = downloadHandle->GetStatus();
            if (downStat != Transfer::TransferStatus::COMPLETED)
            {
                auto err = downloadHandle->GetLastError();
                std::cout << "File download failed:  " << err.GetMessage() << std::endl;
            }
            std::cout << "File download to memory finished."  << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/transfer-manager/transferOnStream.cpp) on Github\.