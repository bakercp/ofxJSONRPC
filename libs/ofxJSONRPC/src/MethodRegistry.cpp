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
    std::unique_lock<std::mutex> lock(_mutex);

    MethodMapIter methodIter = _methodMap.find(method);

    if (methodIter != _methodMap.end())
    {
        _methodMap.erase(methodIter);
        return;
    }

    NoArgMethodMapIter noArgMethodIter = _noArgMethodMap.find(method);
    
    if (noArgMethodIter != _noArgMethodMap.end())
    {
        _noArgMethodMap.erase(noArgMethodIter);
        return;
    }
}


Response MethodRegistry::processCall(const void* pSender, Request& request)
{
    try
    {
        std::unique_lock<std::mutex> lock(_mutex);

        const std::string& method = request.getMethod();

        NoArgMethodMapIter noArgMethodIter = _noArgMethodMap.find(method);

        MethodMapIter methodIter = _methodMap.find(method);

        if (methodIter != _methodMap.end())
        {
            MethodArgs args(request, request.getParameters());

            // Argument result is filled in the event notification callback.
            ofNotifyEvent((*methodIter).second->event, args, pSender);

            // If an error is present, then ignore any args.results
            // and return the error response.
            if (Errors::RPC_ERROR_NONE == args.error.getCode())
            {
                return Response(request,
                                request.getId(),
                                args.result);
            }
            else
            {
                // Return the error.
                return Response(request,
                                request.getId(),
                                args.error);
            }
        }
        else if (noArgMethodIter != _noArgMethodMap.end())
        {
            if (request.getParameters().isNull())
            {
                ofNotifyEvent((*noArgMethodIter).second->event, pSender);

                return Response(request,
                                request.getId(),
                                Json::Value::null);
            }
            else
            {
                return Response(request,
                                request.getId(),
                                Error(Errors::RPC_ERROR_INVALID_REQUEST,
                                      "This method does not support parameters.",
                                      Request::toJSON(request)));
            }
        }
        else
        {
            return Response(request,
                            request.getId(),
                            Error(Errors::RPC_ERROR_METHOD_NOT_FOUND,
                                  Request::toJSON(request)));
        }
    }
    catch (const JSONRPCException& exc)
    {
        return Response(request,
                        request.getId(),
                        Error(exc.code(),
                              exc.message()));
    }
    catch (const Poco::InvalidArgumentException& exc)
    {
        return Response(request,
                        request.getId(),
                        Error(Errors::RPC_ERROR_INVALID_PARAMETERS,
                              Request::toJSON(request)));
    }
    catch (const Poco::Exception& exc)
    {
        return Response(request,
                        request.getId(),
                        Error(Errors::RPC_ERROR_INTERNAL_ERROR,
                              exc.displayText(),
                              Request::toJSON(request)));
    }
    catch (const std::exception& exc)
    {
        return Response(request,
                        request.getId(),
                        Error(Errors::RPC_ERROR_INTERNAL_ERROR,
                              exc.what(),
                              Request::toJSON(request)));
    }
    catch ( ... )
    {
        return Response(request,
                        request.getId(),
                        Error(Errors::RPC_ERROR_INTERNAL_ERROR,
                              "Unknown Exception",
                              Request::toJSON(request)));
    }
}


void MethodRegistry::processNotification(const void* pSender, Request& request)
{
    processCall(pSender, request); // return nothing
}


bool MethodRegistry::hasMethod(const std::string& method) const
{
    std::unique_lock<std::mutex> lock(_mutex);
    return _methodMap.find(method) != _methodMap.end();
}


MethodRegistry::MethodDescriptionMap MethodRegistry::getMethods() const
{
    MethodRegistry::MethodDescriptionMap methods;
    std::unique_lock<std::mutex> lock(_mutex);
    MethodMap::const_iterator iter = _methodMap.begin();
    while (iter != _methodMap.end())
    {
        methods[(*iter).first] = (*iter).second->getDescription();
        ++iter;
    }
    return methods;
}


} } // namespace ofx::JSONRPC
