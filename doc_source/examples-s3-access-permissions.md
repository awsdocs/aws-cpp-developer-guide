# Managing Amazon S3 Access Permissions<a name="examples-s3-access-permissions"></a>

Access permissions for an Amazon S3 bucket or object are defined in an access control list \(ACL\)\. The ACL specifies the owner of the bucket/object and a list of grants\. Each grant specifies a user \(or grantee\) and the user’s permissions to access the bucket/object, such as READ or WRITE access\.

## Manage an Object’s Access Control List<a name="manage-an-object-s-access-control-list"></a>

The access control list for an object can be retrieved by calling the `S3Client` method `GetObjectAcl`\. The method accepts the names of the object and its bucket\. The return value includes the ACL’s `Owner` and list of `Grants`\.

```
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/model/Permission.h>
#include <aws/s3/model/Type.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/Owner.h>
#include <aws/s3/model/Grantee.h>
#include <aws/s3/model/Grant.h>
#include <aws/s3/model/AccessControlPolicy.h>
#include <aws/s3/model/AccessControlPolicy.h>
#include <aws/s3/model/GetObjectAclRequest.h>
#include <aws/s3/model/PutObjectAclRequest.h>
#include <awsdoc/s3/s3_examples.h>
```

```
bool AwsDoc::S3::GetObjectAcl(const Aws::String& bucketName,
    const Aws::String& objectKey, 
    const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::GetObjectAclRequest request;
    request.SetBucket(bucketName);
    request.SetKey(objectKey);

    Aws::S3::Model::GetObjectAclOutcome outcome =
        s3_client.GetObjectAcl(request);

    if (outcome.IsSuccess())
    {
        Aws::S3::Model::Owner owner = outcome.GetResult().GetOwner();
        Aws::Vector<Aws::S3::Model::Grant> grants =
            outcome.GetResult().GetGrants();

        std::cout << "Object ACL information for object '" << objectKey <<
            "' in bucket '" << bucketName << "':" << std::endl << std::endl;

        std::cout << "Owner:" << std::endl << std::endl;
        std::cout << "Display name:  " << owner.GetDisplayName() << std::endl;
        std::cout << "ID:            " << owner.GetID() << std::endl <<
            std::endl;

        std::cout << "Grantees:" << std::endl << std::endl;

        for (auto it = std::begin(grants); it != end(grants); ++it) {
            auto grantee = it->GetGrantee();
            std::cout << "Display name:  " << grantee.GetDisplayName() <<
                std::endl;
            std::cout << "Email address: " << grantee.GetEmailAddress() <<
                std::endl;
            std::cout << "ID:            " << grantee.GetID() << std::endl;
            std::cout << "Type:          " << GetGranteeType(
                grantee.GetType()) <<
                std::endl;
            std::cout << "URI:           " << grantee.GetURI() << std::endl <<
                std::endl;
        }

        return true;
    }
    else
    {
        auto error = outcome.GetError();
        std::cout << "Error: GetObjectAcl: " << error.GetExceptionName()
            << " - " << error.GetMessage() << std::endl;

        return false;
    }
}
```

The ACL can be modified by either creating a new ACL or changing the grants specified in the current ACL\. The updated ACL becomes the new current ACL by passing it to the `PutObjectAcl` method\.

The following code uses the ACL retrieved by `GetObjectAcl` and adds a new grant to it\. The user or grantee is given READ permission for the object\. The modified ACL is passed to `PutObjectAcl`, making it the new current ACL\. For further details, see [the example source file](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/get_put_object_acl.cpp)\.

