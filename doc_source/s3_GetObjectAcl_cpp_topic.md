# Get the ACL of an object<a name="s3_GetObjectAcl_cpp_topic"></a>

The following code example shows how to get the access control list \(ACL\) of an Amazon S3 object\.

**SDK for C\+\+**  
  

```
bool GetBucketAcl(const Aws::String& bucketName, const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::GetBucketAclRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::GetBucketAclOutcome outcome = 
        s3_client.GetBucketAcl(request);

    if (outcome.IsSuccess())
    {
        Aws::Vector<Aws::S3::Model::Grant> grants = 
            outcome.GetResult().GetGrants();

        for (auto it = grants.begin(); it != grants.end(); it++)
        {
            Aws::S3::Model::Grant grant = *it;
            Aws::S3::Model::Grantee grantee = grant.GetGrantee();
            
            std::cout << "For bucket " << bucketName << ": " 
                << std::endl << std::endl;

            if (grantee.TypeHasBeenSet())
            {
                std::cout << "Type:          "
                    << GetGranteeTypeString(grantee.GetType()) << std::endl;
            }
            
            if (grantee.DisplayNameHasBeenSet())
            {
                std::cout << "Display name:  " 
                    << grantee.GetDisplayName() << std::endl;
            }

            if (grantee.EmailAddressHasBeenSet())
            {
                std::cout << "Email address: " 
                    << grantee.GetEmailAddress() << std::endl;
            }

            if (grantee.IDHasBeenSet())
            {
                std::cout << "ID:            " 
                    << grantee.GetID() << std::endl;
            }
            
            if (grantee.URIHasBeenSet())
            {
                std::cout << "URI:           " 
                    << grantee.GetURI() << std::endl;
            }
            
            std::cout << "Permission:    " << 
                GetPermissionString("bucket", grant.GetPermission()) << 
                std::endl << std::endl;
        }
    }
    else
    {
        auto err = outcome.GetError();
        std::cout << "Error: GetBucketAcl: " 
            << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }

    return true;
}
```
+  Find instructions and more code on [GitHub](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3#code-examples)\. 
+  For API details, see [GetObjectAcl](https://docs.aws.amazon.com/goto/SdkForCpp/s3-2006-03-01/GetObjectAcl) in *AWS SDK for C\+\+ API Reference*\. 