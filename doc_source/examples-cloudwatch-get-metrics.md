# Getting Metrics from CloudWatch<a name="examples-cloudwatch-get-metrics"></a>

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Listing Metrics<a name="listing-metrics"></a>

To list CloudWatch metrics, create a [ListMetricsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_list_metrics_request.html) and call the CloudWatchClient’s `ListMetrics` function\. You can use the `ListMetricsRequest` to filter the returned metrics by namespace, metric name, or dimensions\.

**Note**  
A list of metrics and dimensions that are posted by AWS services can be found within the [Amazon CloudWatch Metrics and Dimensions Reference](https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CW_Support_For_AWS.html) in the Amazon CloudWatch User Guide\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/monitoring/CloudWatchClient.h>
#include <aws/monitoring/model/ListMetricsRequest.h>
#include <aws/monitoring/model/ListMetricsResult.h>
#include <iomanip>
#include <iostream>
```

 **Code** 

```
Aws::CloudWatch::CloudWatchClient cw;
Aws::CloudWatch::Model::ListMetricsRequest request;

if (argc > 1)
{
    request.SetMetricName(argv[1]);
}

if (argc > 2)
{
    request.SetNamespace(argv[2]);
}

bool done = false;
bool header = false;
while (!done)
{
    auto outcome = cw.ListMetrics(request);
    if (!outcome.IsSuccess())
    {
        std::cout << "Failed to list CloudWatch metrics:" <<
            outcome.GetError().GetMessage() << std::endl;
        break;
    }

    if (!header)
    {
        std::cout << std::left << std::setw(48) << "MetricName" <<
            std::setw(32) << "Namespace" << "DimensionNameValuePairs" <<
            std::endl;
        header = true;
    }

    const auto &metrics = outcome.GetResult().GetMetrics();
    for (const auto &metric : metrics)
    {
        std::cout << std::left << std::setw(48) <<
            metric.GetMetricName() << std::setw(32) <<
            metric.GetNamespace();
        const auto &dimensions = metric.GetDimensions();
        for (auto iter = dimensions.cbegin();
            iter != dimensions.cend(); ++iter)
        {
            const auto &dimkv = *iter;
            std::cout << dimkv.GetName() << " = " << dimkv.GetValue();
            if (iter + 1 != dimensions.cend())
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    const auto &next_token = outcome.GetResult().GetNextToken();
    request.SetNextToken(next_token);
    done = next_token.empty();
}
```

The metrics are returned in a [ListMetricsResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_1_1_model_1_1_list_metrics_result.html) by calling its `GetMetrics` function\. The results may be *paged*\. To retrieve the next batch of results, call `SetNextToken` on the original request object with the return value of the `ListMetricsResult` object’s `GetNextToken` function, and pass the modified request object back to another call to `ListMetrics`\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/cloudwatch/list_metrics.cpp)\.

## More Information<a name="more-information"></a>
+  [ListMetrics](https://docs.aws.amazon.com/AmazonCloudWatch/latest/APIReference/ListMetrics.html) in the Amazon CloudWatch API Reference\.