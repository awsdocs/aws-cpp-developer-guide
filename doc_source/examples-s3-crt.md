# Using `S3CrtClient` for Amazon S3 operations<a name="examples-s3-crt"></a>

The `S3CrtClient` class is available in version 1\.9 of the AWS SDK for C\+\+ and improves the throughput of uploading and downloading large data files to and from Amazon S3\. For more information on the improvements of this release, see [Improving Amazon S3 Throughput with AWS SDK for C\+\+ v1\.9 ](https://github.com/aws/aws-sdk-cpp/wiki/Improving-S3-Throughput-with-AWS-SDK-for-CPP-v1.9)

The `S3CrtClient` is implemented on the top of the [AWS Common Runtime \(CRT\) libraries](https://docs.aws.amazon.com/sdkref/latest/guide/common-runtime.html)\.

**Note**  
To avoid being charged for incomplete or partial uploads, we recommend that you enable the [AbortMultipartUpload](https://docs.aws.amazon.com/AmazonS3/latest/API/API_AbortMultipartUpload.html) lifecycle rule on your Amazon S3 buckets\.  
This rule directs Amazon S3 to abort multipart uploads that don’t complete within a specified number of days after being initiated\. When the set time limit is exceeded, Amazon S3 aborts the upload and then deletes the incomplete upload data\.   
For more information, see [Setting lifecycle configuration on a bucket](https://docs.aws.amazon.com/AmazonS3/latest/userguide/how-to-set-lifecycle-configuration-intro.html) in the Amazon S3 User Guide\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Upload and download of object using `S3CrtClient`<a name="stream"></a>

This example demonstrates how to use the [https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_crt_1_1_s3_crt_client.html](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s3_crt_1_1_s3_crt_client.html)\. The example creates a bucket, uploads an object, downloads the object, then deletes the file and the bucket\. A PUT operation turns into a multipart upload\. A GET operation turns into multiple "ranged" GET requests\. For more information on multipart uploads, see [Uploading and copying objects using multipart upload](https://docs.aws.amazon.com/AmazonS3/latest/userguide/mpuoverview.html) in the Amazon S3 User Guide\. 

The provided data file, `ny.json`, gets uploaded as a multipart upload in this example\. This can be confirmed by viewing the debug logs after a successful run of the program\.

If the upload fails, an `AbortMultipartUpload` is issued in the underlying CRT library to clean up any already\-uploaded parts\. However, not all failures can be handled internally \(such as a network cable being unplugged\)\. It is recommended to create a lifecycle rule on your Amazon S3 bucket to ensure partially uploaded data does not linger on your account \(partially uploaded data is still billable\)\. To find out how to set up a lifecycle rule, see [Discovering and Deleting Incomplete Multipart Uploads to Lower Amazon S3 Costs](http://aws.amazon.com/blogs/aws-cost-management/discovering-and-deleting-incomplete-multipart-uploads-to-lower-amazon-s3-costs/ )\. 

**Using the debug log to explore multipart upload details**

1. In `main()`, note that there are "TODO" comments with instructions for updating the code\.

   1. For `file_name`: From the link provided in the code comment download sample data file `ny.json`, or use a large data file of your own\.

   1. For `region`: Update the `region` variable, using the enum, to the AWS Region of your account\. To find your Region of your account, log into the AWS Management Console, and locate the Region in the upper right\-hand corner\.

1. Build the example\.

1. Copy the file specified by variable `file_name` to your executable folder and run the `s3-crt-demo` executable\.

1. In your executable folder, find the most recent `.log` file\.

1. Open the log file, select **search**, and enter **partNumber**\.

1. The log contains entries similar to the following, where the `partNumber` and `uploadId` are specified for each portion of the uploaded file:

    `PUT /my-object partNumber=1&uploadId=gsk8vDbmnlA5EseDo._LDEgq22Qmt0SeuszYxMsZ9ABt503VqDIFOP8xzZI1P0zp.ToS.qo5kK16HNWogZF3KpRo.Dc7QnLZIK0BTmzCWwWoPax4T21hvP6nPdz9591F content-length:8388608 host:my-bucketasdfasdf.s3.us-east-2.amazonaws.com x-amz-content-sha256:UNSIGNED-PAYLOAD`

    and 

    `PUT /my-object partNumber=2&uploadId=gsk8vDbmnlA5EseDo._LDEgq22Qmt0SeuszYxMsZ9ABt503VqDIFOP8xzZI1P0zp.ToS.qo5kK16HNWogZF3KpRo.Dc7QnLZIK0BTmzCWwWoPax4T21hvP6nPdz9591F content-length:8388608 host:my-bucketasdfasdf.s3.us-east-2.amazonaws.com x-amz-content-sha256:UNSIGNED-PAYLOAD `

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3-crt/s3-crt-demo.cpp) on Github\.