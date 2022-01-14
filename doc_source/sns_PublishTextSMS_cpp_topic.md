# Publish an SMS text message<a name="sns_PublishTextSMS_cpp_topic"></a>

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