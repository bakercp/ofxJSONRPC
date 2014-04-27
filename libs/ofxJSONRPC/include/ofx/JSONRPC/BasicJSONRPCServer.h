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


#include "ofTypes.h"
#include "ofxHTTP.h"
#include "ofx/HTTP/Server/BasicServer.h"
#include "ofx/HTTP/Server/PostRouteSettings.h"
#include "ofx/HTTP/Server/SessionCache.h"
#include "ofx/HTTP/WebSocket/WebSocketRouteSettings.h"
#include "ofx/JSONRPC/MethodRegistry.h"


namespace ofx {
namespace JSONRPC {


class BasicJSONRPCServerSettings:
    public ofx::HTTP::BasicServerSettings,
    public ofx::HTTP::PostRouteSettings,
    public ofx::HTTP::WebSocketRouteSettings
{
};


class BasicJSONRPCServer: public ofx::HTTP::BasicServer, public MethodRegistry
{
public:
    typedef std::shared_ptr<BasicJSONRPCServer> SharedPtr;
    typedef std::weak_ptr<BasicJSONRPCServer> WeakPtr;
    typedef BasicJSONRPCServerSettings Settings;

    BasicJSONRPCServer(const Settings& settings = Settings());
    
    virtual ~BasicJSONRPCServer();

    /// \returns the PostRoute attached to this server.
    ofx::HTTP::PostRoute::SharedPtr getPostRoute();

    /// \returns the WebSocketRoute attached to this server.
    ofx::HTTP::WebSocketRoute::SharedPtr getWebSocketRoute();

    bool onWebSocketOpenEvent(ofx::HTTP::WebSocketEventArgs& evt);
    bool onWebSocketCloseEvent(ofx::HTTP::WebSocketEventArgs& evt);
    bool onWebSocketFrameReceivedEvent(ofx::HTTP::WebSocketFrameEventArgs& evt);
    bool onWebSocketFrameSentEvent(ofx::HTTP::WebSocketFrameEventArgs& evt);
    bool onWebSocketErrorEvent(ofx::HTTP::WebSocketEventArgs& evt);

    bool onHTTPPostEvent(ofx::HTTP::PostEventArgs& evt);
    bool onHTTPFormEvent(ofx::HTTP::PostFormEventArgs& evt);
    bool onHTTPUploadEvent(ofx::HTTP::PostUploadEventArgs& evt);

    /// \returns a new Shared instance of a BasicJSONRPCServer
    static SharedPtr makeShared(const Settings& settings = Settings())
    {
        return SharedPtr(new BasicJSONRPCServer(settings));
    }

protected:
    ofx::HTTP::SessionCache::SharedPtr _sessionCache;
        ///< \brief A session cache for this server.

    ofx::HTTP::PostRoute::SharedPtr _postRoute;
        ///< \brief The PostRoute attached to this server.

    ofx::HTTP::WebSocketRoute::SharedPtr _webSocketRoute;
        ///< \brief The WebSocketRoute attached to this server.

};


} } // namespace ofx::JSONRPC
