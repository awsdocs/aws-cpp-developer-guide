# DynamoDB examples using SDK for C\+\+<a name="cpp_dynamodb_code_examples"></a>

The following code examples show you how to perform actions and implement common scenarios by using the AWS SDK for C\+\+ with DynamoDB\.

*Actions* are code excerpts that show you how to call individual DynamoDB functions\.

*Scenarios* are code examples that show you how to accomplish a specific task by calling multiple DynamoDB functions\.

Each example includes a link to GitHub, where you can find instructions on how to set up and run the code in context\.

**Topics**
+ [Actions](#w62aac13c21b9c15c13)

## Actions<a name="w62aac13c21b9c15c13"></a>

### Create a table<a name="dynamodb_CreateTable_cpp_topic"></a>

The following code example shows how to create a DynamoDB table\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

```
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

        std::cout << "Creating table " << table <<
            " with a simple primary key: \"Name\"" << std::endl;

        Aws::DynamoDB::Model::CreateTableRequest req;

        Aws::DynamoDB::Model::AttributeDefinition haskKey;
        haskKey.SetAttributeName("Name");
        haskKey.SetAttributeType(Aws::DynamoDB::Model::ScalarAttributeType::S);
        req.AddAttributeDefinitions(haskKey);

        Aws::DynamoDB::Model::KeySchemaElement keyscelt;
        keyscelt.WithAttributeName("Name").WithKeyType(Aws::DynamoDB::Model::KeyType::HASH);
        req.AddKeySchema(keyscelt);

        Aws::DynamoDB::Model::ProvisionedThroughput thruput;
        thruput.WithReadCapacityUnits(5).WithWriteCapacityUnits(5);
        req.SetProvisionedThroughput(thruput);
        req.SetTableName(table);

        const Aws::DynamoDB::Model::CreateTableOutcome& result = dynamoClient.CreateTable(req);
        if (result.IsSuccess())
        {
            std::cout << "Table \"" << result.GetResult().GetTableDescription().GetTableName() <<
                " created!" << std::endl;
        }
        else
        {
            std::cout << "Failed to create table: " << result.GetError().GetMessage();
        }
```
+  For API details, see [CreateTable](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/CreateTable) in *AWS SDK for C\+\+ API Reference*\. 

### Delete a table<a name="dynamodb_DeleteTable_cpp_topic"></a>

The following code example shows how to delete a DynamoDB table\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

```
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

        Aws::DynamoDB::Model::DeleteTableRequest dtr;
        dtr.SetTableName(table);

        const Aws::DynamoDB::Model::DeleteTableOutcome& result = dynamoClient.DeleteTable(dtr);
        if (result.IsSuccess())
        {
            std::cout << "Your Table \"" << result.GetResult().GetTableDescription().GetTableName() << " was deleted!\n";
        }
        else
        {
            std::cout << "Failed to delete table: " << result.GetError().GetMessage();
        }
```
+  For API details, see [DeleteTable](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/DeleteTable) in *AWS SDK for C\+\+ API Reference*\. 

### Get an item from a table<a name="dynamodb_GetItem_cpp_topic"></a>

The following code example shows how to get an item from a DynamoDB table\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

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
+  For API details, see [GetItem](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/GetItem) in *AWS SDK for C\+\+ API Reference*\. 

### Get information about a table<a name="dynamodb_DescribeTable_cpp_topic"></a>

The following code example shows how to get information about a DynamoDB table\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

```
        Aws::Client::ClientConfiguration clientConfig;
        if (!region.empty())
            clientConfig.region = region;
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

        Aws::DynamoDB::Model::DescribeTableRequest dtr;
        dtr.SetTableName(table);

        const Aws::DynamoDB::Model::DescribeTableOutcome& result = dynamoClient.DescribeTable(dtr);

        if (result.IsSuccess())
        {
            const Aws::DynamoDB::Model::TableDescription& td = result.GetResult().GetTable();
            std::cout << "Table name  : " << td.GetTableName() << std::endl;
            std::cout << "Table ARN   : " << td.GetTableArn() << std::endl;
            std::cout << "Status      : " << Aws::DynamoDB::Model::TableStatusMapper::GetNameForTableStatus(td.GetTableStatus()) << std::endl;
            std::cout << "Item count  : " << td.GetItemCount() << std::endl;
            std::cout << "Size (bytes): " << td.GetTableSizeBytes() << std::endl;

            const Aws::DynamoDB::Model::ProvisionedThroughputDescription& ptd = td.GetProvisionedThroughput();
            std::cout << "Throughput" << std::endl;
            std::cout << "  Read Capacity : " << ptd.GetReadCapacityUnits() << std::endl;
            std::cout << "  Write Capacity: " << ptd.GetWriteCapacityUnits() << std::endl;

            const Aws::Vector<Aws::DynamoDB::Model::AttributeDefinition>& ad = td.GetAttributeDefinitions();
            std::cout << "Attributes" << std::endl;
            for (const auto& a : ad)
                std::cout << "  " << a.GetAttributeName() << " (" <<
                Aws::DynamoDB::Model::ScalarAttributeTypeMapper::GetNameForScalarAttributeType(a.GetAttributeType()) <<
                ")" << std::endl;
        }
        else
        {
            std::cout << "Failed to describe table: " << result.GetError().GetMessage();
        }
```
+  For API details, see [DescribeTable](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/DescribeTable) in *AWS SDK for C\+\+ API Reference*\. 

### List tables<a name="dynamodb_ListTables_cpp_topic"></a>

The following code example shows how to list DynamoDB tables\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

```
        Aws::Client::ClientConfiguration clientConfig;
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

        Aws::DynamoDB::Model::ListTablesRequest listTablesRequest;
        listTablesRequest.SetLimit(50);
        do
        {
            const Aws::DynamoDB::Model::ListTablesOutcome& lto = dynamoClient.ListTables(listTablesRequest);
            if (!lto.IsSuccess())
            {
                std::cout << "Error: " << lto.GetError().GetMessage() << std::endl;
                return 1;
            }
            
            for (const auto& s : lto.GetResult().GetTableNames())
                std::cout << s << std::endl;
            listTablesRequest.SetExclusiveStartTableName(lto.GetResult().GetLastEvaluatedTableName());
        
        } while (!listTablesRequest.GetExclusiveStartTableName().empty());
```
+  For API details, see [ListTables](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/ListTables) in *AWS SDK for C\+\+ API Reference*\. 

### Put an item in a table<a name="dynamodb_PutItem_cpp_topic"></a>

The following code example shows how to put an item in a DynamoDB table\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

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
+  For API details, see [PutItem](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/PutItem) in *AWS SDK for C\+\+ API Reference*\. 

### Query a table<a name="dynamodb_Query_cpp_topic"></a>

The following code example shows how to query a DynamoDB table\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

```
        Aws::Client::ClientConfiguration clientConfig;
       
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
        Aws::DynamoDB::Model::QueryRequest req;
        
        req.SetTableName(table);

        // Set query key condition expression
        req.SetKeyConditionExpression(partitionKeyAttributeName + "= :valueToMatch");

        // Set Expression AttributeValues
        Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> attributeValues;
        attributeValues.emplace(":valueToMatch", partitionKeyAttributeValue);

        req.SetExpressionAttributeValues(attributeValues);

        // Perform Query operation
        const Aws::DynamoDB::Model::QueryOutcome& result = dynamoClient.Query(req);
        if (result.IsSuccess())
        {
            // Reference the retrieved items
            const Aws::Vector<Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue>>& items = result.GetResult().GetItems();
            if(items.size() > 0) 
            {
                std::cout << "Number of items retrieved from Query: " << items.size() << std::endl;
                //Iterate each item and print
                for(const auto &item: items)
                {
                std::cout << "******************************************************" << std::endl;
                // Output each retrieved field and its value
                for (const auto& i : item)
                    std::cout << i.first << ": " << i.second.GetS() << std::endl;
                }
            }

            else
            {
                std::cout << "No item found in table: " << table << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to Query items: " << result.GetError().GetMessage();
        }
```
+  For API details, see [Query](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/Query) in *AWS SDK for C\+\+ API Reference*\. 

### Scan a table<a name="dynamodb_Scan_cpp_topic"></a>

The following code example shows how to scan a DynamoDB table\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

```
        Aws::Client::ClientConfiguration clientConfig;
       
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
        Aws::DynamoDB::Model::ScanRequest req;
        req.SetTableName(table);

        if (!projection.empty())
            req.SetProjectionExpression(projection);        

        // Perform scan on table
        const Aws::DynamoDB::Model::ScanOutcome& result = dynamoClient.Scan(req);
        if (result.IsSuccess())
        {
            // Reference the retrieved items
            const Aws::Vector<Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue>>& items = result.GetResult().GetItems();
            if(items.size() > 0) 
            {
                std::cout << "Number of items retrieved from scan: " << items.size() << std::endl;
                //Iterate each item and print
                for(const auto &item: items)
                {
                std::cout << "******************************************************" << std::endl;
                // Output each retrieved field and its value
                for (const auto& i : item)
                    std::cout << i.first << ": " << i.second.GetS() << std::endl;
                }
            }

            else
            {
                std::cout << "No item found in table: " << table << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to Scan items: " << result.GetError().GetMessage();
        }
```
+  For API details, see [Scan](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/Scan) in *AWS SDK for C\+\+ API Reference*\. 

### Update an item in a table<a name="dynamodb_UpdateItem_cpp_topic"></a>

The following code example shows how to update an item in a DynamoDB table\.

**SDK for C\+\+**  
 To learn how to set up and run this example, see [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
  

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
+  For API details, see [UpdateItem](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/UpdateItem) in *AWS SDK for C\+\+ API Reference*\. 