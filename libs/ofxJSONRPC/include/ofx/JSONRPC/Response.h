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
             const ofJson& id,
             const ofJson& result);

    /// \brief Create an Error Response.
    /// \param id The id of the original remote call.
    /// \param error The Error response. The Error MUST
    ///        contain a valid error code.
    Response(HTTP::ServerEventArgs& evt,
             const ofJson& id,
             const Error& error);

    /// \brief Destroy the Response.
    virtual ~Response();

    /// \brief Get the Result JSON if available.
    /// \returns result JSON data if available.
    /// \note The JSON data will be empty if there is an error.
    const ofJson& result() const;
    OF_DEPRECATED_MSG("Use result() instead.", const ofJson& getResult() const);

    /// \brief Get the Error if available.
    ///
    /// The Error code will be NO_ERROR if the call was successful.
    ///
    /// \returns the Error if available.
    const Error& error() const;
    OF_DEPRECATED_MSG("Use error() instead.", const Error& getError() const);

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
    static ofJson toJSON(const Response& response);

    /// \brief Deserialize the JSON to a Response object.
    /// \param json JSONRPC compatible JSON to deserialize.
    /// \returns the deserialized Response.
    /// \throws ParseException if the JSON is not valid.
    static Response fromJSON(HTTP::ServerEventArgs& evt, const ofJson& json);

protected:
    /// \brief The result of the remote call.
    ofJson _result;

    /// \brief An Error object.  Will be empty if there is no error.
    Error _error;

    /// \brief Error tag.
    static const std::string ERROR_TAG;

    /// \brief Result tag.
    static const std::string RESULT_TAG;

};


} } // namespace ofx::JSONRPC
