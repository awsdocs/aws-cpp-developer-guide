# Managing IAM Access Keys<a name="examples-iam-access-keys"></a>

## Prerequisites<a name="codeExamplePrereq"></a>

Before you begin, we recommend you read [Getting started using the AWS SDK for C\+\+](getting-started.md)\. 

Download the example code and build the solution as described in [Getting started on code examples](getting-started-code-examples.md)\. 

To run the examples, the user profile your code uses to make the requests must have proper permissions in AWS \(for the service and the action\)\. For more information, see [Providing AWS credentials](credentials.md)\.

## Create an Access Key<a name="create-an-access-key"></a>

To create an IAM access key, call the IAMClient’s `CreateAccessKey` function with an [CreateAccessKeyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_create_access_key_request.html) object\.

You must set the user name using the `CreateAccessKeyRequest`’s `WithUserName` setter function before passing it to the `CreateAccessKey` function\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/CreateAccessKeyRequest.h>
#include <aws/iam/model/CreateAccessKeyResult.h>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;

        Aws::IAM::Model::CreateAccessKeyRequest request;
        request.SetUserName(user_name);

        auto outcome = iam.CreateAccessKey(request);
        if (!outcome.IsSuccess())
        {
            std::cout << "Error creating access key for IAM user " << user_name
                << ":" << outcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            const auto &accessKey = outcome.GetResult().GetAccessKey();
            std::cout << "Successfully created access key for IAM user " <<
                user_name << std::endl << "  aws_access_key_id = " <<
                accessKey.GetAccessKeyId() << std::endl <<
                " aws_secret_access_key = " << accessKey.GetSecretAccessKey() <<
                std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/create_access_key.cpp)\.

## List Access Keys<a name="list-access-keys"></a>

To list the access keys for a given user, create a [ListAccessKeysRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_access_keys_request.html) object that contains the user name to list keys for, and pass it to the IAMClient’s `ListAccessKeys` function\.

