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


#include "ofx/JSONRPC/BaseMessage.h"


namespace ofx {
namespace JSONRPC {


const std::string BaseMessage::PROTOCOL_VERSION_TAG = "jsonrpc";
const std::string BaseMessage::PROTOCOL_VERSION     = "2.0";
const std::string BaseMessage::ID_TAG               = "id";


BaseMessage::BaseMessage(const Json::Value& id):
    _id(id)
{
}


BaseMessage::~BaseMessage()
{
}


Json::Value BaseMessage::getID() const
{
    return _id;
}


bool BaseMessage::hasID() const
{
    return !_id.empty();
}


} } // namespace ofx::JSONRPC
