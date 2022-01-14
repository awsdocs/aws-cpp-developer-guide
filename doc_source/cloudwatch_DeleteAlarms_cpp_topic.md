# Delete alarms<a name="cloudwatch_DeleteAlarms_cpp_topic"></a>

The following code example shows how to delete Amazon CloudWatch alarms\.

**SDK for C\+\+**  
Include the required files\.  

```
#include <aws/core/Aws.h>
#include <aws/monitoring/CloudWatchClient.h>
#include <aws/monitoring/model/DeleteAlarmsRequest.h>
#include <iostream>
```
Delete the alarm\.  

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
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/cloudwatch#code-examples)\. 
+  For API details, see [DeleteAlarms](https://docs.aws.amazon.com/goto/SdkForCpp/monitoring-2010-08-01/DeleteAlarms) in *AWS SDK for C\+\+ API Reference*\. 