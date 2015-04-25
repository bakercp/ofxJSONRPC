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


#include "ofx/JSONRPC/MethodArgs.h"


namespace ofx {
namespace JSONRPC {


MethodArgs::MethodArgs(const Json::Value& params):
    params(params),
    result(Json::Value::null),
    error(Json::Value::null)
{
}


MethodArgs::~MethodArgs()
{
}


std::string MethodArgs::toString(bool styled) const
{
    std::stringstream ss;

    ss << "Params:" << std::endl;
    ss << JSONRPCUtils::toString(params, styled) << std::endl;
    ss << "Results:" << std::endl;
    ss << JSONRPCUtils::toString(result, styled) << std::endl;
    ss << "Error:" << std::endl;
    ss << JSONRPCUtils::toString(error, styled) << std::endl;

    return ss.str();
}


} } // namespace ofx::JSONRPC
