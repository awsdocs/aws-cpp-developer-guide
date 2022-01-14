# Sending, Receiving, and Deleting Amazon SQS Messages<a name="examples-sqs-messages"></a>

Messages are always delivered using an [SQS queue](examples-sqs-message-queues.md)\. These C\+\+ examples show you how to use the AWS SDK for C\+\+ to send, receive, and delete Amazon SQS messages from SQS queues\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Send a Message<a name="sqs-message-send"></a>

You can add a single message to an Amazon SQS queue by calling the SQSClient class `SendMessage` member function\. You provide `SendMessage` with a [SendMessageRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s_q_s_1_1_model_1_1_send_message_request.html) object containing the queue’s [URL](examples-sqs-message-queues.md#sqs-get-queue-url), the message body, and an optional delay value \(in seconds\)\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/SendMessageRequest.h>
#include <aws/sqs/model/SendMessageResult.h>
#include <iostream>
```

 **Code** 

```
        Aws::SQS::SQSClient sqs;

        Aws::SQS::Model::SendMessageRequest sm_req;
        sm_req.SetQueueUrl(queue_url);
        sm_req.SetMessageBody(msg_body);

        auto sm_out = sqs.SendMessage(sm_req);
        if (sm_out.IsSuccess())
        {
            std::cout << "Successfully sent message to " << queue_url <<
                std::endl;
        }
        else
        {
            std::cout << "Error sending message to " << queue_url << ": " <<
                sm_out.GetError().GetMessage() << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sqs/send_message.cpp)\.

## Receive Messages<a name="sqs-messages-receive"></a>

Retrieve any messages that are currently in the queue by calling the SQSClient class `ReceiveMessage` member function, passing it the queue’s URL\. Messages are returned as a list of [Message](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s_q_s_1_1_model_1_1_message.html) objects\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/ReceiveMessageRequest.h>
#include <aws/sqs/model/ReceiveMessageResult.h>
```

 **Code** 

```
    Aws::SQS::SQSClient sqs(client_cfg);

    Aws::SQS::Model::ReceiveMessageRequest rm_req;
    rm_req.SetQueueUrl(queue_url);
    rm_req.SetMaxNumberOfMessages(1);

    auto rm_out = sqs.ReceiveMessage(rm_req);
    if (!rm_out.IsSuccess())
    {
        std::cout << "Error receiving message from queue " << queue_url << ": "
            << rm_out.GetError().GetMessage() << std::endl;
        return;
    }

    const auto& messages = rm_out.GetResult().GetMessages();
    if (messages.size() == 0)
    {
        std::cout << "No messages received from queue " << queue_url <<
            std::endl;
        return;
    }

    const auto& message = messages[0];
    std::cout << "Received message:" << std::endl;
    std::cout << "  MessageId: " << message.GetMessageId() << std::endl;
    std::cout << "  ReceiptHandle: " << message.GetReceiptHandle() << std::endl;
    std::cout << "  Body: " << message.GetBody() << std::endl << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sqs/receive_message.cpp)\.

### Delete Messages after Receipt<a name="sqs-messages-delete"></a>

After receiving a message and processing its contents, delete the message from the queue by sending the message’s receipt handle and the queue URL to the SQSClient class `DeleteMessage` member function\.

 **Includes** 

```
#include <aws/sqs/model/DeleteMessageRequest.h>
```

 **Code** 

```
    Aws::SQS::Model::DeleteMessageRequest dm_req;
    dm_req.SetQueueUrl(queue_url);
    dm_req.SetReceiptHandle(message.GetReceiptHandle());

    auto dm_out = sqs.DeleteMessage(dm_req);
    if (dm_out.IsSuccess())
    {
        std::cout << "Successfully deleted message " << message.GetMessageId()
            << " from queue " << queue_url << std::endl;
    }
    else
    {
        std::cout << "Error deleting message " << message.GetMessageId() <<
            " from queue " << queue_url << ": " <<
            dm_out.GetError().GetMessage() << std::endl;
    }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sqs/receive_message.cpp)\.

## More Info<a name="more-info"></a>
+  [How Amazon SQS Queues Work](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-how-it-works.html) in the Amazon Simple Queue Service Developer Guide
+  [SendMessage](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_SendMessage.html) in the Amazon Simple Queue Service API Reference
+  [SendMessageBatch](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_SendMessageBatch.html) in the Amazon Simple Queue Service API Reference
+  [ReceiveMessage](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_ReceiveMessage.html) in the Amazon Simple Queue Service API Reference
+  [DeleteMessage](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_DeleteMessage.html) in the Amazon Simple Queue Service API Reference