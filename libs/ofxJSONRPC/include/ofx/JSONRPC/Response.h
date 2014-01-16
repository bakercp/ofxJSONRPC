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
#include "ofx/JSONRPC/Error.h"
#include "ofx/JSONRPC/BaseMessage.h"



namespace ofx {
namespace JSONRPC {


class Response: public BaseMessage
    /// \brief A JSONRPC 2.0 response.
    /// \details An Response has the following format:
    ///
    /// \code{.json}
    /// {
    ///     "jsonrpc": "2.0",
    ///     "result": 19,
    ///     "id": 1
    /// }
    /// \endcode
    ///
    /// \sa http://www.jsonrpc.org/specification
{
public:
    Response();
        ///< \brief Create a default Error Response.
    
    Response(const Json::Value& id, const Json::Value& result);
        ///< \brief Create a Response.

    Response(const Json::Value& id, const Error& error);
        ///< \brief Create a Response.
        ///< \param id is the id of the original remote call.
        ///< \param error is the Error response. The Error MUST
        ///<        contain a valid error code.

    virtual ~Response();
        ///< \brief Destroy the Response.

    Json::Value getResult() const;
        ///< \returns result JSON data.
        ///< \note The JSON data will be empty if there is an error.

    Error getError() const;
        ///< \returns the Error.
        ///< \note The Error will be empty the response if the
        ///<        call was successful.

    bool isErrorResponse() const;
        ///< \returns true iff an error code is present.

    std::string toString(bool styled = false) const;
        ///< \returns a raw json string of this Response

    static Json::Value toJSON(const Response& response);
        ///< \brief Serialize the Response object to JSON.
        ///< \param response the Response object to serialize.
        ///< \returns JSONRPC compatible JSON.

    static Response fromJSON(const Json::Value& json);
        ///< \brief Deserialize the JSON to a Response object.
        ///< \param json JSONRPC compatible JSON to deserialize.
        ///< \returns the deserialized Response.
        ///< \throws Poco::Exception if the JSON is not valid.

protected:
    Json::Value _result;
        ///< \brief The result of the remote call.

    Error _error;
        ///< \brief An Error object.  Will be empty if there is no error.

    static const std::string ERROR_TAG;
        ///< \brief Error tag.

    static const std::string RESULT_TAG;
        ///< \brief Result tag.

};


} } // namespace ofx::JSONRPC
