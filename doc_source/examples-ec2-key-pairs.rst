.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

############################
Working with |EC2| Key Pairs
############################

.. meta::
   :description: How to create, list and delete EC2 key pairs using the AWS SDK for C++.
   :keywords: ec2

.. include:: includes/examples-note.txt

Create a Key Pair
===================

To create a key pair, call the |ec2client|'s :functionname:`CreateKeyPair` function with a
:aws-cpp-class:`CreateKeyPairRequest <aws_1_1_e_c2_1_1_model_1_1_create_key_pair_request>` that
contains the key's name.

**Includes**

.. literalinclude:: ec2.cpp.create_key_pair.inc.txt

**Code**

.. literalinclude:: ec2.cpp.create_key_pair.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <ec2/create_key_pair.cpp>`.


Describe Key Pairs
====================

To list your key pairs or to get information about them, call the |ec2client|'s
:functionname:`DescribeKeyPairs` function with a :aws-cpp-class:`DescribeKeyPairsRequest
<aws_1_1_e_c2_1_1_model_1_1_describe_key_pairs_request>`.

You will receive a :aws-cpp-class:`DescribeKeyPairsResponse
<aws_1_1_e_c2_1_1_model_1_1_describe_key_pairs_response>` that you can use to access the list of key
pairs by calling its :functionname:`GetKeyPairs` function, which returns a list of
:aws-cpp-class:`KeyPairInfo <aws_1_1_e_c2_1_1_model_1_1_key_pair_info>` objects.

**Includes**

.. literalinclude:: ec2.cpp.describe_key_pairs.inc.txt

**Code**

.. literalinclude:: ec2.cpp.describe_key_pairs.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <ec2/describe_key_pairs.cpp>`.


Delete a Key Pair
===================

To delete a key pair, call the |ec2client|'s :functionname:`DeleteKeyPair` function, passing it a
:aws-cpp-class:`DeleteKeyPairRequest <aws_1_1_e_c2_1_1_model_1_1_delete_key_pair_request>` that
contains the name of the key pair to delete.

**Includes**

.. literalinclude:: ec2.cpp.delete_key_pair.inc.txt

**Code**

.. literalinclude:: ec2.cpp.delete_key_pair.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <ec2/delete_key_pair.cpp>`.


More Information
================

* :ec2-ug:`Amazon EC2 Key Pairs <ec2-key-pairs>` in the |ec2-ug|
* :ec2-api:`CreateKeyPair` in the |ec2-api|
* :ec2-api:`DescribeKeyPairs` in the |ec2-api|
* :ec2-api:`DeleteKeyPair` in the |ec2-api|

