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


#include "WebSocketMethodRegistry.h"


namespace ofx {


WebSocketMethodRegistry::WebSocketMethodRegistry()
{
}


WebSocketMethodRegistry::~WebSocketMethodRegistry()
{

}


void WebSocketMethodRegistry::onWebSocketOpenEvent(HTTP::WebSocketEventArgs& evt)
{
    cout << "Connection opened from: " << evt.getConnectionRef().getClientAddress().toString() << endl;

//    clients[&evt.getConnectionRef()] = ClientInfo();
}


void WebSocketMethodRegistry::onWebSocketCloseEvent(HTTP::WebSocketEventArgs& evt)
{
    cout << "Connection closed from: " << evt.getConnectionRef().getClientAddress().toString() << endl;
}


void WebSocketMethodRegistry::onWebSocketFrameReceivedEvent(HTTP::WebSocketFrameEventArgs& evt)
{
    Json::Value json;
    Json::Reader reader;

    if (reader.parse(evt.getFrameRef().getText(), json))
    {
        try
        {
            JSONRPC::Request request = JSONRPC::Request::fromJSON(json);
            JSONRPC::Response response = processCall(request);
            if (response.hasID())
            {
                evt.getConnectionRef().sendFrame(response.toString());
            }
        }
        catch (JSONRPC::ParseException& exc)
        {
            JSONRPC::Response response(Json::Value::null, // null value is required when parse exceptions
                                       JSONRPC::Error::METHOD_NOT_FOUND);
            evt.getConnectionRef().sendFrame(response.toString());
        }
    }
    else
    {
        cout << "NOT JSON: " << reader.getFormattedErrorMessages() << endl;
    }
}


void WebSocketMethodRegistry::onWebSocketFrameSentEvent(HTTP::WebSocketFrameEventArgs& evt)
{
    // frame was sent to clients
}


void WebSocketMethodRegistry::onWebSocketErrorEvent(HTTP::WebSocketEventArgs& evt)
{
    cout << "Error from: " << evt.getConnectionRef().getClientAddress().toString() << endl;
}


} // namespace ofx
