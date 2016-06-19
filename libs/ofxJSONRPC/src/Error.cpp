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
