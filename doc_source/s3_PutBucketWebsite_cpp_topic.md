# Set the website configuration for a bucket<a name="s3_PutBucketWebsite_cpp_topic"></a>

The following code example shows how to set the website configuration for an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
bool AwsDoc::S3::PutWebsiteConfig(const Aws::String& bucketName, 
    const Aws::String& indexPage, const Aws::String& errorPage, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;

    }

    Aws::S3::S3Client s3_client(config);
        
    Aws::S3::Model::IndexDocument index_doc;
    index_doc.SetSuffix(indexPage);

    Aws::S3::Model::ErrorDocument error_doc;
    error_doc.SetKey(errorPage);

    Aws::S3::Model::WebsiteConfiguration website_config;
    website_config.SetIndexDocument(index_doc);
    website_config.SetErrorDocument(error_doc);

    Aws::S3::Model::PutBucketWebsiteRequest request;
    request.SetBucket(bucketName);
    request.SetWebsiteConfiguration(website_config);

    Aws::S3::Model::PutBucketWebsiteOutcome outcome = 
        s3_client.PutBucketWebsite(request);

    if (outcome.IsSuccess())
    {
        std::cout << "Success: Set website configuration for bucket '" 
            << bucketName << "'." << std::endl;

        return true;
    }
    else
    {
        std::cout << "Error: PutBucketWebsite: "
            << outcome.GetError().GetMessage() << std::endl;

        return false;
    }
    
    return 1;
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
        //TODO: Create these two files to serve as your website
        const Aws::String index_page = "index.html";
        const Aws::String error_page = "404.html";


        if (!AwsDoc::S3::PutWebsiteConfig(bucket_name, index_page, error_page, region))
        {
            return 1;
        }
        
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [PutBucketWebsite](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/PutBucketWebsite) in *AWS SDK for C\+\+ API Reference*\. 