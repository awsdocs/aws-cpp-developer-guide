.. Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

########################
AWS Client Configuration
########################

You can use the client configuration to control most functionality in the |sdk-cpp|.

``ClientConfiguration`` declaration:

.. code-block:: cpp

    struct AWS_CORE_API ClientConfiguration
    {
        ClientConfiguration();

        Aws::String userAgent;
        Aws::Http::Scheme scheme;
        Aws::Region region;
        Aws::String authenticationRegion;
        unsigned maxConnections;
        long requestTimeoutMs;
        long connectTimeoutMs;
        std::shared_ptr<RetryStrategy> retryStrategy;
        Aws::String endpointOverride;
        Aws::String proxyHost;
        unsigned proxyPort;
        Aws::String proxyUserName;
        Aws::String proxyPassword;
        std::shared_ptr<Aws::Utils::Threading::Executor> executor;
        bool verifySSL;
        Aws::String caPath;
        std::shared_ptr<Aws::Utils::RateLimits::RateLimiterInterface> writeRateLimiter;
        std::shared_ptr<Aws::Utils::RateLimits::RateLimiterInterface> readRateLimiter;
    };

Configuration Variables
=======================

userAgent
    Built in the constructor and pulls information from your operating system. Do not alter the user
    agent.

scheme
    The default value is HTTPS. You can set this value to HTTP if the information you are passing is
    not sensitive and the service to which you want to connect supports an HTTP endpoint.  AWS Auth
    protects you from tampering.

region
    Specifies where you want the client to communicate. Examples include *us-east-1* or *us-west-1*.
    You must ensure that the service you want to use has an endpoint in the region you configure.

authenticationRegion
    Allows you to specify an arbitrary region to use for signing. If you don't set
    ``authenticationRegion``, we fall back to ``region``. If you do set ``authenticationRegion``,
    you are also responsible for setting endpoint override to connect to the endpoint that
    cooresponds with your custom region.

maxConnections
    The maximum number of allowed connections to a single server for your HTTP communications. The
    default value is 25. You can set this value as high as you can support the bandwidth. We
    recommend a value around 25.

requestTimeoutMs and connectTimeoutMs
    Values that determine the length of time, in milliseconds, to wait before timing out a request.
    You can increase this value if you need to transfer large files, such as in |S3long| or
    |CFlong|.

retryStrategy
    Defaults to exponential backoff. You can override this default by implementing a subclass of
    ``RetryStrategy`` and passing an instance.

endpointOverride
    Do not alter the endpoint.

proxyHost, proxyPort, proxyUserName, and proxyPassword
    These settings allow you to configure a proxy for all communication with AWS. Examples of when
    this functionality might be useful include debugging in conjunction with the Burp suite, or
    using a proxy to connect to the Internet.

executor
    The default behavior is to create and detach a thread for each async call. You can change this
    behavior by implementing a subclass of ``Executor`` and passing an instance.

verifySSL
    Specifies whether to enable SSL certificate verification. If necessary, you can disable SSL
    certificate verification by setting ``verifySSL`` to ``false``.

caPath
    Enables you to tell the HTTP client where to find your SSL certificate trust store (for example,
    a directory prepared with OpenSSL's ``c_rehash`` utility). You shouldn't need to do this unless
    you are using symlinks in your environment. This has no effect on Windows or OS X.

writeRateLimiter and readRateLimiter
    Used to throttle the bandwidth used by the transport layer. The default for these limiters is
    open. You can use the default implementation with the rates you want, or you can create your own
    instance by implementing a subclass of ``RateLimiterInterface``.

