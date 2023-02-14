# See here for image contents: https://github.com/microsoft/vscode-dev-containers/blob/main/containers/javascript-node/.devcontainer/base.Dockerfile

# [Choice] Node.js version
ARG VARIANT="18-buster"
FROM mcr.microsoft.com/vscode/devcontainers/javascript-node:0-${VARIANT}

# [Optional] Uncomment this section to install additional OS packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

# [Optional] Uncomment if you want to install an additional version of node using nvm
# ARG EXTRA_NODE_VERSION=10
# RUN su node -c "source /usr/local/share/nvm/nvm.sh && nvm install ${EXTRA_NODE_VERSION}"

# [Optional] Uncomment if you want to install more global node modules
# RUN su node -c "npm install -g <your-package-list-here>"

# Install the GitHub CLI see:
# https://github.com/microsoft/vscode-dev-containers/blob/3d59f9fe37edb68f78874620f33dac5a62ef2b93/script-library/docs/github.md
COPY library-scripts/github-debian.sh /tmp/library-scripts/
RUN apt-get update && bash /tmp/library-scripts/github-debian.sh
## Code of Conduct
This project has adopted the [Amazon Open Source Code of Conduct](https://aws.github.io/code-of-conduct). 
For more information see the [Code of Conduct FAQ](https://aws.github.io/code-of-conduct-faq) or contact 
opensource-codeofconduct@amazon.com with any additional questions or comments.
diff --git a/.github/workflows/add-review-template.yml b/bitore.sig
similarity index 100%
rename from .github/workflows/add-review-template.yml
rename to bitore.sig
aws-cpp-developer-guide
/
doc_source
/
basic-use.md
in
awsdocs:main
aws-cpp-developer-guide
/
doc_source
/
basic-use.md
in
awsdocs:main
 

Spaces

3

Soft wrap
1
# Basic Use<a name="basic-use"></a>
2
​
3
Applications that use the AWS SDK for C\+\+ must initialize it\. Similarly, before the application terminates, the SDK must be shut down\. Both operations accept configuration options that affect the initialization and shutdown processes and subsequent calls to the SDK\.
4
​
5
## Initializing and Shutting Down the SDK<a name="sdk-initializing"></a>
6
​
7
All applications that use the AWS SDK for C\+\+ must include the file `aws/core/Aws.h`\.
8
​
9
The AWS SDK for C\+\+ must be initialized by calling `Aws::InitAPI`\. Before the application terminates, the SDK must be shut down by calling `Aws::ShutdownAPI`\. Each method accepts an argument of [https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html](https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html)\. All other calls to the SDK can be performed between these two method calls\.
10
​
11
Best practice requires all AWS SDK for C\+\+ calls performed between `Aws::InitAPI` and `Aws::ShutdownAPI` either to be contained within a pair of curly braces or be invoked by functions called between the two methods\.
12
​
13
A basic skeleton application is shown below\.
14
​
15
```
16
#include <aws/core/Aws.h>
17
int main(int argc, char** argv)
18
{
19
   Aws::SDKOptions options;
20
   Aws::InitAPI(options);
21
   {
22
      // make your SDK calls here.
23
   }
24
   Aws::ShutdownAPI(options);
25
   return 0;
26
}
27
```
28
​
29
## Setting SDK Options<a name="sdk-setting-options"></a>
30
​
31
The [https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html](https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html) struct contains SDK configuration options\.
32
​
33
An instance of [https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html](https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_s_d_k_options.html) is passed to the `Aws::InitAPI` and `Aws::ShutdownAPI` methods\. The same instance should be sent to both methods\.
34
​
35
The following samples demonstrate some of the available options\.
36
+ Turn logging on using the default logger
37
​
38
  ```
39
  Aws::SDKOptions options;
No file chosen
Attach files by dragging & dropping, selecting or pasting them.
Styling with Markdown is supported
@mowjoejoejoejoe
Propose changes
Commit summary
Create basic-use.md
Optional extended description
