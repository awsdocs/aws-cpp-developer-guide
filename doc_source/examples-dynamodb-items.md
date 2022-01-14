# Working with Items in DynamoDB<a name="examples-dynamodb-items"></a>

In DynamoDB, an item is a collection of *attributes*, each of which has a *name* and a *value*\. An attribute value can be a scalar, set, or document type\. For more information, see [Naming Rules and Data Types](https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/HowItWorks.NamingRulesDataTypes.html) in the Amazon DynamoDB Developer Guide\.

## Retrieve an Item from a Table<a name="dynamodb-get-item"></a>

Call the [DynamoDB client](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_dynamo_d_b_client.html) `GetItem` method\. Pass it a [GetItemRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_model_1_1_get_item_request.html) object with the table name and primary key value of the item you want\. It returns a [GetItemResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_model_1_1_get_item_result.html) object\.

You can use the returned `GetItemResult` object’s `GetItem()` method to retrieve an `Aws::Map` of key `Aws::String` and value [AttributeValue](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_model_1_1_attribute_value.html) pairs associated with the item\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <iostream>
```

 **Code** 

```
        Aws::Client::ClientConfiguration clientConfig;
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
        Aws::DynamoDB::Model::GetItemRequest req;

        // Set up the request.
        req.SetTableName(table);
        Aws::DynamoDB::Model::AttributeValue hashKey;
        hashKey.SetS(keyval);
        req.AddKey(key, hashKey);
     
        // Retrieve the item's fields and values
        const Aws::DynamoDB::Model::GetItemOutcome& result = dynamoClient.GetItem(req);
        if (result.IsSuccess())
        {
            // Reference the retrieved fields/values.
            const Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue>& item = result.GetResult().GetItem();
            if (item.size() > 0)
            {
                // Output each retrieved field and its value.
                for (const auto& i : item)
                    std::cout << "Values: " << i.first << ": " << i.second.GetS() << std::endl;
            }
            else
            {
                std::cout << "No item found with the key " << key << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get item: " << result.GetError().GetMessage();
        }
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb/get_item.cpp) on GitHub\.

## Add an Item to a Table<a name="dynamodb-add-item"></a>

Create key `Aws::String` and value [AttributeValue](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_model_1_1_attribute_value.html) pairs that represent each item\. These must include values for the table’s primary key fields\. If the item identified by the primary key already exists, its fields are *updated* by the request\. Add them to the [PutItemRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_model_1_1_put_item_request.html) using the `AddItem` method\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/PutItemRequest.h>
#include <aws/dynamodb/model/PutItemResult.h>
#include <iostream>
```

 **Code** 

```
        Aws::Client::ClientConfiguration clientConfig;
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

        Aws::DynamoDB::Model::PutItemRequest putItemRequest;
        putItemRequest.SetTableName(table);
               
        Aws::DynamoDB::Model::AttributeValue av;
        av.SetS(keyVal);
        
        Aws::DynamoDB::Model::AttributeValue album;
        album.SetS(AlbumTitleValue);

        Aws::DynamoDB::Model::AttributeValue awards;
        awards.SetS(AwardVal);

        Aws::DynamoDB::Model::AttributeValue song;
        song.SetS(SongTitleVal);

        // Add all AttributeValue objects.
        putItemRequest.AddItem(key, av);
        putItemRequest.AddItem(albumTitle, album);
        putItemRequest.AddItem(Awards, awards);
        putItemRequest.AddItem(SongTitle, song);

        const Aws::DynamoDB::Model::PutItemOutcome result = dynamoClient.PutItem(putItemRequest);
        if (!result.IsSuccess())
        {
            std::cout << result.GetError().GetMessage() << std::endl;
            return 1;
        }
        std::cout << "Successfully added Item!" << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb/put_item.cpp) on GitHub\.

## Update an Existing Item in a Table<a name="dynamodb-update-item"></a>

You can update an attribute for an item that already exists in a table by using the DynamoDBClient’s `UpdateItem` method, providing a table name, primary key value, and fields to update and their corresponding value\.

 **Imports** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/UpdateItemRequest.h>
#include <aws/dynamodb/model/UpdateItemResult.h>
#include <iostream>
```

 **Code** 

```
        Aws::Client::ClientConfiguration clientConfig;
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

        // *** Define UpdateItem request arguments
        // Define TableName argument.
        Aws::DynamoDB::Model::UpdateItemRequest request;
        request.SetTableName(tableName);

        // Define KeyName argument.
        Aws::DynamoDB::Model::AttributeValue attribValue;
        attribValue.SetS(keyValue);
        request.AddKey("id", attribValue);

        // Construct the SET update expression argument.
        Aws::String update_expression("SET #a = :valueA");
        request.SetUpdateExpression(update_expression);

        // Parse the attribute name and value. Syntax: "name=value".
        auto parsed = Aws::Utils::StringUtils::Split(attributeNameAndValue, '=');
        
        if (parsed.size() != 2)
        {
            std::cout << "Invalid argument syntax: " << attributeNameAndValue << USAGE;
            return 1;
        }

        // Construct attribute name argument
        // Note: Setting the ExpressionAttributeNames argument is required only
        // when the name is a reserved word, such as "default". Otherwise, the 
        // name can be included in the update_expression, as in 
        // "SET MyAttributeName = :valueA"
        Aws::Map<Aws::String, Aws::String> expressionAttributeNames;
        expressionAttributeNames["#a"] = parsed[0];
        request.SetExpressionAttributeNames(expressionAttributeNames);

        // Construct attribute value argument.
        Aws::DynamoDB::Model::AttributeValue attributeUpdatedValue;
        attributeUpdatedValue.SetS(parsed[1]);
        Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> expressionAttributeValues;
        expressionAttributeValues[":valueA"] = attributeUpdatedValue;
        request.SetExpressionAttributeValues(expressionAttributeValues);

        // Update the item.
        const Aws::DynamoDB::Model::UpdateItemOutcome& result = dynamoClient.UpdateItem(request);
        if (!result.IsSuccess())
        {
            std::cout << result.GetError().GetMessage() << std::endl;
            return 1;
        }
        std::cout << "Item was updated" << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb/update_item.cpp)\.

## More Info<a name="more-info"></a>
+  [Guidelines for Working with Items](https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/GuidelinesForItems.html) in the Amazon DynamoDB Developer Guide
+  [Working with Items in DynamoDB](https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/WorkingWithItems.html) in the Amazon DynamoDB Developer Guide