# Setting Visibility Timeout in Amazon SQS<a name="examples-sqs-visibility-timeout"></a>

When a message is received in Amazon SQS, it remains on the queue until it’s deleted in order to ensure receipt\. A message that was received, but not deleted, will be available in subsequent requests after a given *visibility timeout* to help prevent the message from being received more than once before it can be processed and deleted\.

When using [standard queues](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/standard-queues.html), visibility timeout isn’t a guarantee against receiving a message twice\. If you are using a standard queue, be sure that your code can handle the case where the same message has been delivered more than once\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Set the Message Visibility Timeout upon Message Receipt<a name="sqs-visibility-timeout-receipt"></a>

When you have received a message, you can modify its visibility timeout by passing its receipt handle in a [ChangeMessageVisibilityRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s_q_s_1_1_model_1_1_change_message_visibility_request.html) that you pass to the SQSClient class’ `ChangeMessageVisibility` member function\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/ChangeMessageVisibilityRequest.h>
#include <aws/sqs/model/ReceiveMessageRequest.h>
#include <aws/sqs/model/ReceiveMessageResult.h>
#include <iostream>
```

 **Code** 

```
    Aws::SQS::Model::ChangeMessageVisibilityRequest request;
    request.SetQueueUrl(queue_url);
    request.SetReceiptHandle(message.GetReceiptHandle());
    request.SetVisibilityTimeout(visibility_timeout);
    auto outcome = sqs.ChangeMessageVisibility(request);
    if (outcome.IsSuccess())
    {
        std::cout << "Successfully changed visibility of message " <<
            message.GetMessageId() << " from queue " << queue_url << std::endl;
    }
    else
    {
        std::cout << "Error changing visibility of message " <<
            message.GetMessageId() << " from queue " << queue_url << ": " <<
            outcome.GetError().GetMessage() << std::endl;
    }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sqs/change_message_visibility.cpp)\.

## More Info<a name="more-info"></a>
+  [Visibility Timeout](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-visibility-timeout.html) in the Amazon Simple Queue Service Developer Guide
+  [SetQueueAttributes](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_SetQueueAttributes.html) in the Amazon Simple Queue Service API Reference
+  [GetQueueAttributes](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_GetQueueAttributes.html) in the Amazon Simple Queue Service API Reference
+  [ReceiveMessage](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_ReceiveMessage.html) in the Amazon Simple Queue Service API Reference
+  [ChangeMessageVisibility](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_ChangeMessageVisibility.html) in the Amazon Simple Queue Service API Reference
+  [ChangeMessageVisibilityBatch](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_ChangeMessageVisibilityBatch.html) in the Amazon Simple Queue Service API Reference