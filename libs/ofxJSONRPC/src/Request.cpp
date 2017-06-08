//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/JSONRPC/Request.h"
#include "ofx/JSONRPC/JSONRPCUtils.h"


namespace ofx {
namespace JSONRPC {


const std::string Request::METHOD_TAG = "method";
const std::string Request::PARAMS_TAG = "params";


Request::Request(HTTP::ServerEventArgs& evt, const std::string& method):
    BaseMessage(evt, nullptr),
    _method(method),
    _parameters(nullptr)
{
}


Request::Request(HTTP::ServerEventArgs& evt,
                 const std::string& method,
                 const ofJson& parameters):
    BaseMessage(evt, nullptr),
    _method(method),
    _parameters(parameters)
{
}


Request::Request(HTTP::ServerEventArgs& evt,
                 const ofJson& id,
                 const std::string& method):
    BaseMessage(evt, id),
    _method(method),
    _parameters(nullptr)
{
}


Request::Request(HTTP::ServerEventArgs& evt,
                 const ofJson& id,
                 const std::string& method,
                 const ofJson& parameters):
    
    BaseMessage(evt, id),
    _method(method),
    _parameters(parameters)
{
}


Request::~Request()
{
}


const std::string& Request::method() const
{
    return _method;
}


const std::string& Request::getMethod() const
{
    return method();
}


const ofJson& Request::parameters() const
{
    return _parameters;
}


const ofJson& Request::getParameters() const
{
    return parameters();
}


bool Request::isNotification() const
{
    return !hasId();
}


std::string Request::toString(bool styled) const
{
    return JSONRPCUtils::toString(toJSON(*this), styled);
}


ofJson Request::toJSON(const Request& request)
{
    ofJson result;

    result[PROTOCOL_VERSION_TAG] = PROTOCOL_VERSION;

    result[ID_TAG] = request.id();
    result[METHOD_TAG] = request.method();

    if (!request.parameters().is_null())
    {
        result[PARAMS_TAG] = request.parameters();
    }
    
    return result;
}


Request Request::fromJSON(HTTP::ServerEventArgs& evt,
                          const ofJson& json)
{
    if (JSONRPCUtils::hasStringKey(json, PROTOCOL_VERSION_TAG) &&
        json[PROTOCOL_VERSION_TAG] == PROTOCOL_VERSION)
    {
        if (JSONRPCUtils::hasStringKey(json, METHOD_TAG))
        {
            std::string method = json[METHOD_TAG];

            if (JSONRPCUtils::hasKey(json, ID_TAG))
            {
                ofJson id = json[ID_TAG];

                if (JSONRPCUtils::hasKey(json, PARAMS_TAG))
                {
                    ofJson params = json[PARAMS_TAG];
                    return Request(evt, id, method, params);
                }
                else
                {
                    return Request(evt, id, method);
                }
            }
            else
            {
                if (JSONRPCUtils::hasKey(json, PARAMS_TAG))
                {
                    ofJson params = json[PARAMS_TAG];
                    return Request(evt, method, params);
                }
                else
                {
                    return Request(evt, method);
                }
            }
        }
        else
        {
            throw ParseException("No method.");
        }
    }
    else
    {
        throw ParseException("No version string.");
    }
}


} } // namespace ofx::JSONRPC
