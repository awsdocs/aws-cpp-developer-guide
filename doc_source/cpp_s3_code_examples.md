# Amazon S3 examples using SDK for C\+\+<a name="cpp_s3_code_examples"></a>

The following code examples show you how to perform actions and implement common scenarios by using the AWS SDK for C\+\+ with Amazon S3\.

*Actions* are code excerpts that show you how to call individual Amazon S3 functions\.

*Scenarios* are code examples that show you how to accomplish a specific task by calling multiple Amazon S3 functions\.

Each example includes a link to GitHub, where you can find instructions on how to set up and run the code in context\.

**Topics**
+ [Actions](#w62aac13c21b9c19c13)

## Actions<a name="w62aac13c21b9c19c13"></a>

### Add a policy to a bucket<a name="s3_PutBucketPolicy_cpp_topic"></a>

The following code example shows how to add a policy to an Amazon S3 bucket\.

**SDK for C\+\+**  
  

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
        //TODO: Set to the AWS Region in which the bucket was created.
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
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [PutBucketPolicy](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/PutBucketPolicy) in *AWS SDK for C\+\+ API Reference*\. 

### Copy an object from one bucket to another<a name="s3_CopyObject_cpp_topic"></a>

The following code example shows how to copy an Amazon S3 object from one bucket to another\.

**SDK for C\+\+**  
  

```
using namespace Aws;

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        //TODO: Name of object already in bucket.
        Aws::String objectKey = "<enter object key>";
        
        //TODO: Change from_bucket to the name of your bucket that already contains "my-file.txt". 
        Aws::String fromBucket = "<Enter bucket name>";
        
        //TODO: Change to the name of another bucket in your account.
        Aws::String toBucket = "<Enter bucket name>";
        
        //TODO: Set to the AWS Region in which the bucket was created.
        Aws::String region = "us-east-1";
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;
        
        S3::S3Client client(clientConfig);
        S3::Model::CopyObjectRequest request;

        request.WithCopySource(fromBucket + "/" + objectKey)
            .WithKey(objectKey)
            .WithBucket(toBucket);

        S3::Model::CopyObjectOutcome outcome = client.CopyObject(request);

        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            std::cout << "Error: CopyObject: " <<
               err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        }
    }
    ShutdownAPI(options);
    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [CopyObject](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/CopyObject) in *AWS SDK for C\+\+ API Reference*\. 

### Create a bucket<a name="s3_CreateBucket_cpp_topic"></a>

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

### Delete a policy from a bucket<a name="s3_DeleteBucketPolicy_cpp_topic"></a>

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

### Delete an empty bucket<a name="s3_DeleteBucket_cpp_topic"></a>

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

### Delete an object<a name="s3_DeleteObject_cpp_topic"></a>

The following code example shows how to delete an Amazon S3 object\.

**SDK for C\+\+**  
  

```
using namespace Aws;

int main()
{
    //TODO: The object_key is the unique identifier for the object in the bucket. In this example set,
    //it is the filename you added in put_object.cpp.
    Aws::String objectKey = "<Enter object key>";
    //TODO: Change from_bucket to the name of a bucket in your account.
    Aws::String fromBucket = "<Enter bucket name>";
    //TODO: Set to the AWS Region in which the bucket was created.
    Aws::String region = "us-east-1";

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;

        S3::S3Client client(clientConfig);
        Aws::S3::Model::DeleteObjectRequest request;

        request.WithKey(objectKey)
            .WithBucket(fromBucket);

        Aws::S3::Model::DeleteObjectOutcome outcome =
            client.DeleteObject(request);

        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            std::cout << "Error: DeleteObject: " <<
                err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        }
        else
        {
            std::cout << "Successfully deleted the object." << std::endl;
        }
    }
    ShutdownAPI(options);

    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [DeleteObject](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/DeleteObject) in *AWS SDK for C\+\+ API Reference*\. 

### Delete the website configuration from a bucket<a name="s3_DeleteBucketWebsite_cpp_topic"></a>

The following code example shows how to delete the website configuration from an Amazon S3 bucket\.

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
        // Create the bucket.
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;

        S3::S3Client client(clientConfig);
        Aws::S3::Model::DeleteBucketWebsiteRequest request;
        request.SetBucket(bucketName);

        Aws::S3::Model::DeleteBucketWebsiteOutcome outcome =
            client.DeleteBucketWebsite(request);

        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            std::cout << "Error: DeleteBucketWebsite: " <<
                err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        }
        else
        {
            std::cout << "Website configuration was removed." << std::endl;
        }
    }
    ShutdownAPI(options);
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [DeleteBucketWebsite](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/DeleteBucketWebsite) in *AWS SDK for C\+\+ API Reference*\. 

