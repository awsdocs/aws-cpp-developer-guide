# Providing AWS Credentials<a name="credentials"></a>

To connect to any of the supported services with the AWS SDK for C\+\+, you must provide AWS credentials\. The AWS SDKs and CLIs use *provider chains* to look for AWS credentials in several different places, including system/user environment variables and local AWS configuration files\. For details, see [Credentials Providers](https://github.com/aws/aws-sdk-cpp/blob/master/Docs/Credentials_Providers.md) in the aws\-sdk\-cpp repository in GitHub\.

## Create an AWS account<a name="s3-1-winvs-setup-account"></a>

To create an AWS account, see [ How do I create and activate a new Amazon Web Services account?](https://aws.amazon.com/premiumsupport/knowledge-center/create-and-activate-aws-account/) 

## Create AWS credentials and a profile<a name="s3-1-winvs-setup-creds"></a>

To use the SDK, you need to create an AWS Identity and Access Management \(IAM\) user and obtain credentials for that user\. After you have those credentials, you make them available to the SDK in your development environment\. Here's how\.

**To create and use credentials**

1. Sign in to the AWS Management Console and open the IAM console at [https://console\.aws\.amazon\.com/iam/](https://console.aws.amazon.com/iam/)\.

1. Choose **Users**, and then choose **Add user**\.

1. Provide a user name\. For this tutorial, we'll use *SdkUser*\.

1. Under **Select AWS access type**, select **Programmatic access**, and then choose **Next: Permissions**\.

1. Choose **Attach existing policies directly**\.

1. In **Search**, enter **s3**, and then select **AmazonS3FullAccess**\.

1. Choose **Next: Tags**, **Next: Review**, and **Create user**\.

1. On the *Success* screen, choose **Download \.csv**\.

   The downloaded file contains the Access Key ID and the Secret Access Key for this IAM user\. Treat your Secret Access Key as a password; save in a trusted location and do not share it\. 
**Note**  
You will not have another opportunity to download or copy the Secret Access Key\.

1. Save the file in the appropriate location for your operating system\. See [Location of Credentials Files](https://docs.aws.amazon.com/credref/latest/refdocs/file-location.html)\.

The preceding procedure is the simplest of several possibilities for authentication and authorization\. For other options, see below\.

## More information on user credentials<a name="credother"></a>

To explore other ways to provide credentials to SDKs, see the following:
+ To create long\-term AWS credentials, see [Programmatic access](https://docs.aws.amazon.com/general/latest/gr/aws-sec-cred-types.html#access-keys-and-secret-access-keys) in the AWS General Reference\.
+ To create short\-term AWS credentials, see [Temporary Security Credentials](https://docs.aws.amazon.com/IAM/latest/UserGuide/id_credentials_temp.html) in the AWS Identity and Access Management User Guide\.
+ To learn more about supported provider chains, see the [AWS Tools and SDKs Shared Configuration and Credentials Reference Guide](https://docs.aws.amazon.com/credref/latest/refdocs), specifically:
  +  [The \.aws/credentials and \.aws/config files](https://docs.aws.amazon.com/credref/latest/refdocs/creds-config-files.html) 
  +  [Using environment variables](https://docs.aws.amazon.com/credref/latest/refdocs/environment-variables.html) 
  +  [role\_arn](https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-role_arn.html) \(corresponds to the `AWS_ROLE_ARN` environment variable\)
  +  [web\_identity\_token\_file](https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-web_identity_token_file.html) \(corresponds to the `AWS_WEB_IDENTITY_TOKEN_FILE` environment variable\)
  +  [role\_session\_name](https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-role_session_name.html) \(corresponds to the `AWS_ROLE_SESSION_NAME` environment variable\)
+ To learn more about the `AWS_CONTAINER_CREDENTIALS_RELATIVE_URI` environment variable, see [IAM Roles for Tasks](https://docs.aws.amazon.com/AmazonECS/latest/developerguide/task-iam-roles.html) in the Amazon ECS Developer Guide\.