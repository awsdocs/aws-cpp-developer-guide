# Working with IAM Policies<a name="examples-iam-policies"></a>

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Create a Policy<a name="create-a-policy"></a>

To create a new policy, provide the policy’s name and a JSON\-formatted policy document in a [CreatePolicyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_create_policy_request.html) to the IAMClient’s `CreatePolicy` function\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/CreatePolicyRequest.h>
#include <aws/iam/model/CreatePolicyResult.h>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;

        Aws::IAM::Model::CreatePolicyRequest request;
        request.SetPolicyName(policy_name);
        request.SetPolicyDocument(BuildSamplePolicyDocument(rsrc_arn));

        auto outcome = iam.CreatePolicy(request);
        if (!outcome.IsSuccess())
        {
            std::cout << "Error creating policy " << policy_name << ": " <<
                outcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            std::cout << "Successfully created policy " << policy_name <<
                std::endl;
        }
```

IAM policy documents are JSON strings with a [well\-documented syntax](https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies_grammar.html)\. Here is an example that provides access to make particular requests to DynamoDB\. It takes the policy ARN as a passed\-in variable\.

```
static const char* const POLICY_TEMPLATE =
"{"
"  \"Version\": \"2012-10-17\","
"  \"Statement\": ["
"    {"
"        \"Effect\": \"Allow\","
"        \"Action\": \"logs:CreateLogGroup\","
"        \"Resource\": \"%s\""
"    },"
"    {"
"        \"Effect\": \"Allow\","
"        \"Action\": ["
"            \"dynamodb:DeleteItem\","
"            \"dynamodb:GetItem\","
"            \"dynamodb:PutItem\","
"            \"dynamodb:Scan\","
"            \"dynamodb:UpdateItem\""
"       ],"
"       \"Resource\": \"%s\""
"    }"
"   ]"
"}";

Aws::String BuildSamplePolicyDocument(const Aws::String& rsrc_arn)
{
    char policyBuffer[512];
#ifdef WIN32
    sprintf_s(policyBuffer, POLICY_TEMPLATE, rsrc_arn.c_str(), rsrc_arn.c_str());
#else
    sprintf(policyBuffer, POLICY_TEMPLATE, rsrc_arn.c_str(), rsrc_arn.c_str());
#endif // WIN32
    return Aws::String(policyBuffer);
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/create_policy.cpp)\.

## Retrieve a Policy<a name="retrieve-a-policy"></a>

To retrieve an existing policy, call the IAMClient’s `GetPolicy` function, providing the policy’s ARN within a [GetPolicyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_get_policy_request.html) object\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/GetPolicyRequest.h>
#include <aws/iam/model/GetPolicyResult.h>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;
        Aws::IAM::Model::GetPolicyRequest request;
        request.SetPolicyArn(policy_arn);

        auto outcome = iam.GetPolicy(request);
        if (!outcome.IsSuccess())
        {
            std::cout << "Error getting policy " << policy_arn << ": " <<
                outcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            const auto &policy = outcome.GetResult().GetPolicy();
            std::cout << "Name: " << policy.GetPolicyName() << std::endl <<
                "ID: " << policy.GetPolicyId() << std::endl << "Arn: " <<
                policy.GetArn() << std::endl << "Description: " <<
                policy.GetDescription() << std::endl << "CreateDate: " <<
                policy.GetCreateDate().ToGmtString(Aws::Utils::DateFormat::ISO_8601)
                << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/get_policy.cpp)\.

## Delete a Policy<a name="delete-a-policy"></a>

To delete a policy, provide the policy’s ARN in a [DeletePolicyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_delete_policy_request.html) to the IAMClient’s `DeletePolicy` function\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/DeletePolicyRequest.h>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;
        Aws::IAM::Model::DeletePolicyRequest request;
        request.SetPolicyArn(policy_arn);

        auto outcome = iam.DeletePolicy(request);
        if (!outcome.IsSuccess())
        {
            std::cout << "Error deleting policy with arn " << policy_arn << ": "
                << outcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            std::cout << "Successfully deleted policy with arn " << policy_arn
                << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/delete_policy.cpp)\.

## Attach a Policy<a name="attach-a-policy"></a>

You can attach a policy to an IAM[role](https://docs.aws.amazon.com/IAM/latest/UserGuide/id_roles.html) by calling the IAMClient’s `AttachRolePolicy` function, providing it with the role name and policy ARN in an [AttachRolePolicyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_attach_role_policy_request.html)\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/AttachRolePolicyRequest.h>
#include <aws/iam/model/ListAttachedRolePoliciesRequest.h>
#include <aws/iam/model/ListAttachedRolePoliciesResult.h>
#include <iostream>
#include <iomanip>
```

 **Code:** 

```
    Aws::IAM::IAMClient iam;

    Aws::IAM::Model::ListAttachedRolePoliciesRequest list_request;
    list_request.SetRoleName(role_name);

    bool done = false;
    while (!done)
    {
        auto list_outcome = iam.ListAttachedRolePolicies(list_request);
        if (!list_outcome.IsSuccess())
        {
            std::cout << "Failed to list attached policies of role " <<
                role_name << ": " << list_outcome.GetError().GetMessage() <<
                std::endl;
            return;
        }

        const auto& policies = list_outcome.GetResult().GetAttachedPolicies();
        if (std::any_of(policies.cbegin(), policies.cend(),
            [=](const Aws::IAM::Model::AttachedPolicy& policy)
        {
            return policy.GetPolicyArn() == policy_arn;
        }))
        {
            std::cout << "Policy " << policy_arn <<
                " is already attached to role " << role_name << std::endl;
            return;
        }

        done = !list_outcome.GetResult().GetIsTruncated();
        list_request.SetMarker(list_outcome.GetResult().GetMarker());
    }

    Aws::IAM::Model::AttachRolePolicyRequest request;
    request.SetRoleName(role_name);
    request.SetPolicyArn(policy_arn);

    auto outcome = iam.AttachRolePolicy(request);
    if (!outcome.IsSuccess())
    {
        std::cout << "Failed to attach policy " << policy_arn << " to role " <<
            role_name << ": " << outcome.GetError().GetMessage() << std::endl;
        return;
    }

    std::cout << "Successfully attached policy " << policy_arn << " to role " <<
        role_name << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/attach_role_policy.cpp)\.

