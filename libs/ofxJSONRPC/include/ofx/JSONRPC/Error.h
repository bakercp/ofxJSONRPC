//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <map>
#include "ofConstants.h"
#include "ofJson.h"
#include "ofx/JSONRPC/Errors.h"


namespace ofx {
namespace JSONRPC {


/// \brief A JSONRPC 2.0 error object.
/// \sa http://www.jsonrpc.org/specification
class Error
{
public:
    /// \brief Create an Error.
    /// \note The code will be set to Errors::RPC_ERROR_NONE.
    Error();

    /// \brief Create an Error.
    /// \param code is the error code.
    /// \note The error message will be queried based on the code.
    /// \note The data field will be left blank.
    explicit Error(int code);

	/// \brief Create an Error.
	/// \param code is the error code.
	/// \param message the error message.
	explicit Error(int code, const ofJson& data);

	/// \brief Create an Error.
	/// \param code is the error code.
	/// \param message the error message.
	/// \param data the error data.
	explicit Error(int code, const std::string& message, const ofJson& data);

    /// \brief Destroy the Error.
    virtual ~Error();

    /// \returns the error code.
    int code() const;
    OF_DEPRECATED_MSG("Use code() instead.", int getCode() const);

    /// \returns the error message.
    const std::string& message() const;
    OF_DEPRECATED_MSG("Use message() instead.", std::string getMessage() const);

    /// \returns the data.
    /// \note The JSON data may be empty.
    const ofJson& data() const;
    OF_DEPRECATED_MSG("Use data() instead.", ofJson getData() const);

    /// \brief Serialize the Error object to JSON.
    /// \param error the Error object to serialize.
    /// \returns JSONRPC compatible JSON.
    static ofJson toJSON(const Error& error);

    /// \brief Deserialize the JSON to a Error object.
    /// \param json JSONRPC compatible JSON to deserialize.
    /// \returns the deserialized Error.
    /// \throws Poco::Exception if the JSON is not valid.
    static Error fromJSON(const ofJson& json);

protected:
    /// \brief A Number that indicates the error type that occurred.
    /// \details This code MUST be an integer.
    int _code;

    /// \brief A String providing a short description of the error.
    /// \details The message SHOULD be limited to a concise single sentence.
    std::string _message;

    /// \brief A Json::Value that contains additional error info.
    ///
    /// This may be omitted. The value of this member is defined by the Server
    /// (e.g. detailed error information, nested errors etc.).
    ofJson _data;

    /// \brief Error code tag.
    static const std::string ERROR_CODE_TAG;

    /// \brief Error message tag.
    static const std::string ERROR_MESSAGE_TAG;

    /// \brief Error data tag.
    static const std::string ERROR_DATA_TAG;

};


} } // namespace ofx::JSONRPC
