# List tables<a name="dynamodb_ListTables_cpp_topic"></a>

The following code example shows how to list DynamoDB tables\.

**SDK for C\+\+**  
  

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
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
+  For API details, see [ListTables](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/ListTables) in *AWS SDK for C\+\+ API Reference*\. 