# Using Alarm Actions in CloudWatch<a name="examples-cloudwatch-use-alarm-actions"></a>

Using CloudWatch alarm actions, you can create alarms that perform actions such as automatically stopping, terminating, rebooting, or recovering Amazon EC2 instances\.

Alarm actions can be added to an alarm by using the [PutMetricAlarmRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_put_metric_alarm_request.html)’s `SetAlarmActions` function when [creating an alarm](examples-cloudwatch-create-alarms.md)\.

**Note**  
These code snippets assume that you understand the material in [Getting Started Using the AWS SDK for C\+\+](getting-started.md) and have configured default AWS credentials using the information in [Providing AWS Credentials](credentials.md)\.

## Enable Alarm Actions<a name="enable-alarm-actions"></a>

To enable alarm actions for a CloudWatch alarm, call the CloudWatchClient’s `EnableAlarmActions` with a [EnableAlarmActionsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_enable_alarm_actions_request.html) containing one or more names of alarms whose actions you want to enable\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/monitoring/CloudWatchClient.h>
#include <aws/monitoring/model/EnableAlarmActionsRequest.h>
#include <aws/monitoring/model/PutMetricAlarmRequest.h>
#include <iostream>
```

 **Code** 

```
Aws::CloudWatch::CloudWatchClient cw;
Aws::CloudWatch::Model::PutMetricAlarmRequest request;
request.SetAlarmName(alarm_name);
request.SetComparisonOperator(
    Aws::CloudWatch::Model::ComparisonOperator::GreaterThanThreshold);
request.SetEvaluationPeriods(1);
request.SetMetricName("CPUUtilization");
request.SetNamespace("AWS/EC2");
request.SetPeriod(60);
request.SetStatistic(Aws::CloudWatch::Model::Statistic::Average);
request.SetThreshold(70.0);
request.SetActionsEnabled(false);
request.SetAlarmDescription("Alarm when server CPU exceeds 70%");
request.SetUnit(Aws::CloudWatch::Model::StandardUnit::Seconds);
request.AddAlarmActions(actionArn);

Aws::CloudWatch::Model::Dimension dimension;
dimension.SetName("InstanceId");
dimension.SetValue(instanceId);
request.AddDimensions(dimension);

auto outcome = cw.PutMetricAlarm(request);
if (!outcome.IsSuccess())
{
    std::cout << "Failed to create CloudWatch alarm:" <<
        outcome.GetError().GetMessage() << std::endl;
    return;
}

Aws::CloudWatch::Model::EnableAlarmActionsRequest enable_request;
enable_request.AddAlarmNames(alarm_name);

auto enable_outcome = cw.EnableAlarmActions(enable_request);
if (!enable_outcome.IsSuccess())
{
    std::cout << "Failed to enable alarm actions:" <<
        enable_outcome.GetError().GetMessage() << std::endl;
    return;
}

std::cout << "Successfully created alarm " << alarm_name <<
    " and enabled actions on it." << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/cloudwatch/enable_alarm_actions.cpp)\.

## Disable Alarm Actions<a name="disable-alarm-actions"></a>

To disable alarm actions for a CloudWatch alarm, call the CloudWatchClient’s `DisableAlarmActions` with a [DisableAlarmActionsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_disable_alarm_actions_request.html) containing one or more names of alarms whose actions you want to disable\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/monitoring/CloudWatchClient.h>
#include <aws/monitoring/model/DisableAlarmActionsRequest.h>
#include <iostream>
```

 **Code** 

```
Aws::CloudWatch::CloudWatchClient cw;

Aws::CloudWatch::Model::DisableAlarmActionsRequest disableAlarmActionsRequest;
disableAlarmActionsRequest.AddAlarmNames(alarm_name);

auto disableAlarmActionsOutcome = cw.DisableAlarmActions(disableAlarmActionsRequest);
if (!disableAlarmActionsOutcome.IsSuccess())
{
    std::cout << "Failed to disable actions for alarm " << alarm_name <<
        ": " << disableAlarmActionsOutcome.GetError().GetMessage() <<
        std::endl;
}
else
{
    std::cout << "Successfully disabled actions for alarm " <<
        alarm_name << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/cloudwatch/disable_alarm_actions.cpp)\.

## More Information<a name="more-information"></a>
+  [Create Alarms to Stop, Terminate, Reboot, or Recover an Instance](https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/UsingAlarmActions.html) in the Amazon CloudWatch User Guide
+  [PutMetricAlarm](https://docs.aws.amazon.com/AmazonCloudWatch/latest/APIReference/PutMetricAlarm.html) in the Amazon CloudWatch API Reference
+  [EnableAlarmActions](https://docs.aws.amazon.com/AmazonCloudWatch/latest/APIReference/EnableAlarmActions.html) in the Amazon CloudWatch API Reference
+  [DisableAlarmActions](https://docs.aws.amazon.com/AmazonCloudWatch/latest/APIReference/DisableAlarmActions.html) in the Amazon CloudWatch API Reference