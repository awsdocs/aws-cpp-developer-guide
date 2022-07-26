# Overriding your HTTP client<a name="overriding-http-client"></a>

The default HTTP client for Windows is [WinHTTP](https://msdn.microsoft.com/en-us/library/windows/desktop/aa382925%28v=vs.85%29.aspx)\. The default HTTP client for all other platforms is [curl](https://curl.haxx.se/)\. 

Optionally, you can override the HTTP client default by creating a custom `HttpClientFactory` to pass to any service client’s constructor\. To override the HTTP client, the SDK must be built with curl support\. Curl support is built by default in Linux and macOS, but additional steps are required to build on Windows\. For more information about building the SDK on Windows with curl support, see [ Building the AWS SDK for C\+\+ on Windows](setup-windows.md)\.