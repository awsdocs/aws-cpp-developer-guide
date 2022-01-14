# Delete a subscription filter<a name="cloudwatch-logs_DeleteSubscriptionFilter_cpp_topic"></a>

The following code example shows how to delete an Amazon CloudWatch Logs subscription filter\.

**SDK for C\+\+**  
Include the required files\.  

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/logs/CloudWatchLogsClient.h>
#include <aws/logs/model/DeleteSubscriptionFilterRequest.h>
#include <iostream>
```
Delete the subscription filter\.  

```
        Aws::CloudWatchLogs::CloudWatchLogsClient cwl;
        Aws::CloudWatchLogs::Model::DeleteSubscriptionFilterRequest request;
        request.SetFilterName(filter_name);
        request.SetLogGroupName(log_group);

        auto outcome = cwl.DeleteSubscriptionFilter(request);
        if (!outcome.IsSuccess()) {
            std::cout << "Failed to delete CloudWatch log subscription filter "
                << filter_name << ": " << outcome.GetError().GetMessage() <<
                std::endl;
        } else {
            std::cout << "Successfully deleted CloudWatch logs subscription " <<
                "filter " << filter_name << std::endl;
        }
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/cloudwatch-logs#code-examples)\. 
+  For API details, see [DeleteSubscriptionFilter](https://docs.aws.amazon.com/goto/SdkForCpp/logs-2014-03-28/DeleteSubscriptionFilter) in *AWS SDK for C\+\+ API Reference*\. 