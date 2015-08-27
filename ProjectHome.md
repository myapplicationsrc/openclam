Provides a C++ wrapper around C low level OpenCL API.

KERNEL macro helps the user to check its OpenCL code at compile time by mocking builin functions (like get\_global\_id).
OpenCL code does not have to be anymore inside quotes. Moreover, user can iterate over standard containers (like std::vector or std::list) with openclam algortihms like (openclam::for\_each).

Example:
```
#include <openclam/cl.hpp>
#include <vector>
#include <boost/assign.hpp>

openclam::opencl wrapper;
openclam::context context( wrapper );
KERNEL( Add, context, float
        __kernel void Add( __global const float* a )
        {
            a[ get_global_id( 0 ) ] += 42;
        }; );
std::vector< float > data = boost::assign::list_of( 1 ).repeat( 9, 1 );
openclam::for_each( data.begin(), data.end(), Add );
```
This code compiles under any standard C++ compiler.

/!\ KERNEL macro does not realy build your code like nvcc with CUDA, it still builds it at runtime.