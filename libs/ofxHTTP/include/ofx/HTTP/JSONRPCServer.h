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
#include "ofx/HTTP/PostRoute.h"
#include "ofx/HTTP/WebSocketConnection.h"
#include "ofx/HTTP/WebSocketRoute.h"
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


/// \brief A simple JSONRPCServer.
///
/// This server can process JSONRPC calls submitted via WebSockets or
/// POST requests.
template <typename SessionStoreType>
class JSONRPCServer_:
    public BaseServer_<JSONRPCServerSettings, SessionStoreType>,
    public JSONRPC::MethodRegistry
{
public:
    /// \brief A typedef for JSONRPCServerSettings.
    typedef JSONRPCServerSettings Settings;

    /// \brief Create a JSONRPCServer with settings.
    /// \param settings configure the JSONRPCServer with the given settings.
    JSONRPCServer_(const Settings& settings = Settings());

    /// \brief Destroy the JSONRPCServer.
    virtual ~JSONRPCServer_();

    /// \brief Set up the JSONRPCServer with the given settings.
    ///
    /// Settings will be applied on next server startup.
    /// \param settings configure the JSONRPCServer with the given settings.
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

    bool onWebSocketOpenEvent(WebSocketOpenEventArgs& evt);
    bool onWebSocketCloseEvent(WebSocketCloseEventArgs& evt);
    bool onWebSocketFrameReceivedEvent(WebSocketFrameEventArgs& evt);
    bool onWebSocketFrameSentEvent(WebSocketFrameEventArgs& evt);
    bool onWebSocketErrorEvent(WebSocketErrorEventArgs& evt);

    bool onHTTPPostEvent(PostEventArgs& evt);
    bool onHTTPFormEvent(PostFormEventArgs& evt);
    bool onHTTPUploadEvent(PostUploadEventArgs& evt);

protected:
    /// \brief The FileSystemRoute attached to this server.
    FileSystemRoute _fileSystemRoute;

    /// \brief The PostRoute attached to this server.
    PostRoute _postRoute;

    /// \brief The WebSocketRoute attached to this server.
    WebSocketRoute _webSocketRoute;

};


typedef JSONRPCServer_<SimpleSessionStore> JSONRPCServer;


template <typename SessionStoreType>
JSONRPCServer_<SessionStoreType>::JSONRPCServer_(const Settings& settings):
    BaseServer_<JSONRPCServerSettings, SessionStoreType>(settings),
    _fileSystemRoute(settings.fileSystemRouteSettings),
    _postRoute(settings.postRouteSettings),
    _webSocketRoute(settings.webSocketRouteSettings)
{
    this->addRoute(&_fileSystemRoute); // #3 to test.
    this->addRoute(&_postRoute);       // #2 to test.
    this->addRoute(&_webSocketRoute);  // #1 to test.

    _postRoute.registerPostEvents(this);
    _webSocketRoute.registerWebSocketEvents(this);
}


template <typename SessionStoreType>
JSONRPCServer_<SessionStoreType>::~JSONRPCServer_()
{
    _webSocketRoute.unregisterWebSocketEvents(this);
    _postRoute.unregisterPostEvents(this);

    this->removeRoute(&_webSocketRoute);
    this->removeRoute(&_postRoute);
    this->removeRoute(&_fileSystemRoute);
}


template <typename SessionStoreType>
void JSONRPCServer_<SessionStoreType>::setup(const Settings& settings)
{
    BaseServer_<JSONRPCServerSettings, SessionStoreType>::setup(settings);
    _fileSystemRoute.setup(settings.fileSystemRouteSettings);
    _postRoute.setup(settings.postRouteSettings);
    _webSocketRoute.setup(settings.webSocketRouteSettings);
}


template <typename SessionStoreType>
FileSystemRoute& JSONRPCServer_<SessionStoreType>::getFileSystemRoute()
{
    return _fileSystemRoute;
}


template <typename SessionStoreType>
PostRoute& JSONRPCServer_<SessionStoreType>::getPostRoute()
{
    return _postRoute;
}


