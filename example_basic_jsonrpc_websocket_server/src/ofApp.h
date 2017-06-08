//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxJSONRPC.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();
    void exit();

    // Registered methods.
    void getText(ofx::JSONRPC::MethodArgs& args);
    void setText(ofx::JSONRPC::MethodArgs& args);

    // Register a no-argument notification method.
    void ping();

    // Register a no-argument notification method.
    void pong();

    /// \todo is ofSoundPlayer thread-safe?
    ofSoundPlayer pingPlayer;
    ofSoundPlayer pongPlayer;

    /// \brief The server that handles the JSONRPC requests.
    ofx::HTTP::JSONRPCServer server;

    /// \brief Get a snippet of random text in a thread-safe way.
    /// \returns The snippet of random text.
    std::string getRandomText() const;

    /// \brief Get the user text in a thread-safe way.
    /// \returns The user text.
    std::string getUserText() const;

    /// \brief Set the user text in a thread-safe way.
    /// \param text the user text to set.
    void setUserText(const std::string& text);

private:
    // A custom logging channel to mirror all log messages to the web clients.
    // WebSocketLoggerChannel::SharedPtr loggerChannel;

    // This piece of text might be modified by multiple client threads.
    // Thus we must use a mutex to protect it during multi-threaded access.
    std::string ipsum;

    // This piece of text might be modified by multiple client threads.
    // Thus we must use a mutex to protect it during multi-threaded access.
    std::string userText;

    // We use a mutex to protect any variables that can be
    // modified by multiple clients.  In our case, userText must be protected.
    // We mark the mutex as mutable so that it can be used in const functions.
    mutable std::mutex mutex;

};
