//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(30);

    ofSetLogLevel(OF_LOG_VERBOSE);

    // Load test text.
    ipsum = ofBufferFromFile("media/ipsum.txt").getText();

    // Load test media.
    pingPlayer.load("media/ping.wav");
    pongPlayer.load("media/pong.wav");

    ofx::HTTP::JSONRPCServerSettings settings;
    settings.setPort(8197);

    // Initialize the server.
    server.setup(settings);


    // Register RPC methods.
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

    // Start the server.
    server.start();

    // Launch a browser with the address of the server.
    ofLaunchBrowser(server.url());
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
    ofLogVerbose("ofApp::getText") << args.result.dump(4);
}


void ofApp::setText(ofx::JSONRPC::MethodArgs& args)
{
    // Set the user text.
    setUserText(args.params);
    ofLogVerbose("ofApp::setText") << args.params.dump(4);
}


std::string ofApp::getRandomText() const
{
    static const std::size_t LENGTH = 140;

    std::unique_lock<std::mutex> lock(mutex);

    // Generate a random start index.
    std::size_t startIndex = (std::size_t)ofRandom(ipsum.length());

    // Ensure that the length is valid.
    std::size_t length = (startIndex + LENGTH) < ipsum.length() ? LENGTH : string::npos;

    // return the result equal to the substring.
    return ipsum.substr(startIndex, length);
}


std::string ofApp::getUserText() const
{
    std::unique_lock<std::mutex> lock(mutex);
    return userText;
}


void ofApp::setUserText(const std::string& text)
{
    std::unique_lock<std::mutex> lock(mutex);
    userText = text;
}

