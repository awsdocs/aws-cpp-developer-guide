# Delete a subscription<a name="sns_Unsubscribe_cpp_topic"></a>

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