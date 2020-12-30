# SDK Metrics<a name="sdk-metrics"></a>

AWS SDK Metrics for Enterprise Support \(SDK Metrics\) enables Enterprise customers to collect metrics from AWS SDKs on their hosts and clients shared with AWS Enterprise Support\. SDK Metrics provides information that helps speed up detection and diagnosis of issues occurring in connections to AWS services for AWS Enterprise Support customers\.

As telemetry is collected on each host, it is relayed via UDP to 127\.0\.0\.1 \(AKA localhost\), where the CloudWatch Agent aggregates the data and sends it to the SDK Metrics service\. Therefore, to receive metrics, the CloudWatch Agent is required to be added to your instance\.

The following steps to set up SDK Metrics pertain to an Amazon EC2 instance running Amazon Linux for a client application that is using the AWS SDK for C\+\+\. SDK Metrics is also available for your production environments if you enable it while configuring the AWS SDK for C\+\+\.

To utilize SDK Metrics, run the latest version of the CloudWatch agent\. Learn how to [Configure the CloudWatch Agent for SDK Metrics](https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/Configure-CloudWatch-Agent-SDK-Metrics.html) in the Amazon CloudWatch User Guide\.

To set up SDK Metrics with the AWS SDK for C\+\+, follow these instructions:

1. Install the latest version of the AWS SDK for C\+\+\.

1. Host your project on an Amazon EC2 instance or in your local environment\.

1. Create an application with an AWS SDK for C\+\+ client to use an AWS service\.

1. Install and configure a CloudWatch agent on an EC2 instance or in your local environment\.

1. Authorize SDK Metrics to Collect and Send Metrics

