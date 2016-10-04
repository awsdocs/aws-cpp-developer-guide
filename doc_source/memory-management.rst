.. Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0
   International License (the "License"). You may not use this file except in compliance with the
   License. A copy of the License is located at http://creativecommons.org/licenses/by-nc-sa/4.0/.

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
   either express or implied. See the License for the specific language governing permissions and
   limitations under the License.

#################
Memory Management
#################

The AWS SDK for C++ provides a way to control memory allocation and deallocation in a library.

.. note:: Custom memory management is available only if you use a version of the library built using
   the defined compile-time constant ``AWS_CUSTOM_MEMORY_MANAGEMENT``.

   If you use a version of the library that is built without the compile-time constant, global
   memory system functions such as ``InitializeAWSMemorySystem`` won't work; the global ``new`` and
   ``delete`` functions are used instead.

For more information about the compile-time constant, see `STL and AWS Strings and Vectors`_.

.. contents::
    :local:

Allocating and Deallocating Memory
==================================

**To allocate or deallocate memory**

#. Subclass ``MemorySystemInterface``: ``aws/core/utils/memory/MemorySystemInterface.h``.

   .. code-block:: cpp

       class MyMemoryManager : public Aws::Utils::Memory::MemorySystemInterface
       {
       public:
           // ...
           virtual void* AllocateMemory(
               std::size_t blockSize, std::size_t alignment,
               const char *allocationTag = nullptr) override;
           virtual void FreeMemory(void* memoryPtr) override;
       };

   .. note:: You can change the type signature for ``AllocateMemory`` as needed.

#. Install a memory manager with an instance of your subclass by calling
   ``InitializeAWSMemorySystem``. This should occur at the beginning of your application. For
   example, in your ``main()`` function:

   .. code-block:: cpp

       int main(void)
       {
         MyMemoryManager sdkMemoryManager;
         Aws::Utils::Memory::InitializeAWSMemorySystem(sdkMemoryManager);
         // ... do stuff
         Aws::Utils::Memory::ShutdownAWSMemorySystem();
         return 0;
       }

#. Just before exit, call ``ShutdownAWSMemorySystem`` (as shown in the preceding example, but
   repeated here):

   .. code-block:: cpp

       Aws::Utils::Memory::ShutdownAWSMemorySystem();


STL and AWS Strings and Vectors
===============================

When initialized with a memory manager, the |sdk-cpp| defers all allocation and deallocation to the
memory manager. If a memory manager doesn't exist, the SDK uses global new and delete.

If you use custom STL allocators, you must alter the type signatures for all STL objects to match
the allocation policy. Because STL is used prominently in the SDK implementation and interface, a
single approach in the SDK would inhibit direct passing of default STL objects into the SDK or
control of STL allocation. Alternately, a hybrid approach |mdash| using custom allocators internally
and allowing standard and custom STL objects on the interface |mdash| could potentially make it more
difficult to investigate memory issues.

The solution is to use the memory system’s compile-time constant ``AWS_CUSTOM_MEMORY_MANAGEMENT`` to
control which STL types the SDK uses.

If the compile-time constant is enabled (on), the types resolve to STL types with a custom allocator
connected to the AWS memory system.

If the compile-time constant is disabled (off), all ``Aws::*`` types resolve to the corresponding
default ``std::*`` type.

**Example code from the ``AWSAllocator.h`` file in the SDK**

.. code-block:: cpp

    #ifdef AWS_CUSTOM_MEMORY_MANAGEMENT

    template< typename T >
    class AwsAllocator : public std::allocator< T >
    {
       ... definition of allocator that uses AWS memory system
    };

    #else

    template< typename T > using Allocator = std::allocator<T>;

    #endif

In the example code, the ``AwsAllocator`` can be a custom allocator or a default allocator,
depending on the compile-time constant.

**Example code from the ``AWSVector.h`` file in the SDK**

.. code-block:: cpp

    template<typename T> using Vector = std::vector<T, Aws::Allocator<T>>;

In the example code, we define the ``Aws::*`` types.

If the compile-time constant is enabled (on), the type maps to a vector using custom memory
allocation and the AWS memory system.

If the compile-time constant is disabled (off), the type maps to a regular ``std::vector`` with
default type parameters.

Type aliasing is used for all ``std::`` types in the SDK that perform memory allocation, such as
containers, string streams, and string buffers. The |sdk-cpp| uses these types.

Remaining Issues
================

You can control memory allocation in the SDK; however, STL types still dominate the public interface
through string parameters to the model object ``initialize`` and ``set`` methods. If you don't use
STL and use strings and containers instead, you have to create a lot of temporaries whenever you
want to make a service call.

To remove most of the temporaries and allocation when you make service calls using non-STL, we have
implemented the following:

* Every Init/Set function that takes a string has an overload that takes a ``const char*``.

* Every Init/Set function that takes a container (map/vector) has an add variant that takes a single
  entry.

* Every Init/Set function that takes binary data has an overload that takes a pointer to the data
  and a ``length`` value.

* (Optional) Every Init/Set function that takes a string has an overload that takes a non-zero
  terminated ``const char*`` and a ``length`` value.


Native SDK Developers and Memory Controls
=========================================

Follow these rules in the SDK code:

* Don't use ``new`` and ``delete``; use ``Aws::New<>`` and ``Aws::Delete<>`` instead.

* Don't use ``new[]`` and ``delete[]``; use ``Aws::NewArray<>`` and ``Aws::DeleteArray<>``.

* Don't use ``std::make_shared``; use ``Aws::MakeShared``.

* Use ``Aws::UniquePtr`` for unique pointers to a single object. Use the ``Aws::MakeUnique``
  function to create the unique pointer.

* Use ``Aws::UniqueArray`` for unique pointers to an array of objects. Use the
  ``Aws::MakeUniqueArray`` function to create the unique pointer.

* Don't directly use STL containers; use one of the ``Aws::`` typedefs or add a typedef for the
  container you want. For example:

  .. code-block:: cpp

      Aws::Map<Aws::String, Aws::String> m_kvPairs;

* Use ``shared_ptr`` for any external pointer passed into and managed by the SDK. You must
  initialize the shared pointer with a destruction policy that matches how the object was allocated.
  You can use a raw pointer if the SDK is not expected to clean up the pointer.

