# Working with IAM Server Certificates<a name="examples-iam-server-certificates"></a>

To enable HTTPS connections to your website or application on AWS, you need an SSL/TLS *server certificate*\. You can use a server certificate provided by AWS Certificate Manager or one that you obtained from an external provider\.

We recommend that you use ACM to provision, manage, and deploy your server certificates\. With ACM you can request a certificate, deploy it to your AWS resources, and let ACM handle certificate renewals for you\. Certificates provided by ACM are free\. For more information about ACM, see the [AWS Certificate Manager User Guide](https://docs.aws.amazon.com/acm/latest/userguide/)\.

**Note**  
These code snippets assume that you understand the material in [Getting Started Using the AWS SDK for C\+\+](getting-started.md) and have configured default AWS credentials using the information in [Providing AWS Credentials](credentials.md)\.

## Retrieve a Server Certificate<a name="retrieve-a-server-certificate"></a>

You can retrieve a server certificate by calling the IAMClient’s `GetServerCertificate` function, passing it a [GetServerCertificateRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_get_server_certificate_request.html) with the certificate’s name\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/GetServerCertificateRequest.h>
#include <aws/iam/model/GetServerCertificateResult.h>
#include <iostream>
```

 **Code:** 

```
Aws::IAM::IAMClient iam;
Aws::IAM::Model::GetServerCertificateRequest request;
request.SetServerCertificateName(cert_name);

auto outcome = iam.GetServerCertificate(request);
if (!outcome.IsSuccess())
{
    std::cout << "Error getting server certificate " << cert_name <<
        ": " << outcome.GetError().GetMessage() << std::endl;
}
else
{
    const auto &certificate = outcome.GetResult().GetServerCertificate();
    std::cout << "Name: " <<
        certificate.GetServerCertificateMetadata().GetServerCertificateName()
        << std::endl << "Body: " << certificate.GetCertificateBody() <<
        std::endl << "Chain: " << certificate.GetCertificateChain() <<
        std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/iam/get_server_cert.cpp)\.

## List Server Certificates<a name="list-server-certificates"></a>

To list your server certificates, call the IAMClient’s `ListServerCertificates` function with a [ListServerCertificatesRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_server_certificates_request.html)\. It returns a [ListServerCertificatesResult](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_list_server_certificates_result.html)\.

Call the returned `ListServerCertificateResult` object’s `GetServerCertificateMetadataList` function to get a list of [ServerCertificateMetadata](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_server_certificate_metadata.html) objects that you can use to get information about each certificate\.

Results may be truncated; if the `ListServerCertificateResult` object’s `GetIsTruncated` function returns `true`, call the `ListServerCertificatesRequest` object’s `SetMarker` function and use it to call `listServerCertificates` again to get the next batch of results\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/ListServerCertificatesRequest.h>
#include <aws/iam/model/ListServerCertificatesResult.h>
#include <iomanip>
#include <iostream>
```

 **Code:** 

```
Aws::IAM::IAMClient iam;
Aws::IAM::Model::ListServerCertificatesRequest request;

bool done = false;
bool header = false;
while (!done)
{
    auto outcome = iam.ListServerCertificates(request);
    if (!outcome.IsSuccess())
    {
        std::cout << "Failed to list server certificates: " <<
            outcome.GetError().GetMessage() << std::endl;
        break;
    }

    if (!header)
    {
        std::cout << std::left << std::setw(55) << "Name" <<
            std::setw(30) << "ID" << std::setw(80) << "Arn" <<
            std::setw(14) << "UploadDate" << std::setw(14) <<
            "ExpirationDate" << std::endl;
        header = true;
    }

    const auto &certificates =
        outcome.GetResult().GetServerCertificateMetadataList();

    for (const auto &certificate : certificates)
    {
        std::cout << std::left << std::setw(55) <<
            certificate.GetServerCertificateName() << std::setw(30) <<
            certificate.GetServerCertificateId() << std::setw(80) <<
            certificate.GetArn() << std::setw(14) <<
            certificate.GetUploadDate().ToGmtString(DATE_FORMAT) <<
            std::setw(14) <<
            certificate.GetExpiration().ToGmtString(DATE_FORMAT) <<
            std::endl;
    }

    if (outcome.GetResult().GetIsTruncated())
    {
        request.SetMarker(outcome.GetResult().GetMarker());
    }
    else
    {
        done = true;
    }
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/iam/list_server_certs.cpp)\.

## Update a Server Certificate<a name="update-a-server-certificate"></a>

You can update a server certificate’s name or path by calling the IAMClient’s `UpdateServerCertificate` function\. It takes a [UpdateServerCertificateRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_aws_1_1_i_a_m_1_1_model_1_1_update_server_certificate_request.html) object set with the server certificate’s current name and either a new name or new path to use\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/UpdateServerCertificateRequest.h>
#include <iostream>
```

 **Code:** 

```
Aws::IAM::IAMClient iam;
Aws::IAM::Model::UpdateServerCertificateRequest request;
request.SetServerCertificateName(old_name);
request.SetNewServerCertificateName(new_name);

auto outcome = iam.UpdateServerCertificate(request);
if (outcome.IsSuccess())
{
    std::cout << "Server certificate " << old_name
        << " successfully renamed as " << new_name
        << std::endl;
}
else
{
    std::cout << "Error changing name of server certificate " <<
        old_name << " to " << new_name << ":" <<
        outcome.GetError().GetMessage() << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/iam/update_server_cert.cpp)\.

## Delete a Server Certificate<a name="delete-a-server-certificate"></a>

To delete a server certificate, call the IAMClient’s `DeleteServerCertificate` function with a [DeleteServerCertificateRequest](https://sdk.amazonaws.com/cpp/api/LATEST/class_.html) containing the certificate’s name\.

 **Includes:** 

```
#include <aws/core/Aws.h>
#include <aws/iam/IAMClient.h>
#include <aws/iam/model/DeleteServerCertificateRequest.h>
#include <iostream>
```

 **Code:** 

```
Aws::IAM::IAMClient iam;
Aws::IAM::Model::DeleteServerCertificateRequest request;
request.SetServerCertificateName(cert_name);

const auto outcome = iam.DeleteServerCertificate(request);
if (!outcome.IsSuccess())
{
    std::cout << "Error deleting server certificate " << cert_name <<
        ": " << outcome.GetError().GetMessage() << std::endl;
}
else
{
    std::cout << "Successfully deleted server certificate " << cert_name
        << std::endl;
}
```

See the [complete example](https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp/example_code/iam/delete_server_cert.cpp)\.

## More Information<a name="more-information"></a>
+  [Working with Server Certificates](https://docs.aws.amazon.com/IAM/latest/UserGuide/id_credentials_server-certs.html) in the IAM User Guide
+  [GetServerCertificate](https://docs.aws.amazon.com/IAM/latest/APIReference/API_GetServerCertificate.html) in the IAM API Reference
+  [ListServerCertificates](https://docs.aws.amazon.com/IAM/latest/APIReference/API_ListServerCertificates.html) in the IAM API Reference
+  [UpdateServerCertificate](https://docs.aws.amazon.com/IAM/latest/APIReference/API_UpdateServerCertificate.html) in the IAM API Reference
+  [DeleteServerCertificate](https://docs.aws.amazon.com/IAM/latest/APIReference/API_DeleteServerCertificate.html) in the IAM API Reference
+  [AWS Certificate Manager User Guide](https://docs.aws.amazon.com/acm/latest/userguide/) 