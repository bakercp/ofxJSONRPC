//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include "ofJson.h"
#include "ofx/HTTP/ServerEvents.h"


namespace ofx {
namespace JSONRPC {


/// \brief A BaseMessage is a base class for both Request and Response objects.
class BaseMessage: public HTTP::ServerEventArgs
{
public:
    /// \brief Create a BaseMessage.
    BaseMessage(HTTP::ServerEventArgs& evt,
                const ofJson& id);

    /// \brief Destroy the BaseMessage.
    virtual ~BaseMessage();

    /// \returns the message ID.
    const ofJson& id() const;
    OF_DEPRECATED_MSG("Use id() instead.", ofJson getId() const);

    /// \return true iff the ID is not null.
    bool hasId() const;

protected:
    /// \brief The id of the remote call.
    ofJson _id;

    /// \brief JSONRPC tag.
    static const std::string PROTOCOL_VERSION_TAG;

    /// \brief The JSONRPC version.
    static const std::string PROTOCOL_VERSION;

    /// \brief ID tag.
    static const std::string ID_TAG;

};


} } // namespace ofx::JSONRPC
