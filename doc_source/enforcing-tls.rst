.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#######################################
Enforcing TLS 1.2 in |SERVICENAMETITLE|
#######################################

.. meta::
   :description: Learn how to enforce TLS 1.2 in this AWS product or service.
   :keywords:

.. include:: common/_security-includes.txt

To increase security when communicating with AWS services, you should configure |SERVICENAME| to use TLS 1.2 or later.

The |sdk-cpp| is a cross-platform library; you can build and run your application on the platforms you want.
Different platforms might depend on different underlying HTTP clients.

By default, macOS, Linux, Android and other non-Windows platforms use `libcurl <https://curl.haxx.se/libcurl/>`_.
If the libcurl version is greater than 7.34.0, TLS 1.0 is the minimal version used by the underlying HTTP clients.

For Windows, the default library is `WinHttp <https://docs.microsoft.com/en-us/windows/win32/winhttp>`_.
In this case, TLS 1.0, TLS 1.1, and TLS 1.2 are acceptable secure protocols and the actual protocol to use is decided by Windows.
`WinINet <https://docs.microsoft.com/en-us/windows/win32/wininet>`_ and `IXMLHttpRequest2 <https://docs.microsoft.com/en-us/windows/win32/api/_ixhr2>`_ are the other two options that are available on Windows.
You can configure your application to replace the default library during CMake and at run-time.
For these two HTTP clients, the secure protocol is also decided by Windows.

The |sdk-cpp| also provides the flexibility to override the default HTTP clients.
For example you can enforce libcurl or use whatever HTTP clients you want by using a custom HTTP client factory.
So in order to use TLS 1.2 as the minimal version, you must be aware of the HTTP client library you are using.

Enforce TLS 1.2 with libcurl on all platforms
=============================================

This section assumes that the |sdk-cpp| is using libcurl as a dependency for HTTP protocol support.
In order to explicitly specify the TLS version, you will need a minimum libcurl version of 7.34.0.
In addition, you might need to modify the source code of the |sdk-cpp| and then rebuild it.

The following procedure shows you how to perform these tasks.

