# Configuring an Amazon S3 Bucket as a Website<a name="examples-s3-website-configuration"></a>

You can configure an Amazon S3 bucket to behave as a website\. To do this, you need to set its website configuration\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Set a Bucket’s Website Configuration<a name="set-a-bucket-s-website-configuration"></a>

To set an Amazon S3 bucket’s website configuration, call the S3Client’s `PutBucketWebsite` function with a [PutBucketWebsiteRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_put_bucket_website_request.html) object containing the bucket name and its website configuration, provided in a [WebsiteConfiguration](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_website_configuration.html) object\.

Setting an index document is *required*; all other parameters are optional\.

 **Code** 

```
bool AwsDoc::S3::DeleteBucketWebsite(const Aws::String& bucketName, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::DeleteBucketWebsiteRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::DeleteBucketWebsiteOutcome outcome =
        s3_client.DeleteBucketWebsite(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "Error: DeleteBucketWebsite: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }

    return true;
}

int main()
{
    //TODO: Change bucket_name to the name of a bucket in your account.
    const Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";
    //TODO: Set to the region in which the bucket was created.
    const Aws::String region = "us-east-1";


    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        if (AwsDoc::S3::DeleteBucketWebsite(bucket_name, region))
        {
            std::cout << "Removed website configuration from '" << 
                bucket_name << "'." << std::endl;
        }
    }
    ShutdownAPI(options);

    return 0;
}
```

**Note**  
Setting a website configuration does not modify the access permissions for your bucket\. To make your files visible on the web, you will also need to set a *bucket policy* that allows public read access to the files in the bucket\. For more information, see [Managing Access to Amazon S3 Buckets Using Bucket Policies](examples-s3-bucket-policies.md)\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/put_website_config.cpp) on Github\.

## Get a Bucket’s Website Configuration<a name="get-a-bucket-s-website-configuration"></a>

To get an Amazon S3 bucket’s website configuration, call the S3Client’s `GetBucketWebsite` function with a [GetBucketWebsiteRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_get_bucket_website_request.html) containing the name of the bucket to retrieve the configuration for\.

The configuration will be returned as a [GetBucketWebsiteResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_get_bucket_website_result.html) object within the outcome object\. If there is no website configuration for the bucket, then `null` will be returned\.

 **Code** 

```
bool AwsDoc::S3::DeleteBucketWebsite(const Aws::String& bucketName, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::DeleteBucketWebsiteRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::DeleteBucketWebsiteOutcome outcome =
        s3_client.DeleteBucketWebsite(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "Error: DeleteBucketWebsite: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }

    return true;
}

int main()
{
    //TODO: Change bucket_name to the name of a bucket in your account.
    const Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";
    //TODO: Set to the region in which the bucket was created.
    const Aws::String region = "us-east-1";


    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        if (AwsDoc::S3::DeleteBucketWebsite(bucket_name, region))
        {
            std::cout << "Removed website configuration from '" << 
                bucket_name << "'." << std::endl;
        }
    }
    ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/get_website_config.cpp) on Github\.

## Delete a Bucket’s Website Configuration<a name="delete-a-bucket-s-website-configuration"></a>

To delete an Amazon S3 bucket’s website configuration, call the S3Client’s `DeleteBucketWebsite` function with a [DeleteBucketWebsiteRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_delete_bucket_website_request.html): containing the name of the bucket to delete the configuration from\.

 **Code** 

```
bool AwsDoc::S3::DeleteBucketWebsite(const Aws::String& bucketName, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::DeleteBucketWebsiteRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::DeleteBucketWebsiteOutcome outcome =
        s3_client.DeleteBucketWebsite(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "Error: DeleteBucketWebsite: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }

    return true;
}

int main()
{
    //TODO: Change bucket_name to the name of a bucket in your account.
    const Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";
    //TODO: Set to the region in which the bucket was created.
    const Aws::String region = "us-east-1";


    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        if (AwsDoc::S3::DeleteBucketWebsite(bucket_name, region))
        {
            std::cout << "Removed website configuration from '" << 
                bucket_name << "'." << std::endl;
        }
    }
    ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/delete_website_config.cpp) on Github\.

## More Information<a name="more-information"></a>
+  [PUT Bucket website](https://docs.aws.amazon.com/AmazonS3/latest/API/RESTBucketPUTwebsite.html) in the Amazon Simple Storage Service API Reference
+  [GET Bucket website](https://docs.aws.amazon.com/AmazonS3/latest/API/RESTBucketGETwebsite.html) in the Amazon Simple Storage Service API Reference
+  [DELETE Bucket website](https://docs.aws.amazon.com/AmazonS3/latest/API/RESTBucketDELETEwebsite.html) in the Amazon Simple Storage Service API Reference