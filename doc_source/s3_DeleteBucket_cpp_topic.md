# Delete an empty bucket<a name="s3_DeleteBucket_cpp_topic"></a>

The following code example shows how to delete an empty Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
using namespace Aws;
int main()
{
    //TODO: Change bucket_name to the name of a bucket in your account.
    //If the bucket is not in your account, you will get one of two errors:
    Aws::String bucketName = "<Bucket Name>";
    //TODO:  Set to the AWS Region of the bucket bucket_name.
    Aws::String region = "us-east-1";

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
       
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;

        S3::S3Client client(clientConfig);

        Aws::S3::Model::DeleteBucketRequest request;
        request.SetBucket(bucketName);

        Aws::S3::Model::DeleteBucketOutcome outcome =
            client.DeleteBucket(request);

        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            std::cout << "Error: DeleteBucket: " <<
                err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        }
        else
        {
            std::cout << "The bucket was deleted" << std::endl;
        }
    }
    ShutdownAPI(options);
    
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [DeleteBucket](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/DeleteBucket) in *AWS SDK for C\+\+ API Reference*\. 