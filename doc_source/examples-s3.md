# Amazon S3 code examples using the AWS SDK for C\+\+<a name="examples-s3"></a>

Amazon Simple Storage Service \(Amazon S3\) is storage for the internet\. You can use the following examples to program [Amazon S3](https://aws.amazon.com/s3) using the AWS SDK for C\+\+\. The Amazon S3 example is catered specifically to work with CURL on Linux/Mac \(though can be modified to work on Windows\)\.

Get the source and build the project\. If you are on Windows, first delete the file `list_buckets_disabling_dns_cache.cpp` because it relies on the curl HttpClient of Linux\.

**Note**  
Only the code that is necessary to demonstrate each technique is supplied here, but [complete example code is available on GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp), where you can download a single source file or you can clone the repository locally to get all examples, build and run them\.

**Topics**
+ [Creating, listing, and deleting buckets](examples-s3-buckets.md)
+ [Operations on Objects](examples-s3-objects.md)
+ [Managing Amazon S3 Access Permissions](examples-s3-access-permissions.md)
+ [Managing Access to Amazon S3 Buckets Using Bucket Policies](examples-s3-bucket-policies.md)
+ [Configuring an Amazon S3 Bucket as a Website](examples-s3-website-configuration.md)