.. topic:: To enforce TLS 1.2 with libcurl

   #. Verify that your installation of libcurl is at least version 7.34.0.

   #. Download the source code for the |sdk-cpp| from `GitHub <http://github.com/aws/aws-sdk-cpp>`_.

   #. Open ``aws-cpp-sdk-core/source/http/curl/CurlHttpClient.cpp`` and find the following lines of code.
      ::

         #if LIBCURL_VERSION_MAJOR >= 7
         #if LIBCURL_VERSION_MINOR >= 34
         curl_easy_setopt(connectionHandle, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
         #endif //LIBCURL_VERSION_MINOR
         #endif //LIBCURL_VERSION_MAJOR

   #. If necessary, change the last parameter in the function call as follows.
      ::

         #if LIBCURL_VERSION_MAJOR >= 7
         #if LIBCURL_VERSION_MINOR >= 34
         curl_easy_setopt(connectionHandle, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
         #endif //LIBCURL_VERSION_MINOR
         #endif //LIBCURL_VERSION_MAJOR

   #. If you performed the preceding code changes, build and install the |sdk-cpp| according to the instructions at `<https://github.com/aws/aws-sdk-cpp#building-the-sdk>`_.

   #. For the service client in your application, enable ``verifySSL`` in its client configuration if this option isn't already enabled.

Enforce TLS 1.2 on Windows
==========================

The following procedures show you how to enforce TLS 1.2 with WinHttp, WinINet, or IXMLHTTPRequest2.

Prerequisite: Enable TLS 1.1 and 1.2 on Windows
-----------------------------------------------

   #. Determine whether your Windows version supports TLS 1.1 and TLS 1.2 natively, as described at `<https://docs.microsoft.com/en-us/windows/win32/secauthn/protocols-in-tls-ssl--schannel-ssp->`_.

   #. Determine whether your Windows version needs to be patched to enable TLS 1.1 and TLS 1.2 as the default, as described at `<https://support.microsoft.com/en-us/help/3140245/update-to-enable-tls-1-1-and-tls-1-2-as-default-secure-protocols-in-wi>`_.

   #. Proceed to one of the next procedures, as appropriate.

To enforce TLS 1.2 with WinHttp
-------------------------------

WinHttp provides an API to explicitly set the acceptable secure protocols.
However, to make this configurable at run-time, you need to modify the source code of the |sdk-cpp| and then rebuild it.

   #. Download the source code for the |sdk-cpp| from `GitHub <http://github.com/aws/aws-sdk-cpp>`_.

   #. Open ``aws-cpp-sdk-core/source/http/windows/WinHttpSyncHttpClient.cpp`` and find the following lines of code.
      ::

         //disable insecure tls protocols, otherwise you might as well turn ssl verification off.
         DWORD flags = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1 | WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_1 | WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2;
         if (!WinHttpSetOption(GetOpenHandle(), WINHTTP_OPTION_SECURE_PROTOCOLS, &flags, sizeof(flags)))
         {
             AWS_LOGSTREAM_FATAL(GetLogTag(), "Failed setting secure crypto protocols with error code: " << GetLastError());
         }

   #. If necessary, change the value of the ``flags`` variable as follows.
      ::

         //disable insecure tls protocols, otherwise you might as well turn ssl verification off.
         DWORD flags = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2;
         if (!WinHttpSetOption(GetOpenHandle(), WINHTTP_OPTION_SECURE_PROTOCOLS, &flags, sizeof(flags)))
         {
             AWS_LOGSTREAM_FATAL(GetLogTag(), "Failed setting secure crypto protocols with error code: " << GetLastError());
         }

   #. If you performed the preceding code changes, build and install the |sdk-cpp| according to the instructions at `<https://github.com/aws/aws-sdk-cpp#building-the-sdk>`_.

   #. For the service client in your application, enable ``verifySSL`` in its client configuration if this option isn't already enabled.

To enforce TLS 1.2 with WinINet and IXMLHTTPRequest2
----------------------------------------------------

For these two libraries there's no API to specify the secure protocol, so the |sdk-cpp| uses the default for the operating system.
You can update the Windows registry to enforce the use of TLS 1.2, as shown in the following procedure.
Be advised, however, that the result is a global change that impacts all applications that depend on Schannel.

   #. Open Registry Editor and go to ``Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SecurityProviders\SCHANNEL\Protocols``.

   #. If they don't already exist, create the following subkeys: ``TLS 1.0,``, ``TLS 1.1``, and ``TLS 1.2``.

   #. Under each of the subkeys mentioned previously, create a ``Client`` and a ``Server`` subkey.

   #. Create the following keys and values.

      .. table::

         +------------------------------------+----------+-------+
         | Key name                           | Key type | Value |
         +====================================+==========+=======+
         | TLS 1.0\\Client\\DisabledByDefault | DWORD    | 0     |
         +------------------------------------+----------+-------+
         | TLS 1.1\\Client\\DisabledByDefault | DWORD    | 0     |
         +------------------------------------+----------+-------+
         | TLS 1.2\\Client\\DisabledByDefault | DWORD    | 0     |
         +------------------------------------+----------+-------+
         | TLS 1.0\\Client\\Enabled           | DWORD    | 0     |
         +------------------------------------+----------+-------+
         | TLS 1.1\\Client\\Enabled           | DWORD    | 0     |
         +------------------------------------+----------+-------+
         | TLS 1.2\\Client\\Enabled           | DWORD    | 1     |
         +------------------------------------+----------+-------+

      Notice that ``TLS 1.2\Client\Enabled`` is the only key that's set to 1.
      Setting this key to 1 enforces TLS 1.2 as the only acceptable secure protocol.
