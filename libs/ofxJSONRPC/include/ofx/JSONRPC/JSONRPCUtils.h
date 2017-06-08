//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include "json.hpp"
#include "Poco/UUID.h"
#include "ofx/JSONRPC/Errors.h"
#include "ofx/JSONRPC/Response.h"
#include "ofx/JSONRPC/Request.h"


namespace ofx {
namespace JSONRPC {


/// \brief A collection of utilities for JSONRPC.
class JSONRPCUtils
{
public:
    /// \brief Convert JSON values to a raw string representation.
    /// \param json The JSON value to convert.
    /// \param styled If true, the raw string will be indented
    ///        with returns and thus easier to read (aka pretty print).
    /// \returns A std::string representation of the JSON.
    static std::string toString(const ofJson& json, bool styled = false);

    /// \brief Determine whether the given json has the named key.
    /// \param json The json to check.
    /// \param key The key to check.
    /// \returns true if the given key exists.
    static bool hasKey(const ofJson& json, const std::string& key);

    /// \brief Determine whether the given json has the named key of a certain type.
    /// \param json The json to check.
    /// \param key The key to check.
    /// \param type The data type to check.
    /// \returns true if the given key exists.
    static bool hasKeyOfType(const ofJson& json,
                             const std::string& key,
                             ofJson::value_t type);

    /// \brief Determine whether the given json has the named key of string type.
    /// \param json The json to check.
    /// \param key The key to check.
    /// \returns true if the given key exists.
    static bool hasStringKey(const ofJson& json,
                             const std::string& key);

    /// \brief Determine whether the given json has the named key of integer type.
    /// \param json The json to check.
    /// \param key The key to check.
    /// \returns true if the given key exists.
    static bool hasIntegerKey(const ofJson& json,
                              const std::string& key);

};


} } // namespace ofx::JSONRPC
