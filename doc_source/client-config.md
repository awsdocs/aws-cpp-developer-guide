# AWS Client configuration<a name="client-config"></a>

The AWS SDK for C\+\+ enables you to change the default client configuration, which is helpful when you want to do things like:
+ Connect to the Internet through proxy
+ Change HTTP transport settings, such as connection timeout and request retries
+ Specify TCP socket buffer size hints

`ClientConfiguration` is a structure in the SDK for C\+\+ that you can instantiate and utilize in your code\. The following snippet illustrates using this class to access Amazon S3 through a proxy\.

```
Aws::Client::ClientConfiguration clientConfig;
clientConfig.proxyHost = "localhost";
clientConfig.proxyPort = 1234;
clientConfig.proxyScheme = Aws::Http::Scheme::HTTPS;
Aws::S3::S3Client(clientConfig);
```

 `ClientConfiguration` declaration \(See latest at [https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_client_1_1_client_configuration.html](https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_client_1_1_client_configuration.html) in the *AWS SDK for C\+\+ API Reference*\):

```
struct AWS_CORE_API ClientConfiguration
{
    ClientConfiguration();

    Aws::String userAgent;
    Aws::Http::Scheme scheme;
    Aws::Region region;
    bool useDualStack;
    unsigned maxConnections;
    long requestTimeoutMs;
    long connectTimeoutMs;
    bool enableTcpKeepAlive;
    unsigned long tcpKeepAliveIntervalMs;
    unsigned long lowSpeedLimit;
    std::shared_ptr<RetryStrategy> retryStrategy;
    Aws::String endpointOverride;
    Aws::Http::Scheme proxyScheme;
    Aws::String proxyHost;
    unsigned proxyPort;
    Aws::String proxyUserName;
    Aws::String proxyPassword;
    std::shared_ptr<Aws::Utils::Threading::Executor> executor;
    bool verifySSL;
    Aws::String caPath;
    Aws::String caFile;
    std::shared_ptr<Aws::Utils::RateLimits::RateLimiterInterface> writeRateLimiter;
    std::shared_ptr<Aws::Utils::RateLimits::RateLimiterInterface> readRateLimiter;
    Aws::Http::TransferLibType httpLibOverride;
    Aws::Client::FollowRedirectsPolicy followRedirects;
    bool disableExpectHeader;
    bool enableClockSkewAdjustment;
    bool enableHostPrefixInjection;
    bool enableEndpointDiscovery;
};
```

## Configuration Variables<a name="configuration-variables"></a>

**userAgent**  
For internal use only\. Do not change the setting of this variable\.

**scheme**  
Specifies the URI addressing scheme, either HTTP or HTTPS\. The default scheme is HTTPS\.

**region**  
Specifies the AWS Region to use, such as *us\-east\-1*\. By default, the Region used is the default Region configured in the applicable AWS credentials\.

**useDualStack**  
Controls whether to use dual stack IPv4 and IPv6 endpoints\. Note that not all AWS services support IPv6 in all Regions\.

**maxConnections**  
Specifies the maximum number of HTTP connections to a single server\. The default value is 25\. No maximum allowed value exists other than what your bandwidth can reasonably support\.

**requestTimeoutMs and connectTimeoutMs**  
Specifies the amount of time in milliseconds to wait before timing out an HTTP request\. For example, consider increasing these times when transferring large files\.

**enableTcpKeepAlive**  
Controls whether to send TCP keep\-alive packets\. The default setting is true\. Use in conjunction with the `tcpKeepAliveIntervalMs` variable\. This variable is not applicable for WinINet and the IXMLHTTPRequest2 client\.

**tcpKeepAliveIntervalMs**  
Specifies the time interval in milliseconds at which to send a keep\-alive packet over a TCP connection\. The default interval is 30 seconds\. The minimum setting is 15 seconds\. This variable is not applicable for WinINet and the IXMLHTTPRequest2 client\.

**lowSpeedLimit**  
Specifies the minimum allowed transfer speed in bytes per second\. If the transfer speed falls below the specified speed, the transfer operation is aborted\. The default setting is 1 byte/second\. This variable is applicable only for CURL clients\.

**retryStrategy**  
References the implementation of the retry strategy\. The default strategy implements an exponential backoff policy\. To perform a different strategy, implement a subclass of the `RetryStrategy` class and assign an instance to this variable\.

**endpointOverride**  
Specifies an overriding HTTP endpoint with which to communicate with a service\.

**proxyScheme, proxyHost, proxyPort, proxyUserName, and proxyPassword**  
Used to set up and configure a proxy for all communications with AWS\. Examples of when this functionality might be useful include debugging in conjunction with the Burp suite, or using a proxy to connect to the Internet\.

**executor**  
References the implementation of the asynchronous Executor handler\. The default behavior is to create and detach a thread for each async call\. To change this behavior, implement a subclass of the `Executor` class and assign an instance to this variable\.

**verifySSL**  
Controls whether to verify SSL certificates\. By default SSL certificates are verified\. To disable verification, set the variable to false\.

**caPath, caFile**  
Instructs the HTTP client where to find your SSL certificate trust store\. An example trust store might be a directory prepared with the OpenSSL `c_rehash` utility\. These variables should not need to be set unless your environment uses symlinks\. These variables have no effect on Windows and macOS systems\.

**writeRateLimiter and readRateLimiter**  
References to the implementations of read and write rate limiters which are used to throttle the bandwidth used by the transport layer\. By default, the read and write rates are not throttled\. To introduce throttling, implement a subclass of the `RateLimiterInterface` and assign an instance to these variables\.

**httpLibOverride**  
Specifies the HTTP implementation returned by the default HTTP factory\. The default HTTP client for Windows is WinHTTP\. The default HTTP client for all other platforms is CURL\.

**followRedirects**  
Controls the behavior when handling HTTP 300 redirect codes\.

**disableExpectHeader**  
Applicable only for CURL HTTP clients\. By default, CURL adds an “Expect: 100\-Continue” header in an HTTP request to avoid sending the HTTP payload in situations where the server responds with an error immediately after receiving the header\. This behavior can save a round\-trip and is useful in situations where the payload is small and network latency is relevant\. The variable’s default setting is false\. If set to true, CURL is instructed to send both the HTTP request header and body payload together\.

**enableClockSkewAdjustment**  
Controls whether clock skew is adjusted after each HTTP attempt\. The default setting is false\.

**enableHostPrefixInjection**  
Controls whether the HTTP host adds a “data\-” prefix to DiscoverInstances requests\. By default, this behavior is enabled\. To disable it, set the variable to false\.

**enableEndpointDiscovery**  
Controls whether endpoint discovery is used\. By default, regional or overridden endpoints are used\. To enable endpoint discovery, set the variable to true\.