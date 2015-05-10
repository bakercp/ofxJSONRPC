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


/// \brief A JSONRPC 2.0 Response.
///
/// A Response has the following format:
///
/// ~~~{.json}
/// {
///     "jsonrpc": "2.0",
///     "result": 19,
///     "id": 1
/// }
/// ~~~
///
/// \sa http://www.jsonrpc.org/specification
class Response: public BaseMessage
{
public:
    /// \brief Create a default Error Response.
    Response(HTTP::ServerEventArgs& evt);

    /// \brief Create a successful Response.
    /// \param id The id of the original remote call.
    /// \param result The results of the function call as JSON.
    Response(HTTP::ServerEventArgs& evt,
             const Json::Value& id,
             const Json::Value& result);

    /// \brief Create an Error Response.
    /// \param id The id of the original remote call.
    /// \param error The Error response. The Error MUST
    ///        contain a valid error code.
    Response(HTTP::ServerEventArgs& evt,
             const Json::Value& id,
             const Error& error);

    /// \brief Destroy the Response.
    virtual ~Response();

    /// \brief Get the Result JSON if available.
    /// \returns result JSON data if available.
    /// \note The JSON data will be empty if there is an error.
    const Json::Value& getResult() const;

    /// \brief Get the Error if available.
    ///
    /// The Error code will be NO_ERROR if the call was successful.
    ///
    /// \returns the Error if available.
    const Error& getError() const;

    /// \brief Query if the Response is an error response.
    /// \returns true iff an error code is present.
    bool isErrorResponse() const;

    /// \brief Get the JSON Response as a string.
    /// \param styled true if the output string should be pretty-print.
    /// \returns a raw json string of this Response
    std::string toString(bool styled = false) const;

    /// \brief Serialize the Response object to JSON.
    /// \param response the Response object to serialize.
    /// \returns JSONRPC compatible JSON.
    static Json::Value toJSON(const Response& response);

    /// \brief Deserialize the JSON to a Response object.
    /// \param json JSONRPC compatible JSON to deserialize.
    /// \returns the deserialized Response.
    /// \throws Poco::Exception if the JSON is not valid.
    static Response fromJSON(HTTP::ServerEventArgs& evt, const Json::Value& json);

protected:
    /// \brief The result of the remote call.
    Json::Value _result;

    /// \brief An Error object.  Will be empty if there is no error.
    Error _error;

    /// \brief Error tag.
    static const std::string ERROR_TAG;

    /// \brief Result tag.
    static const std::string RESULT_TAG;

};


} } // namespace ofx::JSONRPC
