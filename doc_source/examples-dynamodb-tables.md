# Working with Tables in DynamoDB<a name="examples-dynamodb-tables"></a>

Tables are the containers for all items in a DynamoDB database\. Before you can add or remove data from DynamoDB, you must create a table\.

For each table, you must define:
+ A table *name* that is unique for your account and region\.
+ A *primary key* for which every value must be unique\. No two items in your table can have the same primary key value\.

  A primary key can be *simple*, consisting of a single partition \(HASH\) key, or *composite*, consisting of a partition and a sort \(RANGE\) key\.

  Each key value has an associated *data type*, enumerated by the [ScalarAttributeType](https://sdk.amazonaws.com/cpp/api/LATEST/namespace_aws_1_1_dynamo_d_b_1_1_model.html#a4b39ae66214e022d3737079d071e4bcb.html) class\. The key value can be binary \(B\), numeric \(N\), or a string \(S\)\. For more information, see [Naming Rules and Data Types](https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/HowItWorks.NamingRulesDataTypes.html) in the Amazon DynamoDB Developer Guide\.
+  *Provisioned throughput* values that define the number of reserved read/write capacity units for the table\.
**Note**  
 [Amazon DynamoDB pricing](https://aws.amazon.com/dynamodb/pricing/) is based on the provisioned throughput values that you set on your tables, so reserve only as much capacity as you think you’ll need for your table\.  
Provisioned throughput for a table can be modified at any time, so you can adjust capacity if your needs change\.

## Create a Table<a name="dynamodb-create-table"></a>

Use the [DynamoDB client](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_dynamo_d_b_client.html) `CreateTable` method to create a new DynamoDB table\. You need to construct table attributes and a table schema, both of which are used to identify the primary key of your table\. You must also supply initial provisioned throughput values and a table name\. `CreateTable` is an asynchronous operation\. `GetTableStatus` will return CREATING until the table is ACTIVE and ready for use\.

### Create a Table with a Simple Primary Key<a name="dynamodb-create-table-simple"></a>

This code creates a table with a simple primary key \(“Name”\)\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/CreateTableRequest.h>
#include <aws/dynamodb/model/KeySchemaElement.h>
#include <aws/dynamodb/model/ProvisionedThroughput.h>
#include <aws/dynamodb/model/ScalarAttributeType.h>
#include <iostream>
```

 **Code** 

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

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/dynamodb/create_table.cpp)\.

### Create a Table with a Composite Primary Key<a name="dynamodb-create-table-composite"></a>

Add another [AttributeDefinition](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_model_1_1_attribute_definition.html) and [KeySchemaElement](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_model_1_1_key_schema_element.html) to [CreateTableRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_model_1_1_create_table_request.html)\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/CreateTableRequest.h>
#include <aws/dynamodb/model/KeySchemaElement.h>
#include <aws/dynamodb/model/ProvisionedThroughput.h>
#include <aws/dynamodb/model/ScalarAttributeType.h>
#include <iostream>
```

 **Code** 

```
Aws::Client::ClientConfiguration clientConfig;
if (!region.empty())
    clientConfig.region = region;
Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

std::cout << "Creating table " << table <<
    " with a composite primary key:\n" \
    "* Language - partition key\n" \
    "* Greeting - sort key\n";

Aws::DynamoDB::Model::CreateTableRequest req;

Aws::DynamoDB::Model::AttributeDefinition hashKey1, hashKey2;
hashKey1.WithAttributeName("Language").WithAttributeType(Aws::DynamoDB::Model::ScalarAttributeType::S);
req.AddAttributeDefinitions(hashKey1);
hashKey2.WithAttributeName("Greeting").WithAttributeType(Aws::DynamoDB::Model::ScalarAttributeType::S);
req.AddAttributeDefinitions(hashKey2);

Aws::DynamoDB::Model::KeySchemaElement kse1, kse2;
kse1.WithAttributeName("Language").WithKeyType(Aws::DynamoDB::Model::KeyType::HASH);
req.AddKeySchema(kse1);
kse2.WithAttributeName("Greeting").WithKeyType(Aws::DynamoDB::Model::KeyType::RANGE);
req.AddKeySchema(kse2);

Aws::DynamoDB::Model::ProvisionedThroughput thruput;
thruput.WithReadCapacityUnits(5).WithWriteCapacityUnits(5);
req.SetProvisionedThroughput(thruput);

req.SetTableName(table);

const Aws::DynamoDB::Model::CreateTableOutcome& result = dynamoClient.CreateTable(req);
if (result.IsSuccess())
{
    std::cout << "Table \"" << result.GetResult().GetTableDescription().GetTableName() <<
        "\" was created!\n";
}
else
{
    std::cout << "Failed to create table:" << result.GetError().GetMessage();
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/dynamodb/create_table_composite_key.cpp) on GitHub\.

## List Tables<a name="dynamodb-list-tables"></a>

You can list the tables in a particular region by calling the [DynamoDB client](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_dynamo_d_b_client.html) `ListTables` method\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/ListTablesRequest.h>
#include <aws/dynamodb/model/ListTablesResult.h>
#include <iostream>
```

 **Code** 

```
Aws::Client::ClientConfiguration clientConfig;
Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

Aws::DynamoDB::Model::ListTablesRequest ltr;
ltr.SetLimit(50);
do
{
    const Aws::DynamoDB::Model::ListTablesOutcome& lto = dynamoClient.ListTables(ltr);
    if (!lto.IsSuccess())
    {
        std::cout << "Error: " << lto.GetError().GetMessage() << std::endl;
        return 1;
    }
    for (const auto& s : lto.GetResult().GetTableNames())
        std::cout << s << std::endl;
    ltr.SetExclusiveStartTableName(lto.GetResult().GetLastEvaluatedTableName());
} while (!ltr.GetExclusiveStartTableName().empty());
```

By default, up to 100 tables are returned per call\. Use `GetExclusiveStartTableName` on the returned [ListTablesOutcome](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_dynamo_d_b_client.html) object to get the last table that was evaluated\. You can use this value to start the listing after the last returned value of the previous listing\.

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/dynamodb/list_tables.cpp)\.

## Retrieve Information about a Table<a name="dynamodb-describe-table"></a>

You can find out more about a table by calling the [DynamoDB client](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_dynamo_d_b_client.html) `DescribeTable` method\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/DescribeTableRequest.h>
#include <iostream>
```

 **Code** 

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

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/dynamodb/describe_table.cpp) on GitHub\.

## Modify a Table<a name="dynamodb-update-table"></a>

You can modify your table’s provisioned throughput values at any time by calling the [DynamoDB client](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_dynamo_d_b_client.html) `UpdateTable` method\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/ProvisionedThroughput.h>
#include <aws/dynamodb/model/UpdateTableRequest.h>
#include <iostream>
```

 **Code** 

```
Aws::Client::ClientConfiguration clientConfig;
Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

std::cout << "Updating " << table << " with new provisioned throughput values" << std::endl;
std::cout << "Read capacity : " << rc << std::endl;
std::cout << "Write capacity: " << wc << std::endl;

Aws::DynamoDB::Model::UpdateTableRequest utr;
Aws::DynamoDB::Model::ProvisionedThroughput pt;
pt.WithReadCapacityUnits(rc).WithWriteCapacityUnits(wc);
utr.WithProvisionedThroughput(pt).WithTableName(table);

const Aws::DynamoDB::Model::UpdateTableOutcome& result = dynamoClient.UpdateTable(utr);
if (!result.IsSuccess())
{
    std::cout << result.GetError().GetMessage() << std::endl;
    return 1;
}
std::cout << "Done!" << std::endl;
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/dynamodb/update_table.cpp)\.

## Delete a Table<a name="dynamodb-delete-table"></a>

Call the [DynamoDB client](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_dynamo_d_b_1_1_dynamo_d_b_client.html) `DeleteTable` method and pass it the table’s name\.

 **Includes** 

```
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h> 
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/DeleteTableRequest.h>
#include <iostream>
```

 **Code** 

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
    std::cout << "Table \"" << result.GetResult().GetTableDescription().GetTableName() <<
        " deleted!\n";
}
else
{
    std::cout << "Failed to delete table: " << result.GetError().GetMessage();
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/dynamodb/delete_table.cpp) on GitHub\.

## More Info<a name="more-info"></a>
+  [Guidelines for Working with Tables](https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/GuidelinesForTables.html) in the Amazon DynamoDB Developer Guide
+  [Working with Tables in DynamoDB](https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/WorkingWithTables.html) in the Amazon DynamoDB Developer Guide