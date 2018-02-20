.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

##############
Error Handling
##############

.. meta::
    :description:
        Using the outcome object to manage AWS SDK for C++ errors.
    :keywords:

The |sdk-cpp| does not use exceptions; however, you can use exceptions in your code. Every service
client returns an outcome object that includes the result and an error code.

**Example of handling error conditions**

.. code-block:: cpp

    bool CreateTableAndWaitForItToBeActive()
    {
      CreateTableRequest createTableRequest;
      AttributeDefinition hashKey;
      hashKey.SetAttributeName(HASH_KEY_NAME);
      hashKey.SetAttributeType(ScalarAttributeType::S);
      createTableRequest.AddAttributeDefinitions(hashKey);
      KeySchemaElement hashKeySchemaElement;
      hashKeySchemaElement.WithAttributeName(HASH_KEY_NAME).WithKeyType(KeyType::HASH);
      createTableRequest.AddKeySchema(hashKeySchemaElement);
      ProvisionedThroughput provisionedThroughput;
      provisionedThroughput.SetReadCapacityUnits(readCap);
      provisionedThroughput.SetWriteCapacityUnits(writeCap);
      createTableRequest.WithProvisionedThroughput(provisionedThroughput);
      createTableRequest.WithTableName(tableName);

      CreateTableOutcome createTableOutcome = dynamoDbClient->CreateTable(createTableRequest);
      if (createTableOutcome.IsSuccess())
      {
         DescribeTableRequest describeTableRequest;
         describeTableRequest.SetTableName(tableName);
         bool shouldContinue = true;
         DescribeTableOutcome outcome = dynamoDbClient->DescribeTable(describeTableRequest);

         while (shouldContinue)
         {
             if (outcome.GetResult().GetTable().GetTableStatus() == TableStatus::ACTIVE)
             {
                break;
             }
             else
             {
                std::this_thread::sleep_for(std::chrono::seconds(1));
             }
         }
         return true;
      }
      else if(createTableOutcome.GetError().GetErrorType() == DynamoDBErrors::RESOURCE_IN_USE)
      {
         return true;
      }

      return false;
    }

