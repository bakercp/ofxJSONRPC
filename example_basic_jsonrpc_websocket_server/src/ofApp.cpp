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


#include "ofApp.h"




void ofApp::setup()
{
    ofSetFrameRate(30);

    ofSetLogLevel(OF_LOG_VERBOSE);

    // Load test text.
    ipsum = ofBufferFromFile("media/ipsum.txt").getText();

    // Load test media.
    pingPlayer.loadSound("media/ping.wav");
    pongPlayer.loadSound("media/pong.wav");

    ofx::HTTP::BasicJSONRPCServerSettings settings;
    settings.setPort(8197);

    // Initialize the server.
    server = ofx::HTTP::BasicJSONRPCServer::makeShared(settings);

    // Create a new logger channel.
    loggerChannel = WebSocketLoggerChannel::makeShared();

    // Attach the websocket route.
    loggerChannel->setWebSocketRoute(server->getWebSocketRoute());

    // Set the logger channel as active.
    ofSetLoggerChannel(loggerChannel);

    // Register RPC methods.
    server->registerMethod("get-text",
                           "Returns a random chunk of text to the client.",
                           this,
                           &ofApp::getText);

    server->registerMethod("set-text",
                           "Sets text from the user.",
                           this,
                           &ofApp::setText);

    server->registerMethod("ping",
                           "Send a JSONRPC Ping Notification",
                           this,
                           &ofApp::ping);

    server->registerMethod("pong",
                           "Send a JSONRPC Pong Notification",
                           this,
                           &ofApp::pong);

    // Start the server.
    server->start();

    // Launch a browser with the address of the server.
    ofLaunchBrowser(server->getURL());
}

void ofApp::draw()
{
    ofBackground(255);
    ofDrawBitmapStringHighlight(userText, ofPoint(14, 18));
}


void ofApp::exit()
{
    // Set the logger back to the default to make sure any
    // remaining messages are logged correctly.
    ofLogToConsole();
}


void ofApp::ping()
{
    pingPlayer.play();
    ofLogVerbose("ofApp::ping") << "Ping'd";
}


void ofApp::pong()
{
    pongPlayer.play();
    ofLogVerbose("ofApp::pong") << "Pong'd";
}


void ofApp::getText(ofx::JSONRPC::MethodArgs& args)
{
    // Set the result equal to the substring.
    args.result = getRandomText();
    ofLogVerbose("ofApp::getText") << args.result;
}


void ofApp::setText(ofx::JSONRPC::MethodArgs& args)
{
    // Set the user text.
    setUserText(args.params.asString());
    ofLogVerbose("ofApp::setText") << args.params.asString();
}


std::string ofApp::getRandomText() const
{
    static const std::size_t LENGTH = 140;

    ofScopedLock lock(mutex);

   // Generate a random start index.
    std::size_t startIndex = (std::size_t)ofRandom(ipsum.length());

    // Ensure that the length is valid.
    std::size_t length = (startIndex + LENGTH) < ipsum.length() ? LENGTH : string::npos;

    // return the result equal to the substring.
    return ipsum.substr(startIndex, length);
}


std::string ofApp::getUserText() const
{
    ofScopedLock lock(mutex);
    return userText;
}


void ofApp::setUserText(const std::string& text)
{
    ofScopedLock lock(mutex);
    userText = text;
}

