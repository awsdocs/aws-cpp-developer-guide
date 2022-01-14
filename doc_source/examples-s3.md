# Amazon S3 code examples using the AWS SDK for C\+\+<a name="examples-s3"></a>

[Amazon S3](https://aws.amazon.com/s3) is object storage built to store and retrieve any amount of data from anywhere\. There are multiple classes provided by the AWS SDK for C\+\+ to interface with Amazon S3\. 

**Note**  
Only the code that is necessary to demonstrate certain techniques is supplied in this Guide, but the [complete example code is available on GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp)\. On GitHub you can download a single source file or you can clone the repository locally to get, build, and run all examples\.
+ [https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_s3_client.html](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_1_1_s3_client.html) class 

  The `S3Client` library is a fully\-featured Amazon S3 interface\.

  The `list_buckets_disabling_dns_cache.cpp` example in this set is catered specifically to work with CURL on Linux/Mac \(though can be modified to work on Windows\)\. If you are on Windows, delete the file `list_buckets_disabling_dns_cache.cpp` before building the project because it relies on the curl HttpClient of Linux\.

  The example code utilizing the `S3Client` is in the [`s3` folder](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3) on Github\. See the [Readme](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3/README.md) on Github for a full list of functions demonstrated by this example set\.

  Portions of the `s3` example set are covered in additional detail in this guide:
  + [ Creating, listing, and deleting buckets](examples-s3-buckets.md)
  + [ Operations on objects](examples-s3-objects.md) – Uploading and downloading data objects
  + [ Managing Amazon S3 Access Permissions](examples-s3-access-permissions.md)
  + [ Managing Access to Amazon S3 Buckets Using Bucket Policies](examples-s3-bucket-policies.md)
  + [ Configuring an Amazon S3 Bucket as a Website](examples-s3-website-configuration.md)
+ [https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_crt_1_1_s3_crt_client.html](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_crt_1_1_s3_crt_client.html) class 

  The `S3CrtClient` was added in version 1\.9 of the SDK\. `S3CrtClient` provides high throughput for Amazon S3 GET \(download\) and PUT \(upload\) operations\. The `S3CrtClient` is implemented on the top of the AWS Common Runtime \(CRT\) libraries\. 

  The example code utilizing the `S3CrtClient` is in the [`s3-crt` folder](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3-crt) on Github\. See the [Readme](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3-crt/README.md) on Github for a full list of functions demonstrated by this example set\.
  + [ Using `S3CrtClient` for Amazon S3 operations](examples-s3-crt.md)
+ [https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_transfer_1_1_transfer_manager.html](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_transfer_1_1_transfer_manager.html) class 

  `TransferManager` is a fully managed service that enables the transfer of files over the File Transfer Protocol \(FTP\), File Transfer Protocol over SSL \(FTPS\), or Secure Shell \(SSH\) File Transfer Protocol \(SFTP\) directly into and out of Amazon S3\.

  The example code utilizing the `TransferManager` is in the [`transfer-manager` folder](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/transfer-manager) on Github\. See the [Readme](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/transfer-manager/README.md) on Github for a full list of functions demonstrated by this example set\.
  + [ Using TransferManager for Amazon S3 operations](examples-s3-transfermanager.md)