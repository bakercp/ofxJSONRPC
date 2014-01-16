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


class Request: public BaseMessage
    /// \brief A JSONRPC 2.0 request.
    /// \details An Request has the following format:
    ///
    /// \code{.json}
    /// {
    ///     "jsonrpc": "2.0",
    ///     "method": "subtract",
    ///     "params": {
    ///         "subtrahend": 23,
    ///         "minuend": 42
    ///     },
    ///     "id": 3
    /// }
    /// \endcode
    ///
    /// \sa http://www.jsonrpc.org/specification
{
public:
    Request(const std::string& method);
        ///< \brief Create a notification Request.

    Request(const std::string& method, const Json::Value& parameters);
        ///< \brief Create a notification Request.

    Request(const Json::Value& id, const std::string& method);
        ///< \brief Create a Request.

    Request(const Json::Value& id,
            const std::string& method,
            const Json::Value& parameters);
        ///< \brief Create a Request.

    virtual ~Request();
        ///< \brief Destroy the ErrorResponse.

    std::string getMethod() const;
        ///< \returns the method.

    Json::Value getParameters() const;
        ///< \returns the method parameters.

    std::string toString(bool styled = false) const;
        ///< \returns a raw json string of this Request

    static Json::Value toJSON(const Request& request);
        ///< \brief Serialize the Request object to JSON.
        ///< \param request the Request object to serialize.
        ///< \returns JSONRPC compatible JSON.

    static Request fromJSON(const Json::Value& json);
        ///< \brief Deserialize the JSON to a Request object.
        ///< \param json JSONRPC compatible JSON to deserialize.
        ///< \returns deserialized Request.
        ///< \throws Poco::Exception if the json is not valid.

protected:
    std::string _method;
        ///< \brief The method name.

    Json::Value _parameters;
        ///< \brief The method parameters.

    static const std::string METHOD_TAG;
        ///< \brief Method tag.

    static const std::string PARAMS_TAG;
        ///< \brief Parameters tag.

};


} } // namespace ofx::JSONRPC
