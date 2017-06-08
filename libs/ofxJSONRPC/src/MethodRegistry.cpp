//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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

        const std::string& method = request.method();

        NoArgMethodMapIter noArgMethodIter = _noArgMethodMap.find(method);

        MethodMapIter methodIter = _methodMap.find(method);

        if (methodIter != _methodMap.end())
        {
            MethodArgs args(request, request.parameters());

            // Argument result is filled in the event notification callback.
            ofNotifyEvent((*methodIter).second->event, args, pSender);

            // If an error is present, then ignore any args.results
            // and return the error response.
            if (Errors::RPC_ERROR_NONE == args.error.code())
            {
                return Response(request,
                                request.id(),
                                args.result);
            }
            else
            {
                // Return the error.
                return Response(request,
                                request.id(),
                                args.error);
            }
        }
        else if (noArgMethodIter != _noArgMethodMap.end())
        {
            if (request.parameters().is_null())
            {
                ofNotifyEvent((*noArgMethodIter).second->event, pSender);

                return Response(request, request.id(), nullptr);
            }
            else
            {
                return Response(request,
                                request.id(),
                                Error(Errors::RPC_ERROR_INVALID_REQUEST,
                                      "This method does not support parameters.",
                                      Request::toJSON(request)));
            }
        }
        else
        {
            return Response(request,
                            request.id(),
                            Error(Errors::RPC_ERROR_METHOD_NOT_FOUND,
                                  Request::toJSON(request)));
        }
    }
    catch (const JSONRPCException& exc)
    {
        return Response(request,
                        request.id(),
                        Error(exc.code(),
                              exc.message()));
    }
    catch (const Poco::InvalidArgumentException& exc)
    {
        return Response(request,
                        request.id(),
                        Error(Errors::RPC_ERROR_INVALID_PARAMETERS,
                              Request::toJSON(request)));
    }
    catch (const Poco::Exception& exc)
    {
        return Response(request,
                        request.id(),
                        Error(Errors::RPC_ERROR_INTERNAL_ERROR,
                              exc.displayText(),
                              Request::toJSON(request)));
    }
    catch (const std::exception& exc)
    {
        return Response(request,
                        request.id(),
                        Error(Errors::RPC_ERROR_INTERNAL_ERROR,
                              exc.what(),
                              Request::toJSON(request)));
    }
    catch ( ... )
    {
        return Response(request,
                        request.id(),
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


MethodRegistry::MethodDescriptionMap MethodRegistry::methods() const
{
    std::unique_lock<std::mutex> lock(_mutex);
    MethodRegistry::MethodDescriptionMap methods;
    
    for (const auto& method: _methodMap)
    {
        methods[method.first] = method.second->description();
    }

    return methods;
}


MethodRegistry::MethodDescriptionMap MethodRegistry::getMethods() const
{
    return methods();
}


} } // namespace ofx::JSONRPC
