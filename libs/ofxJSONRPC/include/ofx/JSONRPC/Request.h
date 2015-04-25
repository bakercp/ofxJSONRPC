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
#include "ofx/HTTP/AbstractServerTypes.h"
#include "ofx/JSONRPC/Error.h"
#include "ofx/JSONRPC/BaseMessage.h"


namespace ofx {
namespace JSONRPC {


/// \brief A JSONRPC 2.0 Request.
///
/// A Request has the following format:
///
/// ~~~{.json}
/// {
///     "jsonrpc": "2.0",
///     "method": "subtract",
///     "params": {
///         "subtrahend": 23,
///         "minuend": 42
///     },
///     "id": 3
/// }
/// ~~~
///
/// \sa http://www.jsonrpc.org/specification
class Request: public BaseMessage, public HTTP::AbstractSessionId
{
public:
    /// \brief Create a notification Request.
    /// \param method The method's name.
    Request(const std::string& method);

    /// \brief Create a notification Request.
    /// \param method The method's name.
    /// \param parameters The parameters to pass to the method.
    Request(const std::string& method, const Json::Value& parameters);

    /// \brief Create a Request.
    /// \param id The transatction identification number.
    /// \param method The method's name.
    Request(const Json::Value& id, const std::string& method);

    /// \brief Create a Request.
    /// \param id The transatction identification number.
    /// \param method The method's name.
    /// \param parameters The parameters to pass to the method.
    Request(const Json::Value& id,
            const std::string& method,
            const Json::Value& parameters);

    /// \brief Destroy the ErrorResponse.
    virtual ~Request();

    /// \brief Get the request method.
    /// \returns the request method.
    const std::string& getMethod() const;

    /// \brief Get the request parameters.
    /// \returns the request method parameters.
    const Json::Value& getParameters() const;

    /// \brief Query whether this Request is a notification.
    /// \returns true iff the id is null.
    bool isNotification() const;

    /// \brief Get the session id for the Request.
    ///
    /// The session id identifies the client session. This is not the same as
    /// the request id, which identifies a unique request sent by a client
    /// during a session.
    ///
    /// \returns the session id for the request.
    Poco::UUID getSessionId() const;

    /// \brief Get the JSON Request as a string.
    /// \param styled true if the output string should be pretty-print.
    /// \returns a raw json string of this Request
    std::string toString(bool styled = false) const;

    /// \brief Serialize the Request object to JSON.
    /// \param request the Request object to serialize.
    /// \returns JSONRPC compatible JSON.
    static Json::Value toJSON(const Request& request);

    /// \brief Deserialize the JSON to a Request object.
    /// \param json JSONRPC compatible JSON to deserialize.
    /// \returns deserialized Request.
    /// \throws Poco::Exception if the json is not valid.
    static Request fromJSON(const Json::Value& json);

protected:
    /// \brief The session id for request.
    Poco::UUID _sessionId;

    /// \brief The method name.
    std::string _method;

    /// \brief The method parameters.
    Json::Value _parameters;

    /// \brief Method tag.
    static const std::string METHOD_TAG;

    /// \brief Parameters tag.
    static const std::string PARAMS_TAG;

};


} } // namespace ofx::JSONRPC
