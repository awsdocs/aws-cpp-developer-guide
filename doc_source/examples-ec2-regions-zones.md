# Using Regions and Availability Zones for Amazon EC2<a name="examples-ec2-regions-zones"></a>

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Describe Regions<a name="describe-regions"></a>

To list the AWS Regions available to your AWS account, call the EC2Client’s `DescribeRegions` function with a [DescribeRegionsRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_regions_request.html)\.

You will receive a [DescribeRegionsResponse](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_regions_response.html) in the outcome object\. Call its `GetRegions` function to get a list of [Region](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_region.html) objects that represent each Region\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/DescribeRegionsRequest.h>
#include <aws/ec2/model/DescribeRegionsResponse.h>
```

 **Code** 

```
        Aws::EC2::EC2Client ec2;
        Aws::EC2::Model::DescribeRegionsRequest request;
        auto outcome = ec2.DescribeRegions(request);
        if (outcome.IsSuccess())
        {
            std::cout << std::left <<
                std::setw(32) << "RegionName" <<
                std::setw(64) << "Endpoint" << std::endl;

            const auto &regions = outcome.GetResult().GetRegions();
            for (const auto &region : regions)
            {
                std::cout << std::left <<
                    std::setw(32) << region.GetRegionName() <<
                    std::setw(64) << region.GetEndpoint() << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to describe regions:" <<
                outcome.GetError().GetMessage() << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/ec2/describe_regions_and_zones.cpp)\.

## Describe Availability Zones<a name="describe-availability-zones"></a>

To list each availability zone available to your account, call the EC2Client’s `DescribeAvailabilityZones` function with a [DescribeAvailabilityZonesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_availability_zones_request.html)\.

You will receive a [DescribeAvailabilityZonesResponse](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_availability_zones_response.html) in the outcome object\. Call its `GetAvailabilityZones` function to get a list of [AvailabilityZone](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_availability_zone.html) objects that represent each availability zone\.

 **Includes** 

```
#include <aws/ec2/model/DescribeAvailabilityZonesRequest.h>
#include <aws/ec2/model/DescribeAvailabilityZonesResponse.h>
```

 **Code** 

```
        Aws::EC2::Model::DescribeAvailabilityZonesRequest describe_request;
        auto describe_outcome = ec2.DescribeAvailabilityZones(describe_request);

        if (describe_outcome.IsSuccess())
        {
            std::cout << std::left <<
                std::setw(32) << "ZoneName" <<
                std::setw(20) << "State" <<
                std::setw(32) << "Region" << std::endl;

            const auto &zones =
                describe_outcome.GetResult().GetAvailabilityZones();

            for (const auto &zone : zones)
            {
                Aws::String stateString =
                    Aws::EC2::Model::AvailabilityZoneStateMapper::GetNameForAvailabilityZoneState(
                        zone.GetState());
                std::cout << std::left <<
                    std::setw(32) << zone.GetZoneName() <<
                    std::setw(20) << stateString <<
                    std::setw(32) << zone.GetRegionName() << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to describe availability zones:" <<
                describe_outcome.GetError().GetMessage() << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/ec2/describe_regions_and_zones.cpp)\.

## More Information<a name="more-information"></a>
+  [Regions and Availability Zones](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-regions-availability-zones.html) in the Amazon EC2 User Guide for Linux Instances
+  [DescribeRegions](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DescribeRegions.html) in the Amazon EC2 API Reference
+  [DescribeAvailabilityZones](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DescribeAvailabilityZones.html) in the Amazon EC2 API Reference