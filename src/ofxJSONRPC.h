//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "json.hpp"
#include "ofxHTTP.h"
#include "ofx/JSONRPC/BaseMessage.h"
#include "ofx/JSONRPC/Error.h"
#include "ofx/JSONRPC/Errors.h"
#include "ofx/JSONRPC/MethodArgs.h"
#include "ofx/JSONRPC/MethodRegistry.h"
#include "ofx/JSONRPC/Request.h"
#include "ofx/JSONRPC/Response.h"
#include "ofx/HTTP/JSONRPCServer.h"

namespace ofxJSONRPC = ofx::JSONRPC;
