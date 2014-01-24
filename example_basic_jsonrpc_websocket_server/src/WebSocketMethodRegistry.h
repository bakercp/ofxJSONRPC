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


#include <map>
#include <string>
#include <json/json.h>
#include "ofxHTTP.h"
#include "ofx/JSONRPC/Utils.h"
#include "ofx/JSONRPC/MethodRegistry.h"


namespace ofx {


class ClientInfo
{
public:
    ClientInfo(HTTP::WebSocketConnection* connection):
        connection(connection),
        nextUpdate(0)
    {
    }


    virtual ~ClientInfo()
    {
    }


    void update()
    {
    }

    HTTP::WebSocketConnection* connection;
    unsigned long long nextUpdate;

};


class WebSocketMethodRegistry: public JSONRPC::MethodRegistry
{
public:
    WebSocketMethodRegistry();
    virtual ~WebSocketMethodRegistry();

    void onWebSocketOpenEvent(HTTP::WebSocketEventArgs& evt);
    void onWebSocketCloseEvent(HTTP::WebSocketEventArgs& evt);
    void onWebSocketFrameReceivedEvent(HTTP::WebSocketFrameEventArgs& evt);
    void onWebSocketFrameSentEvent(HTTP::WebSocketFrameEventArgs& evt);
    void onWebSocketErrorEvent(HTTP::WebSocketEventArgs& evt);

//    bool setRandomNumberStream(JSONRPC::MethodArgs& args);

    std::map<const HTTP::WebSocketConnection*, ClientInfo> clients;

};


} // namespace ofx
