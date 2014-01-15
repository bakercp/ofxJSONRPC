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


#include "ofx/JSONRPC/MethodRegistry.h"


namespace ofx {
namespace JSONRPC {


MethodRegistry::MethodRegistry()
{
}


MethodRegistry::~MethodRegistry()
{
}


void MethodRegistry::unregisterMethod(const std::string& method)
{
    Poco::Mutex::ScopedLock lock(_mutex);
    MethodMapIter iter = _methodMap.find(method);
    if (iter != _methodMap.end())
    {
        _methodMap.erase(iter);
    }
}


Response MethodRegistry::processCall(const Request& request)
{
    Poco::Mutex::ScopedLock lock(_mutex);
    MethodMapIter iter = _methodMap.find(request.getMethod());
    if (iter != _methodMap.end())
    {
        SharedMethodPtr pMethod = (*iter).second;

        MethodArgs args(request.getParameters());

        if (pMethod->invoke(args))
        {
            return Response(request.getID(), args.result);
        }
        else
        {
            return Response(request.getID(),
                            Error(Errors::RPC_ERROR_INVALID_REQUEST,
                                  args.error));
        }
    }
    else
    {
        return Response(request.getID(), // if there is one
                        Error(Errors::RPC_ERROR_METHOD_NOT_FOUND));
    }
}


void MethodRegistry::processNotification(const Request& request)
{
    processCall(request); // return nothing
}


bool MethodRegistry::hasMethod(const std::string& method) const
{
    Poco::Mutex::ScopedLock lock(_mutex);
    return _methodMap.find(method) != _methodMap.end();
}


MethodRegistry::MethodDescriptionMap MethodRegistry::getMethods() const
{
    MethodRegistry::MethodDescriptionMap methods;
    Poco::Mutex::ScopedLock lock(_mutex);
    MethodMap::const_iterator iter = _methodMap.begin();
    while (iter != _methodMap.end())
    {
        methods[(*iter).first] = (*iter).second->getDescription();
        ++iter;
    }

    return methods;
}


} } // namespace ofx::JSONRPC
