# Delete a table<a name="dynamodb_DeleteTable_cpp_topic"></a>

The following code example shows how to delete a DynamoDB table\.

**SDK for C\+\+**  
  

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
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
+  For API details, see [DeleteTable](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/DeleteTable) in *AWS SDK for C\+\+ API Reference*\. 