### Get an object from a bucket<a name="s3_GetObject_cpp_topic"></a>

The following code example shows how to read data from an object in an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
bool GetObject(const Aws::String& objectKey,
    const Aws::String& fromBucket, const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::GetObjectRequest object_request;
    object_request.SetBucket(fromBucket);
    object_request.SetKey(objectKey);

    Aws::S3::Model::GetObjectOutcome get_object_outcome = 
        s3_client.GetObject(object_request);

    if (get_object_outcome.IsSuccess())
    {
        auto& retrieved_file = get_object_outcome.GetResultWithOwnership().
            GetBody();

        // Print a beginning portion of the text file.
        std::cout << "Beginning of file contents:\n";
        char file_data[255] = { 0 };
        retrieved_file.getline(file_data, 254);
        std::cout << file_data << std::endl;

        return true;
    }
    else
    {
        auto err = get_object_outcome.GetError();
        std::cout << "Error: GetObject: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        //TODO: Change bucket_name to the name of a bucket in your account.
        const Aws::String bucket_name = "<Enter bucket name>";
        
        //TODO: The bucket "DOC-EXAMPLE-BUCKET" must have been created and previously loaded with "my-file.txt". 
        //See create_bucket.cpp and put_object.cpp to create a bucket and load an object into that bucket.
        const Aws::String object_name = "<Enter object name>";
       
        //TODO: Set to the AWS Region in which the bucket was created.
        const Aws::String region = "us-east-1";

        if (!GetObject(object_name, bucket_name, region))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [GetObject](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/GetObject) in *AWS SDK for C\+\+ API Reference*\. 

### Get the ACL of an object<a name="s3_GetObjectAcl_cpp_topic"></a>

The following code example shows how to get the access control list \(ACL\) of an Amazon S3 object\.

**SDK for C\+\+**  
  

```
bool GetBucketAcl(const Aws::String& bucketName, const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::GetBucketAclRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::GetBucketAclOutcome outcome = 
        s3_client.GetBucketAcl(request);

    if (outcome.IsSuccess())
    {
        Aws::Vector<Aws::S3::Model::Grant> grants = 
            outcome.GetResult().GetGrants();

        for (auto it = grants.begin(); it != grants.end(); it++)
        {
            Aws::S3::Model::Grant grant = *it;
            Aws::S3::Model::Grantee grantee = grant.GetGrantee();
            
            std::cout << "For bucket " << bucketName << ": " 
                << std::endl << std::endl;

            if (grantee.TypeHasBeenSet())
            {
                std::cout << "Type:          "
                    << GetGranteeTypeString(grantee.GetType()) << std::endl;
            }
            
            if (grantee.DisplayNameHasBeenSet())
            {
                std::cout << "Display name:  " 
                    << grantee.GetDisplayName() << std::endl;
            }

            if (grantee.EmailAddressHasBeenSet())
            {
                std::cout << "Email address: " 
                    << grantee.GetEmailAddress() << std::endl;
            }

            if (grantee.IDHasBeenSet())
            {
                std::cout << "ID:            " 
                    << grantee.GetID() << std::endl;
            }
            
            if (grantee.URIHasBeenSet())
            {
                std::cout << "URI:           " 
                    << grantee.GetURI() << std::endl;
            }
            
            std::cout << "Permission:    " << 
                GetPermissionString("bucket", grant.GetPermission()) << 
                std::endl << std::endl;
        }
    }
    else
    {
        auto err = outcome.GetError();
        std::cout << "Error: GetBucketAcl: " 
            << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }

    return true;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [GetObjectAcl](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/GetObjectAcl) in *AWS SDK for C\+\+ API Reference*\. 

### Get the policy for a bucket<a name="s3_GetBucketPolicy_cpp_topic"></a>

The following code example shows how to get the policy for an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
bool GetBucketPolicy(const Aws::String& bucketName, 
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
    const Aws::String bucket_name = "<Enter bucket name>";
    //TODO: Set to the AWS Region in which the bucket was created.
    const Aws::String region = "us-east-1";

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        if (!GetBucketPolicy(bucket_name, region))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [GetBucketPolicy](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/GetBucketPolicy) in *AWS SDK for C\+\+ API Reference*\. 

### Get the website configuration for a bucket<a name="s3_GetBucketWebsite_cpp_topic"></a>

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

### List buckets<a name="s3_ListBuckets_cpp_topic"></a>

The following code example shows how to list Amazon S3 buckets\.

**SDK for C\+\+**  
  

```
using namespace Aws;

int main()
{
    //The Aws::SDKOptions struct contains SDK configuration options.
    //An instance of Aws::SDKOptions is passed to the Aws::InitAPI and 
    //Aws::ShutdownAPI methods.  The same instance should be sent to both methods.
    SDKOptions options;
    options.loggingOptions.logLevel = Utils::Logging::LogLevel::Debug;

    //The AWS SDK for C++ must be initialized by calling Aws::InitAPI.
    InitAPI(options);
    {
        S3::S3Client client;

        auto outcome = client.ListBuckets();
        if (outcome.IsSuccess()) {
            std::cout << "Found " << outcome.GetResult().GetBuckets().size() << " buckets\n";
            for (auto&& b : outcome.GetResult().GetBuckets()) {
                std::cout << b.GetName() << std::endl;
            }
        }
        else {
            std::cout << "Failed with error: " << outcome.GetError() << std::endl;
        }
    }

    //Before the application terminates, the SDK must be shut down. 
    ShutdownAPI(options);
    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [ListBuckets](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/ListBuckets) in *AWS SDK for C\+\+ API Reference*\. 

### List objects in a bucket<a name="s3_ListObjects_cpp_topic"></a>

The following code example shows how to list objects in an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
bool AwsDoc::S3::ListObjects(const Aws::String& bucketName, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::ListObjectsRequest request;
    request.WithBucket(bucketName);

    auto outcome = s3_client.ListObjects(request);

    if (outcome.IsSuccess())
    {
        std::cout << "Objects in bucket '" << bucketName << "':" 
            << std::endl << std::endl;

        Aws::Vector<Aws::S3::Model::Object> objects =
            outcome.GetResult().GetContents();

        for (Aws::S3::Model::Object& object : objects)
        {
            std::cout << object.GetKey() << std::endl;
        }

        return true;
    }
    else
    {
        std::cout << "Error: ListObjects: " <<
            outcome.GetError().GetMessage() << std::endl;

        return false;
    }
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        //TODO: Name of a bucket in your account.
        //The bucket must have at least one object in it.  One way to achieve
        //this is to configure and run put_object.cpp's executable first.
        const Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";

        //TODO: Set to the AWS Region in which the bucket was created.
        Aws::String region = "us-east-1";

        if (!AwsDoc::S3::ListObjects(bucket_name, region))
        {
            return 1;
        }
        
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [ListObjects](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/ListObjects) in *AWS SDK for C\+\+ API Reference*\. 

### Set the website configuration for a bucket<a name="s3_PutBucketWebsite_cpp_topic"></a>

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

### Upload an object to a bucket<a name="s3_PutObject_cpp_topic"></a>

The following code example shows how to upload an object to an Amazon S3 bucket\.

**SDK for C\+\+**  
  

```
bool PutObject(const Aws::String& bucketName, 
    const Aws::String& objectName,
    const Aws::String& region)
{
    // Verify that the file exists.
    struct stat buffer;

    if (stat(objectName.c_str(), &buffer) == -1)
    {
        std::cout << "Error: PutObject: File '" <<
            objectName << "' does not exist." << std::endl;

        return false;
    }

    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);
    
    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bucketName);
    //We are using the name of the file as the key for the object in the bucket.
    //However, this is just a string and can set according to your retrieval needs.
    request.SetKey(objectName);

    std::shared_ptr<Aws::IOStream> input_data = 
        Aws::MakeShared<Aws::FStream>("SampleAllocationTag", 
            objectName.c_str(), 
            std::ios_base::in | std::ios_base::binary);

    request.SetBody(input_data);

    Aws::S3::Model::PutObjectOutcome outcome = 
        s3_client.PutObject(request);

    if (outcome.IsSuccess()) {

        std::cout << "Added object '" << objectName << "' to bucket '"
            << bucketName << "'.";
        return true;
    }
    else 
    {
        std::cout << "Error: PutObject: " << 
            outcome.GetError().GetMessage() << std::endl;
       
        return false;
    }
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        //TODO: Change bucket_name to the name of a bucket in your account.
        const Aws::String bucket_name = "<Enter bucket name>";
        //TODO: Create a file called "my-file.txt" in the local folder where your executables are built to.
        const Aws::String object_name = "<Enter file>";
        //TODO: Set to the AWS Region in which the bucket was created.
        const Aws::String region = "us-east-1";

        if (!PutObject(bucket_name, object_name, region)) {
            
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [PutObject](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/PutObject) in *AWS SDK for C\+\+ API Reference*\. 