```
bool AwsDoc::S3::PutObjectAcl(const Aws::String& bucketName,
    const Aws::String& objectKey, 
    const Aws::String& region, 
    const Aws::String& ownerID, 
    const Aws::String& granteePermission, 
    const Aws::String& granteeType, 
    const Aws::String& granteeID, 
    const Aws::String& granteeDisplayName, 
    const Aws::String& granteeEmailAddress, 
    const Aws::String& granteeURI)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::Owner owner;
    owner.SetID(ownerID);

    Aws::S3::Model::Grantee grantee;
    grantee.SetType(SetGranteeType(granteeType));

    if (granteeEmailAddress != "")
    {
        grantee.SetEmailAddress(granteeEmailAddress);
    }

    if (granteeID != "")
    {
        grantee.SetID(granteeID);
    }

    if (granteeDisplayName != "")
    {
        grantee.SetDisplayName(granteeDisplayName);
    }

    if (granteeURI != "")
    {
        grantee.SetURI(granteeURI);
    }

    Aws::S3::Model::Grant grant;
    grant.SetGrantee(grantee);
    grant.SetPermission(SetGranteePermission(granteePermission));

    Aws::Vector<Aws::S3::Model::Grant> grants;
    grants.push_back(grant);

    Aws::S3::Model::AccessControlPolicy acp;
    acp.SetOwner(owner);
    acp.SetGrants(grants);

    Aws::S3::Model::PutObjectAclRequest request;
    request.SetAccessControlPolicy(acp);
    request.SetBucket(bucketName);
    request.SetKey(objectKey);

    Aws::S3::Model::PutObjectAclOutcome outcome =
        s3_client.PutObjectAcl(request);

    if (outcome.IsSuccess())
    {
        return true;
    }
    else
    {
        auto error = outcome.GetError();
        std::cout << "Error: PutObjectAcl: " << error.GetExceptionName()
            << " - " << error.GetMessage() << std::endl;

        return false;
    }
}
```

## Manage a Bucket’s Access Control List<a name="manage-a-bucket-s-access-control-list"></a>

In most cases, the preferred method for setting the access permissions of a bucket is to define a bucket policy\. However, buckets also support access control lists for users who wish to use them\.

Management of an access control list for a bucket is identical to that used for an object\. The `GetBucketAcl` method retrieves a bucket’s current ACL and `PutBucketAcl` applies a new ACL to the bucket\.

The following code demonstrates getting and setting a bucket ACL\. For details, see [the example source file](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/s3/get_put_bucket_acl.cpp)\.

```
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/model/Permission.h>
#include <aws/s3/model/Type.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/Owner.h>
#include <aws/s3/model/Grantee.h>
#include <aws/s3/model/Grant.h>
#include <aws/s3/model/AccessControlPolicy.h>
#include <aws/s3/model/PutBucketAclRequest.h>
#include <aws/s3/model/GetBucketAclRequest.h>
#include <awsdoc/s3/s3_examples.h>
```

