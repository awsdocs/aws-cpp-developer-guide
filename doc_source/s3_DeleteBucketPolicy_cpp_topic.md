# Delete a policy from a bucket<a name="s3_DeleteBucketPolicy_cpp_topic"></a>

The following code example shows how to delete a policy from an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
using namespace Aws;

int main()
{
    //TODO: Change bucket_name to the name of a bucket in your account.
    const Aws::String bucketName = "<Enter bucket name>";
    //TODO: Set to the AWS Region in which the bucket was created.
    const Aws::String region = "us-east-1";


    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;

        S3::S3Client client(clientConfig);
        
        Aws::S3::Model::DeleteBucketPolicyRequest request;
        request.SetBucket(bucketName);

        Aws::S3::Model::DeleteBucketPolicyOutcome outcome =  client.DeleteBucketPolicy(request);

        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            std::cout << "Error: DeleteBucketPolicy: " <<
                err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

            return false;
        }
        else
        {
            std::cout << "Policy was deleted from the bucket." << std::endl;
        }
    }
    ShutdownAPI(options);
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [DeleteBucketPolicy](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/DeleteBucketPolicy) in *AWS SDK for C\+\+ API Reference*\. 