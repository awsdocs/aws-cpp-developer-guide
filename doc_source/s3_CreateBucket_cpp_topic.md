# Create a bucket<a name="s3_CreateBucket_cpp_topic"></a>

The following code example shows how to create an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
using namespace Aws;
int main()
{
    Aws::SDKOptions options;
    InitAPI(options);
    {
        //TODO: Set to the AWS Region of your account.  If not, you will get a runtime
        //IllegalLocationConstraintException Message: "The unspecified location constraint is incompatible
        //for the Region specific endpoint this request was sent to."
        Aws::String region = "us-east-1";

        // Create a unique bucket name to increase the chance of success 
        // when trying to create the bucket.
        // Format: "my-bucket-" + lowercase UUID.
        Aws::String uuid = Aws::Utils::UUID::RandomUUID();
        Aws::String bucketName = "my-bucket-" +
            Aws::Utils::StringUtils::ToLower(uuid.c_str());

        // Create the bucket.
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;

        S3::S3Client client(clientConfig);
        Aws::S3::Model::CreateBucketRequest request;
        request.SetBucket(bucketName);
        
        Aws::S3::Model::CreateBucketOutcome outcome = client.CreateBucket(request);
        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            std::cout << "Error: CreateBucket: " <<
               err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        }
        else
        {
            std::cout << "Created bucket " << bucketName <<
                " in the specified AWS Region." << std::endl;
        }
    }
    ShutdownAPI(options);
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [CreateBucket](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/CreateBucket) in *AWS SDK for C\+\+ API Reference*\. 