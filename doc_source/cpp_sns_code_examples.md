# Amazon SNS examples using SDK for C\+\+<a name="cpp_sns_code_examples"></a>

The following code examples show you how to perform actions and implement common scenarios by using the AWS SDK for C\+\+ with Amazon SNS\.

*Actions* are code excerpts that show you how to call individual Amazon SNS functions\.

*Scenarios* are code examples that show you how to accomplish a specific task by calling multiple Amazon SNS functions\.

Each example includes a link to GitHub, where you can find instructions on how to set up and run the code in context\.

**Topics**
+ [Actions](#w62aac13c21b9c21c13)

## Actions<a name="w62aac13c21b9c21c13"></a>

### Create a topic<a name="sns_CreateTopic_cpp_topic"></a>

The following code example shows how to create an Amazon SNS topic\.

**SDK for C\+\+**  
  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::String topic_name = argv[1];
    Aws::SNS::SNSClient sns;

    Aws::SNS::Model::CreateTopicRequest ct_req;
    ct_req.SetName(topic_name);

    auto ct_out = sns.CreateTopic(ct_req);

    if (ct_out.IsSuccess())
    {
      std::cout << "Successfully created topic " << topic_name << std::endl;
    }
    else
    {
      std::cout << "Error creating topic " << topic_name << ":" <<
        ct_out.GetError().GetMessage() << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [CreateTopic](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/CreateTopic) in *AWS SDK for C\+\+ API Reference*\. 

### Delete a subscription<a name="sns_Unsubscribe_cpp_topic"></a>

The following code example shows how to delete an Amazon SNS subscription\.

**SDK for C\+\+**  
  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;
    Aws::String subscription_arn = argv[1];

    Aws::SNS::Model::UnsubscribeRequest s_req;
    s_req.SetSubscriptionArn(subscription_arn);

    auto s_out = sns.Unsubscribe(s_req);

    if (s_out.IsSuccess())
    {
      std::cout << "Unsubscribed successfully " << std::endl;
    }
    else
    {
      std::cout << "Error while unsubscribing " << s_out.GetError().GetMessage()
        << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [Unsubscribe](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/Unsubscribe) in *AWS SDK for C\+\+ API Reference*\. 

### Delete a topic<a name="sns_DeleteTopic_cpp_topic"></a>

The following code example shows how to delete an Amazon SNS topic and all subscriptions to that topic\.

**SDK for C\+\+**  
  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::String topic_arn = argv[1];
    Aws::SNS::SNSClient sns;

    Aws::SNS::Model::DeleteTopicRequest dt_req;
    dt_req.SetTopicArn(topic_arn);

    auto dt_out = sns.DeleteTopic(dt_req);

    if (dt_out.IsSuccess())
    {
      std::cout << "Successfully deleted topic " << topic_arn << std::endl;
    }
    else
    {
      std::cout << "Error deleting topic " << topic_arn << ":" <<
        dt_out.GetError().GetMessage() << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [DeleteTopic](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/DeleteTopic) in *AWS SDK for C\+\+ API Reference*\. 

### Get the properties of a topic<a name="sns_GetTopicAttributes_cpp_topic"></a>

The following code example shows how to get the properties of an Amazon SNS topic\.

**SDK for C\+\+**  
  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;
    Aws::String topic_arn = argv[1];

    Aws::SNS::Model::GetTopicAttributesRequest gta_req;
    gta_req.SetTopicArn(topic_arn);

    auto gta_out = sns.GetTopicAttributes(gta_req);

    if (gta_out.IsSuccess())
    {
      std::cout << "Topic Attributes:" << std::endl;
      for (auto const &attribute : gta_out.GetResult().GetAttributes())
      {
        std::cout << "  * " << attribute.first << " : " << attribute.second << std::endl;
      }
    }
    else
    {
      std::cout << "Error while getting Topic attributes " << gta_out.GetError().GetMessage()
        << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [GetTopicAttributes](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/GetTopicAttributes) in *AWS SDK for C\+\+ API Reference*\. 

### Get the settings for sending SMS messages<a name="sns_GetSMSAttributes_cpp_topic"></a>

The following code example shows how to get the settings for sending Amazon SNS SMS messages\.

**SDK for C\+\+**  
  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;

    Aws::SNS::Model::GetSMSAttributesRequest gsmst_req;
    //Set the request to only retrieve the DefaultSMSType setting. 
    //Without the following line, GetSMSAttributes would retrieve all settings.
    gsmst_req.AddAttributes("DefaultSMSType");

    auto gsmst_out = sns.GetSMSAttributes(gsmst_req);

    if (gsmst_out.IsSuccess())
    {
        for (auto const& att : gsmst_out.GetResult().GetAttributes())
        {
            std::cout <<  att.first << ":  " <<  att.second << std::endl;
        }
    }
    else
    {
      std::cout << "Error while getting SMS Type: '" << gsmst_out.GetError().GetMessage()
        << "'" << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [GetSMSAttributes](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/GetSMSAttributes) in *AWS SDK for C\+\+ API Reference*\. 

### List the subscribers of a topic<a name="sns_ListSubscriptions_cpp_topic"></a>

The following code example shows how to retrieve the list of subscribers of an Amazon SNS topic\.

**SDK for C\+\+**  
  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;

    Aws::SNS::Model::ListSubscriptionsRequest ls_req;

    auto ls_out = sns.ListSubscriptions(ls_req);

    if (ls_out.IsSuccess())
    {
        std::cout << "Subscriptions list:" << std::endl;
        for (auto const& subscription : ls_out.GetResult().GetSubscriptions())
        {
            std::cout << "  * " << subscription.GetSubscriptionArn() << std::endl;
        }
    }
    else
    {
      std::cout << "Error listing subscriptions " << ls_out.GetError().GetMessage() <<
        std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [ListSubscriptions](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/ListSubscriptions) in *AWS SDK for C\+\+ API Reference*\. 

### List topics<a name="sns_ListTopics_cpp_topic"></a>

The following code example shows how to list Amazon SNS topics\.

**SDK for C\+\+**  
  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;

    Aws::SNS::Model::ListTopicsRequest lt_req;

    auto lt_out = sns.ListTopics(lt_req);

    if (lt_out.IsSuccess())
    {
      std::cout << "Topics list:" << std::endl;
      for (auto const &topic : lt_out.GetResult().GetTopics())
      {
        std::cout << "  * " << topic.GetTopicArn() << std::endl;
      }
    }
    else
    {
      std::cout << "Error listing topics " << lt_out.GetError().GetMessage() <<
        std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [ListTopics](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/ListTopics) in *AWS SDK for C\+\+ API Reference*\. 

### Publish an SMS text message<a name="sns_PublishTextSMS_cpp_topic"></a>

The following code example shows how to publish SMS messages using Amazon SNS\.

**SDK for C\+\+**  
  

```
/**
 * Publish SMS: use Amazon SNS to send an SMS text message to a phone number.
 * Note: This requires additional AWS configuration prior to running example. 
 * 
 *  NOTE: When you start using Amazon SNS to send SMS messages, your AWS account is in the SMS sandbox and you can only
 *  use verified destination phone numbers. See https://docs.aws.amazon.com/sns/latest/dg/sns-sms-sandbox.html.
 *  NOTE: If destination is in the US, you also have an additional restriction that you have use a dedicated
 *  origination ID (phone number). You can request an origination number using Amazon Pinpoint for a fee.
 *  See https://aws.amazon.com/blogs/compute/provisioning-and-using-10dlc-origination-numbers-with-amazon-sns/ 
 *  for more information. 
 * 
 *  <phone_number_value> input parameter uses E.164 format. 
 *  For example, in United States, this input value should be of the form: +12223334444
 */
int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: publish_sms <message_value> <phone_number_value> " << std::endl;
    return 1;
  }

  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;
    Aws::String message = argv[1];
    Aws::String phone_number = argv[2];

    Aws::SNS::Model::PublishRequest psms_req;
    psms_req.SetMessage(message);
    psms_req.SetPhoneNumber(phone_number);

    auto psms_out = sns.Publish(psms_req);

    if (psms_out.IsSuccess())
    {
      std::cout << "Message published successfully " << psms_out.GetResult().GetMessageId()
        << std::endl;
    }
    else
    {
      std::cout << "Error while publishing message " << psms_out.GetError().GetMessage()
        << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
  return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [Publish](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/Publish) in *AWS SDK for C\+\+ API Reference*\. 

### Publish to a topic<a name="sns_Publish_cpp_topic"></a>

The following code example shows how to publish messages to an Amazon SNS topic\.

**SDK for C\+\+**  
  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;
    Aws::String message = argv[1];
    Aws::String topic_arn = argv[2];

    Aws::SNS::Model::PublishRequest psms_req;
    psms_req.SetMessage(message);
    psms_req.SetTopicArn(topic_arn);

    auto psms_out = sns.Publish(psms_req);

    if (psms_out.IsSuccess())
    {
      std::cout << "Message published successfully " << std::endl;
    }
    else
    {
      std::cout << "Error while publishing message " << psms_out.GetError().GetMessage()
        << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [Publish](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/Publish) in *AWS SDK for C\+\+ API Reference*\. 

### Set the default settings for sending SMS messages<a name="sns_SetSmsAttributes_cpp_topic"></a>

The following code example shows how to set the default settings for sending SMS messages using Amazon SNS\.

**SDK for C\+\+**  
How to use Amazon SNS to set the DefaultSMSType attribute\.  

```
  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;
    Aws::String sms_type =  argv[1];

    Aws::SNS::Model::SetSMSAttributesRequest ssmst_req;
    ssmst_req.AddAttributes("DefaultSMSType", sms_type);

    auto ssmst_out = sns.SetSMSAttributes(ssmst_req);

    if (ssmst_out.IsSuccess())
    {
      std::cout << "SMS Type set successfully " << std::endl;
    }
    else
    {
        std::cout << "Error while setting SMS Type: '" << ssmst_out.GetError().GetMessage()
            << "'" << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [SetSmsAttributes](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/SetSmsAttributes) in *AWS SDK for C\+\+ API Reference*\. 

### Subscribe a Lambda function to a topic<a name="sns_Subscribe_Lambda_cpp_topic"></a>

The following code example shows how to subscribe a Lambda function so it receives notifications from an Amazon SNS topic\.

**SDK for C\+\+**  
  

```
/**
 * Subscribe an AWS Lambda endpoint to a topic - demonstrates how to initiate a subscription to an Amazon SNS topic with delivery
 *  to an AWS Lambda function.
 * 
 *  NOTE: You must first configure AWS Lambda to run this example.  
 *         See https://docs.amazonaws.cn/en_us/lambda/latest/dg/with-sns-example.html for more information.
 *
 * <protocol_value> set to "lambda" provides delivery of JSON-encoded message to an AWS Lambda function
 *        (see https://docs.aws.amazon.com/sns/latest/api/API_Subscribe.html for available protocols).
 * <topic_arn_value> can be obtained from run_list_topics executable and includes the "arn:" prefix.
 * <lambda_function_arn> is the ARN of an AWS Lambda function.
 */

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cout << "Usage: subscribe_lamda <protocol_value=lambda> <topic_arn_value>"
                 " <lambda_function_arn>" << std::endl;
    return 1;
  }

  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;
    Aws::String protocol = argv[1];
    Aws::String topic_arn = argv[2];
    Aws::String endpoint = argv[3];

    Aws::SNS::Model::SubscribeRequest s_req;
    s_req.SetTopicArn(topic_arn);
    s_req.SetProtocol(protocol);
    s_req.SetEndpoint(endpoint);

    auto s_out = sns.Subscribe(s_req);

    if (s_out.IsSuccess())
    {
      std::cout << "Subscribed successfully " << std::endl;
    }
    else
    {
      std::cout << "Error while subscribing " << s_out.GetError().GetMessage()
        << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
  return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [Subscribe](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/Subscribe) in *AWS SDK for C\+\+ API Reference*\. 

### Subscribe a mobile application to a topic<a name="sns_Subscribe_App_cpp_topic"></a>

The following code example shows how to subscribe a mobile application endpoint so it receives notifications from an Amazon SNS topic\.

**SDK for C\+\+**  
  

```
/**
 * Subscribe an app endpoint to a topic - demonstrates how to initiate a subscription to an Amazon SNS topic
 * with delivery to a mobile app.
 * 
 *  NOTE: You must first create an endpoint by registering an app and device.  
 *     See https://docs.aws.amazon.com/sns/latest/dg/mobile-push-send-devicetoken.html for more information.
 * 
 * <protocol_value> set to "application" provides delivery of JSON-encoded message to an EndpointArn
 *         for a mobile app and device (see https://docs.aws.amazon.com/sns/latest/api/API_Subscribe.html for available protocols).
 * <topic_arn_value> can be obtained from run_list_topics executable and includes the "arn:" prefix.
 * <mobile_endpoint_arn> is the EndpointArn of a mobile app and device.
 */
int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cout << "Usage: subscribe_app <protocol_value/application> <topic_arn_value>"
                 " <mobile_endpoint_arn>" << std::endl;
    return 1;
  }

  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;
    Aws::String protocol = argv[1];
    Aws::String topic_arn = argv[2];
    Aws::String endpoint = argv[3];

    Aws::SNS::Model::SubscribeRequest s_req;
    s_req.SetTopicArn(topic_arn);
    s_req.SetProtocol(protocol);
    s_req.SetEndpoint(endpoint);

    auto s_out = sns.Subscribe(s_req);

    if (s_out.IsSuccess())
    {
      std::cout << "Subscribed successfully " << std::endl;
    }
    else
    {
      std::cout << "Error while subscribing " << s_out.GetError().GetMessage()
        << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
  return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [Subscribe](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/Subscribe) in *AWS SDK for C\+\+ API Reference*\. 

### Subscribe an email address to a topic<a name="sns_Subscribe_cpp_topic"></a>

The following code example shows how to subscribe an email address to an Amazon SNS topic\.

**SDK for C\+\+**  
  

```
/**
 * Subscribe an email address endpoint to a topic - demonstrates how to initiate a subscription to an Amazon SNS topic with delivery
 *  to an email address.
 * 
 * SNS will send a subscription confirmation email to the email address provided which you need to confirm to 
 * receive messages.
 *
 * <protocol_value> set to "email" provides delivery of message via SMTP (see https://docs.aws.amazon.com/sns/latest/api/API_Subscribe.html for available protocols).
 * <topic_arn_value> can be obtained from run_list_topics executable and includes the "arn:" prefix.
 */

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cout << "Usage: subscribe_email <protocol_value=email> <topic_arn_value>"
                 " <email_address>" << std::endl;
    return 1;
  }

  Aws::SDKOptions options;
  Aws::InitAPI(options);
  {
    Aws::SNS::SNSClient sns;
    Aws::String protocol = argv[1];
    Aws::String topic_arn = argv[2];
    Aws::String endpoint = argv[3];

    Aws::SNS::Model::SubscribeRequest s_req;
    s_req.SetTopicArn(topic_arn);
    s_req.SetProtocol(protocol);
    s_req.SetEndpoint(endpoint);

    auto s_out = sns.Subscribe(s_req);

    if (s_out.IsSuccess())
    {
      std::cout << "Subscribed successfully " << std::endl;
    }
    else
    {
      std::cout << "Error while subscribing " << s_out.GetError().GetMessage()
        << std::endl;
    }
  }

  Aws::ShutdownAPI(options);
  return 0;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/sns#code-examples)\. 
+  For API details, see [Subscribe](https://docs.aws.amazon.com/goto/SdkForCpp/sns-2010-03-31/Subscribe) in *AWS SDK for C\+\+ API Reference*\. 