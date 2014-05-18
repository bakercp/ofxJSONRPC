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

    ipsum = ofBufferFromFile("media/ipsum.txt").getText();

    pingPlayer.loadSound("media/ping.wav");
    pongPlayer.loadSound("media/pong.wav");

    HTTP::BasicJSONRPCServerSettings settings;

    server.setup(settings);

    server.registerMethod("get-text",
                          "Returns a random chunk of text to the client.",
                          this,
                          &ofApp::getText);

    server.registerMethod("set-text",
                          "Sets text from the user.",
                          this,
                          &ofApp::setText);

    server.registerMethod("ping",
                          "Send a JSONRPC Ping Notification",
                          this,
                          &ofApp::ping);

    server.registerMethod("pong",
                          "Send a JSONRPC Pong Notification",
                          this,
                          &ofApp::pong);

    server.start();

    // Launch a browser with the address of the server.
    ofLaunchBrowser(server.getURL());
}


void ofApp::draw()
{
    ofBackground(255);
    ofDrawBitmapStringHighlight(userText, ofPoint(14, 18));
}


void ofApp::ping()
{
    pingPlayer.play();
}


void ofApp::pong()
{
    pongPlayer.play();
}


void ofApp::getText(JSONRPC::MethodArgs& args)
{
    // Set the result equal to the substring.
    args.result = getRandomText();
}


void ofApp::setText(JSONRPC::MethodArgs& args)
{
    // Set the user text.
    setUserText(args.params.asString());
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

