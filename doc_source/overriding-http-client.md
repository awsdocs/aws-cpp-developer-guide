# Overriding Your HTTP Client<a name="overriding-http-client"></a>

The default HTTP client for Windows is [WinHTTP](https://msdn.microsoft.com/en-us/library/windows/desktop/aa382925%28v=vs.85%29.aspx)\. The default HTTP client for all other platforms is [curl](https://curl.haxx.se/)\. If needed, you can create a custom `HttpClientFactory` to pass to any service client’s constructor\.