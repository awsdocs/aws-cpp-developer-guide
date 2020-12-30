# Controlling IOStreams Used by the HttpClient and the AWSClient<a name="configuring-iostreams"></a>

By default, all responses use an input stream backed by a `stringbuf`\. If needed, you can override the default behavior\. For example, if you are using an Amazon S3`GetObject` and don’t want to load the entire file into memory, you can use `IOStreamFactory` in `AmazonWebServiceRequest` to pass a lambda to create a file stream\.

 **Example file stream request** 

```
GetObjectRequest getObjectRequest;
getObjectRequest.SetBucket(fullBucketName);
getObjectRequest.SetKey(keyName);
getObjectRequest.SetResponseStreamFactory([](){
    return Aws::New<Aws::FStream>(
        ALLOCATION_TAG, DOWNLOADED_FILENAME, std::ios_base::out); });

auto getObjectOutcome = s3Client->GetObject(getObjectRequest);
```