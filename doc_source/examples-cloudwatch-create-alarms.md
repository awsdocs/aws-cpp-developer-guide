# Working with CloudWatch Alarms<a name="examples-cloudwatch-create-alarms"></a>

**Note**  
These code snippets assume that you understand the material in [Getting Started Using the AWS SDK for C\+\+](getting-started.md) and have configured default AWS credentials using the information in [Providing AWS Credentials](credentials.md)\.

## Create an Alarm<a name="create-an-alarm"></a>

To create an alarm based on a CloudWatch metric, call the CloudWatchClient’s `PutMetricAlarm` function with a [PutMetricAlarmRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_put_metric_alarm_request.html) filled with the alarm conditions\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/monitoring/CloudWatchClient.h>
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

Aws::CloudWatch::Model::Dimension dimension;
dimension.SetName("InstanceId");
dimension.SetValue(instanceId);

request.AddDimensions(dimension);

auto outcome = cw.PutMetricAlarm(request);
if (!outcome.IsSuccess())
{
    std::cout << "Failed to create CloudWatch alarm:" <<
        outcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully created CloudWatch alarm " << alarm_name
        << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/cloudwatch/put_metric_alarm.cpp)\.

## List Alarms<a name="list-alarms"></a>

To list the CloudWatch alarms that you have created, call the CloudWatchClient’s `DescribeAlarms` function with a [DescribeAlarmsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_describe_alarms_request.html) that you can use to set options for the result\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/monitoring/CloudWatchClient.h>
#include <aws/monitoring/model/DescribeAlarmsRequest.h>
#include <aws/monitoring/model/DescribeAlarmsResult.h>
#include <iomanip>
#include <iostream>
```

 **Code** 

```
Aws::CloudWatch::CloudWatchClient cw;
Aws::CloudWatch::Model::DescribeAlarmsRequest request;
request.SetMaxRecords(1);

bool done = false;
bool header = false;
while (!done)
{
    auto outcome = cw.DescribeAlarms(request);
    if (!outcome.IsSuccess())
    {
        std::cout << "Failed to describe CloudWatch alarms:" <<
            outcome.GetError().GetMessage() << std::endl;
        break;
    }

    if (!header)
    {
        std::cout << std::left <<
            std::setw(32) << "Name" <<
            std::setw(64) << "Arn" <<
            std::setw(64) << "Description" <<
            std::setw(20) << "LastUpdated" <<
            std::endl;
        header = true;
    }

    const auto &alarms = outcome.GetResult().GetMetricAlarms();
    for (const auto &alarm : alarms)
    {
        std::cout << std::left <<
            std::setw(32) << alarm.GetAlarmName() <<
            std::setw(64) << alarm.GetAlarmArn() <<
            std::setw(64) << alarm.GetAlarmDescription() <<
            std::setw(20) <<
            alarm.GetAlarmConfigurationUpdatedTimestamp().ToGmtString(
                SIMPLE_DATE_FORMAT_STR) <<
            std::endl;
    }

    const auto &next_token = outcome.GetResult().GetNextToken();
    request.SetNextToken(next_token);
    done = next_token.empty();
}
```

The list of alarms can be obtained by calling `getMetricAlarms` on the [DescribeAlarmsResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_describe_alarms_result.html) that is returned by `DescribeAlarms`\.

The results may be *paged*\. To retrieve the next batch of results, call `SetNextToken` on the original request object with the return value of the `DescribeAlarmsResult` object’s `GetNextToken` function, and pass the modified request object back to another call to `DescribeAlarms`\.

**Note**  
You can also retrieve alarms for a specific metric by using the CloudWatchClient’s `DescribeAlarmsForMetric` function\. Its use is similar to `DescribeAlarms`\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/cloudwatch/describe_alarms.cpp)\.

## Delete Alarms<a name="delete-alarms"></a>

To delete CloudWatch alarms, call the CloudWatchClient’s `DeleteAlarms` function with a [DeleteAlarmsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_delete_alarms_request.html) containing one or more names of alarms that you want to delete\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/monitoring/CloudWatchClient.h>
#include <aws/monitoring/model/DeleteAlarmsRequest.h>
#include <iostream>
```

 **Code** 

```
Aws::CloudWatch::CloudWatchClient cw;
Aws::CloudWatch::Model::DeleteAlarmsRequest request;
request.AddAlarmNames(alarm_name);

auto outcome = cw.DeleteAlarms(request);
if (!outcome.IsSuccess())
{
    std::cout << "Failed to delete CloudWatch alarm:" <<
        outcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully deleted CloudWatch alarm " << alarm_name
        << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/cloudwatch/delete_alarm.cpp)\.

## More Information<a name="more-information"></a>
+  [Creating Amazon CloudWatch Alarms](https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/AlarmThatSendsEmail.html) in the Amazon CloudWatch User Guide
+  [PutMetricAlarm](https://docs.aws.amazon.com/AmazonCloudWatch/latest/APIReference/PutMetricAlarm.html) in the Amazon CloudWatch API Reference
+  [DescribeAlarms](https://docs.aws.amazon.com/AmazonCloudWatch/latest/APIReference/DescribeAlarms.html) in the Amazon CloudWatch API Reference
+  [DeleteAlarms](https://docs.aws.amazon.com/AmazonCloudWatch/latest/APIReference/DeleteAlarms.html) in the Amazon CloudWatch API Reference