```
Aws::S3::Model::Permission SetGranteePermission(const Aws::String& access)
{
    if (access == "FULL_CONTROL")
        return Aws::S3::Model::Permission::FULL_CONTROL;
    if (access == "WRITE")
        return Aws::S3::Model::Permission::WRITE;
    if (access == "READ")
        return Aws::S3::Model::Permission::READ;
    if (access == "WRITE_ACP")
        return Aws::S3::Model::Permission::WRITE_ACP;
    if (access == "READ_ACP")
        return Aws::S3::Model::Permission::READ_ACP;
    return Aws::S3::Model::Permission::NOT_SET;
}

Aws::String GetGranteeType(const Aws::S3::Model::Type& type)
{
    if (type == Aws::S3::Model::Type::AmazonCustomerByEmail)
        return "Amazon customer by email";
    if (type == Aws::S3::Model::Type::CanonicalUser)
        return "Canonical user";
    if (type == Aws::S3::Model::Type::Group)
        return "Group";
    return "Not set";
}

Aws::S3::Model::Type SetGranteeType(const Aws::String& type)
{
    if (type == "Amazon customer by email")
        return Aws::S3::Model::Type::AmazonCustomerByEmail;
    if (type == "Canonical user")
        return Aws::S3::Model::Type::CanonicalUser;
    if (type == "Group")
        return Aws::S3::Model::Type::Group;
    return Aws::S3::Model::Type::NOT_SET;
}

bool AwsDoc::S3::PutBucketAcl(const Aws::String& bucketName, 
    const Aws::String& ownerID, 
    const Aws::String& granteePermission, 
    const Aws::String& granteeType, 
    const Aws::String& granteeID, 
    const Aws::String& region,
    const Aws::String& granteeDisplayName,
    const Aws::String& granteeEmailAddress,
    const Aws::String& granteeURI)
{
    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::Owner owner; 
    owner.SetID(ownerID);

    Aws::S3::Model::Grantee grantee;
    grantee.SetType(SetGranteeType(granteeType));

    if (granteeEmailAddress != "")
    {
        grantee.SetEmailAddress(granteeEmailAddress);
    }

    if (granteeID != "")
    {
        grantee.SetID(granteeID);
    }

    if (granteeDisplayName != "")
    {
        grantee.SetDisplayName(granteeDisplayName);
    }

    if (granteeURI != "")
    {
        grantee.SetURI(granteeURI);
    }

    Aws::S3::Model::Grant grant;
    grant.SetGrantee(grantee);
    grant.SetPermission(SetGranteePermission(granteePermission));

    Aws::Vector<Aws::S3::Model::Grant> grants;
    grants.push_back(grant);

    Aws::S3::Model::AccessControlPolicy acp;
    acp.SetOwner(owner);
    acp.SetGrants(grants);
    
    Aws::S3::Model::PutBucketAclRequest request;
    request.SetAccessControlPolicy(acp);
    request.SetBucket(bucketName);

    Aws::S3::Model::PutBucketAclOutcome outcome = 
        s3_client.PutBucketAcl(request);

    if (outcome.IsSuccess())
    {
        return true;
    }
    else
    {
        auto error = outcome.GetError();
        std::cout << "Error: PutBucketAcl: " << error.GetExceptionName()
            << " - " << error.GetMessage() << std::endl;

        return false;
    }
}

bool AwsDoc::S3::GetBucketAcl(const Aws::String& bucketName,
    const Aws::String& region)
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
        Aws::S3::Model::Owner owner = outcome.GetResult().GetOwner();
        Aws::Vector<Aws::S3::Model::Grant> grants = 
            outcome.GetResult().GetGrants();

        std::cout << "Bucket ACL information for bucket '" << bucketName <<
            "':" << std::endl << std::endl;

        std::cout << "Owner:" << std::endl << std::endl;
        std::cout << "Display name:  " << owner.GetDisplayName() << std::endl;
        std::cout << "ID:            " << owner.GetID() << std::endl << 
                                             std::endl;
        
        std::cout << "Grantees:" << std::endl << std::endl;

        for (auto it = std::begin(grants); it != end(grants); ++it) {
            auto grantee = it->GetGrantee();
            std::cout << "Display name:  " << grantee.GetDisplayName() << 
                                                  std::endl;
            std::cout << "Email address: " << grantee.GetEmailAddress() << 
                                                  std::endl;
            std::cout << "ID:            " << grantee.GetID() << std::endl;
            std::cout << "Type:          " << GetGranteeType(
                                                  grantee.GetType()) << 
                                                  std::endl;
            std::cout << "URI:           " << grantee.GetURI() << std::endl << 
                                                  std::endl;
        }

        return true;
    }
    else
    {
        auto error = outcome.GetError();
        std::cout << "Error: GetBucketAcl: " << error.GetExceptionName()
            << " - " << error.GetMessage() << std::endl;

        return false;
    }
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = "my-bucket";

        // Set the ACL's owner information. 
        const Aws::String owner_id = 
            "b380d412791d395dbcdc1fb1728b32a7cd07edae6467220ac4b7c0769EXAMPLE";

        // Set the ACL's grantee information.
        const Aws::String grantee_permission = "READ";
        
        // If the grantee is by canonical user, then either the user's ID or 
        // display name must be specified:
        const Aws::String grantee_type = "Canonical user";
        const Aws::String grantee_id = 
            "51ffd418eb142601651cc9d54984604a32b51a23153b4898fd2224772EXAMPLE";
        // const Aws::String grantee_display_name = "janedoe";

        // If the grantee is by Amazon customer by email, then the email 
        // address must be specified:
        // const Aws::String grantee_type = "Amazon customer by email";
        // const Aws::String grantee_email_address = "janedoe@example.com";

        // If the grantee is by group, then the predefined group URI must 
        // be specified:
        // const Aws::String grantee_type = "Group";
        // const Aws::String grantee_uri = 
        //     "http://acs.amazonaws.com/groups/global/AuthenticatedUsers";

        // Set the bucket's ACL.
        if (!AwsDoc::S3::PutBucketAcl(bucket_name,
            "us-east-1",
            owner_id,
            grantee_permission,
            grantee_type,
            grantee_id))
            // grantee_display_name, 
            // grantee_email_address, 
            // grantee_uri));
        {
            return 1;
        }
        
        // Get the bucket's ACL information that was just set.
        if (!AwsDoc::S3::GetBucketAcl(bucket_name, "us-east-1"))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
```