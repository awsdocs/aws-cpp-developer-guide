# Working with Security Groups in Amazon EC2<a name="examples-ec2-security-groups"></a>

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Create a Security Group<a name="create-a-security-group"></a>

To create a security group, call the EC2Client’s `CreateSecurityGroup` function with a [CreateSecurityGroupRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_create_security_group_request.html) that contains the key’s name\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/CreateSecurityGroupRequest.h>
#include <aws/ec2/model/CreateSecurityGroupResponse.h>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;
Aws::EC2::Model::CreateSecurityGroupRequest request;

request.SetGroupName(group_name);
request.SetDescription(description);
request.SetVpcId(vpc_id);

auto outcome = ec2.CreateSecurityGroup(request);

if (!outcome.IsSuccess())
{
    std::cout << "Failed to create security group:" <<
        outcome.GetError().GetMessage() << std::endl;
    return;
}

std::cout << "Successfully created security group named " << group_name <<
    std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/create_security_group.cpp)\.

## Configure a Security Group<a name="configure-a-security-group"></a>

A security group can control both inbound \(ingress\) and outbound \(egress\) traffic to your Amazon EC2 instances\.

To add ingress rules to your security group, use the EC2Client’s `AuthorizeSecurityGroupIngress` function, providing the name of the security group and the access rules \([IpPermission](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_ip_permission.html)\) you want to assign to it within an [AuthorizeSecurityGroupIngressRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_authorize_security_group_ingress_request.html) object\. The following example shows how to add IP permissions to a security group\.

 **Includes** 

```
#include <aws/ec2/model/AuthorizeSecurityGroupIngressRequest.h>
```

 **Code** 

```
Aws::EC2::Model::AuthorizeSecurityGroupIngressRequest authorize_request;

authorize_request.SetGroupName(group_name);
```

```
Aws::EC2::Model::IpRange ip_range;
ip_range.SetCidrIp("0.0.0.0/0");

Aws::EC2::Model::IpPermission permission1;
permission1.SetIpProtocol("tcp");
permission1.SetToPort(80);
permission1.SetFromPort(80);
permission1.AddIpRanges(ip_range);

authorize_request.AddIpPermissions(permission1);

Aws::EC2::Model::IpPermission permission2;
permission2.SetIpProtocol("tcp");
permission2.SetToPort(22);
permission2.SetFromPort(22);
permission2.AddIpRanges(ip_range);

authorize_request.AddIpPermissions(permission2);
```

```
auto ingress_req = ec2.AuthorizeSecurityGroupIngress(authorize_request);

if (!ingress_req.IsSuccess())
{
    std::cout << "Failed to set ingress policy for security group " <<
        group_name << ":" << ingress_req.GetError().GetMessage() <<
        std::endl;
    return;
}

std::cout << "Successfully added ingress policy to security group " <<
    group_name << std::endl;
```

To add an egress rule to the security group, provide similar data in an [AuthorizeSecurityGroupEgressRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_authorize_security_group_egress_request.html) to the EC2Client’s `AuthorizeSecurityGroupEgress` function\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/create_security_group.cpp)\.

## Describe Security Groups<a name="describe-security-groups"></a>

To describe your security groups or get information about them, call the EC2Client’s `DescribeSecurityGroups` function with a [DescribeSecurityGroupsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_security_groups_request.html)\.

You will receive a [DescribeSecurityGroupsResponse](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_security_groups_response.html) in the outcome object that you can use to access the list of security groups by calling its `GetSecurityGroups` function, which returns a list of [SecurityGroup](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_security_group.html) objects\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/DescribeSecurityGroupsRequest.h>
#include <aws/ec2/model/DescribeSecurityGroupsResponse.h>
#include <iomanip>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;
Aws::EC2::Model::DescribeSecurityGroupsRequest request;

if (argc == 2)
{
    request.AddGroupIds(argv[1]);
}

auto outcome = ec2.DescribeSecurityGroups(request);

if (outcome.IsSuccess())
{
    std::cout << std::left <<
        std::setw(32) << "Name" <<
        std::setw(20) << "GroupId" <<
        std::setw(20) << "VpcId" <<
        std::setw(64) << "Description" << std::endl;

    const auto &securityGroups =
        outcome.GetResult().GetSecurityGroups();

    for (const auto &securityGroup : securityGroups)
    {
        std::cout << std::left <<
            std::setw(32) << securityGroup.GetGroupName() <<
            std::setw(20) << securityGroup.GetGroupId() <<
            std::setw(20) << securityGroup.GetVpcId() <<
            std::setw(64) << securityGroup.GetDescription() <<
            std::endl;
    }
}
else
{
    std::cout << "Failed to describe security groups:" <<
        outcome.GetError().GetMessage() << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/describe_security_groups.cpp)\.

## Delete a Security Group<a name="delete-a-security-group"></a>

To delete a security group, call the EC2Client’s `DeleteSecurityGroup` function, passing it a [DeleteSecurityGroupRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_delete_security_group_request.html) that contains the ID of the security group to delete\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/DeleteSecurityGroupRequest.h>
#include <iomanip>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;
Aws::EC2::Model::DeleteSecurityGroupRequest request;

request.SetGroupId(groupId);
auto outcome = ec2.DeleteSecurityGroup(request);

if (!outcome.IsSuccess())
{
    std::cout << "Failed to delete security group " << groupId <<
        ":" << outcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully deleted security group " << groupId <<
        std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/delete_security_group.cpp)\.

## More Information<a name="more-information"></a>
+  [Amazon EC2 Security Groups](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-key-pairs.html) in the Amazon EC2 User Guide for Linux Instances
+  [Authorizing Inbound Traffic for Your Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/authorizing-access-to-an-instance.html) in the Amazon EC2 User Guide for Linux Instances
+  [CreateSecurityGroup](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_CreateSecurityGroup.html) in the Amazon EC2 API Reference
+  [DescribeSecurityGroups](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DescribeSecurityGroups.html) in the Amazon EC2 API Reference
+  [DeleteSecurityGroup](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DeleteSecurityGroup.html) in the Amazon EC2 API Reference
+  [AuthorizeSecurityGroupIngress](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_AuthorizeSecurityGroupIngress.html) in the Amazon EC2 API Reference