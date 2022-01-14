# Sending Events to CloudWatch<a name="examples-cloudwatch-send-events"></a>

CloudWatch Events delivers a near real\-time stream of system events that describe changes in AWS resources to Amazon EC2 instances, Lambda functions, Kinesis streams, Amazon ECS tasks, Step Functions state machines, Amazon SNS topics, Amazon SQS queues, or built\-in targets\. You can match events and route them to one or more target functions or streams by using simple rules\.

**Note**  
These code snippets assume that you understand the material in [Getting Started Using the AWS SDK for C\+\+](getting-started.md) and have configured default AWS credentials using the information in [Providing AWS Credentials](credentials.md)\.

## Add Events<a name="add-events"></a>

To add custom CloudWatch events, call the CloudWatchEventsClient’s `PutEvents` function with a [PutEventsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_events_1_1_model_1_1_put_events_request.html) object that contains one or more [PutEventsRequestEntry](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_events_1_1_model_1_1_put_events_request_entry.html) objects that provide details about each event\. You can specify several parameters for the entry such as the source and type of the event, resources associated with the event, and so on\.

**Note**  
You can specify a maximum of 10 events per call to `putEvents`\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/events/EventBridgeClient.h>
#include <aws/events/model/PutEventsRequest.h>
#include <aws/events/model/PutEventsResult.h>
#include <aws/core/utils/Outcome.h>
#include <iostream>
```

 **Code** 

```
        Aws::CloudWatchEvents::EventBridgeClient cwe;

        Aws::CloudWatchEvents::Model::PutEventsRequestEntry event_entry;
        event_entry.SetDetail(MakeDetails(event_key, event_value));
        event_entry.SetDetailType("sampleSubmitted");
        event_entry.AddResources(resource_arn);
        event_entry.SetSource("aws-sdk-cpp-cloudwatch-example");

        Aws::CloudWatchEvents::Model::PutEventsRequest request;
        request.AddEntries(event_entry);

        auto outcome = cwe.PutEvents(request);
        if (!outcome.IsSuccess())
        {
            std::cout << "Failed to post CloudWatch event: " <<
                outcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            std::cout << "Successfully posted CloudWatch event" << std::endl;
        }
```

## Add Rules<a name="add-rules"></a>

To create or update a rule, call the CloudWatchEventsClient’s `PutRule` function with a [PutRuleRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_events_1_1_model_1_1_put_rule_request.html) with the name of the rule and optional parameters such as the [event pattern](https://docs.aws.amazon.com/AmazonCloudWatch/latest/events/CloudWatchEventsandEventPatterns.html), IAM role to associate with the rule, and a [scheduling expression](https://docs.aws.amazon.com/AmazonCloudWatch/latest/events/ScheduledEvents.html) that describes how often the rule is run\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/events/EventBridgeClient.h>
#include <aws/events/model/PutRuleRequest.h>
#include <aws/events/model/PutRuleResult.h>
#include <aws/core/utils/Outcome.h>
#include <iostream>
```

 **Code** 

```
        Aws::CloudWatchEvents::EventBridgeClient cwe;
        Aws::CloudWatchEvents::Model::PutRuleRequest request;
        request.SetName(rule_name);
        request.SetRoleArn(role_arn);
        request.SetScheduleExpression("rate(5 minutes)");
        request.SetState(Aws::CloudWatchEvents::Model::RuleState::ENABLED);

        auto outcome = cwe.PutRule(request);
        if (!outcome.IsSuccess())
        {
            std::cout << "Failed to create CloudWatch events rule " <<
                rule_name << ": " << outcome.GetError().GetMessage() <<
                std::endl;
        }
        else
        {
            std::cout << "Successfully created CloudWatch events rule " <<
                rule_name << " with resulting Arn " <<
                outcome.GetResult().GetRuleArn() << std::endl;
        }
```

## Add Targets<a name="add-targets"></a>

Targets are the resources that are invoked when a rule is triggered\. Example targets include Amazon EC2 instances, Lambda functions, Kinesis streams, Amazon ECS tasks, Step Functions state machines, and built\-in targets\.

To add a target to a rule, call the CloudWatchEventsClient’s `PutTargets` function with a [PutTargetsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_cloud_watch_events_1_1_model_1_1_put_targets_request.html) containing the rule to update and a list of targets to add to the rule\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/events/EventBridgeClient.h>
#include <aws/events/model/PutTargetsRequest.h>
#include <aws/events/model/PutTargetsResult.h>
#include <aws/core/utils/Outcome.h>
#include <iostream>
```

 **Code** 

```
        Aws::CloudWatchEvents::EventBridgeClient cwe;

        Aws::CloudWatchEvents::Model::Target target;
        target.SetArn(lambda_arn);
        target.SetId(target_id);

        Aws::CloudWatchEvents::Model::PutTargetsRequest request;
        request.SetRule(rule_name);
        request.AddTargets(target);

        auto putTargetsOutcome = cwe.PutTargets(request);
        if (!putTargetsOutcome.IsSuccess())
        {
            std::cout << "Failed to create CloudWatch events target for rule "
                << rule_name << ": " <<
                putTargetsOutcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            std::cout <<
                "Successfully created CloudWatch events target for rule "
                << rule_name << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/eventbridge/put_targets.cpp)\.

## More Information<a name="more-information"></a>
+  [Adding Events with PutEvents](https://docs.aws.amazon.com/AmazonCloudWatch/latest/events/AddEventsPutEvents.html) in the Amazon CloudWatch Events User Guide
+  [Schedule Expressions for Rules](https://docs.aws.amazon.com/AmazonCloudWatch/latest/events/ScheduledEvents.html) in the Amazon CloudWatch Events User Guide
+  [Event Types for CloudWatch Events](https://docs.aws.amazon.com/AmazonCloudWatch/latest/events/EventTypes.html) in the Amazon CloudWatch Events User Guide
+  [Events and Event Patterns](https://docs.aws.amazon.com/AmazonCloudWatch/latest/events/CloudWatchEventsandEventPatterns.html) in the Amazon CloudWatch Events User Guide
+  [PutEvents](https://docs.aws.amazon.com/AmazonCloudWatchEvents/latest/APIReference/PutEvents.html) in the Amazon CloudWatch Events API Reference
+  [PutTargets](https://docs.aws.amazon.com/AmazonCloudWatchEvents/latest/APIReference/PutTargets.html) in the Amazon CloudWatch Events API Reference
+  [PutRule](https://docs.aws.amazon.com/AmazonCloudWatchEvents/latest/APIReference/PutRule.html) in the Amazon CloudWatch Events API Reference