# Current version #
  * Compile an OpenCL Program
    * Finish to add C99 extensions (local, ...)
    * Add attribute qualifiers (binded to empty string for compilation)
    * Non-kernel functions can be called inside kernel
    * Struct and typedef
    * Check if "global" variables inside opencl program are valid
    * OpenCL Preprocessor directives
    * Buitin types (scalar types like float4)
    * Conversions and type casting
    * Image access qualifiers (read\_only, write\_only)
    * Mock all the builtin functions
      * Work-item functions
      * Math functions
      * Integer functions
      * Common functions
      * Geometric functions
      * Relational Functions
      * Vector data load and store functions
      * Image read and write functions
      * Synchronizations functions
      * Explicit memory fence functions
      * Async copies from Global to Local Memory, Local to Global Memoryn abd Prefetch
  * Better error handling
  * User can use its STL containers with openclam algorithms
    * ~~openclam::for\_each~~
    * openclam::reduce
    * kernels are unary or binary functions?
  * Add profiling support
  * Add objects queries support (program, context, kernel, ...)
  * Expose kernel build log
  * Let the user to write its own Kernel without KERNEL macro (constructed with a const std::string& or binary)
  * Packaging
    * Release version 1.0
    * Add documentation (examples, API)
    * Tests on different platforms (ATI vs NVIDIA) + different drivers
    * Add a default context inside global scope and a default kernel construction?

# Future versions #
  * Use TBB as alternative CPU implementation (if neither CPU nor GPU devices or plateforms are present)
    * implement all the built-in functions (with boost::math?)
  * Use STL algorithms if TBB is disabled
  * Add Image type support
  * Add optional extensions support (atomic functions, ...)
  * Add better/simplified devices choice (best device, all devices, ...)
  * Choose automatically best work group size
  * User can specify its build options
  * Save kernel binaries to speed up initialization time (proxy)
  * Add CUDA\_KERNEL to ease CUDA -> OpenCL transition
  * Expose openclam buffer and matrix operators
  * Add multi-gpu support