//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_CONTEXT_HPP_INCLUDED
#define OPENCLAM_CONTEXT_HPP_INCLUDED

#include "error.hpp"
#include "program.hpp"
#include <memory>
#include <string>
#include <boost/noncopyable.hpp>

namespace openclam
{

class context : private boost::noncopyable
{
public:
    enum device_type
    {
        default     = CL_DEVICE_TYPE_DEFAULT,
        cpu         = CL_DEVICE_TYPE_CPU,
        gpu         = CL_DEVICE_TYPE_GPU,
        accelerator = CL_DEVICE_TYPE_ACCELERATOR,
        all         = CL_DEVICE_TYPE_ALL
    };

    explicit context( device_type type = default )
    {
        ERROR_HANDLER( context_ = clCreateContextFromType( 0, type, NULL, NULL, &ERROR ) );
        unsigned int size;
        ERROR_HANDLER( ERROR = clGetContextInfo( context_, CL_CONTEXT_DEVICES, 0, NULL, &size ) );
        ERROR_HANDLER( ERROR = size > 0 ? CL_SUCCESS : CL_DEVICE_NOT_AVAILABLE );
        devices_.reset( new cl_device_id[ size ] );
        ERROR_HANDLER( ERROR = clGetContextInfo( context_, CL_CONTEXT_DEVICES, size, devices_.get(), NULL ) );
    }
    virtual ~context()
    {
        clReleaseContext( context_ ); // $$$$ 28-02-2010 SILVIN: check error code?
    }

    std::auto_ptr< openclam::program > create( const std::string& sources ) const
    {
        const unsigned int size = sources.size();
        const char* buffer = sources.c_str();
        cl_program result;
        ERROR_HANDLER( result = clCreateProgramWithSource( context_, 1, &buffer, &size, &ERROR ) );
        return std::auto_ptr< openclam::program >( new openclam::program( result ) );
    }
private:
    cl_context context_;
    std::auto_ptr< cl_device_id > devices_;
};

}

#endif // #ifndef OPENCLAM_CONTEXT_HPP_INCLUDED