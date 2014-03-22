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

    BasicJSONRPCServerSettings settings;

    server = BasicJSONRPCServer::makeShared(settings);

    server->start();

    // Launch a browser with the address of the server.
    ofLaunchBrowser(server->getURL());


    server->registerMethod("get-random-number",
                           "Get a random number.",
                           this,
                           &ofApp::generateRandomNumber);

    server->registerMethod("set-random-number",
                           "Set a random number",
                            this,
                            &ofApp::setRandomNumber);

    server->registerMethod("hi",
                           "hihi",
                           this,
                           &ofApp::notificationHi);

    server->registerMethod("hi2",
                           "hihi",
                           this,
                           &ofApp::notificationHiClient);

}


void ofApp::update()
{
}


void ofApp::draw()
{
    ofBackground(bgColor);
    ofSetColor(255);

    std::map<const WebSocketConnection*, ClientInfo::SharedPtr>::iterator iter = clients.begin();

    int y = 14;

    while (iter != clients.end())
    {
        std::string address = (*iter).first->getClientAddress().toString();

        ofDrawBitmapStringHighlight(address, ofPoint(15, y));

        y+= 14;

        ++iter;
    }

}


//void ofApp::setRandomNumberStream(const void* client, JSONRPC::MethodArgs& args)
//{
//    cout << "got that message " << client << JSONRPC::Utils::toString(args.params) << endl;
//}
//

void ofApp::notificationHiClient(const void* client)
{
    cout << "HI" << " " << client << endl;
}


void ofApp::notificationHi()
{
    cout << "just hi" << endl;
}


void ofApp::generateRandomNumber(const void* client, MethodArgs& args)
{
    args.result = ofRandom(1);
}


void ofApp::setRandomNumber(const void* client, MethodArgs& args)
{
    double d = args.params.isDouble() ? args.params.asDouble() : 0;
    bgColor = ofColor(d * 255);
}



void ofApp::onWebSocketOpenEvent(WebSocketEventArgs& evt)
{
    clients[&evt.getConnectionRef()] = ClientInfo::SharedPtr(new ClientInfo(&evt.getConnectionRef()));
}


void ofApp::onWebSocketCloseEvent(WebSocketEventArgs& evt)
{
    std::map<const WebSocketConnection*, ClientInfo::SharedPtr>::iterator iter = clients.find(&evt.getConnectionRef());

    if (iter != clients.end())
    {
        clients.erase(iter);
    }

    cout << "ofApp::Connection closed from: " << evt.getConnectionRef().getClientAddress().toString() << endl;
}


void ofApp::onWebSocketFrameReceivedEvent(WebSocketFrameEventArgs& evt)
{
    cout << "ofApp::onWebSocketFrameReceivedEvent: " << evt.getConnectionRef().getClientAddress().toString() << endl;
}


void ofApp::onWebSocketFrameSentEvent(WebSocketFrameEventArgs& evt)
{
    cout << "ofApp::onWebSocketFrameSentEvent: " << evt.getConnectionRef().getClientAddress().toString() << endl;
}


void ofApp::onWebSocketErrorEvent(WebSocketEventArgs& evt)
{
    ofLogError("WebSocketMethodRegistry::onWebSocketErrorEvent") << "Error from: " << evt.getConnectionRef().getClientAddress().toString();
}


void ofApp::onHTTPPostEvent(PostEventArgs& args)
{
    ofLogNotice("ofApp::onHTTPPostEvent") << "Data: " << args.data;
}


void ofApp::onHTTPFormEvent(PostFormEventArgs& args)
{
    ofLogNotice("ofApp::onHTTPFormEvent") << "";
    Utils::dumpNameValueCollection(args.form, ofGetLogLevel());
}


void ofApp::onHTTPUploadEvent(PostUploadEventArgs& args)
{
    std::string stateString = "";

    switch (args.getState())
    {
        case PostUploadEventArgs::UPLOAD_STARTING:
            stateString = "STARTING";
            break;
        case PostUploadEventArgs::UPLOAD_PROGRESS:
            stateString = "PROGRESS";
            break;
        case PostUploadEventArgs::UPLOAD_FINISHED:
            stateString = "FINISHED";
            break;
    }

    ofLogNotice("ofApp::onHTTPUploadEvent") << "";
    cout << "         state: " << stateString << endl;
    cout << " formFieldName: " << args.getFormFieldName() << endl;
    cout << "orig. filename: " << args.getOriginalFilename() << endl;
    cout << "      filename: " << args.getFilename() << endl;
    cout << "      fileType: " << args.getFileType().toString() << endl;
    cout << "# bytes xfer'd: " << args.getNumBytesTransferred() << endl;
}
