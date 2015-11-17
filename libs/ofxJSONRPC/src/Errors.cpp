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


#include "ofx/JSONRPC/Errors.h"
#include <typeinfo>


namespace ofx {
namespace JSONRPC {


const int Errors::RPC_ERROR_NONE                = 0;
const int Errors::RPC_ERROR_INVALID_REQUEST     = -32600;
const int Errors::RPC_ERROR_METHOD_NOT_FOUND    = -32601;
const int Errors::RPC_ERROR_INVALID_PARAMETERS  = -32602;
const int Errors::RPC_ERROR_INTERNAL_ERROR      = -32603;
const int Errors::RPC_ERROR_PARSE               = -32700;


std::string Errors::getErrorMessage(int code)
{
    switch (code)
    {
        case Errors::RPC_ERROR_NONE:
            return "RPC_ERROR_NONE";
        case Errors::RPC_ERROR_INVALID_REQUEST:
            return "RPC_ERROR_INVALID_REQUEST";
        case Errors::RPC_ERROR_METHOD_NOT_FOUND:
            return "RPC_ERROR_METHOD_NOT_FOUND";
        case Errors::RPC_ERROR_INVALID_PARAMETERS:
            return "RPC_ERROR_INVALID_PARAMETERS";
        case Errors::RPC_ERROR_INTERNAL_ERROR:
            return "RPC_ERROR_INTERNAL_ERROR";
        case Errors::RPC_ERROR_PARSE:
            return "RPC_ERROR_PARSE";
        default:
        {
            if (code >= -32099 && code <= -32000)
            {
                return "undefined server error";
            }
            else
            {
                return "Unknown Error";
            }
        }
    }
}


POCO_IMPLEMENT_EXCEPTION(JSONRPCException,
                         Poco::Exception,
                         "RPC_ERROR_INTERNAL_ERROR")


POCO_IMPLEMENT_EXCEPTION(InvalidRequestException,
                         JSONRPCException,
                         "RPC_ERROR_INVALID_REQUEST")

POCO_IMPLEMENT_EXCEPTION(MethodNotFoundException,
                         JSONRPCException,
                         "RPC_ERROR_METHOD_NOT_FOUND")

POCO_IMPLEMENT_EXCEPTION(InvalidParametersException,
                         JSONRPCException,
                         "RPC_ERROR_INVALID_PARAMETERS")

POCO_IMPLEMENT_EXCEPTION(InternalErrorException,
                         JSONRPCException,
                         "RPC_ERROR_INTERNAL_ERROR")

POCO_IMPLEMENT_EXCEPTION(ParseException,
                         JSONRPCException,
                         "RPC_ERROR_PARSE")


} } // namespace ofx::JSONRPC
