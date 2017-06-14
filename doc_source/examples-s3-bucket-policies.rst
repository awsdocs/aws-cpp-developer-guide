.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#####################################################
Managing Access to |S3| Buckets Using Bucket Policies
#####################################################

.. meta::
   :description: How to set, get, and delete a policy for an Amazon S3 bucket using the AWS SDK for
                 C++.
   :keywords: AWS for C++ SDK code examples, bucket policies, delete policy, get policy, set policy


You can set, get, or delete a *bucket policy* to manage access to your |S3| buckets.

.. include:: includes/examples-note.txt


.. _set-s3-bucket-policy:

Set a Bucket Policy
===================

You can set the bucket policy for a particular S3 bucket by calling the |s3client|'s
:functionname:`PutBucketPolicy` function and providing it with the bucket name and policy's JSON
representation in a :aws-cpp-class:`PutBucketPolicyRequest
<aws_1_1_s3_1_1_model_1_1_put_bucket_policy_request>`.

**Includes**

.. literalinclude:: example_code/s3/put_bucket_policy.cpp
   :lines: 14-16

**Code**

.. literalinclude:: example_code/s3/put_bucket_policy.cpp
   :dedent: 8
   :lines: 65-84

.. tip:: The :aws-cpp-class:`Aws::Utils::Json::JsonValue <aws_1_1_utils_1_1_json_1_1_json_value>`
   utility class can be used to help you construct valid JSON objects to pass to
   :classname:`PutBucketPolicy`.

See the :sdk-examples-cpp:`complete example <s3/put_bucket_policy.cpp>`.


.. _get-s3-bucket-policy:

Get a Bucket Policy
===================

To retrieve the policy for an |S3| bucket, call the |s3client|'s :functionname:`GetBucketPolicy`
function, passing it the name of the bucket in a :aws-cpp-class:`GetBucketPolicyRequest
<aws_1_1_s3_1_1_model_1_1_get_bucket_policy_request>`.

**Includes**

.. literalinclude:: example_code/s3/get_bucket_policy.cpp
   :lines: 14-16

**Code**

.. literalinclude:: example_code/s3/get_bucket_policy.cpp
   :dedent: 8
   :lines: 44-65

See the :sdk-examples-cpp:`complete example <s3/get_bucket_policy.cpp>`.


.. _delete-s3-bucket-policy:

Delete a Bucket Policy
======================

To delete a bucket policy, call the |s3client|'s :functionname:`DeleteBucketPolicy` function,
providing it with the bucket name in a :aws-cpp-class:`DeleteBucketPolicyRequest
<aws_1_1_s3_1_1_model_1_1_delete_bucket_policy_request>`.

**Includes**

.. literalinclude:: example_code/s3/delete_bucket_policy.cpp
   :lines: 14-16

**Code**

.. literalinclude:: example_code/s3/delete_bucket_policy.cpp
   :dedent: 8
   :lines: 45-60

This function succeeds even if the bucket doesn't already have a policy. If you specify a bucket
name that doesn't exist or if you don't have access to the bucket, an
:classname:`AmazonServiceException` is thrown.

See the :sdk-examples-cpp:`complete example <s3/delete_bucket_policy.cpp>`.

More Info
=========

* :s3-api:`PutBucketPolicy` in the |S3-api|
* :s3-api:`GetBucketPolicy` in the |S3-api|
* :s3-api:`DeleteBucketPolicy` in the |S3-api|
* :s3-dg:`Access Policy Language Overview <access-policy-language-overview>` in the |S3-dg|
* :s3-dg:`Bucket Policy Examples <example-bucket-policies>` in the |S3-dg|
