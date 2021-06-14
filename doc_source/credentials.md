# Providing AWS credentials<a name="credentials"></a>

To connect to any of the supported services with the AWS SDK for C\+\+, you must provide AWS credentials\. The AWS SDKs and CLIs use *provider chains* to look for AWS credentials in several different places, including system/user environment variables and local AWS configuration files\. For details, see [Credentials Providers](https://github.com/aws/aws-sdk-cpp/blob/master/Docs/Credentials_Providers.md) in the aws\-sdk\-cpp repository in GitHub\.

## Create an AWS account and administrator user<a name="s3-1-winvs-setup-account"></a>

1. **Create an account\.**

   To create an AWS account, see [How do I create and activate a new Amazon Web Services account?](https://aws.amazon.com/premiumsupport/knowledge-center/create-and-activate-aws-account)

1. **Create an administrative user\.**

   Avoid using your root user account \(the initial account you create\) to access the AWS Management Console and services\. Instead, create an administrative user account, as explained in [Creating your first IAM admin user and group](https://docs.aws.amazon.com/IAM/latest/UserGuide/getting-started_create-admin-group.html)\.

   After you create the administrative user account and record the login details, **sign out of your root user account** and sign back in using the administrative account\.

## Create AWS credentials and a profile<a name="s3-1-winvs-setup-creds"></a>

To use the SDK, create an AWS Identity and Access Management \(IAM\) user and obtain credentials for that user\. Then make them available to the SDK in your development environment by saving them to the AWS shared credentials file\.

**To create and use credentials**

1. Sign in to the AWS Management Console and open the IAM console at [https://console\.aws\.amazon\.com/iam/](https://console.aws.amazon.com/iam/)\.

1. Choose **Users**, and then choose **Add user**\.

1. Enter a user name\. For this tutorial, we'll use *SdkUser*\.

1. Under **Select AWS access type**, select **Programmatic access**, and then choose **Next: Permissions**\.

1. Choose **Attach existing policies directly**\.

1. In **Search**, enter **s3**, and then select **AmazonS3FullAccess**\.

1. Choose **Next: Tags**, **Next: Review**, and **Create user**\.

1. On the *Success* screen, choose **Download \.csv**\.

   The downloaded file contains the Access Key ID and the Secret Access Key for this IAM user\. 
**Note**  
You will not have another opportunity to download or copy the Secret Access Key\.

1. Treat your Secret Access Key as a password; save in a trusted location and do not share it\. 
**Warning**  
Use appropriate security measures to keep these credentials safe and rotated\.

1. Create or open the AWS shared credentials file\. This file is `~/.aws/credentials` on Linux and macOS systems, and `%USERPROFILE%\.aws\credentials` on Windows\.

1. Add the following text to the AWS shared credentials file, but replace the example ID value and example key value with the ones you obtained earlier\. Save the file\. See [Location of Credentials Files](https://docs.aws.amazon.com/credref/latest/refdocs/file-location.html) for more information\.

   ```
   [default]
   aws_access_key_id = AKIAIOSFODNN7EXAMPLE
   aws_secret_access_key = wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
   ```

   

The preceding procedure is the simplest of several possibilities for authentication and authorization\. For other options, see below\.

## More information on user credentials<a name="credother"></a>

To explore other ways to provide credentials to SDKs, see the following:
+ To create long\-term AWS credentials, see [Programmatic access](https://docs.aws.amazon.com/general/latest/gr/aws-sec-cred-types.html#access-keys-and-secret-access-keys) in the AWS General Reference\.
+ To create short\-term AWS credentials, see [Temporary Security Credentials](https://docs.aws.amazon.com/IAM/latest/UserGuide/id_credentials_temp.html) in the IAM User Guide\.
+ To learn more about supported provider chains, see the [AWS SDKs and Tools Reference Guide](https://docs.aws.amazon.com/sdkref/latest/guide/), specifically:
  +  [The \.aws/credentials and \.aws/config files](https://docs.aws.amazon.com/sdkref/latest/guide/creds-config-files.html) 
  +  [Using environment variables](https://docs.aws.amazon.com/sdkref/latest/guide/environment-variables.html) 
  +  [role\_arn](https://docs.aws.amazon.com/sdkref/latest/guide/setting-global-role_arn.html) \(corresponds to the `AWS_ROLE_ARN` environment variable\)
  +  [web\_identity\_token\_file](https://docs.aws.amazon.com/sdkref/latest/guide/setting-global-web_identity_token_file.html) \(corresponds to the `AWS_WEB_IDENTITY_TOKEN_FILE` environment variable\)
  +  [role\_session\_name](https://docs.aws.amazon.com/sdkref/latest/guide/setting-global-role_session_name.html) \(corresponds to the `AWS_ROLE_SESSION_NAME` environment variable\)
+ To learn more about the `AWS_CONTAINER_CREDENTIALS_RELATIVE_URI` environment variable, see [IAM Roles for Tasks](https://docs.aws.amazon.com/AmazonECS/latest/developerguide/task-iam-roles.html) in the Amazon Elastic Container Service Developer Guide\.