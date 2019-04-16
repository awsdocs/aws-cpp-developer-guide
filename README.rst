.. Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

########################
aws-cpp-developer-guide
########################

This repository contains the source text files for the *AWS SDK for C++ Developer Guide*.

The guide content is written in reStructuredText_ and built using Sphinx_. It relies upon content
provided in the AWS documentation team's `shared content`_ repository.


Reporting issues
================

To report a problem in the guide, use the Issues_ section of the repository.

When submitting an issue, please indicate:

* The URL or source filename where the issue occurs.

* A description of the issue. Use as much detail as necessary.


Contributing fixes and updates
==============================

To contribute documentation fixes or updates, use the Github-standard procedures for
`forking the repository`_ and submitting a `pull request`_.

Many common substitutions_ and extlinks_ found in this guide are sourced from the `shared
content`_ repository. If you see a text substitution that is not declared at the top of the source
file or in the ``_includes.txt`` file, then it is probably defined in the shared content.


Building the documentation
--------------------------

When contributing to the guide, build your changes and review them before submitting a pull request.

**To build the docs:**

1. Install the Python Sphinx_ package.
2. In the repository's root directory, run the Python ``build_docs.py`` script.

``build_docs.py`` accepts arguments of any of the `available Sphinx builders`_. For example, to
build the guide in a single HTML page, use the ``singlehtml`` target::

 python build_docs.py singlehtml

The build process automatically downloads a snapshot of the `shared content`_ repository, 
combines it in the ``build`` directory, and generates output in the ``output`` directory.


Code examples in the documentation
----------------------------------

The code examples featured in the guide are located in a separate repository:
`aws-doc-sdk-examples <https://github.com/awsdocs/aws-doc-sdk-examples/tree/master/cpp>`_. Full
code and build files are included, so you can build and run any example yourself.

In addition to examples in C++, the repository includes examples in the other programming 
languages supported by the AWS SDKs. If you discover an issue with any example, submit an 
issue or fork the repository and submit a pull request.

The code examples are provided under the *Apache 2.0* open source license. See the example
repository's `README <https://github.com/awsdocs/aws-doc-sdk-examples/blob/master/README.rst>`_ for
details.


Copyright and license
=====================

Unless otherwise stated, all content in this repository is Copyright © 2010-2019, Amazon Web
Services, Inc. or its affiliates. All rights reserved.

Except where otherwise noted, this work is licensed under a `Creative Commons
Attribution-NonCommercial-ShareAlike 4.0 International License
<http://creativecommons.org/licenses/by-nc-sa/4.0/>`_ (the "License"). Use the preceding link for a
human-readable summary of the license terms. The full license text is available at:
http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode and in the LICENSE file accompanying this
repository.

.. =================================================================================
.. Links used in the README. For sanity's sake, keep this list sorted alphabetically
.. =================================================================================

.. _`available sphinx builders`: http://www.sphinx-doc.org/en/stable/builders.html
.. _`forking the repository`: https://help.github.com/articles/fork-a-repo/
.. _`pull request`: https://help.github.com/articles/using-pull-requests/
.. _`shared content`: https://github.com/awsdocs/aws-doc-shared-content
.. _extlinks: http://www.sphinx-doc.org/en/stable/ext/extlinks.html
.. _issues: https://github.com/awsdocs/aws-cpp-developer-guide/issues
.. _restructuredtext: http://docutils.sourceforge.net/rst.html
.. _sphinx: http://www.sphinx-doc.org/en/stable/
.. _substitutions: http://www.sphinx-doc.org/en/stable/rest.html#substitutions

