//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/JSONRPC/Error.h"
#include "ofx/JSONRPC/JSONRPCUtils.h"


namespace ofx {
namespace JSONRPC {


const std::string Error::ERROR_CODE_TAG = "code";
const std::string Error::ERROR_MESSAGE_TAG = "message";
const std::string Error::ERROR_DATA_TAG = "data";


Error::Error():
    _code(Errors::RPC_ERROR_NONE),
    _message(Errors::getErrorMessage(_code)),
    _data(ofJson())
{
}


Error::Error(int code):
    _code(code),
    _message(Errors::getErrorMessage(code)),
    _data(ofJson())
{
}


Error::Error(int code, const ofJson& data):
    _code(code),
    _message(Errors::getErrorMessage(_code)),
    _data(data)
{
}


Error::Error(int code, const std::string& message, const ofJson& data):
    _code(code),
    _message(message),
    _data(data)
{
}


Error::~Error()
{
}


int Error::code() const
{
    return _code;
}


int Error::getCode() const
{
    return code();
}

    
const std::string& Error::message() const
{
    return _message;
}


std::string Error::getMessage() const
{
    return message();
}


const ofJson& Error::data() const
{
    return _data;
}


ofJson Error::getData() const
{
    return data();
}


ofJson Error::toJSON(const Error& error)
{
    ofJson result;

    result[ERROR_CODE_TAG] = error.code();

    if (!error.message().empty())
    {
        result[ERROR_MESSAGE_TAG] = error.message();
    }

    if (!error.data().is_null())
    {
        result[ERROR_DATA_TAG] = error.data();
    }

    return result;
}

Error Error::fromJSON(const ofJson& json)
{
    if (JSONRPCUtils::hasIntegerKey(json, ERROR_CODE_TAG))
    {
        int code = json[ERROR_CODE_TAG];

        if (JSONRPCUtils::hasStringKey(json, ERROR_MESSAGE_TAG))
        {
            std::string message = json[ERROR_MESSAGE_TAG];

            if (JSONRPCUtils::hasKey(json, ERROR_DATA_TAG))
            {
                ofJson data = json[ERROR_DATA_TAG];
                return Error(code, message, data);
            }
            else
            {
                return Error(code, message);
            }
        }
        else
        {
            return Error(code);
        }
    }
    else
    {
        return Error(Errors::RPC_ERROR_PARSE);
    }
}


} } // namespace ofx::JSONRPC
