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


#include "ofx/JSONRPC/Request.h"
#include "ofx/JSONRPC/Utils.h"


namespace ofx {
namespace JSONRPC {


const std::string Request::METHOD_TAG = "method";
const std::string Request::PARAMS_TAG = "params";


Request::Request(const std::string& method):
    BaseMessage(Json::Value::null),
    _method(method),
    _parameters(Json::Value())
{
}


Request::Request(const std::string& method, const Json::Value& parameters):
    BaseMessage(Json::Value::null),
    _method(method),
    _parameters(parameters)
{
}


Request::Request(const Json::Value& id, const std::string& method):
    BaseMessage(id),
    _method(method),
    _parameters(Json::Value::null)
{
}


Request::Request(const Json::Value& id,
                 const std::string& method,
                 const Json::Value& parameters):
    BaseMessage(id),
    _method(method),
    _parameters(parameters)
{
}


Request::~Request()
{
}


std::string Request::getMethod() const
{
    return _method;
}


Json::Value Request::getParameters() const
{
    return _parameters;
}


std::string Request::toString(bool styled) const
{
    return Utils::toString(toJSON(*this), styled);
}


Json::Value Request::toJSON(const Request& request)
{
    Json::Value result;

    result[PROTOCOL_VERSION_TAG] = PROTOCOL_VERSION;

    result[ID_TAG] = request.getID();
    result[METHOD_TAG] = request.getMethod();

    if (!request.getParameters().isNull())
    {
        result[PARAMS_TAG] = request.getParameters();
    }
    
    return result;
}


Request Request::fromJSON(const Json::Value& json)
{
    if (json.isMember(PROTOCOL_VERSION_TAG) &&
        json[PROTOCOL_VERSION_TAG].isString() && // require string
        json[PROTOCOL_VERSION_TAG].asString() == PROTOCOL_VERSION)
    {
        if (json.isMember(METHOD_TAG) &&
            json[METHOD_TAG].isString()) // require method as string
        {
            if (json.isMember(ID_TAG))
            {
                if (json.isMember(PARAMS_TAG))
                {
                    return Request(json[ID_TAG],
                                   json[METHOD_TAG].asString(), // checked above
                                   json[PARAMS_TAG]);

                }
                else
                {
                    return Request(json[ID_TAG],
                                   json[METHOD_TAG].asString()); // checked above
                }
            }
            else
            {
                if (json.isMember(PARAMS_TAG))
                {
                    return Request(json[METHOD_TAG].asString(), // checked above
                                   json[PARAMS_TAG]);

                }
                else
                {
                    return Request(json[METHOD_TAG].asString()); // checked above
                }
            }
        }
        else
        {
            throw Poco::Exception("Invalid JSONRPC: No Method", Errors::RPC_ERROR_PARSE);
        }
    }
    else
    {
        throw Poco::Exception("Invalid JSONRPC: No Version String", Errors::RPC_ERROR_PARSE);
    }
}


} } // namespace ofx::JSONRPC
