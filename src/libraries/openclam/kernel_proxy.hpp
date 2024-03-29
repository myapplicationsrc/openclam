//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_KERNEL_PROXY_HPP_INCLUDED
#define OPENCLAM_KERNEL_PROXY_HPP_INCLUDED

#include "ikernel_proxy.hpp"
#include "iopencl.hpp"

namespace openclam
{

class kernel_proxy : public openclam::ikernel_proxy
{
public:
    kernel_proxy( const std::string& name, const openclam::iopencl& wrapper, cl_program program )
       : wrapper_( wrapper )
       , program_( program )
    {
        ERROR_HANDLER( kernel_ = wrapper_.clCreateKernel( program_, name.c_str(), &ERROR ) );
    }
    virtual ~kernel_proxy()
    {
        wrapper_.clReleaseKernel( kernel_ ); // $$$$ 28-02-2010 SILVIN: check error code?
        wrapper_.clReleaseProgram( program_ ); // $$$$ 28-02-2010 SILVIN: check error code?
    }

    virtual void execute( void* data, size_t size, cl_context context, cl_command_queue queue ) const
    {
        cl_mem arg;
        ERROR_HANDLER( arg = wrapper_.clCreateBuffer( context, CL_MEM_READ_WRITE, size, NULL, &ERROR ) );
        ERROR_HANDLER( ERROR = wrapper_.clSetKernelArg( kernel_, 0, sizeof( cl_mem ), &arg ) );
        ERROR_HANDLER( ERROR = wrapper_.clEnqueueWriteBuffer( queue, arg, CL_TRUE, 0, size, data, 0, NULL, NULL ) );
        ERROR_HANDLER( ERROR = wrapper_.clEnqueueNDRangeKernel( queue, kernel_, 1, NULL, &size, NULL, 0, NULL, NULL ) );
        ERROR_HANDLER( ERROR = wrapper_.clEnqueueReadBuffer( queue, arg, CL_TRUE, 0, size, data, 0, NULL, NULL ) );
        ERROR_HANDLER( ERROR = wrapper_.clReleaseMemObject( arg ) );
    }

private:
    const openclam::iopencl& wrapper_;
    cl_program program_;
    cl_kernel kernel_;
};
}

#endif // #ifndef OPENCLAM_CONTEXT_HPP_INCLUDED
