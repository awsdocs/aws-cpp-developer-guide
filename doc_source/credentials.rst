.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#########################
Providing AWS Credentials
#########################

.. meta::
    :description:
        Different ways to supply AWS credentials when using the AWS SDK for C++.
    :keywords:

To connect to any of the supported services with the |sdk-cpp|, you must provide AWS credentials.
The AWS SDKs and CLIs use :emphasis:`provider chains` to look for AWS credentials in several
different places, including system/user environment variables and local AWS configuration files. 
For details, see `Credentials Providers <https://github.com/aws/aws-sdk-cpp/blob/master/Docs/Credentials_Providers.md>`_ 
in the aws-sdk-cpp repository in GitHub.

For related information, see the following: 

* To create a new AWS account, see `How do I create and activate a new AWS account <https://aws.amazon.com/premiumsupport/knowledge-center/create-and-activate-aws-account/>`_ 
  on the AWS Premium Support website.
* To create long-term AWS credentials, see `Programmtic access <https://docs.aws.amazon.com/general/latest/gr/aws-sec-cred-types.html#access-keys-and-secret-access-keys>`_ 
  in the AWS General Reference.
* To create short-term AWS credentials, see `Temporary Security Credentials <https://docs.aws.amazon.com/IAM/latest/UserGuide/id_credentials_temp.html>`_ in the AWS Identity and Access Management User Guide.
* To learn more about supported provider chains, see the `AWS Tools and SDKs Shared Configuration and Credentials Reference Guide <https://docs.aws.amazon.com/credref/latest/refdocs>`_, specifically:

  * `The .aws/credentials and .aws/config files <https://docs.aws.amazon.com/credref/latest/refdocs/creds-config-files.html>`_
  * `Using environment variables <https://docs.aws.amazon.com/credref/latest/refdocs/environment-variables.html>`_
  * `role_arn <https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-role_arn.html>`_ (corresponds to the :code:`AWS_ROLE_ARN` environment variable)
  * `web_identity_token_file <https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-web_identity_token_file.html>`_ (corresponds to the :code:`AWS_WEB_IDENTITY_TOKEN_FILE` environment variable)
  * `role_session_name <https://docs.aws.amazon.com/credref/latest/refdocs/setting-global-role_session_name.html>`_ (corresponds to the :code:`AWS_ROLE_SESSION_NAME` environment variable)

* To learn more about the :code:`AWS_CONTAINER_CREDENTIALS_RELATIVE_URI` environment variable, see `IAM Roles for Tasks <https://docs.aws.amazon.com/AmazonECS/latest/developerguide/task-iam-roles.html>`_ in the Amazon ECS Developer Guide. 

