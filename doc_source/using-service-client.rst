.. Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#####################
Using Service Clients
#####################

AWS service client classes provide you with an interface to the AWS service represented by the
class. Service clients follow the namespace convention :samp:`Aws::{Service}::{Service}Client`.

For example, a client for |IAM| is constructed using the :classname:`Aws::IAM::IAMClient` class. For
an |S3| client, use :classname:`Aws::S3::S3Client`.

.. contents::
    :local:
    :depth: 1

Constructing client classes
===========================

You must supply AWS credentials when instantiating a service client. This can be accomplished using
the default credential provider chain, can be passed to the client directly, or you can use a custom
credential provider.

For more information about setting credentials, see :doc:`credentials`.

.. contents::
    :local:
    :depth: 1


Use the default credential provider chain
-----------------------------------------

The following code creates an Amazon DynamoDB client using a specialized client configuration,
default credential provider chain, and default HTTP client factory:

.. code-block:: cpp

    auto limiter = Aws::MakeShared<Aws::Utils::RateLimits::DefaultRateLimiter<>>(ALLOCATION_TAG, 200000);

    // Create a client
    ClientConfiguration config;
    config.scheme = Scheme::HTTPS;
    config.connectTimeoutMs = 30000;
    config.requestTimeoutMs = 30000;
    config.readRateLimiter = m_limiter;
    config.writeRateLimiter = m_limiter;

    auto client = Aws::MakeShared<DynamoDBClient>(ALLOCATION_TAG, config);


Manually pass credentials
-------------------------

To manually pass credentials, use the client constructor that takes three arguments, and use the
Aws::Auth::AWSCredentials class to provide your credentials to the constructor:

.. code-block:: cpp

    auto client = Aws::MakeShared<DynamoDBClient>(
        ALLOCATION_TAG, AWSCredentials("access_key_id", "secret_key"), config);


Use a custom credentials provider
---------------------------------

To use a custom credentials provider, pass to the Aws::MakeShared function, create a client using
one of the credential providers in the Aws::Auth namespace.

For example:

.. code-block:: cpp

    auto client = Aws::MakeShared<DynamoDBClient>(
        ALLOCATION_TAG,
        Aws::MakeShared<CognitoCachingAnonymousCredentialsProvider>(
            ALLOCATION_TAG, "identityPoolId", "accountId"), config);


