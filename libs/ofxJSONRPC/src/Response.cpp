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


#include "ofx/JSONRPC/Response.h"
#include "ofx/JSONRPC/JSONRPCUtils.h"


namespace ofx {
namespace JSONRPC {


const std::string Response::ERROR_TAG = "error";
const std::string Response::RESULT_TAG = "result";


Response::Response(HTTP::ServerEventArgs& evt):
    BaseMessage(evt, ofJson(nullptr)),
    _result(ofJson(nullptr)),
    _error(Error(Errors::RPC_ERROR_INTERNAL_ERROR))
{
}


Response::Response(HTTP::ServerEventArgs& evt,
                   const ofJson& id,
                   const ofJson& result):
    BaseMessage(evt, id),
    _result(result),
    _error(Error())
{
}


Response::Response(HTTP::ServerEventArgs& evt,
                   const ofJson& id,
                   const Error& error):
    BaseMessage(evt, id),
    _result(ofJson()),
    _error(error)
{
}


Response::~Response()
{
}


const ofJson& Response::result() const
{
    return _result;
}


const ofJson& Response::getResult() const
{
    return result();
}

const Error& Response::error() const
{
    return _error;
}


const Error& Response::getError() const
{
    return error();
}


bool Response::isErrorResponse() const
{
    return Errors::RPC_ERROR_NONE != error().code();
}


std::string Response::toString(bool styled) const
{
    return JSONRPCUtils::toString(toJSON(*this), styled);
}


ofJson Response::toJSON(const Response& response)
{
    ofJson result;

    result[PROTOCOL_VERSION_TAG] = PROTOCOL_VERSION;

    result["id"] = response.id();

    if (response.isErrorResponse())
    {
        result["error"] = Error::toJSON(response.error());
    }
    else
    {
        result["result"] = response.result();
    }

    return result;
}


Response Response::fromJSON(HTTP::ServerEventArgs& evt, const ofJson& json)
{
    if (JSONRPCUtils::hasStringKey(json, PROTOCOL_VERSION_TAG) &&
        json[PROTOCOL_VERSION_TAG].get<std::string>() == PROTOCOL_VERSION)
    {
        if (JSONRPCUtils::hasKey(json, ID_TAG))
        {
            ofJson id = json[ID_TAG];

            if (JSONRPCUtils::hasKey(json, RESULT_TAG))
            {
                ofJson result = json[RESULT_TAG];
                return Response(evt, id, result);
            }
            else if(JSONRPCUtils::hasKey(json, ERROR_TAG))
            {
                ofJson error = json[ERROR_TAG];
                return Response(evt, id, Error::fromJSON(error));
            }
            else
            {
                throw ParseException("No result OR error.");
            }
        }
        else
        {
            throw ParseException("No ID.");
        }
    }
    else
    {
        throw ParseException("No version string.");
    }
}


} } // namespace ofx::JSONRPC
