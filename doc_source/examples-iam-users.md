# Managing IAM Users<a name="examples-iam-users"></a>

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Create a User<a name="create-a-user"></a>

Use the IAMClient `CreateUser` function, passing it a [CreateUserRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_create_user_request.html) with the name of the user to create\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/CreateUserRequest.h>
#include <aws/iam/model/CreateUserResult.h>
```

 **Code:** 

```
    Aws::IAM::IAMClient iam;
```

```
    Aws::IAM::Model::CreateUserRequest create_request;
    create_request.SetUserName(user_name);

    auto create_outcome = iam.CreateUser(create_request);
    if (!create_outcome.IsSuccess())
    {
        std::cout << "Error creating IAM user " << user_name << ":" <<
            create_outcome.GetError().GetMessage() << std::endl;
        return;
    }
    std::cout << "Successfully created IAM user " << user_name << std::endl;
```

## Get Information About a User<a name="get-information-about-a-user"></a>

To get information about a particular user, such as the user’s creation date, path, ID or ARN, call the IAMClient `GetUser` function with a [GetUserRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_get_user_request.html) containing the user name\. If successful, you can get the [User](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_user.html) from the returned [GetUserResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_get_user_result.html) outcome\.

If the user doesn’t already exist, `GetUser` will fail with `Aws::IAM::IAMErrors::NO_SUCH_ENTITY`\.

 **Includes:** 

```
#include <aws/iam/model/GetUserRequest.h>
#include <aws/iam/model/GetUserResult.h>
```

 **Code:** 

```
    Aws::IAM::IAMClient iam;
```

```
    Aws::IAM::Model::GetUserRequest get_request;
    get_request.SetUserName(user_name);

    auto get_outcome = iam.GetUser(get_request);
    if (get_outcome.IsSuccess())
    {
        std::cout << "IAM user " << user_name << " already exists" << std::endl;
        return;
    }
    else if (get_outcome.GetError().GetErrorType() !=
        Aws::IAM::IAMErrors::NO_SUCH_ENTITY)
    {
        std::cout << "Error checking existence of IAM user " << user_name << ":"
            << get_outcome.GetError().GetMessage() << std::endl;
        return;
    }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/create_user.cpp)\.

## List Users<a name="list-users"></a>

List the existing IAM users for your account by calling the IAMClient `ListUsers` function, passing it a [ListUsersRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_users_request.html) object\. The list of users is returned in a [ListUsersResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_users_result.html) object that you can use to get information about the users\.

The result may be paginated; to check to see if there are more results available, check the value of `GetResult().GetIsTruncated()`\. If `true`, then set a marker on the request and call `ListUsers` again to get the next batch of users\. This code demonstrates the technique\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/ListUsersRequest.h>
#include <aws/iam/model/ListUsersResult.h>
#include <iomanip>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;
        Aws::IAM::Model::ListUsersRequest request;

        bool done = false;
        bool header = false;
        while (!done)
        {
            auto outcome = iam.ListUsers(request);
            if (!outcome.IsSuccess())
            {
                std::cout << "Failed to list iam users:" <<
                    outcome.GetError().GetMessage() << std::endl;
                break;
            }

            if (!header)
            {
                std::cout << std::left << std::setw(32) << "Name" <<
                    std::setw(30) << "ID" << std::setw(64) << "Arn" <<
                    std::setw(20) << "CreateDate" << std::endl;
                header = true;
            }

            const auto &users = outcome.GetResult().GetUsers();
            for (const auto &user : users)
            {
                std::cout << std::left << std::setw(32) << user.GetUserName() <<
                    std::setw(30) << user.GetUserId() << std::setw(64) <<
                    user.GetArn() << std::setw(20) <<
                    user.GetCreateDate().ToGmtString(DATE_FORMAT) << std::endl;
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

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/list_users.cpp)\.

## Update a User<a name="update-a-user"></a>

To update an existing user, create an [UpdateUserRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_update_user_request.html) and pass it to the IAMClient `UpdateUser` member function\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/UpdateUserRequest.h>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;

        Aws::IAM::Model::UpdateUserRequest request;
        request.SetUserName(old_name);
        request.SetNewUserName(new_name);

        auto outcome = iam.UpdateUser(request);
        if (outcome.IsSuccess())
        {
            std::cout << "IAM user " << old_name <<
                " successfully updated with new user name " << new_name <<
                std::endl;
        }
        else
        {
            std::cout << "Error updating user name for IAM user " << old_name <<
                ":" << outcome.GetError().GetMessage() << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/update_user.cpp)\.

## Delete a User<a name="delete-a-user"></a>

To delete an existing user, call the IAMClient `DeleteUser` function, passing it a [DeleteUserRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_delete_user_request.html) object containing the name of the user to delete\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/DeleteUserRequest.h>
```

 **Code:** 

```
    Aws::IAM::IAMClient iam;
```

```
    Aws::IAM::Model::DeleteUserRequest request;
    request.SetUserName(user_name);
    auto outcome = iam.DeleteUser(request);
    if (!outcome.IsSuccess())
    {
        std::cout << "Error deleting IAM user " << user_name << ": " <<
            outcome.GetError().GetMessage() << std::endl;
        return;
    }
    std::cout << "Successfully deleted IAM user " << user_name << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/delete_user.cpp)\.