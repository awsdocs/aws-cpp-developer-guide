# Managing Amazon EC2 Instances<a name="examples-ec2-instances"></a>

**Note**  
These code snippets assume that you understand the material in [Getting Started Using the AWS SDK for C\+\+](getting-started.md) and have configured default AWS credentials using the information in [Providing AWS Credentials](credentials.md)\.

## Create an Instance<a name="create-an-instance"></a>

Create a new Amazon EC2 instance by calling the EC2Client’s `RunInstances` function, providing it with a [RunInstancesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_run_instances_request.html) containing the [Amazon Machine Image \(AMI\)](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/AMIs.html) to use and an [instance type](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instance-types.html)\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/CreateTagsRequest.h>
#include <aws/ec2/model/RunInstancesRequest.h>
#include <aws/ec2/model/RunInstancesResponse.h>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;

Aws::EC2::Model::RunInstancesRequest run_request;
run_request.SetImageId(ami_id);
run_request.SetInstanceType(Aws::EC2::Model::InstanceType::t1_micro);
run_request.SetMinCount(1);
run_request.SetMaxCount(1);

auto run_outcome = ec2.RunInstances(run_request);
if (!run_outcome.IsSuccess())
{
    std::cout << "Failed to start ec2 instance " << instanceName <<
        " based on ami " << ami_id << ":" <<
        run_outcome.GetError().GetMessage() << std::endl;
    return;
}

const auto& instances = run_outcome.GetResult().GetInstances();
if (instances.size() == 0)
{
    std::cout << "Failed to start ec2 instance " << instanceName <<
        " based on ami " << ami_id << ":" <<
        run_outcome.GetError().GetMessage() << std::endl;
    return;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/create_instance.cpp)\.

## Start an Instance<a name="start-an-instance"></a>

To start an Amazon EC2 instance, call the EC2Client’s `StartInstances` function, providing it with a [StartInstancesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_start_instances_request.html) containing the ID of the instance to start\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/StartInstancesRequest.h>
#include <aws/ec2/model/StartInstancesResponse.h>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;

Aws::EC2::Model::StartInstancesRequest start_request;
start_request.AddInstanceIds(instance_id);
start_request.SetDryRun(true);

auto dry_run_outcome = ec2.StartInstances(start_request);
assert(!dry_run_outcome.IsSuccess());
if (dry_run_outcome.GetError().GetErrorType() !=
    Aws::EC2::EC2Errors::DRY_RUN_OPERATION)
{
    std::cout << "Failed dry run to start instance " << instance_id << ": "
        << dry_run_outcome.GetError().GetMessage() << std::endl;
    return;
}

start_request.SetDryRun(false);
auto start_instancesOutcome = ec2.StartInstances(start_request);

if (!start_instancesOutcome.IsSuccess())
{
    std::cout << "Failed to start instance " << instance_id << ": " <<
        start_instancesOutcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully started instance " << instance_id <<
        std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/start_stop_instance.cpp)\.

## Stop an Instance<a name="stop-an-instance"></a>

To stop an Amazon EC2 instance, call the EC2Client’s `StopInstances` function, providing it with a [StopInstancesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_stop_instances_request.html) containing the ID of the instance to stop\.

 **Includes** 

