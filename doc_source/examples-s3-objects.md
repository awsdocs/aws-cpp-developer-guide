# Operations on Objects<a name="examples-s3-objects"></a>

An Amazon S3 object represents a *file*, which is a collection of data\. Every object must reside within a [bucket](examples-s3-buckets.md)\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Upload an Object<a name="upload-object"></a>

Use the S3Client object `PutObject` function, supplying it with a bucket name, key name, and file to upload\. The bucket must exist or an error will result\.

 **Code** 

```
bool AwsDoc::S3::PutObject(const Aws::String& bucketName, 
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
        const Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";
        //TODO: Create a file called "my-file.txt" in the local folder where your executables are built to.
        const Aws::String object_name = "my-file.txt";
        //TODO: Set to the region in which the bucket was created.
        const Aws::String region = "us-east-1";

        if (!AwsDoc::S3::PutObject(bucket_name, object_name, region)) {
            
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/put_object.cpp) on Github\.

## List Objects<a name="list-objects"></a>

To get a list of objects within a bucket, use the S3Client object `ListObjects` function\. Supply it with a `ListObjectsRequest` that you set with the name of a bucket to list the contents of\.

The `ListObjects` function returns a `ListObjectsOutcome` object that you can use to get a list of objects in the form of `Object` instances\.

 **Code** 

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
        //The bucket must have at least one object in it.  The easiest way to achieve
        //this is to configure and run put_object.cpp's executable first.
        const Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";

        //TODO: Set to the region in which the bucket was created.
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

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/list_objects.cpp) on Github\.

## Download an Object<a name="download-object"></a>

Use the S3Client object `GetObject` function, passing it a `GetObjectRequest` that you set with the name of a bucket and the object key to download\. `GetObject` returns a `GetObjectOutcome` object that you can use to access the S3 object’s data\.

The following example downloads an object from Amazon S3\. The object contents are stored in a local variable and the first line of the contents is output to the console\.

 **Code** 

```
bool AwsDoc::S3::GetObject(const Aws::String& objectKey,
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
        //TODO: Name of a bucket in your account.
        const Aws::String bucket_name = "DOC-EXAMPLE-BUCKET";
        //TODO: The bucket "DOC-EXAMPLE-BUCKET" must have been created and previously loaded with "my-file.txt". 
        //See create_bucket.cpp and put_object.cpp to create a bucket and load an object into that bucket.
        const Aws::String object_name = "my-file.txt";
        //TODO: Set to the region in which the bucket was created.
        const Aws::String region = "us-east-1";

        if (!AwsDoc::S3::GetObject(object_name, bucket_name, region))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/get_object.cpp) on Github\.

## Delete an Object<a name="delete-object"></a>

Use the S3Client object’s `DeleteObject` function, passing it a `DeleteObjectRequest` that you set with the name of a bucket and object to download\. *The specified bucket and object key must exist or an error will result*\.

 **Code** 

```
bool AwsDoc::S3::DeleteObject(const Aws::String& objectKey, 
    const Aws::String& fromBucket,const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::DeleteObjectRequest request;

    request.WithKey(objectKey)
        .WithBucket(fromBucket);

    Aws::S3::Model::DeleteObjectOutcome outcome = 
        s3_client.DeleteObject(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "Error: DeleteObject: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    //TODO: The object_key is the unique identifier for the object in the bucket. In this example set,
    //it is the filename you added in put_object.cpp.
    Aws::String object_key = "my-file.txt";
    //TODO: Name of a bucket in your account.
    Aws::String from_bucket = "DOC-EXAMPLE-BUCKET";
    //TODO: Set to the region in which the bucket was created.
    Aws::String region = "us-east-1";

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        if (AwsDoc::S3::DeleteObject(object_key, from_bucket, region))
        {
            std::cout << "Deleted object " << object_key <<
                " from " << from_bucket << "." << std::endl;
        }
    }
    ShutdownAPI(options);

    return 0;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/delete_object.cpp) on Github\.