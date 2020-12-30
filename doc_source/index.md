# AWS SDK for C++ Developer Guide

-----
*****Copyright &copy; 2020 Amazon Web Services, Inc. and/or its affiliates. All rights reserved.*****

-----
Amazon's trademarks and trade dress may not be used in 
     connection with any product or service that is not Amazon's, 
     in any manner that is likely to cause confusion among customers, 
     or in any manner that disparages or discredits Amazon. All other 
     trademarks not owned by Amazon are the property of their respective
     owners, who may or may not be affiliated with, connected to, or 
     sponsored by Amazon.

-----
## Contents
+ [AWS SDK for C++ Developer Guide](welcome.md)
+ [Getting Started Using the AWS SDK for C++](getting-started.md)
   + [Setting Up the AWS SDK for C++](setup.md)
   + [Providing AWS Credentials](credentials.md)
   + [Using the AWS SDK for C++](basic-use.md)
   + [Building Your Application with CMake](build-cmake.md)
+ [Configuring the AWS SDK for C++](configuring.md)
   + [CMake Parameters](cmake-params.md)
   + [AWS Client Configuration](client-config.md)
   + [Overriding Your HTTP Client](overriding-http-client.md)
   + [Controlling IOStreams Used by the HttpClient and the AWSClient](configuring-iostreams.md)
   + [SDK Metrics](sdk-metrics.md)
+ [Using the AWS SDK for C++](programming-general.md)
   + [Service Client Classes](using-service-client.md)
   + [Utility Modules](utility-modules.md)
   + [Memory Management](memory-management.md)
   + [Logging](logging.md)
   + [Error Handling](error-handling.md)
+ [AWS SDK for C++ Code Examples](programming-services.md)
   + [Amazon CloudWatch Examples Using the AWS SDK for C++](examples-cloudwatch.md)
      + [Getting Metrics from CloudWatch](examples-cloudwatch-get-metrics.md)
      + [Publishing Custom Metric Data](examples-cloudwatch-publish-custom-metrics.md)
      + [Working with CloudWatch Alarms](examples-cloudwatch-create-alarms.md)
      + [Using Alarm Actions in CloudWatch](examples-cloudwatch-use-alarm-actions.md)
      + [Sending Events to CloudWatch](examples-cloudwatch-send-events.md)
   + [Amazon DynamoDB Examples Using the AWS SDK for C++](examples-dynamodb.md)
      + [Working with Tables in DynamoDB](examples-dynamodb-tables.md)
      + [Working with Items in DynamoDB](examples-dynamodb-items.md)
   + [Amazon EC2 Examples Using the AWS SDK for C++](examples-ec2.md)
      + [Managing Amazon EC2 Instances](examples-ec2-instances.md)
      + [Using Elastic IP Addresses in Amazon EC2](examples-ec2-elastic-ip.md)
      + [Using Regions and Availability Zones for Amazon EC2](examples-ec2-regions-zones.md)
      + [Working with Amazon EC2 Key Pairs](examples-ec2-key-pairs.md)
      + [Working with Security Groups in Amazon EC2](examples-ec2-security-groups.md)
   + [IAM Code Examples Using the AWS SDK for C++](examples-iam.md)
      + [Managing IAM Access Keys](examples-iam-access-keys.md)
      + [Managing IAM Users](examples-iam-users.md)
      + [Using IAM Account Aliases](examples-iam-account-aliases.md)
      + [Working with IAM Policies](examples-iam-policies.md)
      + [Working with IAM Server Certificates](examples-iam-server-certificates.md)
   + [Amazon S3 Code Examples Using the AWS SDK for C++](examples-s3.md)
      + [Creating, Listing, and Deleting Buckets](examples-s3-buckets.md)
      + [Operations on Objects](examples-s3-objects.md)
      + [Managing Amazon S3 Access Permissions](examples-s3-access-permissions.md)
      + [Managing Access to Amazon S3 Buckets Using Bucket Policies](examples-s3-bucket-policies.md)
      + [Configuring an Amazon S3 Bucket as a Website](examples-s3-website-configuration.md)
   + [Amazon SQS Code Examples Using the AWS SDK for C++](examples-sqs.md)
      + [Working with Amazon SQS Message Queues](examples-sqs-message-queues.md)
      + [Sending, Receiving, and Deleting Amazon SQS Messages](examples-sqs-messages.md)
      + [Enabling Long Polling for Amazon SQS Message Queues](examples-sqs-long-polling.md)
      + [Setting Visibility Timeout in Amazon SQS](examples-sqs-visibility-timeout.md)
      + [Using Dead Letter Queues in Amazon SQS](examples-sqs-dead-letter-queues.md)
   + [Asynchronous Methods](async-methods.md)
+ [Security for AWS SDK for C++](security.md)
   + [Data Protection in AWS SDK for C++](data-protection.md)
   + [Identity and Access Management for this AWS Product or Service](security-iam.md)
   + [Compliance Validation for this AWS Product or Service](compliance-validation.md)
   + [Resilience for this AWS Product or Service](disaster-recovery-resiliency.md)
   + [Infrastructure Security for this AWS Product or Service](infrastructure-security.md)
   + [Enforcing TLS 1.2 in AWS SDK for C++](enforcing-tls.md)
   + [Amazon S3 Encryption Client Migration](s3-encryption-migration.md)
+ [Document History for the AWS SDK for C++ Developer Guide](document-history.md)