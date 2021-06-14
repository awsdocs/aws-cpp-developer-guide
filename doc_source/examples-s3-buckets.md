# Creating, listing, and deleting buckets<a name="examples-s3-buckets"></a>

Every *object* or file in Amazon Simple Storage Service \(Amazon S3\) is contained in a *bucket*, which represents a folder of objects\. Each bucket has a name that is globally unique within AWS\. For more information, see [Working with Amazon S3 Buckets](https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html) in the Amazon Simple Storage Service Developer Guide\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## List buckets<a name="list-buckets"></a>

To run the `list_buckets` example, at a command prompt, navigate to the folder where your build system creates your build executables\. Run the executable like `run_list_buckets` \(your full executable filename will differ based on your operating system\)\. The output lists your account's buckets if you have any, or it displays an empty list if you don't have any buckets\.

In `list_buckets.cpp`, there are two methods\.
+ `main()` calls `ListBuckets()`\. 
+ `ListBuckets()` uses the SDK to query your buckets\.

The S3Client object calls the SDK's `ListBuckets()` method\. If successful, the method returns a `ListBucketOutcome` object, which contains a `ListBucketResult` object\. The `ListBucketResult` object calls the `GetBuckets()` method to get a list of `Bucket` objects that contain information about each Amazon S3 bucket in your account\.

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

See the complete [list\_buckets example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/list_buckets.cpp) on Github\.

## Create a bucket<a name="create-bucket"></a>



To run the `create_bucket` example, at a command prompt, navigate to the folder where your build system creates your build executables\. Run the executable like `run_create_bucket` \(your full executable filename will differ based on your operating system\)\. The code creates an empty bucket under your account and then displays the success or failure of the request\.

In `create_bucket.cpp`, there are two methods\. 
+ `main()` calls `CreateBucket()`\. In `main()`, you need to change the AWS Region to the Region of your account by using the `enum`\. You can view the Region of your account by logging into the [AWS Management Console](https://console.aws.amazon.com/), and locating the Region in the upper right\-hand corner\. 
+ `CreateBucket()` uses the SDK to create a bucket\. 



The S3Client object calls the SDK's `CreateBucket()` method, passing in a `CreateBucketRequest` with the bucket’s name\. By default, buckets are created in the *us\-east\-1* \(N\. Virginia\) Region\. If your Region is not *us\-east\-1* then the code sets up a bucket constraint to ensure the bucket is created in your Region\.

 **Code** 

```
bool AwsDoc::S3::CreateBucket(const Aws::String& bucketName, 
    const Aws::S3::Model::BucketLocationConstraint& region)
{
    Aws::Client::ClientConfiguration config;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::CreateBucketRequest request;
    request.SetBucket(bucketName);

    //  If you don't specify a Region, the bucket is created in the US East (N. Virginia) Region (us-east-1)
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
        //TODO: Set to the region of your account.  If not, you will get a runtime
        //IllegalLocationConstraintException Message: "The unspecified location constraint is incompatible
        //for the region specific endpoint this request was sent to."
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

See the complete [create\_buckets example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/create_bucket.cpp) on Github\.

## Delete a bucket<a name="delete-bucket"></a>



To run the `delete_bucket` example, at a command prompt, navigate to the folder where your build system creates your build executables\. Run the executable like `run_delete_bucket` \(your full executable filename will differ based on your operating system\)\. The code deletes the specified bucket in your account and then displays the success or failure of the request\.

In `delete_bucket.cpp` there are two methods\. 
+ `main()` calls `DeleteBucket()`\. In `main()`, you need to change the AWS Region to the Region of your account by using the `enum`\. You also need to change the `bucket_name` to the name of the bucket to delete\. 
+ `DeleteBucket()` uses the SDK to delete the bucket\. 



The S3Client object uses the SDK's `DeleteBucket()` method, passing in a `DeleteBucketRequest` object with the name of the bucket to delete\. The bucket must be empty to be successful\.

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
    //TODO: Change bucket_name to the name of a bucket in your account.
    //If the bucket is not in your account, you will get one of two errors:
    //AccessDenied if the bucket exists in some other account, or NoSuchBucket
    //if the bucket does not exist in any account.
    Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";
    //TODO:  Set region to the region of the bucket bucket_name.
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

See the complete [delete\_bucket example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/delete_bucket.cpp) on Github\.