template <typename SessionStoreType>
WebSocketRoute& JSONRPCServer_<SessionStoreType>::getWebSocketRoute()
{
    return _webSocketRoute;
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onWebSocketOpenEvent(WebSocketOpenEventArgs& evt)
{
    return false;  // We did not attend to this event, so pass it along.
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onWebSocketCloseEvent(WebSocketCloseEventArgs& evt)
{
    return false;  // We did not attend to this event, so pass it along.
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onWebSocketFrameReceivedEvent(WebSocketFrameEventArgs& evt)
{
    Json::Value json;
    Json::Reader reader;

    if (reader.parse(evt.getFrame().getText(), json))
    {
        try
        {
            JSONRPC::Request request = JSONRPC::Request::fromJSON(evt, json);
            JSONRPC::Response response = processCall(this, request);

            if (response.hasId())
            {
                evt.getConnection().sendFrame(response.toString());
            }
        }
        catch (const Poco::InvalidArgumentException& exc)
        {
            JSONRPC::Response response(evt,
                                       Json::Value::null, // null value is required when parse exceptions
                                       JSONRPC::Error(JSONRPC::Errors::RPC_ERROR_INVALID_PARAMETERS));

            evt.getConnection().sendFrame(response.toString());
        }
        catch (const Poco::Exception& exc)
        {
            JSONRPC::Response response(evt,
                                       Json::Value::null, // null value is required when parse exceptions
                                       JSONRPC::Error(JSONRPC::Errors::RPC_ERROR_INTERNAL_ERROR));

            evt.getConnection().sendFrame(response.toString());
        }

        return true;  // We attended to the event, so consume it.
    }
    else
    {
        ofLogVerbose("JSONRPCServer::onWebSocketFrameReceivedEvent") << "Could not parse as JSON: " << reader.getFormattedErrorMessages();
        ofLogVerbose("JSONRPCServer::onWebSocketFrameReceivedEvent") << evt.getFrame().getText();
        return false;  // We did not attend to this event, so pass it along.
    }
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onWebSocketFrameSentEvent(WebSocketFrameEventArgs& evt)
{
    return false;  // We did not attend to this event, so pass it along.
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onWebSocketErrorEvent(WebSocketErrorEventArgs& evt)
{
    return false;  // We did not attend to this event, so pass it along.
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onHTTPFormEvent(PostFormEventArgs& args)
{
    ofLogVerbose("JSONRPCServer::onHTTPFormEvent") << "";
    HTTP::HTTPUtils::dumpNameValueCollection(args.getForm(), ofGetLogLevel());
    return false;  // We did not attend to this event, so pass it along.
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onHTTPPostEvent(PostEventArgs& args)
{
    std::cout << "in here" << endl;

    Json::Value json;
    Json::Reader reader;

    if (reader.parse(args.getBuffer().getText(), json))
    {
        try
        {
            JSONRPC::Request request = JSONRPC::Request::fromJSON(args, json);
            JSONRPC::Response response = processCall(this, request);

            if (response.hasId())
            {
                std::string buffer = response.toString();
                args.getResponse().sendBuffer(buffer.c_str(), buffer.length());
            }
        }
        catch (Poco::Exception& exc)
        {
            JSONRPC::Response response(args,
                                       Json::Value::null, // null value is required when parse exceptions.
                                       JSONRPC::Error(JSONRPC::Errors::RPC_ERROR_METHOD_NOT_FOUND));
            std::string buffer = response.toString();
            args.getResponse().sendBuffer(buffer.c_str(), buffer.length());
        }

        return true;  // We attended to the event, so consume it.
    }
    else
    {
        ofLogVerbose("JSONRPCServer::onHTTPPostEvent") << "Could not parse as JSON: " << reader.getFormattedErrorMessages();
        
        return false;  // We did not attend to this event, so pass it along.
    }
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onHTTPUploadEvent(PostUploadEventArgs& args)
{
    std::string stateString = "";
    
    switch (args.getState())
    {
        case HTTP::PostUploadEventArgs::UPLOAD_STARTING:
            stateString = "STARTING";
            break;
        case HTTP::PostUploadEventArgs::UPLOAD_PROGRESS:
            stateString = "PROGRESS";
            break;
        case HTTP::PostUploadEventArgs::UPLOAD_FINISHED:
            stateString = "FINISHED";
            break;
    }
    
    return false;  // We did not attend to this event, so pass it along.
}




} } // namespace ofx::HTTP
