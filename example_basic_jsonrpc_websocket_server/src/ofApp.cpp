// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
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

    HTTP::BasicWebSocketServerSettings settings;
    server = HTTP::BasicWebSocketServer::makeShared(settings);

    server->getWebSocketRoute()->registerWebSocketEvents(&wsMethodRegistry);
    server->start();

    // Launch a browser with the address of the server.
//    ofLaunchBrowser(server->getURL());

    wsMethodRegistry.registerMethod(this,
                                    &ofApp::generateRandomNumber,
                                    "get-random-number");


    wsMethodRegistry.registerMethod(this,
                                    &ofApp::setRandomNumber,
                                    "set-random-number");

}

void ofApp::update()
{
//    server->getWebSocketRoute()->getSessionManagerRef().
}


void ofApp::draw()
{
    ofBackground(bgColor);
    ofSetColor(255);
}


bool ofApp::generateRandomNumber(JSONRPC::MethodArgs& args)
{
    args.result = ofRandom(1);
    return true;
}

bool ofApp::setRandomNumber(JSONRPC::MethodArgs& args)
{
    double d = args.params.isDouble() ? args.params.asDouble() : 0;

    bgColor = ofColor(d * 255);

    return true;
}

