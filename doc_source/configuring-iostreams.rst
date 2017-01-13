.. Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

##############################################################
Controlling IOStreams Used by the HttpClient and the AWSClient
##############################################################

By default, all responses use an input stream backed by a ``stringbuf``. If needed, you can override
the default behavior. For example, if you are using an |S3long| ``GetObject`` and don't want to load
the entire file into memory, you can use :classname:`IOStreamFactory` in
:classname:`AmazonWebServiceRequest` to pass a lambda to create a file stream.

Example file stream request:

.. code-block:: cpp

    GetObjectRequest getObjectRequest;
    getObjectRequest.SetBucket(fullBucketName);
    getObjectRequest.SetKey(keyName);
    getObjectRequest.SetResponseStreamFactory([](){
        return Aws::New<Aws::FStream>(
            ALLOCATION_TAG, DOWNLOADED_FILENAME, std::ios_base::out); });

    auto getObjectOutcome = s3Client->GetObject(getObjectRequest);

