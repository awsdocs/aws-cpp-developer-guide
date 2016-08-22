.. Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

###########################
Overriding your HTTP Client
###########################

.. _winhttp: https://msdn.microsoft.com/en-us/library/windows/desktop/aa382925%28v=vs.85%29.aspx
.. _curl: https://curl.haxx.se/

The default HTTP client for Windows is WinHTTP_. The default HTTP client for all other platforms is
curl_. If needed, you can create a custom ``HttpClientFactory`` to pass to any service client’s
constructor.