1.  [Enable SDK Metrics for the AWS SDK for C\+\+](#csm-enable-agent) 

For more information, see the following:
+  [Update a CloudWatch Agent](#csm-update-agent) 
+  [Disable SDK Metrics](#csm-disable-agent) 

## Enable SDK Metrics for the AWS SDK for C\+\+<a name="csm-enable-agent"></a>

By default, SDK Metrics uses port 31000 and is disabled\.

```
//default values
 [
     'enabled' => false,
     'port' => 31000,
 ]
```

Enabling SDK Metrics is independent of configuring your credentials to use an AWS service\.

You can enable SDK Metrics by setting environment variables or by using the AWS Shared config file\.

### Option 1: Set Environment Variables<a name="option-1-set-environment-variables"></a>

If `AWS_CSM_ENABLED` is not set, the SDK checks the profile specified in the environment variable under `AWS_PROFILE` to determine if SDK Metrics is enabled\. By default this is set to `false`\.

To turn on SDK Metrics, add the following to your environmental variables\.

```
export AWS_CSM_ENABLED=true
```

 [Other configuration settings](#csm-update-agent) are available\.

Note: Enabling SDK Metrics does not configure your credentials to use an AWS service\.

### Option 2: AWS Shared Config File<a name="option-2-aws-shared-config-file"></a>

If no CSM configuration is found in the environment variables, the SDK looks for your default AWS profile field\. If `AWS_DEFAULT_PROFILE` is set to something other than default, update that profile\. To enable SDK Metrics, add `csm_enabled` to the shared config file located at `~/.aws/config`\.

```
[default]
csm_enabled = true

[profile aws_csm]
csm_enabled = true
```

 [Other configuration settings](#csm-update-agent) are available\.

Note: Enabling SDK Metrics is independent from configuring your credentials to use an AWS service\. You can use a different profile to authenticate\.

## Update a CloudWatch Agent<a name="csm-update-agent"></a>

To make changes to the port, you need to set the values and then restart any AWS jobs that are currently active\.

### Option 1: Set Environment Variables<a name="id1"></a>

Most services use the default port\. But if your service requires a unique port ID, add *AWS\_CSM\_PORT=\[port\_number\]*, to the host’s environment variables\.

```
export AWS_CSM_ENABLED=true
export AWS_CSM_PORT=1234
```

### Option 2: AWS Shared Config File<a name="id2"></a>

Most services use the default port\. But if your service requires a unique port ID, add *csm\_port = \[port\_number\]* to *\~/\.aws/config*\.

```
[default]
csm_enabled = false
csm_port = 1234

[profile aws_csm]
csm_enabled = false
csm_port = 1234
```

### Restart SDK Metrics<a name="restart-sdkm"></a>

To restart a job, run the following commands\.

```
amazon-cloudwatch-agent-ctl –a stop;
amazon-cloudwatch-agent-ctl –a start;
```

## Disable SDK Metrics<a name="csm-disable-agent"></a>

To turn off SDK Metrics, set *csm\_enabled* to *false* in your environment variables, or in your AWS Shared config file located at `~/.aws/config`\. Then restart your CloudWatch agent so that the changes can take effect\.

 **Environment Variables** 

```
export AWS_CSM_ENABLED=false
```

 **AWS Shared Config File** 

Remove *csm\_enabled* from the profiles in your AWS Shared config file located at `~/.aws/config`\.

**Note**  
Environment variables override the AWS Shared config file\. If SDK Metrics is enabled in the environment variables, the SDK Metrics remains enabled\.

```
[default]
csm_enabled = false

[profile aws_csm]
csm_enabled = false
```

To disable SDK Metrics, use the following command to stop CloudWatch Agent\.

```
sudo /opt/aws/amazon-cloudwatch-agent/bin/amazon-cloudwatch-agent-ctl -a stop &&
echo "Done"
```

If you are using other CloudWatch features, restart CloudWatch Agent with the following command\.

```
amazon-cloudwatch-agent-ctl –a start;
```

### Restart SDK Metrics<a name="id3"></a>

To restart a SDK Metrics job, run the following commands\.

```
amazon-cloudwatch-agent-ctl –a stop;
amazon-cloudwatch-agent-ctl –a start;
```

## Definitions for SDK Metrics<a name="definitions-for-sdkm"></a>

You can use the following descriptions of SDK Metrics to interpret your results\. In general, these metrics are available for review with your Technical Account Manager during regular business reviews\. AWS Support resources and your Technical Account Manager should have access to SDK Metrics data to help you resolve cases, but if you discover data that is confusing or unexpected, but doesn’t seem to be negatively impacting your applications’ performance, it is best to review that data during scheduled business reviews\.


**Metrics**  

| Metric | Definition | How to use it | 
| --- | --- | --- | 
|  CallCount  |  Total number of successful or failed API calls from your code to AWS services  |  Use it as a baseline to correlate with other metrics like errors or throttling\.  | 
|  ClientErrorCount  |  Number of API calls that fail with client errors \(4xx HTTP response codes\)\. Examples: Throttling, Access denied, S3 bucket does not exist, and Invalid parameter value\.  |  Except in certain cases related to throttling \(ex\. when throttling occurs due to a limit that needs to be increased\) this metric can indicate something in your application that needs to be fixed\.  | 
|  ConnectionErrorCount  |  Number of API calls that fail because of errors connecting to the service\. These can be caused by network issues between the customer application and AWS services including load balancers, DNS failures, transit providers\. In some cases, AWS issues may result in this error\.  |  Use this metric to determine whether issues are specific to your application or are caused by your infrastructure and/or network\. High ConnectionErrorCount could also indicate short timeout values for API calls\.  | 
|  EndToEndLatency  |  Total time for your application to make a call using the AWS SDK, inclusive of retries\. In other words, regardless of whether it is successful after several attempts, or as soon as a call fails due to an unretriable error\.  |  Determine how AWS API calls contribute to your application’s overall latency\. Higher than expected latency may be caused by issues with network, firewall, or other configuration settings, or by latency that occurs as a result of SDK retries\.  | 
|  ServerErrorCount  |  Number of API calls that fail due to server errors \(5xx HTTP response codes\) from AWS Services\. These are typically caused by AWS services\.  |  Determine cause of SDK retries or latency\. This metric will not always indicate that AWS services are at fault, as some AWS teams classify latency as an HTTP 503 response\.  | 
|  ThrottleCount  |  Number of API calls that fail due to throttling by AWS services\.  |  Use this metric to assess if your application has reached throttle limits, as well as to determine the cause of retries and application latency\. Consider distributing calls over a window instead of batching your calls\.  | 