# Configuring an Amazon S3 Bucket as a Website<a name="examples-s3-website-configuration"></a>

You can configure an Amazon S3 bucket to behave as a website\. To do this, you need to set its website configuration\.

**Note**  
These code snippets assume that you understand the material in [Getting Started Using the AWS SDK for C\+\+](getting-started.md) and have configured default AWS credentials using the information in [Providing AWS Credentials](credentials.md)\.

## Set a Bucket’s Website Configuration<a name="set-a-bucket-s-website-configuration"></a>

To set an Amazon S3 bucket’s website configuration, call the S3Client’s `PutBucketWebsite` function with a [PutBucketWebsiteRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_put_bucket_website_request.html) object containing the bucket name and its website configuration, provided in a [WebsiteConfiguration](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_website_configuration.html) object\.

Setting an index document is *required*; all other parameters are optional\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/IndexDocument.h>
#include <aws/s3/model/ErrorDocument.h>
#include <aws/s3/model/WebsiteConfiguration.h>
#include <aws/s3/model/PutBucketWebsiteRequest.h>
#include <awsdoc/s3/s3_examples.h>
```

 **Code** 

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
        const Aws::String bucket_name = "my-bucket";
        const Aws::String index_page = "index.html";
        const Aws::String error_page = "404.html";
        const Aws::String region = "us-east-1";

        if (!AwsDoc::S3::PutWebsiteConfig(bucket_name, index_page, error_page, region))
        {
            return 1;
        }
        
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```

**Note**  
Setting a website configuration does not modify the access permissions for your bucket\. To make your files visible on the web, you will also need to set a *bucket policy* that allows public read access to the files in the bucket\. For more information, see [Managing Access to Amazon S3 Buckets Using Bucket Policies](examples-s3-bucket-policies.md)\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/put_website_config.cpp)\.

## Get a Bucket’s Website Configuration<a name="get-a-bucket-s-website-configuration"></a>

To get an Amazon S3 bucket’s website configuration, call the S3Client’s `GetBucketWebsite` function with a [GetBucketWebsiteRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_get_bucket_website_request.html) containing the name of the bucket to retrieve the configuration for\.

The configuration will be returned as a [GetBucketWebsiteResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_get_bucket_website_result.html) object within the outcome object\. If there is no website configuration for the bucket, then `null` will be returned\.

 **Includes** 

```
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetBucketWebsiteRequest.h>
#include <awsdoc/s3/s3_examples.h>
```

 **Code** 

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
        Aws::String bucket_name = "my-bucket";
        Aws::String region = "us-east-1";

        if (!AwsDoc::S3::GetWebsiteConfig(bucket_name, region))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/get_website_config.cpp)\.

## Delete a Bucket’s Website Configuration<a name="delete-a-bucket-s-website-configuration"></a>

To delete an Amazon S3 bucket’s website configuration, call the S3Client’s `DeleteBucketWebsite` function with a [DeleteBucketWebsiteRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_delete_bucket_website_request.html): containing the name of the bucket to delete the configuration from\.

 **Includes** 

```
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/DeleteBucketWebsiteRequest.h>
#include <awsdoc/s3/s3_examples.h>
```

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
    Aws::String bucket_name = "my-bucket";
    Aws::String region = "us-east-1";

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

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/delete_website_config.cpp)\.

## More Information<a name="more-information"></a>
+  [PUT Bucket website](https://docs.aws.amazon.com/AmazonS3/latest/API/RESTBucketPUTwebsite.html) in the Amazon Simple Storage Service API Reference
+  [GET Bucket website](https://docs.aws.amazon.com/AmazonS3/latest/API/RESTBucketGETwebsite.html) in the Amazon Simple Storage Service API Reference
+  [DELETE Bucket website](https://docs.aws.amazon.com/AmazonS3/latest/API/RESTBucketDELETEwebsite.html) in the Amazon Simple Storage Service API Reference