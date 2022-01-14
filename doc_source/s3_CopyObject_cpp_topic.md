# Copy an object from one bucket to another<a name="s3_CopyObject_cpp_topic"></a>

The following code example shows how to copy an Amazon S3 object from one bucket to another\.

**SDK for C\+\+**  
  

```
using namespace Aws;

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        //TODO: Name of object already in bucket.
        Aws::String objectKey = "<enter object key>";
        
        //TODO: Change from_bucket to the name of your bucket that already contains "my-file.txt". 
        Aws::String fromBucket = "<Enter bucket name>";
        
        //TODO: Change to the name of another bucket in your account.
        Aws::String toBucket = "<Enter bucket name>";
        
        //TODO: Set to the AWS Region in which the bucket was created.
        Aws::String region = "us-east-1";
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;
        
        S3::S3Client client(clientConfig);
        S3::Model::CopyObjectRequest request;

        request.WithCopySource(fromBucket + "/" + objectKey)
            .WithKey(objectKey)
            .WithBucket(toBucket);

        S3::Model::CopyObjectOutcome outcome = client.CopyObject(request);

        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            std::cout << "Error: CopyObject: " <<
               err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        }
    }
    ShutdownAPI(options);
    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [CopyObject](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/CopyObject) in *AWS SDK for C\+\+ API Reference*\. 