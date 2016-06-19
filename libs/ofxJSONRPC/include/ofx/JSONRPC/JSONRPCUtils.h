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
