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


#include "ofx/JSONRPC/Error.h"


namespace ofx {
namespace JSONRPC {


const Error Error::NO_ERROR = Error(Errors::RPC_ERROR_NONE);
const Error Error::PARSE_ERROR = Error(Errors::RPC_ERROR_PARSE);
const Error Error::INVALID_REQUEST = Error(Errors::RPC_ERROR_INVALID_REQUEST);
const Error Error::METHOD_NOT_FOUND = Error(Errors::RPC_ERROR_METHOD_NOT_FOUND);
const Error Error::INVALID_PARAMETERS = Error(Errors::RPC_ERROR_INVALID_PARAMETERS);
const Error Error::INTERNAL_ERROR = Error(Errors::RPC_ERROR_INTERNAL_ERROR);

const std::string Error::ERROR_CODE_TAG = "code";
const std::string Error::ERROR_MESSAGE_TAG = "message";
const std::string Error::ERROR_DATA_TAG = "data";


Error::Error():
    _code(Errors::RPC_ERROR_NONE),
    _message(Errors::getErrorMessage(_code)),
    _data(Json::Value())
{
}


Error::Error(int code):
    _code(code),
    _message(Errors::getErrorMessage(code)),
    _data(Json::Value())
{
}

    
Error::Error(int code, const std::string& message):
    _code(code),
    _message(message),
    _data(Json::Value())
{

}


Error::Error(int code, const Json::Value& data):
    _code(code),
    _message(Errors::getErrorMessage(_code)),
    _data(data)
{
}


Error::Error(int code, const std::string& message, const Json::Value& data):
    _code(code),
    _message(message),
    _data(data)
{
}


Error::~Error()
{
}


int Error::getCode() const
{
    return _code;
}


std::string Error::getMessage() const
{
    return _message;
}


Json::Value Error::getData() const
{
    return _data;
}


Json::Value Error::toJSON(const Error& error)
{
    Json::Value result;

    result[ERROR_CODE_TAG] = error.getCode();

    if (!error.getMessage().empty())
    {
        result[ERROR_MESSAGE_TAG] = error.getMessage();
    }

    if (!error.getData().isNull())
    {
        result[ERROR_DATA_TAG] = error.getData();
    }

    return result;
}

Error Error::fromJSON(const Json::Value& json)
{
    if (json.isMember(ERROR_CODE_TAG) &&
        json[ERROR_CODE_TAG].isInt())
    {
        if (json.isMember(ERROR_MESSAGE_TAG) &&
            json[ERROR_CODE_TAG].isString())
        {
            if (json.isMember(ERROR_DATA_TAG))
            {
                return Error(json[ERROR_CODE_TAG].asInt(),
                             json[ERROR_MESSAGE_TAG].asString(),
                             json[ERROR_DATA_TAG]);
            }
            else
            {
                return Error(json[ERROR_CODE_TAG].asInt(),
                             json[ERROR_MESSAGE_TAG].asString());
            }
        }
        else
        {
            return Error(json[ERROR_CODE_TAG].asInt());
        }
    }
    else
    {
        return PARSE_ERROR;
    }
}


} } // namespace ofx::JSONRPC
