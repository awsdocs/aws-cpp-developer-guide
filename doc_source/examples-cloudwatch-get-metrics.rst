.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

.. highlight:: cpp

#########################
Getting Metrics from |CW|
#########################

.. meta::
   :description: How to list metrics from Amazon CloudWatch using the AWS SDK for C++.
   :keywords: cloudwatch

.. include:: includes/examples-note.txt

Listing Metrics
===============

To list |cw| metrics, create a :aws-cpp-class:`ListMetricsRequest
<aws_1_1_cloud_watch_1_1_model_1_1_list_metrics_request>` and call the |cwclient|'s
:functionname:`ListMetrics` function. You can use the :classname:`ListMetricsRequest` to filter the
returned metrics by namespace, metric name, or dimensions.

.. note:: A list of metrics and dimensions that are posted by AWS services can be found within the
   :cw-ug:`Amazon CloudWatch Metrics and Dimensions Reference <CW_Support_For_AWS>` in the |cw-ug|.

**Includes**

.. literalinclude:: cw.cpp.list_metrics.inc.txt

**Code**

.. literalinclude:: cw.cpp.list_metrics.code.txt
   :dedent: 8

The metrics are returned in a :aws-cpp-class:`ListMetricsResult
<aws_1_1_cloud_watch_1_1_model_1_1_list_metrics_result>` by calling its :functionname:`GetMetrics`
function. The results may be *paged*. To retrieve the next batch of results, call
:functionname:`SetNextToken` on the original request object with the return value of the
:classname:`ListMetricsResult` object's :functionname:`GetNextToken` function, and pass the modified
request object back to another call to :functionname:`ListMetrics`.

See the :sdk-examples-cpp:`complete example <cloudwatch/list_metrics.cpp>`.

More Information
================

* :cw-api:`ListMetrics` in the |cw-api|.

