.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###############
Utility Modules
###############

.. meta::
    :description:
        There are many C++ utility modules in the AWS SDK for C++ including string utils, hashing utils, 
        a JSON parser, and an XML parser.
    :keywords:

The |sdk-cpp| includes many :aws-cpp-namespace:`utility modules <aws_1_1_utils>` to reduce the
complexity of developing AWS applications in C++.

HTTP Stack
==========

An HTTP stack that provides connection pooling, is thread-safe, and can be reused as you need. For
more information, see :doc:`client-config`.

.. list-table::
   :widths: 1 2
   :stub-columns: 1

   * - Headers
     - :sdk-source:`/aws/core/http/ <aws-cpp-sdk-core/include/aws/core/http>`
   * - API Documentation
     - :aws-cpp-namespace:`Aws::Http <aws_1_1_http>`


String Utils
============

Core string functions, such as ``trim``, ``lowercase``, and numeric conversions.

.. list-table::
   :widths: 1 2
   :stub-columns: 1

   * - Header
     - :sdk-source:`aws/core/utils/StringUtils.h
       <aws-cpp-sdk-core/include/aws/core/utils/StringUtils.h>`
   * - API Documentation
     - :aws-cpp-class:`Aws::Utils::StringUtils <aws_1_1_utils_1_1_string_utils>`


Hashing Utils
=============

Hashing functions such as ``SHA256``, ``MD5``, ``Base64``, and ``SHA256_HMAC``.

.. list-table::
   :widths: 1 2
   :stub-columns: 1

   * - Header
     - :sdk-source:`/aws/core/utils/HashingUtils.h
       <aws-cpp-sdk-core/include/aws/core/utils/HashingUtils.h>`
   * - API Documentation
     - :aws-cpp-class:`Aws::Utils::HashingUtils <aws_1_1_utils_1_1_hashing_utils>`


JSON Parser
===========

A fully functioning yet lightweight JSON parser (a thin wrapper around *JsonCpp*).

.. list-table::
   :widths: 1 2
   :stub-columns: 1

   * - Header
     - :sdk-source:`/aws/core/utils/json/JsonSerializer.h
       <aws-cpp-sdk-core/include/aws/core/utils/json/JsonSerializer.h>`
   * - API Documentation
     - :aws-cpp-class:`Aws::Utils::Json::JsonValue <aws_1_1_utils_1_1_json_1_1_json_value>`


XML Parser
==========

A lightweight XML parser (a thin wrapper around *tinyxml2*). The `RAII pattern`__ has been
added to the interface.

.. __: http://en.cppreference.com/w/cpp/language/raii

.. list-table::
   :widths: 1 2
   :stub-columns: 1

   * - Header
     - :sdk-source:`/aws/core/utils/xml/XmlSerializer.h
       <aws-cpp-sdk-core/include/aws/core/utils/xml/XmlSerializer.h>`
   * - API Documentation
     - :aws-cpp-namespace:`Aws::Utils::Xml <aws_1_1_utils_1_1_xml>`