## List Attached Policies<a name="list-attached-policies"></a>

List attached policies on a role by calling the IAMClient’s `ListAttachedRolePolicies` function\. It takes a [ListAttachedRolePoliciesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_attached_role_policies_request.html) object that contains the role name to list the policies for\.

Call `GetAttachedPolicies` on the returned [ListAttachedRolePoliciesResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_attached_role_policies_result.html) object to get the list of attached policies\. Results may be truncated; if the `ListAttachedRolePoliciesResult` object’s `GetIsTruncated` function returns `true`, call the `ListAttachedRolePoliciesRequest` object’s `SetMarker` function and use it to call `ListAttachedRolePolicies` again to get the next batch of results\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/ListPoliciesRequest.h>
#include <aws/iam/model/ListPoliciesResult.h>
#include <iomanip>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;
        Aws::IAM::Model::ListPoliciesRequest request;

        bool done = false;
        bool header = false;
        while (!done)
        {
            auto outcome = iam.ListPolicies(request);
            if (!outcome.IsSuccess())
            {
                std::cout << "Failed to list iam policies: " <<
                    outcome.GetError().GetMessage() << std::endl;
                break;
            }

            if (!header)
            {
                std::cout << std::left << std::setw(55) << "Name" <<
                    std::setw(30) << "ID" << std::setw(80) << "Arn" <<
                    std::setw(64) << "Description" << std::setw(12) <<
                    "CreateDate" << std::endl;
                header = true;
            }

            const auto &policies = outcome.GetResult().GetPolicies();
            for (const auto &policy : policies)
            {
                std::cout << std::left << std::setw(55) <<
                    policy.GetPolicyName() << std::setw(30) <<
                    policy.GetPolicyId() << std::setw(80) << policy.GetArn() <<
                    std::setw(64) << policy.GetDescription() << std::setw(12) <<
                    policy.GetCreateDate().ToGmtString(DATE_FORMAT) <<
                    std::endl;
            }

            if (outcome.GetResult().GetIsTruncated())
            {
                request.SetMarker(outcome.GetResult().GetMarker());
            }
            else
            {
                done = true;
            }
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/list_policies.cpp)\.

## Detach a Policy<a name="detach-a-policy"></a>

To detach a policy from a role, call the IAMClient’s `DetachRolePolicy` function, providing it with the role name and policy ARN in a [DetachRolePolicyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_detach_role_policy_request.html)\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/DetachRolePolicyRequest.h>
#include <aws/iam/model/ListAttachedRolePoliciesRequest.h>
#include <aws/iam/model/ListAttachedRolePoliciesResult.h>
#include <iostream>
```

 **Code:** 

```
    Aws::IAM::IAMClient iam;
```

```
    Aws::IAM::Model::DetachRolePolicyRequest detach_request;
    detach_request.SetRoleName(role_name);
    detach_request.SetPolicyArn(policy_arn);

    auto detach_outcome = iam.DetachRolePolicy(detach_request);
    if (!detach_outcome.IsSuccess())
    {
        std::cout << "Failed to detach policy " << policy_arn << " from role "
            << role_name << ": " << detach_outcome.GetError().GetMessage() <<
            std::endl;
        return;
    }

    std::cout << "Successfully detached policy " << policy_arn << " from role "
        << role_name << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/detach_role_policy.cpp)\.

## More Information<a name="more-information"></a>
+  [Overview of IAM Policies](https://docs.aws.amazon.com/IAM/latest/UserGuide/access_policies.html) in the IAM User Guide\.
+  [IAM Policy Reference](https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies.html) in the IAM User Guide\.
+  [CreatePolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_CreatePolicy.html) in the IAM API Reference
+  [GetPolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_GetPolicy.html) in the IAM API Reference
+  [DeletePolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_DeletePolicy.html) in the IAM API Reference
+  [AttachGroupPolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_AttachGroupPolicy.html), [AttachRolePolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_AttachRolePolicy.html) and [AttachUserPolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_AttachUserPolicy.html) in the IAM API Reference
+  [DetachGroupPolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_DetachGroupPolicy.html), [DetachRolePolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_DetachRolePolicy.html) and [DetachUserPolicy](https://docs.aws.amazon.com/IAM/latest/APIReference/API_DetachUserPolicy.html) in the IAM API Reference
+  [ListAttachedGroupPolicies](https://docs.aws.amazon.com/IAM/latest/APIReference/API_ListAttachedGroupPolicies.html), [ListAttachedRolePolicies](https://docs.aws.amazon.com/IAM/latest/APIReference/API_ListAttachedRolePolicies.html) and [ListAttachedUserPolicies](https://docs.aws.amazon.com/IAM/latest/APIReference/API_ListAttachedUserPolicies.html) in the IAM API Reference