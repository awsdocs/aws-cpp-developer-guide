# Upload an object to a bucket<a name="s3_PutObject_cpp_topic"></a>

The following code example shows how to upload an object to an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
bool PutObject(const Aws::String& bucketName, 
    const Aws::String& objectName,
    const Aws::String& region)
{
    // Verify that the file exists.
    struct stat buffer;

    if (stat(objectName.c_str(), &buffer) == -1)
    {
        std::cout << "Error: PutObject: File '" <<
            objectName << "' does not exist." << std::endl;

        return false;
    }

    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);
    
    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bucketName);
    //We are using the name of the file as the key for the object in the bucket.
    //However, this is just a string and can set according to your retrieval needs.
    request.SetKey(objectName);

    std::shared_ptr<Aws::IOStream> input_data = 
        Aws::MakeShared<Aws::FStream>("SampleAllocationTag", 
            objectName.c_str(), 
            std::ios_base::in | std::ios_base::binary);

    request.SetBody(input_data);

    Aws::S3::Model::PutObjectOutcome outcome = 
        s3_client.PutObject(request);

    if (outcome.IsSuccess()) {

        std::cout << "Added object '" << objectName << "' to bucket '"
            << bucketName << "'.";
        return true;
    }
    else 
    {
        std::cout << "Error: PutObject: " << 
            outcome.GetError().GetMessage() << std::endl;
       
        return false;
    }
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        //TODO: Change bucket_name to the name of a bucket in your account.
        const Aws::String bucket_name = "<Enter bucket name>";
        //TODO: Create a file called "my-file.txt" in the local folder where your executables are built to.
        const Aws::String object_name = "<Enter file>";
        //TODO: Set to the AWS Region in which the bucket was created.
        const Aws::String region = "us-east-1";

        if (!PutObject(bucket_name, object_name, region)) {
            
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [PutObject](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/PutObject) in *AWS SDK for C\+\+ API Reference*\. 