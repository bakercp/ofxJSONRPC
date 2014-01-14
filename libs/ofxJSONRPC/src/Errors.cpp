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
            return "none";
        case Errors::RPC_ERROR_INVALID_REQUEST:
            return "invalid request";
        case Errors::RPC_ERROR_METHOD_NOT_FOUND:
            return "method not found";
        case Errors::RPC_ERROR_INVALID_PARAMETERS:
            return "invalid parameters";
        case Errors::RPC_ERROR_INTERNAL_ERROR:
            return "internal error";
        case Errors::RPC_ERROR_PARSE:
            return "parse error";
        default:
        {
            if (code >= -32099 && code <= -32000)
            {
                return "undefined server error";
            }
            else
            {
                return "unknown error";
            }
        }
    }
}


POCO_IMPLEMENT_EXCEPTION(JSONRPCException,          Poco::Exception,  "Unknown Exception");
POCO_IMPLEMENT_EXCEPTION(ParseException,            JSONRPCException, "Parse Exception");
POCO_IMPLEMENT_EXCEPTION(InvalidRequestException,   JSONRPCException, "Invalid Request Exception");
POCO_IMPLEMENT_EXCEPTION(MethodNotFoundException,   JSONRPCException, "Method Not Found Exception");
POCO_IMPLEMENT_EXCEPTION(InvalidParameterException, JSONRPCException, "Invalid Parameter Exception");
POCO_IMPLEMENT_EXCEPTION(InternalErrorException,    JSONRPCException, "Internal Error Exception");


} } // namespace ofx::JSONRPC
