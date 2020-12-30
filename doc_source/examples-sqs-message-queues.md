# Working with Amazon SQS Message Queues<a name="examples-sqs-message-queues"></a>

A *message queue* is the logical container you use to send messages reliably in Amazon SQS\. There are two types of queues: *standard* and *first\-in, first\-out* \(FIFO\)\. To learn more about queues and the differences between these types, see the [Amazon Simple Queue Service Developer Guide](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/)\.

These C\+\+ examples show you how to use the AWS SDK for C\+\+ to create, list, delete, and get the URL of an Amazon SQS queue\.

**Note**  
These code snippets assume that you understand the material in [Getting Started Using the AWS SDK for C\+\+](getting-started.md) and have configured default AWS credentials using the information in [Providing AWS Credentials](credentials.md)\.

## Create a Queue<a name="sqs-create-queue"></a>

Use the SQSClient class `CreateQueue` member function, and provide it with a [CreateQueueRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_s_q_s_1_1_model_1_1_create_queue_request.html) object that describes the queue parameters\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/CreateQueueRequest.h>
#include <aws/sqs/model/CreateQueueResult.h>
#include <iostream>
```

 **Code** 

```
Aws::SQS::SQSClient sqs;

Aws::SQS::Model::CreateQueueRequest cq_req;
cq_req.SetQueueName(queue_name);

auto cq_out = sqs.CreateQueue(cq_req);
if (cq_out.IsSuccess())
{
    std::cout << "Successfully created queue " << queue_name << std::endl;
}
else
{
    std::cout << "Error creating queue " << queue_name << ": " <<
        cq_out.GetError().GetMessage() << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/sqs/create_queue.cpp)\.

## List Queues<a name="sqs-list-queues"></a>

To list Amazon SQS queues for your account, call the SQSClient class `ListQueues` member function, and pass it a [ListQueuesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_class_aws_1_1_s_q_s_1_1_model_1_1_list_queues_request.html) object\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/ListQueuesRequest.h>
#include <aws/sqs/model/ListQueuesResult.h>
#include <iostream>
```

 **Code** 

```
Aws::SQS::SQSClient sqs;

Aws::SQS::Model::ListQueuesRequest lq_req;

auto lq_out = sqs.ListQueues(lq_req);
if (lq_out.IsSuccess())
{
    std::cout << "Queue Urls:" << std::endl << std::endl;
    const auto &queue_urls = lq_out.GetResult().GetQueueUrls();
    for (const auto &iter : queue_urls)
    {
        std::cout << " " << iter << std::endl;
    }
}
else
{
    std::cout << "Error listing queues: " <<
        lq_out.GetError().GetMessage() << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/sqs/list_queues.cpp)\.

## Get the Queue’s URL<a name="sqs-get-queue-url"></a>

To get the URL for an existing Amazon SQS queue, call the SQSClient class `GetQueueUrl` member function\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/GetQueueUrlRequest.h>
#include <aws/sqs/model/GetQueueUrlResult.h>
#include <iostream>
```

 **Code** 

```
Aws::SQS::SQSClient sqs;

Aws::SQS::Model::GetQueueUrlRequest gqu_req;
gqu_req.SetQueueName(queue_name);

auto gqu_out = sqs.GetQueueUrl(gqu_req);
if (gqu_out.IsSuccess()) {
    std::cout << "Queue " << queue_name << " has url " <<
    gqu_out.GetResult().GetQueueUrl() << std::endl;
} else {
    std::cout << "Error getting url for queue " << queue_name << ": " <<
        gqu_out.GetError().GetMessage() << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/sqs/get_queue_url.cpp)\.

## Delete a Queue<a name="sqs-delete-queue"></a>

Provide the [URL](#sqs-get-queue-url) to the SQSClient class `DeleteQueue` member function\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/client/DefaultRetryStrategy.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/DeleteQueueRequest.h>
#include <iostream>
```

 **Code** 

```
Aws::SQS::Model::DeleteQueueRequest dq_req;
dq_req.SetQueueUrl(queue_url);

auto dq_out = sqs.DeleteQueue(dq_req);
if (dq_out.IsSuccess())
{
    std::cout << "Successfully deleted queue with url " << queue_url <<
        std::endl;
}
else
{
    std::cout << "Error deleting queue " << queue_url << ": " <<
        dq_out.GetError().GetMessage() << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/sqs/delete_queue.cpp)\.

## More Info<a name="more-info"></a>
+  [How Amazon SQS Queues Work](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-how-it-works.html) in the Amazon Simple Queue Service Developer Guide
+  [CreateQueue](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_CreateQueue.html) in the Amazon Simple Queue Service API Reference
+  [GetQueueUrl](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_GetQueueUrl.html) in the Amazon Simple Queue Service API Reference
+  [ListQueues](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_ListQueues.html) in the Amazon Simple Queue Service API Reference
+  [DeleteQueues](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/APIReference/API_DeleteQueues.html) in the Amazon Simple Queue Service API Reference