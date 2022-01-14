# Get the website configuration for a bucket<a name="s3_GetBucketWebsite_cpp_topic"></a>

The following code example shows how to get the website configuration for an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
bool AwsDoc::S3::GetWebsiteConfig(const Aws::String& bucketName, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::GetBucketWebsiteRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::GetBucketWebsiteOutcome outcome = 
        s3_client.GetBucketWebsite(request);

    if (outcome.IsSuccess())
    {
        Aws::S3::Model::GetBucketWebsiteResult result = outcome.GetResult();

        std::cout << "Success: GetBucketWebsite: "
            << std::endl << std::endl
            << "For bucket '" << bucketName << "':" 
            << std::endl
            << "Index page : "
            << result.GetIndexDocument().GetSuffix()
            << std::endl
            << "Error page: "
            << result.GetErrorDocument().GetKey()
            << std::endl;

        return true;
    }
    else
    {
        auto err = outcome.GetError();

        std::cout << "Error: GetBucketWebsite: "
            << err.GetMessage() << std::endl;

        return false;
    }
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        //TODO: Change bucket_name to the name of a bucket in your account.
        const Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";
        //TODO: Set to the AWS Region in which the bucket was created.
        const Aws::String region = "us-east-1";

        if (!AwsDoc::S3::GetWebsiteConfig(bucket_name, region))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [GetBucketWebsite](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/GetBucketWebsite) in *AWS SDK for C\+\+ API Reference*\. 