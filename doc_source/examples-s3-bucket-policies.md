# Managing Access to Amazon S3 Buckets Using Bucket Policies<a name="examples-s3-bucket-policies"></a>

You can set, get, or delete a *bucket policy* to manage access to your Amazon S3 buckets\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Set a Bucket Policy<a name="set-s3-bucket-policy"></a>

You can set the bucket policy for a particular S3 bucket by calling the S3Client’s `PutBucketPolicy` function and providing it with the bucket name and policy’s JSON representation in a [PutBucketPolicyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_put_bucket_policy_request.html)\.

 **Code** 

```
        "{\n"
        "   \"Version\":\"2012-10-17\",\n"
        "   \"Statement\":[\n"
        "       {\n"
        "           \"Sid\": \"1\",\n"
        "           \"Effect\": \"Allow\",\n"
        "           \"Principal\": {\n"
        "               \"AWS\": \"arn:aws:iam::" + accountID + ":root\"\n"
        "           },\n"
        "           \"Action\": [ \"s3:GetObject\" ],\n"
        "           \"Resource\": [ \"arn:aws:s3:::" + bucketName + "/*\" ]\n"
        "       }\n"
        "   ]\n"
        "}";
```

```
bool AwsDoc::S3::PutBucketPolicy(const Aws::String& bucketName, 
    const Aws::String& policyBody,
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);

    std::shared_ptr<Aws::StringStream> request_body = 
        Aws::MakeShared<Aws::StringStream>("");
    *request_body << policyBody;

    Aws::S3::Model::PutBucketPolicyRequest request;
    request.SetBucket(bucketName);
    request.SetBody(request_body);

    Aws::S3::Model::PutBucketPolicyOutcome outcome = 
        s3_client.PutBucketPolicy(request);

    if (outcome.IsSuccess()) {
        std::cout << "Set the following policy body for the bucket '" <<
            bucketName << "':" << std::endl << std::endl;
        std::cout << policyBody << std::endl;

        return true;
    }
    else {
        std::cout << "Error: PutBucketPolicy: "
            << outcome.GetError().GetMessage() << std::endl;

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
        //TODO: Set to the region in which the bucket was created.
        const Aws::String region = "us-east-1";


        // Get the caller's AWS account ID to be used in the bucket policy.
        Aws::STS::STSClient sts_client;
        Aws::STS::Model::GetCallerIdentityRequest request;
        Aws::STS::Model::GetCallerIdentityOutcome outcome =
            sts_client.GetCallerIdentity(request);

        if (!outcome.IsSuccess())
        {
            std::cout << "Error: GetBucketPolicy setup: Get identity information: " 
                << outcome.GetError().GetMessage() << std::endl;

            return 1;
        }

        // Extract the caller's AWS account ID from the call to AWS STS.
        Aws::String account_id = outcome.GetResult().GetAccount();

        // Use the account ID and bucket name to form the bucket policy to be added.
        Aws::String policy_string = GetPolicyString(account_id, bucket_name);

        if (!AwsDoc::S3::PutBucketPolicy(bucket_name, policy_string, region))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```

**Note**  
The [Aws::Utils::Json::JsonValue](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_utils_1_1_json_1_1_json_value.html) utility class can be used to help you construct valid JSON objects to pass to `PutBucketPolicy`\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/put_bucket_policy.cpp) on Github\.

## Get a Bucket Policy<a name="get-s3-bucket-policy"></a>

To retrieve the policy for an Amazon S3 bucket, call the S3Client’s `GetBucketPolicy` function, passing it the name of the bucket in a [GetBucketPolicyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_get_bucket_policy_request.html)\.

 **Code** 

```
bool AwsDoc::S3::GetBucketPolicy(const Aws::String& bucketName, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::GetBucketPolicyRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::GetBucketPolicyOutcome outcome =
        s3_client.GetBucketPolicy(request);

    if (outcome.IsSuccess())
    {
        Aws::StringStream policy_stream;
        Aws::String line;

        outcome.GetResult().GetPolicy() >> line;
        policy_stream << line;

        std::cout << "Policy:" << std::endl << std::endl << 
            policy_stream.str() << std::endl;

        return true;
    }
    else
    {
        auto err = outcome.GetError();
        std::cout << "Error: GetBucketPolicy: "
            << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }
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
        if (!AwsDoc::S3::GetBucketPolicy(bucket_name, region))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/get_bucket_policy.cpp) on Github\.

## Delete a Bucket Policy<a name="delete-s3-bucket-policy"></a>

To delete a bucket policy, call the S3Client’s `DeleteBucketPolicy` function, providing it with the bucket name in a [DeleteBucketPolicyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_model_1_1_delete_bucket_policy_request.html)\.

 **Code** 

```
bool AwsDoc::S3::DeleteBucketPolicy(const Aws::String& bucketName,const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::DeleteBucketPolicyRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::DeleteBucketPolicyOutcome outcome =
        s3_client.DeleteBucketPolicy(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "Error: DeleteBucketPolicy: " <<
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
        if (AwsDoc::S3::DeleteBucketPolicy(bucket_name, region))
        {
            std::cout << "Deleted bucket policy from '" << bucket_name <<
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

This function succeeds even if the bucket doesn’t already have a policy\. If you specify a bucket name that doesn’t exist or if you don’t have access to the bucket, an `AmazonServiceException` is thrown\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/delete_bucket_policy.cpp) on Github\.

## More Info<a name="more-info"></a>
+  [PutBucketPolicy](https://docs.aws.amazon.com/AmazonS3/latest/API/PutBucketPolicy.html) in the Amazon Simple Storage Service API Reference
+  [GetBucketPolicy](https://docs.aws.amazon.com/AmazonS3/latest/API/GetBucketPolicy.html) in the Amazon Simple Storage Service API Reference
+  [DeleteBucketPolicy](https://docs.aws.amazon.com/AmazonS3/latest/API/DeleteBucketPolicy.html) in the Amazon Simple Storage Service API Reference
+  [Access Policy Language Overview](https://docs.aws.amazon.com/AmazonS3/latest/dev/access-policy-language-overview.html) in the Amazon Simple Storage Service Developer Guide
+  [Bucket Policy Examples](https://docs.aws.amazon.com/AmazonS3/latest/dev/example-bucket-policies.html) in the Amazon Simple Storage Service Developer Guide