//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

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
    FileSystemRoute& fileSystemRoute();

    /// \brief Get the PostRoute.
    /// \returns the PostRoute attached to this server.
    PostRoute& postRoute();

    /// \brief Get the WebSocketRoute.
    /// \returns the WebSocketRoute attached to this server.
    WebSocketRoute& webSocketRoute();

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
FileSystemRoute& JSONRPCServer_<SessionStoreType>::fileSystemRoute()
{
    return _fileSystemRoute;
}


template <typename SessionStoreType>
PostRoute& JSONRPCServer_<SessionStoreType>::postRoute()
{
    return _postRoute;
}


template <typename SessionStoreType>
WebSocketRoute& JSONRPCServer_<SessionStoreType>::webSocketRoute()
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
    try
    {
        ofJson json = ofJson::parse(evt.frame().getText());

        try
        {
            JSONRPC::Request request = JSONRPC::Request::fromJSON(evt, json);
            JSONRPC::Response response = processCall(this, request);

            if (response.hasId())
            {
                evt.connection().sendFrame(response.toString());
            }
        }
        catch (const Poco::InvalidArgumentException& exc)
        {
            JSONRPC::Response response(evt,
                                       ofJson(nullptr), // null value is required when parse exceptions
                                       JSONRPC::Error(JSONRPC::Errors::RPC_ERROR_INVALID_PARAMETERS));

            evt.connection().sendFrame(response.toString());
        }
        catch (const Poco::Exception& exc)
        {
            JSONRPC::Response response(evt,
                                       ofJson(nullptr), // null value is required when parse exceptions
                                       JSONRPC::Error(JSONRPC::Errors::RPC_ERROR_INTERNAL_ERROR));

            evt.connection().sendFrame(response.toString());
        }

        return true;  // We attended to the event, so consume it.

    }
    catch (const std::invalid_argument& exc)
    {
        ofLogVerbose("JSONRPCServer::onWebSocketFrameReceivedEvent") << "Could not parse as JSON: " << exc.what();
        ofLogVerbose("JSONRPCServer::onWebSocketFrameReceivedEvent") << evt.frame().getText();
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
    return false;  // We did not attend to this event, so pass it along.
}


template <typename SessionStoreType>
bool JSONRPCServer_<SessionStoreType>::onHTTPPostEvent(PostEventArgs& args)
{
    try
    {
        ofJson json = ofJson::parse(args.getBuffer().getText());

        try
        {
            JSONRPC::Request request = JSONRPC::Request::fromJSON(args, json);
            JSONRPC::Response response = processCall(this, request);

            if (response.hasId())
            {
                std::string buffer = response.toString();
                args.response().sendBuffer(buffer.c_str(), buffer.length());
            }
        }
        catch (Poco::Exception& exc)
        {
            JSONRPC::Response response(args,
                                       ofJson(nullptr), // null value is required when parse exceptions.
                                       JSONRPC::Error(JSONRPC::Errors::RPC_ERROR_METHOD_NOT_FOUND));

            std::string buffer = response.toString();
            args.response().sendBuffer(buffer.c_str(), buffer.length());
        }

        return true;  // We attended to the event, so consume it.
    }
    catch (const std::invalid_argument& exc)
    {
        ofLogVerbose("JSONRPCServer::onHTTPPostEvent") << "Could not parse as JSON: " << exc.what();
        ofLogVerbose("JSONRPCServer::onHTTPPostEvent") << args.getBuffer().getText();

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
