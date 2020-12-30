# Providing AWS Credentials<a name="credentials"></a>

To connect to any of the supported services with the AWS SDK for C\+\+, you must provide AWS credentials\. The AWS SDKs and CLIs use *provider chains* to look for AWS credentials in several different places, including system/user environment variables and local AWS configuration files\. For details, see [Credentials Providers](https://github.com/aws/aws-sdk-cpp/blob/master/Docs/Credentials_Providers.md) in the aws\-sdk\-cpp repository in GitHub\.

For related information, see the following:
+ To create a new AWS account, see [How do I create and activate a new AWS account](https://aws.amazon.com/premiumsupport/knowledge-center/create-and-activate-aws-account/) on the AWS Premium Support website\.
+ To create long\-term AWS credentials, see [Programmatic access](https://docs.aws.amazon.com/general/latest/gr/aws-sec-cred-types.html#access-keys-and-secret-access-keys) in the AWS General Reference\.
+ To create short\-term AWS credentials, see [Temporary Security Credentials](https://docs.aws.amazon.com/IAM/latest/UserGuide/id_credentials_temp.html) in the AWS Identity and Access Management User Guide\.
+ To learn more about supported provider chains, see the [AWS Tools and SDKs Shared Configuration and Credentials Reference Guide](https://docs.aws.amazon.com/credref/latest/refdocs), specifically:
  +  [The \.aws/credentials and \.aws/config files](https://docs.aws.amazon.com/credref/latest/refdocs/creds-config-files.html) 
  +  [Using environment variables](https://docs.aws.amazon.com/credref/latest/refdocs/environment-variables.html) 
  +  [role\_arn](https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-role_arn.html) \(corresponds to the `AWS_ROLE_ARN` environment variable\)
  +  [web\_identity\_token\_file](https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-web_identity_token_file.html) \(corresponds to the `AWS_WEB_IDENTITY_TOKEN_FILE` environment variable\)
  +  [role\_session\_name](https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-role_session_name.html) \(corresponds to the `AWS_ROLE_SESSION_NAME` environment variable\)
+ To learn more about the `AWS_CONTAINER_CREDENTIALS_RELATIVE_URI` environment variable, see [IAM Roles for Tasks](https://docs.aws.amazon.com/AmazonECS/latest/developerguide/task-iam-roles.html) in the Amazon ECS Developer Guide\.