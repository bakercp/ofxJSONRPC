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
#include "ofx/HTTP/BaseServer.h"
#include "ofx/HTTP/FileSystemRoute.h"
#include "ofx/HTTP/PostRouteSettings.h"
#include "ofx/HTTP/PostRoute.h"
#include "ofx/HTTP/SessionCache.h"
#include "ofx/HTTP/WebSocketConnection.h"
#include "ofx/HTTP/WebSocketRoute.h"
#include "ofx/HTTP/WebSocketRouteSettings.h"
#include "ofx/JSONRPC/MethodRegistry.h"


namespace ofx {
namespace HTTP {


class JSONRPCServerSettings: public BaseServerSettings
{
public:
    FileSystemRouteSettings fileSystemRouteSettings;
    PostRouteSettings postRouteSettings;
    WebSocketRouteSettings webSocketRouteSettings;
};


/// \brief A BasicJSONRPCServer.
///
/// This server can process JSONRPC calls submitted via WebSockets or
/// POST requests.
class BasicJSONRPCServer:
    public BaseServer_<JSONRPCServerSettings>,
    public JSONRPC::MethodRegistry
{
public:
    typedef JSONRPCServerSettings Settings;

    BasicJSONRPCServer(const Settings& settings = Settings());

    /// \brief Destroy the BasicJSONRPCServer.
    virtual ~BasicJSONRPCServer();

    virtual void setup(const Settings& settings);

    /// \brief Get the PostRoute.
    /// \returns the PostRoute attached to this server.
    FileSystemRoute& getFileSystemRoute();

    /// \brief Get the PostRoute.
    /// \returns the PostRoute attached to this server.
    PostRoute& getPostRoute();

    /// \brief Get the WebSocketRoute.
    /// \returns the WebSocketRoute attached to this server.
    WebSocketRoute& getWebSocketRoute();

    SessionCache::SharedPtr getSessionCache();

    bool onWebSocketOpenEvent(WebSocketOpenEventArgs& evt);
    bool onWebSocketCloseEvent(WebSocketCloseEventArgs& evt);
    bool onWebSocketFrameReceivedEvent(WebSocketFrameEventArgs& evt);
    bool onWebSocketFrameSentEvent(WebSocketFrameEventArgs& evt);
    bool onWebSocketErrorEvent(WebSocketErrorEventArgs& evt);

    bool onHTTPPostEvent(PostEventArgs& evt);
    bool onHTTPFormEvent(PostFormEventArgs& evt);
    bool onHTTPUploadEvent(PostUploadEventArgs& evt);

protected:
    /// \brief A session cache for this server.
    SessionCache::SharedPtr _sessionCache;

    /// \brief The FileSystemRoute attached to this server.
    FileSystemRoute _fileSystemRoute;

    /// \brief The PostRoute attached to this server.
    PostRoute _postRoute;

    /// \brief The WebSocketRoute attached to this server.
    WebSocketRoute _webSocketRoute;

};


} } // namespace ofx::HTTP
