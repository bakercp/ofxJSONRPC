//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <map>
#include "json.hpp"
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
class Request: public BaseMessage
{
public:
    /// \brief Create a notification Request.
    /// \param evt The originating server event.
    /// \param method The method's name.
    Request(HTTP::ServerEventArgs& evt,
            const std::string& method);

    /// \brief Create a notification Request.
    /// \param evt The originating server event.
    /// \param method The method's name.
    /// \param parameters The parameters to pass to the method.
    Request(HTTP::ServerEventArgs& evt,
            const std::string& method, const ofJson& parameters);

    /// \brief Create a Request.
    /// \param evt The originating server event.
    /// \param id The transatction identification number.
    /// \param method The method's name.
    Request(HTTP::ServerEventArgs& evt,
            const ofJson& id, const std::string& method);

    /// \brief Create a Request.
    /// \param evt The originating server event.
    /// \param id The transatction identification number.
    /// \param method The method's name.
    /// \param parameters The parameters to pass to the method.
    Request(HTTP::ServerEventArgs& evt,
            const ofJson& id,
            const std::string& method,
            const ofJson& parameters);

    /// \brief Destroy the ErrorResponse.
    virtual ~Request();

    /// \brief Get the request method.
    /// \returns the request method.
    const std::string& method() const;
    OF_DEPRECATED_MSG("Use method() instead.", const std::string& getMethod() const);

    /// \brief Get the request parameters.
    /// \returns the request method parameters.
    const ofJson& parameters() const;
    OF_DEPRECATED_MSG("Use parameters() instead.", const ofJson& getParameters() const);

    /// \brief Query whether this Request is a notification.
    /// \returns true iff the id is null.
    bool isNotification() const;

    /// \brief Get the JSON Request as a string.
    /// \param styled true if the output string should be pretty-print.
    /// \returns a raw json string of this Request
    std::string toString(bool styled = false) const;

    /// \brief Serialize the Request object to JSON.
    /// \param request the Request object to serialize.
    /// \returns JSONRPC compatible JSON.
    static ofJson toJSON(const Request& request);

    /// \brief Deserialize the JSON to a Request object.
    /// \param json JSONRPC compatible JSON to deserialize.
    /// \returns deserialized Request.
    /// \throws ParseException if the json is not valid.
    static Request fromJSON(HTTP::ServerEventArgs& evt, const ofJson& json);

protected:
    /// \brief The method name.
    std::string _method;

    /// \brief The method parameters.
    ofJson _parameters;

    /// \brief Method tag.
    static const std::string METHOD_TAG;

    /// \brief Parameters tag.
    static const std::string PARAMS_TAG;

};


} } // namespace ofx::JSONRPC
