# List topics<a name="sns_ListTopics_cpp_topic"></a>

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