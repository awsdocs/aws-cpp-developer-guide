.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#########################
Providing AWS Credentials
#########################

To connect to any of the supported services with the |sdk-cpp|, you must provide AWS credentials.
The AWS SDKs and CLIs use :emphasis:`provider chains` to look for AWS credentials in several
different places, including system/user environment variables and local AWS configuration files.

You can set your credentials for use by the |sdk-cpp| can be done in various ways, but here are the
recommended approaches:

.. the following file is in the shared content...

.. include:: common/sdk-shared-credentials.txt

Once you set your AWS credentials using one of these methods, the |sdk-cpp| loads them automatically
by using the default credential provider chain.

You can also supply AWS credentials using your own methods by:

* Providing credentials to an AWS client class constructor.

* Using |COG|_, an AWS identity management solution. You can use the
  ``CognitoCachingCredentialsProviders`` classes in the identity-management project. For more
  information, see the |COG-dg|_.

