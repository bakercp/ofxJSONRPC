// =============================================================================
//
// Copyright (c) 2014 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <string>
#include "ofx/HTTP/ServerEvents.h"
#include "ofx/JSONRPC/JSONRPCUtils.h"


namespace ofx {
namespace JSONRPC {


/// \brief A contain all arguments for an JSONRPC method call.
///
/// Arguments include the Request parameters and either Results or an Error to
/// be set if required.
///
/// If the Error object is set to an error code other than RPC_ERROR_NONE, the
/// Json::Value results will be ignored and the error will be returned to the
/// caller.
///
/// Usually, upon error, the user will throw one of the convenient
/// child classes of JSONRPCException, which will be caught and an error
/// response will be returned to the caller. But, in cases where data should
/// be returned with the error response, the user must manually set the
/// error message and return immediately.
class MethodArgs: public HTTP::ServerEventArgs
{
public:
    /// \brief Create a MethodArgs with the given parameters.
    /// \param params The JSON contents of the JSONRPC request params.
    ///        If there are no arguments provided, the params are null.
    MethodArgs(HTTP::ServerEventArgs&,
               const ofJson& params);

    /// \brief Destroy the MethodArgs.
    virtual ~MethodArgs();

    /// \brief The JSON contents of the JSONRPC request params.
    const ofJson params;

    /// \brief The result to be returned, if required.
    ofJson result;

    /// \brief The error to be returned, if required.
    ///
    /// If the Error object is set to an error code other than RPC_ERROR_NONE,
    /// the Json::Value results will be ignored and the error will be returned
    /// to the caller.
    ///
    /// This can be used as an alternative to throwing an exception in the
    /// remote method.
    Error error;

    /// \brief Get the MethodArgs as a string.
    /// \param styled true if the output string should be pretty-print.
    /// \returns a raw json string of this MethodArgs
    std::string toString(bool styled = false) const;

};


} } // namespace ofx::JSONRPC
