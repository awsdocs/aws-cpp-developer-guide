# Creating, Listing, and Deleting Buckets<a name="examples-s3-buckets"></a>

Every *object* or file in Amazon Simple Storage Service must reside within a *bucket* which represents a folder of objects\. Each bucket is known by a name that must be globally unique within the AWS ecosystem\. For detailed information about buckets and their configuration, see [Working with Amazon S3 Buckets](https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html) in the Amazon Simple Storage Service Developer Guide\.

**Note**  
Best Practice  
We recommend that you enable the [AbortIncompleteMultipartUpload](https://docs.aws.amazon.com/AmazonS3/latest/API/RESTBucketPUTlifecycle.html) lifecycle rule on your Amazon S3 buckets\.  
This rule directs Amazon S3 to abort multipart uploads that don’t complete within a specified number of days after being initiated\. When the set time limit is exceeded, Amazon S3 aborts the upload and then deletes the incomplete upload data\.  
For more information, see [Lifecycle Configuration for a Bucket with Versioning](https://docs.aws.amazon.com/AmazonS3/latest/UG/lifecycle-configuration-bucket-with-versioning.html) in the Amazon Simple Storage Service Console User Guide\.

**Note**  
These code snippets assume that you understand the material in [Getting Started Using the AWS SDK for C\+\+](getting-started.md) and have configured default AWS credentials using the information in [Providing AWS Credentials](credentials.md)\.

## Create a Bucket<a name="create-bucket"></a>

Use the S3Client object `CreateBucket` method, passing it a `CreateBucketRequest` with the bucket’s name\. By default, buckets are created in the *us\-east\-1* \(N\. Virginia\) region\. The code example demonstrates how to create a bucket in any specified region\.

 **Includes** 

```
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/BucketLocationConstraint.h>
#include <aws/core/utils/UUID.h>
#include <aws/core/utils/StringUtils.h>
#include <awsdoc/s3/s3_examples.h>
```

 **Code** 

```
bool AwsDoc::S3::CreateBucket(const Aws::String& bucketName, 
    const Aws::S3::Model::BucketLocationConstraint& region)
{
	Aws::S3::S3Client s3_client;

    Aws::S3::Model::CreateBucketRequest request;
    request.SetBucket(bucketName);

    // You only need to set the AWS Region for the bucket if it is 
    // other than US East (N. Virginia) us-east-1.
    if (region != Aws::S3::Model::BucketLocationConstraint::us_east_1)
    {
        Aws::S3::Model::CreateBucketConfiguration bucket_config;
        bucket_config.SetLocationConstraint(region);

        request.SetCreateBucketConfiguration(bucket_config);
    }

    Aws::S3::Model::CreateBucketOutcome outcome = 
        s3_client.CreateBucket(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "Error: CreateBucket: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }

    return true;
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        Aws::S3::Model::BucketLocationConstraint region =
            Aws::S3::Model::BucketLocationConstraint::us_east_1;

        // Create a unique bucket name to increase the chance of success 
        // when trying to create the bucket.
        // Format: "my-bucket-" + lowercase UUID.
        Aws::String uuid = Aws::Utils::UUID::RandomUUID();
        Aws::String bucket_name = "my-bucket-" + 
            Aws::Utils::StringUtils::ToLower(uuid.c_str());

        // Create the bucket.
        if (AwsDoc::S3::CreateBucket(bucket_name, region))
        {
            std::cout << "Created bucket " << bucket_name <<
                " in the specified AWS Region." << std::endl;
        }
        else
        {
            return 1;
        }
    }
    ShutdownAPI(options);

	return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/create_bucket.cpp)\.

## List Buckets<a name="list-buckets"></a>

Use the S3Client object `ListBucket` method\. If successful, the method returns a `ListBucketOutcome` object, which contains a `ListBucketResult` object\.

Use the `ListBucketResult` object `GetBuckets` method to get a list of `Bucket` objects that contain information about each Amazon S3 bucket in your account\.

 **Includes** 

```
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/Bucket.h>
#include <awsdoc/s3/s3_examples.h>
```

 **Code** 

```
bool AwsDoc::S3::ListBuckets()
{
    Aws::S3::S3Client s3_client;
    Aws::S3::Model::ListBucketsOutcome outcome = s3_client.ListBuckets();

    if (outcome.IsSuccess())
    {
        std::cout << "Bucket names:" << std::endl << std::endl;

        Aws::Vector<Aws::S3::Model::Bucket> buckets =
            outcome.GetResult().GetBuckets();

        for (Aws::S3::Model::Bucket& bucket : buckets)
        {
            std::cout << bucket.GetName() << std::endl;
        }

        return true;
    }
    else
    {
        std::cout << "Error: ListBuckets: "
            << outcome.GetError().GetMessage() << std::endl;

        return false;
    }
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        if (!AwsDoc::S3::ListBuckets())
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/list_buckets.cpp)\.

## Delete a Bucket<a name="delete-bucket"></a>

Use the S3Client object `DeleteBucket` method, passing it a `DeleteBucketRequest` object that is set with the name of the bucket to delete\. *The bucket must be empty or an error will result*\.

 **Includes** 

```
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/DeleteBucketRequest.h>
#include <awsdoc/s3/s3_examples.h>
```

 **Code** 

```
bool AwsDoc::S3::DeleteBucket(const Aws::String& bucketName, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::DeleteBucketRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::DeleteBucketOutcome outcome = 
        s3_client.DeleteBucket(request);

    if (!outcome.IsSuccess()) 
    {
        auto err = outcome.GetError();
        std::cout << "Error: DeleteBucket: " <<
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
        if (AwsDoc::S3::DeleteBucket(bucket_name, region))
        {
            std::cout << "Deleted bucket '" << bucket_name <<
                "'." << std::endl;
        }
        else
        {
            return 1;
        }
    }
    ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/delete_bucket.cpp)\.