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
#include <json/json.h>


namespace ofx {
namespace JSONRPC {


class BaseMessage
    /// \brief A BaseMessage is a base class for
    ///         both Request and Response objects.
{
public:
    BaseMessage(const Json::Value& id);
        ///< \brief Create a BaseMessage.

    virtual ~BaseMessage();
        ///< \brief Destroy the BaseMessage.

    Json::Value getID() const;
        ///< \returns the message ID.

    bool hasID() const;
        ///< \return true iff the ID is not empty.

protected:
    Json::Value _id;
        ///< \brief The id of the remote call.

    static const std::string PROTOCOL_VERSION_TAG;
        ///< \brief JSONRPC tag.

    static const std::string PROTOCOL_VERSION;
        ///< \brief The JSONRPC version.

    static const std::string ID_TAG;
        ///< \brief ID tag.

};


} } // namespace ofx::JSONRPC
