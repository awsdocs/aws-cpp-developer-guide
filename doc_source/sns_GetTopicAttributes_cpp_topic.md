# Get the properties of a topic<a name="sns_GetTopicAttributes_cpp_topic"></a>

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