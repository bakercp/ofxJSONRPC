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
#include <map>
#include <json/json.h>
#include "ofx/JSONRPC/Errors.h"


namespace ofx {
namespace JSONRPC {


class Error
    /// \brief A JSONRPC 2.0 error object.
    /// \sa http://www.jsonrpc.org/specification
{
public:
    Error();
        ///< \brief Create an Error.
        ///< \note The code will be set to Errors::RPC_ERROR_NONE.

    Error(int code);
        ///< \brief Create an Error.
        ///< \param code is the error code.
        ///< \note The error message will be queried based on the code.
        ///< \note The data field will be left blank.

    Error(int code, std::string message);
        ///< \brief Create an Error.
        ///< \param code is the error code.
        ///< \param message the error message.
        ///< \note The data field will be left blank.

    Error(int code, const Json::Value& data);
        ///< \brief Create an Error.
        ///< \param code is the error code.
        ///< \param data the error data.
        ///< \note The error message will be queried based on the code.

    Error(int code, std::string message, const Json::Value& data);
        ///< \brief Create an ErrorResponse.
        ///< \param code is the error code.
        ///< \param message the error message.
        ///< \param data the error data.

    virtual ~Error();
        ///< \brief Destroy the ErrorResponse.

    int getCode() const;
        ///< \returns the error code.

    std::string getMessage() const;
        ///< \returns the error message.

    Json::Value getData() const;
        ///< \returns the data.
        ///< \note The JSON data may be empty.

    static Json::Value toJSON(const Error& error);
        ///< \brief Serialize the Error object to JSON.
        ///< \param error the Error object to serialize.
        ///< \returns JSONRPC compatible JSON.

    static Error fromJSON(const Json::Value& json);
        ///< \brief Deserialize the JSON to a Error object.
        ///< \param json JSONRPC compatible JSON to deserialize.
        ///< \returns the deserialized Error.
        ///< \throws Poco::Exception if the JSON is not valid.

    static const Error NO_ERROR;            ///< \brief No Error
    static const Error PARSE_ERROR;         ///< \brief Parse Error
    static const Error INVALID_REQUEST;     ///< \brief Invalid Request
    static const Error METHOD_NOT_FOUND;    ///< \brief Method Not Found
    static const Error INVALID_PARAMETERS;  ///< \brief Invalid Parameters
    static const Error INTERNAL_ERROR;      ///< \brief Internal Error

protected:
    int _code;
        ///< \brief A Number that indicates the error type that occurred.
        ///< \details This code MUST be an integer.

    std::string _message;
        ///< \brief A String providing a short description of the error.
        ///< \details The message SHOULD be limited to a concise single sentence.

    Json::Value _data;
        ///< \brief A Primitive or Structured value that contains additional
        ///<        information about the error.
        ///< \details This may be omitted. The value of this member is defined
        ///<        by the Server (e.g. detailed error information,
        ///<        nested errors etc.).

    static const std::string ERROR_CODE_TAG;    ///< \brief Error code tag.
    static const std::string ERROR_MESSAGE_TAG; ///< \brief Error message tag.
    static const std::string ERROR_DATA_TAG;    ///< \brief Error data tag.

};


} } // namespace ofx::JSONRPC
