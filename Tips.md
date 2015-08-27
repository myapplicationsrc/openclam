From [ATI OpenCL Programming Guide](http://developer.amd.com/gpu_assets/ATI_Stream_SDK_OpenCL_Programming_Guide.pdf):

# Estimating Bandwidth #

(Page 61: 4.3.3)
Effective Bandwidth = (Br + Bw)/T where:
  1. Br = total number of bytes read from global memory.
  1. Bw = total number of bytes written to global memory.
  1. T = time required to run kernel, specified in nanoseconds.
# General Tips #

(Page 65: 4.6.3)

Avoid declaring global arrays on the kernel’s stack frame as these typically cannot be allocated in registers and require expensive global memory operations.

## Predication ##

Use predication rather than control-flow. The predication allows the GPU to execute both paths of execution in parallel, which can be faster than attempting to minimize the work through clever control-flow. A simple example:
```
If (A>B) {
C += D;
} else {
C -= D;
}
```
Replace this with:
```
int factor = (A>B) ? 1:-1;
C += factor*D;
```

The comparison operator (? or the select built-in), when used with scalar operators, produces a scalar 1 if the comparison is true, and a scalar 0 if false. The vector comparison operator has different behavior: each element in a vector comparison is -1 if true, 0 if false. Note this subtle difference when vectorizing code.

## Loop Unrolling ##
OpenCL kernels typically are high instruction-per-clock applications. Thus, the overhead to evaluate control-flow and execute branch instructions can consume a significant part of resource that otherwise can be used for high-throughput compute operations.

The ATI Stream OpenCL compiler performs simple loop unrolling optimizations; however, for more complex loop unrolling, it may be beneficial to do this manually.

If possible, create a reduced-size version of your data set for easier debugging and faster turn-around on performance experimentation. GPUs do not have automatic caching mechanisms and typically scale well as resources are added. In many cases, performance optimization for the reduced-size data implementation also benefits the full-size algorithm.

When tuning an algorithm, it is often beneficial to code a simple but accurate algorithm that is retained and used for functional comparison. GPU tuning can be an iterative process, so success requires frequent experimentation, verification, and performance measurement.

The profiler and analysis tools report statistics on a per-kernel granularity. To narrow the problem further, it might be useful to remove or comment-out sections of code, then re-run the timing and profiling tool.

# Guidance for CPU Programmers Using OpenCL #

(Page 66: 4.6.5)

OpenCL is the industry-standard toolchain for programming GPUs and parallel devices from many vendors. It is expected that many programmers skilled in CPU programming will program GPUs for the first time using OpenCL. This section provides some guidance for experienced programmers who are programming a GPU for the first time. It specifically highlights the key differences in optimization strategy.

Study the local memory (LDS) optimizations. These greatly affect the GPU performance. Note the difference in the organization of local memory on the GPU as compared to the CPU cache. Local memory is shared by many work-items (64 on Cypress). This contrasts with a CPU cache that normally is dedicated to a single work-item. As mentioned in sections 4.4 and 4.5, GPU kernels run well when they collaboratively load the shared memory.

GPUs have a large amount of raw compute horsepower, compared to memory bandwidth and to “control flow” bandwidth. This leads to some high- level differences in GPU programming strategy.
  * A CPU-optimized algorithm may test branching conditions to minimize the workload. On a GPU, it is frequently faster simply to execute the workload.
  * A CPU-optimized version can use memory to store and later load pre- computed values. On a GPU, it frequently is faster to recompute values rather than saving them in registers. Per-thread registers are a scarce resource on the GPU; in contrast, CPUs have many available per-thread register resources.

Use float4 and the OpenCL built-ins for vector types (vload, vstore, etc.). These enable ATI Stream’s OpenCL implementation to generate efficient, packed SSE instructions when running on the CPU. Vectorization is an optimization that benefits both the AMD CPU and GPU.