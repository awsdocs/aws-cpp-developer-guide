.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#######################################
Configuring an |s3| Bucket as a Website
#######################################

.. meta::
   :description: How to manage an S3 bucket's website configuration using the AWS SDK for C++.
   :keywords: s3

You can configure an |s3| bucket to behave as a website. To do this, you need to set its website
configuration.

.. include:: includes/examples-note.txt

Set a Bucket's Website Configuration
====================================

To set an |s3| bucket's website configuration, call the |s3client|'s
:functionname:`PutBucketWebsite` function with a :aws-cpp-class:`PutBucketWebsiteRequest
<aws_1_1_s3_1_1_model_1_1_put_bucket_website_request>` object containing the bucket name and its
website configuration, provided in a :aws-cpp-class:`WebsiteConfiguration
<aws_1_1_s3_1_1_model_1_1_website_configuration>` object.

Setting an index document is *required*; all other parameters are optional.

**Includes**

.. literalinclude:: s3.cpp.put_website_config.inc.txt

**Code**

.. literalinclude:: s3.cpp.put_website_config.code.txt
   :dedent: 8

.. note:: Setting a website configuration does not modify the access permissions for your bucket.
   To make your files visible on the web, you will also need to set a *bucket policy* that allows
   public read access to the files in the bucket. For more information, see
   :doc:`examples-s3-bucket-policies`.

See the :sdk-examples-cpp:`complete example <s3/put_website_config.cpp>`.


Get a Bucket's Website Configuration
====================================

To get an |s3| bucket's website configuration, call the |s3client|'s
:functionname:`GetBucketWebsite` function with a :aws-cpp-class:`GetBucketWebsiteRequest
<aws_1_1_s3_1_1_model_1_1_get_bucket_website_request>` containing the name of the bucket to retrieve
the configuration for.

The configuration will be returned as a :aws-cpp-class:`GetBucketWebsiteResult
<aws_1_1_s3_1_1_model_1_1_get_bucket_website_result>` object within the outcome object. If there is
no website configuration for the bucket, then :code-cpp:`null` will be returned.

**Includes**

.. literalinclude:: s3.cpp.get_website_config.inc.txt

**Code**

.. literalinclude:: s3.cpp.get_website_config.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <s3/get_website_config.cpp>`.


Delete a Bucket's Website Configuration
=======================================

To delete an |s3| bucket's website configuration, call the |s3client|'s
:functionname:`DeleteBucketWebsite` function with a :aws-cpp-class:`DeleteBucketWebsiteRequest
<aws_1_1_s3_1_1_model_1_1_delete_bucket_website_request>`: containing the name of the bucket to
delete the configuration from.

**Includes**

.. literalinclude:: s3.cpp.delete_website_config.inc.txt

**Code**

.. literalinclude:: s3.cpp.delete_website_config.code.txt
   :dedent: 8

See the :sdk-examples-cpp:`complete example <s3/delete_website_config.cpp>`.


More Information
================

* :s3-api:`PUT Bucket website <RESTBucketPUTwebsite>` in the |s3-api|
* :s3-api:`GET Bucket website <RESTBucketGETwebsite>` in the |s3-api|
* :s3-api:`DELETE Bucket website <RESTBucketDELETEwebsite>` in the |s3-api|

