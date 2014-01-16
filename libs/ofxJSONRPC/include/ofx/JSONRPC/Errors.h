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
#include <json/json.h>
#include "Poco/Exception.h"


namespace ofx {
namespace JSONRPC {


class Errors
    /// \brief JSONRPC 2.0 errors and exceptions.
    /// \sa http://www.jsonrpc.org/specification
{
public:
    static std::string getErrorMessage(int code);
        ///< \brief Get the error message for the given error code.
        ///< \param code is the error code to search for.
        ///< \returns a string containing the error string.  If the error code
        ///<        is unknown, but in the range -32000 to -32099,
        ///<        "undefined server error" will be returned.  Otherwise,
        ///<        "unknown error" will be returned.

    static const int RPC_ERROR_NONE;                ///< \brief No Error
    static const int RPC_ERROR_PARSE;               ///< \brief Parse Error
    static const int RPC_ERROR_INVALID_REQUEST;     ///< \brief Invalid Request
    static const int RPC_ERROR_METHOD_NOT_FOUND;    ///< \brief Method Not Found
    static const int RPC_ERROR_INVALID_PARAMETERS;  ///< \brief Invalid Parameters
    static const int RPC_ERROR_INTERNAL_ERROR;      ///< \brief Internal Error

};


} } // namespace ofx::JSONRPC
