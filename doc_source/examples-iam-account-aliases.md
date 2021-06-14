# Using IAM Account Aliases<a name="examples-iam-account-aliases"></a>

If you want the URL for your sign\-in page to contain your company name or other friendly identifier instead of your AWS account ID, you can create an alias for your AWS account\.

**Note**  
AWS supports exactly one account alias per account\.

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Create an Account Alias<a name="create-an-account-alias"></a>

To create an account alias, call the IAMClient’s `CreateAccountAlias` function with a [CreateAccountAliasRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_create_account_alias_request.html) object that contains the alias name\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/CreateAccountAliasRequest.h>
#include <iostream>
```

 **Code:** 

```
Aws::IAM::IAMClient iam;
Aws::IAM::Model::CreateAccountAliasRequest request;
request.SetAccountAlias(alias_name);

auto outcome = iam.CreateAccountAlias(request);
if (!outcome.IsSuccess())
{
    std::cout << "Error creating account alias " << alias_name << ": "
        << outcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully created account alias " << alias_name <<
        std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/iam/create_account_alias.cpp)\.

## List Account Aliases<a name="list-account-aliases"></a>

To list your account’s alias, if any, call the IAMClient’s `ListAccountAliases` function\. It takes a [ListAccountAliasesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_account_aliases_request.html) object\.

**Note**  
The returned [ListAccountAliasesResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_account_aliases_result.html) supports the same `GetIsTruncated` and `GetMarker` functions as other AWS SDK for C\+\+*list* functions, but an AWS account can have only *one* account alias\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/ListAccountAliasesRequest.h>
#include <aws/iam/model/ListAccountAliasesResult.h>
#include <iomanip>
#include <iostream>
```

 **Code:** 

```
Aws::IAM::IAMClient iam;
Aws::IAM::Model::ListAccountAliasesRequest request;

bool done = false;
bool header = false;
while (!done)
{
    auto outcome = iam.ListAccountAliases(request);
    if (!outcome.IsSuccess())
    {
        std::cout << "Failed to list account aliases: " <<
            outcome.GetError().GetMessage() << std::endl;
        break;
    }

    const auto &aliases = outcome.GetResult().GetAccountAliases();
    if (!header)
    {
        if (aliases.size() == 0)
        {
            std::cout << "Account has no aliases" << std::endl;
            break;
        }
        std::cout << std::left << std::setw(32) << "Alias" << std::endl;
        header = true;
    }

    for (const auto &alias : aliases)
    {
        std::cout << std::left << std::setw(32) << alias << std::endl;
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

see the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/iam/list_account_aliases.cpp)\.

## Delete an Account Alias<a name="delete-an-account-alias"></a>

To delete your account’s alias, call the IAMClient’s `DeleteAccountAlias` function\. When deleting an account alias, you must supply its name using a [DeleteAccountAliasRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_delete_account_alias_request.html) object\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/DeleteAccountAliasRequest.h>
#include <iostream>
```

 **Code:** 

```
Aws::IAM::IAMClient iam;

Aws::IAM::Model::DeleteAccountAliasRequest request;
request.SetAccountAlias(alias_name);

const auto outcome = iam.DeleteAccountAlias(request);
if (!outcome.IsSuccess())
{
    std::cout << "Error deleting account alias " << alias_name << ": "
        << outcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully deleted account alias " << alias_name <<
        std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/iam/delete_account_alias.cpp)\.

## More Information<a name="more-information"></a>
+  [Your AWS Account ID and Its Alias](https://docs.aws.amazon.com/IAM/latest/UserGuide/console_account-alias.html) in the IAM User Guide
+  [CreateAccountAlias](https://docs.aws.amazon.com/IAM/latest/APIReference/API_CreateAccountAlias.html) in the IAM API Reference
+  [ListAccountAliases](https://docs.aws.amazon.com/IAM/latest/APIReference/API_ListAccountAliases.html) in the IAM API Reference
+  [DeleteAccountAlias](https://docs.aws.amazon.com/IAM/latest/APIReference/API_DeleteAccountAlias.html) in the IAM API Reference