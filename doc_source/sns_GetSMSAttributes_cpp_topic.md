# Get the settings for sending SMS messages<a name="sns_GetSMSAttributes_cpp_topic"></a>

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