```
#include <aws/ec2/model/StopInstancesRequest.h>
#include <aws/ec2/model/StopInstancesResponse.h>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;
Aws::EC2::Model::StopInstancesRequest request;
request.AddInstanceIds(instance_id);
request.SetDryRun(true);

auto dry_run_outcome = ec2.StopInstances(request);
assert(!dry_run_outcome.IsSuccess());

if (dry_run_outcome.GetError().GetErrorType() !=
    Aws::EC2::EC2Errors::DRY_RUN_OPERATION)
{
    std::cout << "Failed dry run to stop instance " << instance_id << ": "
        << dry_run_outcome.GetError().GetMessage() << std::endl;
    return;
}

request.SetDryRun(false);
auto outcome = ec2.StopInstances(request);
if (!outcome.IsSuccess())
{
    std::cout << "Failed to stop instance " << instance_id << ": " <<
        outcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully stopped instance " << instance_id <<
        std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/start_stop_instance.cpp)\.

## Reboot an Instance<a name="reboot-an-instance"></a>

To reboot an Amazon EC2 instance, call the EC2Client’s `RebootInstances` function, providing it with a [RebootInstancesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_reboot_instances_request.html) containing the ID of the instance to reboot\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/RebootInstancesRequest.h>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;

Aws::EC2::Model::RebootInstancesRequest request;
request.AddInstanceIds(instanceId);
request.SetDryRun(true);

auto dry_run_outcome = ec2.RebootInstances(request);
assert(!dry_run_outcome.IsSuccess());

if (dry_run_outcome.GetError().GetErrorType()
    != Aws::EC2::EC2Errors::DRY_RUN_OPERATION)
{
    std::cout << "Failed dry run to reboot instance " << instanceId << ": "
        << dry_run_outcome.GetError().GetMessage() << std::endl;
    return;
}

request.SetDryRun(false);
auto outcome = ec2.RebootInstances(request);
if (!outcome.IsSuccess())
{
    std::cout << "Failed to reboot instance " << instanceId << ": " <<
        outcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully rebooted instance " << instanceId <<
        std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/reboot_instance.cpp)\.

## Describe Instances<a name="describe-instances"></a>

To list your instances, create a [DescribeInstancesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_instances_request.html) and call the EC2Client’s `DescribeInstances` function\. It will return a [DescribeInstancesResponse](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_describe_instances_response.html) object that you can use to list the Amazon EC2 instances for your account and region\.

Instances are grouped by *reservation*\. Each reservation corresponds to the call to `StartInstances` that launched the instance\. To list your instances, you must first call the `DescribeInstancesResponse` class’ `GetReservations` function, and then call `getInstances` on each returned Reservation object\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/DescribeInstancesRequest.h>
#include <aws/ec2/model/DescribeInstancesResponse.h>
#include <iomanip>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;
Aws::EC2::Model::DescribeInstancesRequest request;
bool header = false;
bool done = false;
while (!done)
{
    auto outcome = ec2.DescribeInstances(request);
    if (outcome.IsSuccess())
    {
        if (!header)
        {
            std::cout << std::left <<
                std::setw(48) << "Name" <<
                std::setw(20) << "ID" <<
                std::setw(15) << "Ami" <<
                std::setw(15) << "Type" <<
                std::setw(15) << "State" <<
                std::setw(15) << "Monitoring" << std::endl;
            header = true;
        }

        const auto &reservations =
            outcome.GetResult().GetReservations();

        for (const auto &reservation : reservations)
        {
            const auto &instances = reservation.GetInstances();
            for (const auto &instance : instances)
            {
                Aws::String instanceStateString =
                    Aws::EC2::Model::InstanceStateNameMapper::GetNameForInstanceStateName(
                        instance.GetState().GetName());

                Aws::String type_string =
                    Aws::EC2::Model::InstanceTypeMapper::GetNameForInstanceType(
                        instance.GetInstanceType());

                Aws::String monitor_str =
                    Aws::EC2::Model::MonitoringStateMapper::GetNameForMonitoringState(
                        instance.GetMonitoring().GetState());
                Aws::String name = "Unknown";

                const auto &tags = instance.GetTags();
                auto nameIter = std::find_if(tags.cbegin(), tags.cend(),
                    [](const Aws::EC2::Model::Tag &tag)
                {
                    return tag.GetKey() == "Name";
                });
                if (nameIter != tags.cend())
                {
                    name = nameIter->GetValue();
                }
                std::cout <<
                    std::setw(48) << name <<
                    std::setw(20) << instance.GetInstanceId() <<
                    std::setw(15) << instance.GetImageId() <<
                    std::setw(15) << type_string <<
                    std::setw(15) << instanceStateString <<
                    std::setw(15) << monitor_str << std::endl;
            }
        }

        if (outcome.GetResult().GetNextToken().size() > 0)
        {
            request.SetNextToken(outcome.GetResult().GetNextToken());
        }
        else
        {
            done = true;
        }
    }
    else
    {
        std::cout << "Failed to describe ec2 instances:" <<
            outcome.GetError().GetMessage() << std::endl;
        done = true;
    }
}
```

Results are paged; you can get further results by passing the value returned from the result object’s `GetNextToken` function to your original request object’s `SetNextToken` function, then using the same request object in your next call to `DescribeInstances`\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/describe_instances.cpp)\.

## Enable Instance Monitoring<a name="enable-instance-monitoring"></a>

