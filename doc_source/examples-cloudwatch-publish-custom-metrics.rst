.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

.. highlight:: cpp

#############################
Publishing Custom Metric Data
#############################

.. meta::
   :description: How to publish custom metric data to Amazon Cloudwatch using the AWS SDK for C++.
   :keywords: cloudwatch


A number of AWS services publish :cw-ug:`their own metrics <aws-namespaces>` in namespaces beginning
with "AWS/" You can also publish custom metric data using your own namespace (as long as it doesn't
begin with "AWS/").

.. include:: includes/examples-note.txt

Publish Custom Metric Data
==========================

To publish your own metric data, call the |cwclient|'s :functionname:`PutMetricData` function with a
:aws-cpp-class:`PutMetricDataRequest <aws_1_1_cloud_watch_1_1_model_1_1_put_metric_data_request>`.
The :classname:`PutMetricDataRequest` must include the custom namespace to use for the data, and
information about the data point itself in a :aws-cpp-class:`MetricDatum
<aws_1_1_cloud_watch_1_1_model_1_1_metric_datum>` object.

.. note:: You cannot specify a namespace that begins with "AWS/". Namespaces that begin with
   "AWS/" are reserved for use by Amazon Web Services products.

**Includes**

.. literalinclude:: example_code/cloudwatch/put_metric_data.cpp
   :start-after: start:[cw.cpp.put_metric_data.inc]
   :end-before: end:[cw.cpp.put_metric_data.inc]

**Code**

.. literalinclude:: example_code/cloudwatch/put_metric_data.cpp
   :start-after: start:[cw.cpp.put_metric_data.code]
   :end-before: end:[cw.cpp.put_metric_data.code]
   :dedent: 8

See the :sdk-examples-cpp:`complete example <cloudwatch/put_metric_data.cpp>`.

More Information
================

* :cw-ug:`Using Amazon CloudWatch Metrics <working_with_metrics>` in the |cw-ug|.
* :cw-ug:`AWS Namespaces <aws-namespaces>` in the |cw-ug|.
* :cw-api:`PutMetricData` in the |cw-api|.

