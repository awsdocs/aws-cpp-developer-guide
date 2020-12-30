# Service Client Classes<a name="using-service-client"></a>

The AWS SDK for C\+\+ includes client classes that provide interfaces to the AWS services\. Each client class supports a particular AWS service\. For example, the `S3Client` provides an interface to the Amazon S3 service\.

The namespace for a client class follows the convention `Aws::Service::ServiceClient`\. For example, the client class for AWS Identity and Access Management \(IAM\) is `Aws::IAM::IAMClient` and the Amazon S3 client class is `Aws::S3::S3Client`\.

All client classes for all AWS services are thread\-safe\.

When instantiating a client class, AWS credentials must be supplied\. For more information about credentials, see [Providing AWS Credentials](credentials.md)\.