**Note**  
If you do not supply a user name to `ListAccessKeys`, it will attempt to list access keys associated with the AWS account that signed the request\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/ListAccessKeysRequest.h>
#include <aws/iam/model/ListAccessKeysResult.h>
#include <iomanip>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;
        Aws::IAM::Model::ListAccessKeysRequest request;
        request.SetUserName(userName);

        bool done = false;
        bool header = false;
        while (!done)
        {
            auto outcome = iam.ListAccessKeys(request);
            if (!outcome.IsSuccess())
            {
                std::cout << "Failed to list access keys for user " << userName
                    << ": " << outcome.GetError().GetMessage() << std::endl;
                break;
            }

            if (!header)
            {
                std::cout << std::left << std::setw(32) << "UserName" <<
                    std::setw(30) << "KeyID" << std::setw(20) << "Status" <<
                    std::setw(20) << "CreateDate" << std::endl;
                header = true;
            }

            const auto &keys = outcome.GetResult().GetAccessKeyMetadata();
            for (const auto &key : keys)
            {
                Aws::String statusString =
                    Aws::IAM::Model::StatusTypeMapper::GetNameForStatusType(
                        key.GetStatus());
                std::cout << std::left << std::setw(32) << key.GetUserName() <<
                    std::setw(30) << key.GetAccessKeyId() << std::setw(20) <<
                    statusString << std::setw(20) <<
                    key.GetCreateDate().ToGmtString(DATE_FORMAT) << std::endl;
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

The results of `ListAccessKeys` are paged \(with a default maximum of 100 records per call\)\. You can call `GetIsTruncated` on the returned [ListAccessKeysResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_access_keys_result.html) object to see if the query returned fewer results then are available\. If so, then call `SetMarker` on the `ListAccessKeysRequest` and pass it back to the next invocation of `ListAccessKeys`\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/list_access_keys.cpp)\.

## Retrieve an Access Key’s Last Used Time<a name="retrieve-an-access-key-s-last-used-time"></a>

To get the time an access key was last used, call the IAMClient’s `GetAccessKeyLastUsed` function with the access key’s ID \(which can be passed in using a [GetAccessKeyLastUsedRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_get_access_key_last_used_request.html) object, or directly to the overload that takes the access key ID directly\.

You can then use the returned [GetAccessKeyLastUsedResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_get_access_key_last_used_result.html) object to retrieve the key’s last used time\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/GetAccessKeyLastUsedRequest.h>
#include <aws/iam/model/GetAccessKeyLastUsedResult.h>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;
        Aws::IAM::Model::GetAccessKeyLastUsedRequest request;

        request.SetAccessKeyId(key_id);

        auto outcome = iam.GetAccessKeyLastUsed(request);

        if (!outcome.IsSuccess())
        {
            std::cout << "Error querying last used time for access key " <<
                key_id << ":" << outcome.GetError().GetMessage() << std::endl;
        }
        else
        {
            auto lastUsedTimeString =
                outcome.GetResult()
                .GetAccessKeyLastUsed()
                .GetLastUsedDate()
                .ToGmtString(Aws::Utils::DateFormat::ISO_8601);
            std::cout << "Access key " << key_id << " last used at time " <<
                lastUsedTimeString << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/access_key_last_used.cpp)\.

## Activate or Deactivate Access Keys<a name="iam-access-keys-update"></a>

You can activate or deactivate an access key by creating an [UpdateAccessKeyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_update_access_key_request.html) object, providing the access key ID, optionally the user name, and the desired `Status Type`, then passing the request object to the IAMClient’s `UpdateAccessKey` function\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/UpdateAccessKeyRequest.h>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;
        Aws::IAM::Model::UpdateAccessKeyRequest request;
        request.SetUserName(user_name);
        request.SetAccessKeyId(accessKeyId);
        request.SetStatus(status);

        auto outcome = iam.UpdateAccessKey(request);
        if (outcome.IsSuccess())
        {
            std::cout << "Successfully updated status of access key " <<
                accessKeyId << " for user " << user_name << std::endl;
        }
        else
        {
            std::cout << "Error updated status of access key " << accessKeyId <<
                " for user " << user_name << ": " <<
                outcome.GetError().GetMessage() << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/update_access_key.cpp)\.

## Delete an Access Key<a name="delete-an-access-key"></a>

To permanently delete an access key, call the IAMClient’s `DeleteKey` function, providing it with a [DeleteAccessKeyRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_delete_access_key_request.html) containing the access key’s ID and username\.

**Note**  
Once deleted, a key can no longer be retrieved or used\. To temporarily deactivate a key so that it can be activated again later, use [updateAccessKey](#iam-access-keys-update) function instead\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/DeleteAccessKeyRequest.h>
#include <iostream>
```

 **Code:** 

```
        Aws::IAM::IAMClient iam;

        Aws::IAM::Model::DeleteAccessKeyRequest request;
        request.SetUserName(user_name);
        request.SetAccessKeyId(key_id);

        auto outcome = iam.DeleteAccessKey(request);

        if (!outcome.IsSuccess())
        {
            std::cout << "Error deleting access key " << key_id << " from user "
                << user_name << ": " << outcome.GetError().GetMessage() <<
                std::endl;
        }
        else
        {
            std::cout << "Successfully deleted access key " << key_id
                << " for IAM user " << user_name << std::endl;
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/iam/delete_access_key.cpp)\.

## More Information<a name="more-information"></a>
+  [CreateAccessKey](https://docs.aws.amazon.com/IAM/latest/APIReference/API_CreateAccessKey.html) in the IAM API Reference
+  [ListAccessKeys](https://docs.aws.amazon.com/IAM/latest/APIReference/API_ListAccessKeys.html) in the IAM API Reference
+  [GetAccessKeyLastUsed](https://docs.aws.amazon.com/IAM/latest/APIReference/API_GetAccessKeyLastUsed.html) in the IAM API Reference
+  [UpdateAccessKey](https://docs.aws.amazon.com/IAM/latest/APIReference/API_UpdateAccessKey.html) in the IAM API Reference
+  [DeleteAccessKey](https://docs.aws.amazon.com/IAM/latest/APIReference/API_DeleteAccessKey.html) in the IAM API Reference