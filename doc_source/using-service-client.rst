.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.


######################
Service Client Classes
######################

.. meta::
    :description:
        Using AWS SDK for C++ service client classes to invoke AWS services.
    :keywords:

The AWS SDK for C++ includes client classes that provide interfaces to the 
AWS services. Each client class supports a particular AWS service. For 
example, the ``S3Client`` provides an interface to the Amazon S3 service.

The namespace for a client class follows the convention 
:samp:`Aws::{Service}::{Service}Client`. For example, the client class for 
|IAMlong| (IAM) is :classname:`Aws::IAM::IAMClient` and the Amazon S3 client 
class is :classname:`Aws::S3::S3Client`.

All client classes for all AWS services are thread-safe.

When instantiating a client class, AWS credentials must be supplied. For more 
information about credentials, see :doc:`credentials`.
