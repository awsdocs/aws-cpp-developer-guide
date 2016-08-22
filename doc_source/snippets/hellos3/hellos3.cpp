#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>

using namespace Aws::S3;
using namespace Aws::S3::Model;

static const char* KEY = "s3_cpp_sample_key";
static const char* BUCKET = "s3-cpp-sample-bucket";

int main()
{
    S3Client client;

    //first put an object into s3
    PutObjectRequest putObjectRequest;
    putObjectRequest.WithKey(KEY)
           .WithBucket(BUCKET);

    //this can be any arbitrary stream (e.g. fstream, stringstream etc...)
    auto requestStream = Aws::MakeShared<Aws::StringStream>("s3-sample");
    *requestStream << "Hello World!";

    //set the stream that will be put to s3
    putObjectRequest.SetBody(requestStream);

    auto putObjectOutcome = client.PutObject(putObjectRequest);

    if(putObjectOutcome.IsSuccess())
    {
        std::cout << "Put object succeeded" << std::endl;
    }
    else
    {
        std::cout << "Error while putting Object " <<
            putObjectOutcome.GetError().GetExceptionName() << " " <<
            putObjectOutcome.GetError().GetMessage() << std::endl;
    }

    //now get the object back out of s3. The response stream can be overridden
    //here if you want it to go directly to a file. In this case the default
    //string buf is exactly what we want.
    GetObjectRequest getObjectRequest;
    getObjectRequest.WithBucket(BUCKET)
        .WithKey(KEY);

    auto getObjectOutcome = client.GetObject(getObjectRequest);

    if(getObjectOutcome.IsSuccess())
    {
        std::cout << "Successfully retrieved object from s3 with value: " <<
            std::endl;
        std::cout << getObjectOutcome.GetResult().GetBody().rdbuf() << std::endl
            << std::endl;;
    }
    else
    {
        std::cout << "Error while getting object " <<
            getObjectOutcome.GetError().GetExceptionName() << " " <<
            getObjectOutcome.GetError().GetMessage() << std::endl;
    }

    return 0;
}

