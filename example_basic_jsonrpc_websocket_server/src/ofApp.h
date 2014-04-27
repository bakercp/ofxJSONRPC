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


#include "ofMain.h"
#include "ofxHTTP.h"
#include "ofxJSONRPC.h"


using namespace ofx::HTTP;
using namespace ofx::JSONRPC;


class ClientInfo
{
public:
    typedef std::shared_ptr<ClientInfo> SharedPtr;
    
    ClientInfo(const WebSocketConnection* wsc):
        _wsc(wsc)
    {
    }


    static SharedPtr makeShared(const WebSocketConnection* wsc)
    {
        return SharedPtr(new ClientInfo(wsc));
    }

private:
    const WebSocketConnection* _wsc;

};


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    // WebSocket callbacks
    void onWebSocketOpenEvent(WebSocketEventArgs& evt);
    void onWebSocketCloseEvent(WebSocketEventArgs& evt);
    void onWebSocketFrameReceivedEvent(WebSocketFrameEventArgs& evt);
    void onWebSocketFrameSentEvent(WebSocketFrameEventArgs& evt);
    void onWebSocketErrorEvent(WebSocketEventArgs& evt);

    // Post events
    void onHTTPPostEvent(PostEventArgs& evt);
    void onHTTPFormEvent(PostFormEventArgs& evt);
    void onHTTPUploadEvent(PostUploadEventArgs& args);


    // RPC callbacks

//    // Notification
//    void enableRandomNumberStream(const void* pSender);
//    void disableRandomStream(const void* pSender);
//
//    void reset();
//
//    // Methods
//    void getRandomNumber(JSONRPC::MethodArgs& args);
//    void setRandomNumber(JSONRPC::MethodArgs& args);
//
//    void getUniqueID(const void* pSender, JSONRPC::MethodArgs& args);
//    void setUniqueID(const void* pSender, JSONRPC::MethodArgs& args);
//

    void notificationHiClient(const void* client);
    void notificationHi();

    void generateRandomNumber(const void* client, MethodArgs& args);
    void setRandomNumber(const void* client, MethodArgs& args);

    ofColor bgColor;

    BasicJSONRPCServer::SharedPtr server;

    std::map<const WebSocketConnection*, ClientInfo::SharedPtr> clients;


};
