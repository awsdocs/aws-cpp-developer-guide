.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###########################
Working with Items in |DDB|
###########################

.. meta::
   :description: How to retrieve (get), add, and update items in Amazon DynamoDB tables.
   :keywords: AWS SDK for C++ code examples, items from DynamoDB tables


In |ddb|, an item is a collection of *attributes*, each of which has a *name* and a *value*. An
attribute value can be a scalar, set, or document type. For more information, see :ddb-dg:`Naming
Rules and Data Types <HowItWorks.NamingRulesDataTypes>` in the |ddb-dg|.

.. _dynamodb-get-item:

Retrieve (Get) an Item from a Table
===================================

Call the :aws-cpp-class:`DynamoDB client <aws_1_1_dynamo_d_b_1_1_dynamo_d_b_client>` :methodname:`GetItem`
method. Pass it a :aws-cpp-class:`GetItemRequest <aws_1_1_dynamo_d_b_1_1_model_1_1_get_item_request>`
object with the table name and primary key value of the item you want. It returns a :aws-cpp-class:`GetItemResult
<aws_1_1_dynamo_d_b_1_1_model_1_1_get_item_result>` object.

You can use the returned :classname:`GetItemResult` object's :methodname:`GetItem()` method to
retrieve an :classname:`Aws::Map` of key :classname:`Aws::String` and
value :aws-cpp-class:`AttributeValue <aws_1_1_dynamo_d_b_1_1_model_1_1_attribute_value>`
pairs associated with the item.

**Includes**

.. literalinclude:: example_code/dynamodb/get_item.cpp
   :lines: 14-19

**Code**

.. literalinclude:: example_code/dynamodb/get_item.cpp
   :lines: 62-94
   :dedent: 8

See the :sdk-examples-cpp:`complete example <dynamodb/get_item.cpp>` on GitHub.

.. _dynamodb-add-item:

Add a New Item to a Table
=========================

Create key :classname:`Aws::String` and
value :aws-cpp-class:`AttributeValue <aws_1_1_dynamo_d_b_1_1_model_1_1_attribute_value>` pairs that
represent each item. These must include values for the table's primary key fields. If the
item identified by the primary key already exists, its fields are *updated* by the request. Add them
to the :aws-cpp-class:`PutItemRequest <aws_1_1_dynamo_d_b_1_1_model_1_1_put_item_request>` using
the :methodname:`AddItem` method.

**Includes**

.. literalinclude:: example_code/dynamodb/put_item.cpp
   :lines: 14-20

**Code**

.. literalinclude:: example_code/dynamodb/put_item.cpp
   :lines: 59-92
   :dedent: 8

See the :sdk-examples-cpp:`complete example <dynamodb/put_item.cpp>` on GitHub.


.. _dynamodb-update-item:

Update an Existing Item in a Table
==================================

You can update an attribute for an item that already exists in a table by using the |ddbclient|'s
:methodname:`UpdateItem` method, providing a table name, primary key value, and fields to
update and their corresponding value.

**Imports**

.. literalinclude:: example_code/dynamodb/update_item.cpp
   :lines: 14-19

**Code**

.. literalinclude:: example_code/dynamodb/update_item.cpp
   :lines: 61-96
   :dedent: 8

See the :sdk-examples-cpp:`complete example <dynamodb/update_item.cpp>`.


More Info
=========

* :ddb-dg:`Guidelines for Working with Items <GuidelinesForItems>` in the |ddb-dg|
* :ddb-dg:`Working with Items in DynamoDB <WorkingWithItems>` in the |ddb-dg|

