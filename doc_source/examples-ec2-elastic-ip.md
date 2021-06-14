# Using Elastic IP Addresses in Amazon EC2<a name="examples-ec2-elastic-ip"></a>

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Allocate an Elastic IP Address<a name="allocate-an-elastic-ip-address"></a>

To use an Elastic IP address, you first allocate one to your account, and then associate it with your instance or a network interface\.

To allocate an Elastic IP address, call the EC2Client’s `AllocateAddress` function with an [AllocateAddressRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_allocate_address_request.html) object containing the network type \(classic EC2 or VPC\)\.

The [AllocateAddressResponse](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_allocate_address_response.html) class in the response object contains an allocation ID that you can use to associate the address with an instance, by passing the allocation ID and instance ID in a [AssociateAddressRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_associate_address_request.html) to the EC2Client’s `AssociateAddress` function\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/AllocateAddressRequest.h>
#include <aws/ec2/model/AllocateAddressResponse.h>
#include <aws/ec2/model/AssociateAddressRequest.h>
#include <aws/ec2/model/AssociateAddressResponse.h>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;

Aws::EC2::Model::AllocateAddressRequest request;
request.SetDomain(Aws::EC2::Model::DomainType::vpc);

auto outcome = ec2.AllocateAddress(request);
if (!outcome.IsSuccess())
{
    std::cout << "Failed to allocate elastic ip address:" <<
        outcome.GetError().GetMessage() << std::endl;
    return;
}

Aws::String allocation_id = outcome.GetResult().GetAllocationId();

Aws::EC2::Model::AssociateAddressRequest associate_request;
associate_request.SetInstanceId(instance_id);
associate_request.SetAllocationId(allocation_id);

auto associate_outcome = ec2.AssociateAddress(associate_request);
if (!associate_outcome.IsSuccess())
{
    std::cout << "Failed to associate elastic ip address" << allocation_id
        << " with instance " << instance_id << ":" <<
        associate_outcome.GetError().GetMessage() << std::endl;
    return;
}

std::cout << "Successfully associated elastic ip address " << allocation_id
    << " with instance " << instance_id << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/allocate_address.cpp)\.

## Describe Elastic IP Addresses<a name="describe-elastic-ip-addresses"></a>

To list the Elastic IP addresses assigned to your account, call the EC2Client’s `DescribeAddresses` function\. It returns an outcome object that contains a [DescribeAddressesResponse](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_addresses_response.html) which you can use to get a list of [Address](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_address.html) objects that represent the Elastic IP addresses on your account\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/DescribeAddressesRequest.h>
#include <aws/ec2/model/DescribeAddressesResponse.h>
#include <iomanip>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;
Aws::EC2::Model::DescribeAddressesRequest request;
auto outcome = ec2.DescribeAddresses(request);
if (outcome.IsSuccess())
{
    std::cout << std::left << std::setw(20) << "InstanceId" <<
        std::setw(15) << "Public IP" << std::setw(10) << "Domain" <<
        std::setw(20) << "Allocation ID" << std::setw(25) <<
        "NIC ID" << std::endl;

    const auto &addresses = outcome.GetResult().GetAddresses();
    for (const auto &address : addresses)
    {
        Aws::String domainString =
            Aws::EC2::Model::DomainTypeMapper::GetNameForDomainType(
                address.GetDomain());

        std::cout << std::left << std::setw(20) <<
            address.GetInstanceId() << std::setw(15) <<
            address.GetPublicIp() << std::setw(10) << domainString <<
            std::setw(20) << address.GetAllocationId() << std::setw(25)
            << address.GetNetworkInterfaceId() << std::endl;
    }
}
else
{
    std::cout << "Failed to describe elastic ip addresses:" <<
        outcome.GetError().GetMessage() << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/describe_addresses.cpp)\.

## Release an Elastic IP Address<a name="release-an-elastic-ip-address"></a>

To release an Elastic IP address, call the EC2Client’s `ReleaseAddress` function, passing it a [ReleaseAddressRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_release_address_request.html) containing the allocation ID of the Elastic IP address you want to release\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/ReleaseAddressRequest.h>
#include <iostream>
```

 **Code** 

```
Aws::Client::ClientConfiguration config;
config.region = Aws::Region::US_WEST_2;

Aws::EC2::EC2Client ec2(config);

Aws::EC2::Model::ReleaseAddressRequest request;
request.SetAllocationId(allocation_id);

auto outcome = ec2.ReleaseAddress(request);
if (!outcome.IsSuccess())
{
    std::cout << "Failed to release elastic ip address " <<
        allocation_id << ":" << outcome.GetError().GetMessage() <<
        std::endl;
}
else
{
    std::cout << "Successfully released elastic ip address " <<
        allocation_id << std::endl;
}
```

After you release an Elastic IP address, it is released to the AWS IP address pool and might be unavailable to you afterward\. Be sure to update your DNS records and any servers or devices that communicate with the address\. If you attempt to release an Elastic IP address that you already released, you’ll get an *AuthFailure* error if the address is already allocated to another AWS account\.

If you are using *EC2\-Classic* or a *default VPC*, then releasing an Elastic IP address automatically disassociates it from any instance that it’s associated with\. To disassociate an Elastic IP address without releasing it, use the EC2Client’s `DisassociateAddress` function\.

If you are using a non\-default VPC, you *must* use `DisassociateAddress` to disassociate the Elastic IP address before you try to release it\. Otherwise, Amazon EC2 returns an error \(*InvalidIPAddress\.InUse*\)\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/release_address.cpp)\.

## More Information<a name="more-information"></a>
+  [Elastic IP Addresses](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/elastic-ip-addresses-eip.html) in the Amazon EC2 User Guide for Linux Instances
+  [AllocateAddress](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_AllocateAddress.html) in the Amazon EC2 API Reference
+  [DescribeAddresses](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DescribeAddresses.html) in the Amazon EC2 API Reference
+  [ReleaseAddress](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_ReleaseAddress.html) in the Amazon EC2 API Reference