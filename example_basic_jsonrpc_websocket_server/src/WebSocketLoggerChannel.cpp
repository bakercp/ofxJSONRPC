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


#include "WebSocketLoggerChannel.h"


WebSocketLoggerChannel::WebSocketLoggerChannel()
{
}


WebSocketLoggerChannel::~WebSocketLoggerChannel()
{
}


void WebSocketLoggerChannel::log(ofLogLevel level,
                                 const std::string& module,
                                 const std::string& message)
{
    std::stringstream ss;

    ss << "[" << ofGetLogLevelName(level, true)  << "] ";
	// only print the module name if it's not ""

    if(module != ""){
		ss << module << ": ";
	}

	ss << message << endl;

    // print to cerr for OF_LOG_ERROR and OF_LOG_FATAL_ERROR, everything else to cout
	ostream& out = level < OF_LOG_ERROR ? cout : cerr;

    out << ss.str();

    ofx::HTTP::WebSocketRoute::SharedPtr route = _webSocketRoute.lock();

    if (route)
    {
        ofBuffer buffer(ss.str());
        ofx::HTTP::WebSocketFrame frame(buffer);
        route->broadcast(frame);
    }
}

void WebSocketLoggerChannel::log(ofLogLevel level,
                                 const std::string& module,
                                 const char* format, ...)
{
	va_list args;
	va_start(args, format);
	log(level, module, format, args);
	va_end(args);
}

void WebSocketLoggerChannel::log(ofLogLevel level,
                                 const std::string& module,
                                 const char* format,
                                 va_list args)
{
	//thanks stefan!
	//http://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html

	FILE* out = level < OF_LOG_ERROR ? stdout : stderr;

	fprintf(out, "[%s] ", ofGetLogLevelName(level, true).c_str());

	if(module != "")
    {
		fprintf(out, "%s: ", module.c_str());
	}

    vfprintf(out, format, args);

	fprintf(out, "\n");
}


void WebSocketLoggerChannel::setWebSocketRoute(ofx::HTTP::WebSocketRoute::SharedPtr webSocketRoute)
{
    _webSocketRoute = webSocketRoute;
}
