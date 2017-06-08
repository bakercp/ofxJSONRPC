//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/JSONRPC/BaseMessage.h"


namespace ofx {
namespace JSONRPC {


const std::string BaseMessage::PROTOCOL_VERSION_TAG = "jsonrpc";
const std::string BaseMessage::PROTOCOL_VERSION     = "2.0";
const std::string BaseMessage::ID_TAG               = "id";


BaseMessage::BaseMessage(HTTP::ServerEventArgs& evt,
                         const ofJson& id):
    HTTP::ServerEventArgs(evt),
    _id(id)
{
}


BaseMessage::~BaseMessage()
{
}


const ofJson& BaseMessage::id() const
{
    return _id;
}


ofJson BaseMessage::getId() const
{
    return _id;
}


bool BaseMessage::hasId() const
{
    return !_id.empty();
}


} } // namespace ofx::JSONRPC
