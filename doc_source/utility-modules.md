# Utility Modules<a name="utility-modules"></a>

The AWS SDK for C\+\+ includes many [utility modules](https://sdk.amazonaws.com/cpp/api/LATEST/namespace_aws_1_1_utils.html) to reduce the complexity of developing AWS applications in C\+\+\.

## HTTP Stack<a name="http-stack"></a>

An HTTP stack that provides connection pooling, is thread\-safe, and can be reused as you need\. For more information, see [AWS Client Configuration](client-config.md)\.


****  

|  |  | 
| --- |--- |
|  Headers  |   [/aws/core/http/](https://github.com/aws/aws-sdk-cpp/tree/master/aws-cpp-sdk-core/include/aws/core/http)   | 
|  API Documentation  |   [Aws::Http](https://sdk.amazonaws.com/cpp/api/LATEST/namespace_aws_1_1_http.html)   | 

## String Utils<a name="string-utils"></a>

Core string functions, such as `trim`, `lowercase`, and numeric conversions\.


****  

|  |  | 
| --- |--- |
|  Header  |   [aws/core/utils/StringUtils\.h](https://github.com/aws/aws-sdk-cpp/tree/master/aws-cpp-sdk-core/include/aws/core/utils/StringUtils.h)   | 
|  API Documentation  |   [Aws::Utils::StringUtils](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_utils_1_1_string_utils.html)   | 

## Hashing Utils<a name="hashing-utils"></a>

Hashing functions such as `SHA256`, `MD5`, `Base64`, and `SHA256_HMAC`\.


****  

|  |  | 
| --- |--- |
|  Header  |   [/aws/core/utils/HashingUtils\.h](https://github.com/aws/aws-sdk-cpp/tree/master/aws-cpp-sdk-core/include/aws/core/utils/HashingUtils.h)   | 
|  API Documentation  |   [Aws::Utils::HashingUtils](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_utils_1_1_hashing_utils.html)   | 

## JSON Parser<a name="json-parser"></a>

A fully functioning yet lightweight JSON parser \(a thin wrapper around *JsonCpp*\)\.


****  

|  |  | 
| --- |--- |
|  Header  |   [/aws/core/utils/json/JsonSerializer\.h](https://github.com/aws/aws-sdk-cpp/tree/master/aws-cpp-sdk-core/include/aws/core/utils/json/JsonSerializer.h)   | 
|  API Documentation  |   [Aws::Utils::Json::JsonValue](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_utils_1_1_json_1_1_json_value.html)   | 

## XML Parser<a name="xml-parser"></a>

A lightweight XML parser \(a thin wrapper around *tinyxml2*\)\. The [RAII pattern](http://en.cppreference.com/w/cpp/language/raii) has been added to the interface\.


****  

|  |  | 
| --- |--- |
|  Header  |   [/aws/core/utils/xml/XmlSerializer\.h](https://github.com/aws/aws-sdk-cpp/tree/master/aws-cpp-sdk-core/include/aws/core/utils/xml/XmlSerializer.h)   | 
|  API Documentation  |   [Aws::Utils::Xml](https://sdk.amazonaws.com/cpp/api/LATEST/namespace_aws_1_1_utils_1_1_xml.html)   | 