# Scan a table<a name="dynamodb_Scan_cpp_topic"></a>

The following code example shows how to scan a DynamoDB table\.

**SDK for C\+\+**  
  

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
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
+  For API details, see [Scan](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/Scan) in *AWS SDK for C\+\+ API Reference*\. 