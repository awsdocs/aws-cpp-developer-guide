# Set the default settings for sending SMS messages<a name="sns_SetSmsAttributes_cpp_topic"></a>

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