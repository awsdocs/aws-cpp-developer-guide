# Working with Amazon EC2 Key Pairs<a name="examples-ec2-key-pairs"></a>

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Create a Key Pair<a name="create-a-key-pair"></a>

To create a key pair, call the EC2Client’s `CreateKeyPair` function with a [CreateKeyPairRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_create_key_pair_request.html) that contains the key’s name\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/CreateKeyPairRequest.h>
#include <aws/ec2/model/CreateKeyPairResponse.h>
#include <iostream>
```

 **Code** 

```
        Aws::EC2::EC2Client ec2;
        Aws::EC2::Model::CreateKeyPairRequest request;
        request.SetKeyName(pair_name);

        auto outcome = ec2.CreateKeyPair(request);
        if (!outcome.IsSuccess())
        {
            std::cout << "Failed to create key pair:" <<
                outcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            std::cout << "Successfully created key pair named " <<
                pair_name << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/ec2/create_key_pair.cpp)\.

## Describe Key Pairs<a name="describe-key-pairs"></a>

To list your key pairs or to get information about them, call the EC2Client’s `DescribeKeyPairs` function with a [DescribeKeyPairsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_key_pairs_request.html)\.

You will receive a [DescribeKeyPairsResponse](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_key_pairs_response.html) that you can use to access the list of key pairs by calling its `GetKeyPairs` function, which returns a list of [KeyPairInfo](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_key_pair_info.html) objects\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/DescribeKeyPairsRequest.h>
#include <aws/ec2/model/DescribeKeyPairsResponse.h>
#include <iomanip>
#include <iostream>
```

 **Code** 

```
        Aws::EC2::EC2Client ec2;
        Aws::EC2::Model::DescribeKeyPairsRequest request;

        auto outcome = ec2.DescribeKeyPairs(request);
        if (outcome.IsSuccess())
        {
            std::cout << std::left <<
                std::setw(32) << "Name" <<
                std::setw(64) << "Fingerprint" << std::endl;

            const auto &key_pairs = outcome.GetResult().GetKeyPairs();
            for (const auto &key_pair : key_pairs)
            {
                std::cout << std::left <<
                    std::setw(32) << key_pair.GetKeyName() <<
                    std::setw(64) << key_pair.GetKeyFingerprint() << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to describe key pairs:" <<
                outcome.GetError().GetMessage() << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/ec2/describe_key_pairs.cpp)\.

## Delete a Key Pair<a name="delete-a-key-pair"></a>

To delete a key pair, call the EC2Client’s `DeleteKeyPair` function, passing it a [DeleteKeyPairRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_delete_key_pair_request.html) that contains the name of the key pair to delete\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/DeleteKeyPairRequest.h>
#include <iostream>
```

 **Code** 

```
        Aws::EC2::EC2Client ec2;
        Aws::EC2::Model::DeleteKeyPairRequest request;

        request.SetKeyName(pair_name);
        auto outcome = ec2.DeleteKeyPair(request);

        if (!outcome.IsSuccess())
        {
            std::cout << "Failed to delete key pair " << pair_name <<
                ":" << outcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            std::cout << "Successfully deleted key pair named " << pair_name <<
                std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/ec2/delete_key_pair.cpp)\.

## More Information<a name="more-information"></a>
+  [Amazon EC2 Key Pairs](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-key-pairs.html) in the Amazon EC2 User Guide for Linux Instances
+  [CreateKeyPair](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_CreateKeyPair.html) in the Amazon EC2 API Reference
+  [DescribeKeyPairs](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DescribeKeyPairs.html) in the Amazon EC2 API Reference
+  [DeleteKeyPair](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DeleteKeyPair.html) in the Amazon EC2 API Reference