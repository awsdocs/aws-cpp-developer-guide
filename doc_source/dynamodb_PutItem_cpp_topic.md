# Put an item in a table<a name="dynamodb_PutItem_cpp_topic"></a>

The following code example shows how to put an item in a DynamoDB table, with the option of using the DynamoDB document client\.

**SDK for C\+\+**  
  

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
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/dynamodb#code-examples)\. 
+  For API details, see [PutItem](https://docs.aws.amazon.com/goto/SdkForCpp/dynamodb-2012-08-10/PutItem) in *AWS SDK for C\+\+ API Reference*\. 