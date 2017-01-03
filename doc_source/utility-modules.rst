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

The |sdk-cpp| provides you with several utility modules to ease the complexity of developing AWS
applications in C++.

HTTP Stack
==========

Headers: ``/aws/core/http/``

The HTTP client provides connection pooling, is thread-safe, and can be reused as you need.  For
more information, see :doc:`client-config`.

String Utils
============

Header: ``/aws/core/utils/StringUtils.h``

This header file provides core string functions, such as ``trim``, ``lowercase``, and numeric
conversions.

Hashing Utils
=============

Header: ``/aws/core/utils/HashingUtils.h``

This header file provides hashing functions such as ``SHA256``, ``MD5``, ``Base64``, and ``SHA256_HMAC``.

JSON Parser
===========

Header: ``/aws/core/utils/json/JsonSerializer.h``

This header file provides a fully functioning yet lightweight JSON parser (thin wrapper around
*JsonCpp*).

XML Parser
==========

Header: ``/aws/core/utils/xml/XmlSerializer.h``

This header file provides a lightweight XML parser (thin wrapper around *tinyxml2*). RAII pattern
has been added to the interface.