You can monitor various aspects of your Amazon EC2 instances, such as CPU and network utilization, available memory, and disk space remaining\. To learn more about instance monitoring, see [Monitoring Amazon EC2](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/monitoring_ec2.html) in the Amazon EC2 User Guide for Linux Instances\.

To start monitoring an instance, you must create a [MonitorInstancesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_monitor_instances_request.html) with the ID of the instance to monitor, and pass it to the EC2Client’s `MonitorInstances` function\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/MonitorInstancesRequest.h>
#include <aws/ec2/model/MonitorInstancesResponse.h>
#include <aws/ec2/model/UnmonitorInstancesRequest.h>
#include <aws/ec2/model/UnmonitorInstancesResponse.h>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;
Aws::EC2::Model::MonitorInstancesRequest request;
request.AddInstanceIds(instance_id);
request.SetDryRun(true);

auto dry_run_outcome = ec2.MonitorInstances(request);
assert(!dry_run_outcome.IsSuccess());
if (dry_run_outcome.GetError().GetErrorType()
    != Aws::EC2::EC2Errors::DRY_RUN_OPERATION)
{
    std::cout << "Failed dry run to enable monitoring on instance " <<
        instance_id << ": " << dry_run_outcome.GetError().GetMessage() <<
        std::endl;
    return;
}

request.SetDryRun(false);
auto monitorInstancesOutcome = ec2.MonitorInstances(request);
if (!monitorInstancesOutcome.IsSuccess())
{
    std::cout << "Failed to enable monitoring on instance " <<
        instance_id << ": " <<
        monitorInstancesOutcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully enabled monitoring on instance " <<
        instance_id << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/monitor_instance.cpp)\.

## Disable Instance Monitoring<a name="disable-instance-monitoring"></a>

To stop monitoring an instance, create an [UnmonitorInstancesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_e_c2_1_1_model_1_1_unmonitor_instances_request.html) with the ID of the instance to stop monitoring, and pass it to the EC2Client’s `UnmonitorInstances` function\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/MonitorInstancesRequest.h>
#include <aws/ec2/model/MonitorInstancesResponse.h>
#include <aws/ec2/model/UnmonitorInstancesRequest.h>
#include <aws/ec2/model/UnmonitorInstancesResponse.h>
#include <iostream>
```

 **Code** 

```
Aws::EC2::EC2Client ec2;
Aws::EC2::Model::UnmonitorInstancesRequest unrequest;
unrequest.AddInstanceIds(instance_id);
unrequest.SetDryRun(true);

auto undry_run_outcome = ec2.UnmonitorInstances(unrequest);
assert(!undry_run_outcome.IsSuccess());
if (undry_run_outcome.GetError().GetErrorType() !=
    Aws::EC2::EC2Errors::DRY_RUN_OPERATION)
{
    std::cout << "Failed dry run to disable monitoring on instance " <<
        instance_id << ": " << undry_run_outcome.GetError().GetMessage() <<
        std::endl;
    return;
}

unrequest.SetDryRun(false);
auto unmonitorInstancesOutcome = ec2.UnmonitorInstances(unrequest);
if (!unmonitorInstancesOutcome.IsSuccess())
{
    std::cout << "Failed to disable monitoring on instance " << instance_id
        << ": " << unmonitorInstancesOutcome.GetError().GetMessage() <<
        std::endl;
}
else
{
    std::cout << "Successfully disable monitoring on instance " <<
        instance_id << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/ec2/monitor_instance.cpp)\.

## More Information<a name="more-information"></a>
+  [RunInstances](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_RunInstances.html) in the Amazon EC2 API Reference
+  [DescribeInstances](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DescribeInstances.html) in the Amazon EC2 API Reference
+  [StartInstances](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_StartInstances.html) in the Amazon EC2 API Reference
+  [StopInstances](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_StopInstances.html) in the Amazon EC2 API Reference
+  [RebootInstances](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_RebootInstances.html) in the Amazon EC2 API Reference
+  [DescribeInstances](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_DescribeInstances.html) in the Amazon EC2 API Reference
+  [MonitorInstances](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_MonitorInstances.html) in the Amazon EC2 API Reference
+  [UnmonitorInstances](https://docs.aws.amazon.com/AWSEC2/latest/APIReference/API_UnmonitorInstances.html) in the Amazon EC2 API Reference