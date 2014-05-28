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
#include "ofx/HTTP/BasicServer.h"
#include "ofx/HTTP/PostRouteSettings.h"
#include "ofx/HTTP/SessionCache.h"
#include "ofx/HTTP/WebSocketRouteSettings.h"
#include "ofx/JSONRPC/MethodRegistry.h"


namespace ofx {
namespace HTTP {


class BasicJSONRPCServerSettings:
    public BasicServerSettings,
    public PostRouteSettings,
    public WebSocketRouteSettings
{
};


/// \brief A BasicJSONRPCServer.
///
/// This server can process JSONRPC calls submitted via WebSockets or
/// POST requests.
class BasicJSONRPCServer: public BasicServer, public JSONRPC::MethodRegistry
{
public:
    typedef std::shared_ptr<BasicJSONRPCServer> SharedPtr;
    typedef BasicJSONRPCServerSettings Settings;

    BasicJSONRPCServer(const Settings& settings = Settings());

    /// \brief Destroy the BasicJSONRPCServer.
    virtual ~BasicJSONRPCServer();

    /// \brief Get the PostRoute.
    /// \returns the PostRoute attached to this server.
    PostRoute::SharedPtr getPostRoute();

    /// \brief Get the WebSocketRoute.
    /// \returns the WebSocketRoute attached to this server.
    WebSocketRoute::SharedPtr getWebSocketRoute();

    bool onWebSocketOpenEvent(WebSocketEventArgs& evt);
    bool onWebSocketCloseEvent(WebSocketEventArgs& evt);
    bool onWebSocketFrameReceivedEvent(WebSocketFrameEventArgs& evt);
    bool onWebSocketFrameSentEvent(WebSocketFrameEventArgs& evt);
    bool onWebSocketErrorEvent(WebSocketEventArgs& evt);

    bool onHTTPPostEvent(PostEventArgs& evt);
    bool onHTTPFormEvent(PostFormEventArgs& evt);
    bool onHTTPUploadEvent(PostUploadEventArgs& evt);

    /// \returns a new Shared instance of a BasicJSONRPCServer
    static SharedPtr makeShared(const Settings& settings = Settings())
    {
        return SharedPtr(new BasicJSONRPCServer(settings));
    }

protected:
    /// \brief A session cache for this server.
    SessionCache::SharedPtr _sessionCache;

    /// \brief The PostRoute attached to this server.
    PostRoute::SharedPtr _postRoute;

    /// \brief The WebSocketRoute attached to this server.
    WebSocketRoute::SharedPtr _webSocketRoute;

};


} } // namespace ofx::HTTP
