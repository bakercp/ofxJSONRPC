//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <map>
#include <string>
#include "json.hpp"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofx/JSONRPC/Method.h"
#include "ofx/JSONRPC/MethodArgs.h"
#include "ofx/JSONRPC/Response.h"
#include "ofx/JSONRPC/Request.h"


namespace ofx {
namespace JSONRPC {


/// \brief A MethodRegistry is a thread-safe method callback manager.
///
/// Additionally, a MethodRegistry is in charge of invoking methods by
/// name using the method signature defined in Method.
class MethodRegistry
{
public:
    /// \brief A typedef mapping method names to method descriptions.
    typedef std::map<std::string, ofJson> MethodDescriptionMap;

    /// \brief Create a MethodRegistry.
    MethodRegistry();

    /// \brief Destroy the MethodRegistry.
    virtual ~MethodRegistry();

    /// \brief Register a method callback.
    ///
    /// Each method needs a name, description, class and method.  This method
    /// registers remote methods with the following signature:
    ///
    /// ~~~{.cpp}
    ///     void ListenerClass::listenerMethod(const void* pSender, MethodArgs& args);
    /// ~~~
    ///
    /// \param name The name of the class to be called by the client.
    /// \param description A JSON description of any information to
    ///        advertise with this method.  This might include a
    ///        description of the functionality, the input / output
    ///        arguments, expected values, etc.
    /// \param listener A pointer to the listener class.
    /// \param listenerMethod A pointer to the method to invoke.
    /// \param priority The priority of the event.
    template <class ListenerClass>
    void registerMethod(const std::string& name,
                        const ofJson& description,
                        ListenerClass* listener,
                        void (ListenerClass::*listenerMethod)(const void*, MethodArgs&),
                        int priority = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Register a method callback.
    ///
    /// Each method needs a name, description, class and method.  This method
    /// registers remote methods with the following signature:
    ///
    /// ~~~{.cpp}
    ///    void ListenerClass::listenerMethod(MethodArgs& args);
    /// ~~~
    ///
    /// \param name The name of the class to be called by the client.
    /// \param description A JSON description of any information to
    ///        advertise with this method.  This might include a
    ///        description of the functionality, the input / output
    ///        arguments, expected values, etc.
    /// \param listener A pointer to the listener class.
    /// \param listenerMethod A pointer to the method to invoke.
    /// \param priority The priority of the event.
    template <class ListenerClass>
    void registerMethod(const std::string& name,
                        const ofJson& description,
                        ListenerClass* listener,
                        void (ListenerClass::*listenerMethod)(MethodArgs&),
                        int priority = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Register a no argument method callback.
    ///
    /// Each method needs a name, description, class and method. This method
    /// registers remote methods with the following signature:
    ///
    /// ~~~{.cpp}
    ///    void ListenerClass::listenerMethod(const void* pSender);
    /// ~~~
    ///
    /// \param name The name of the class to be called by the client.
    /// \param description A JSON description of any information to
    ///        advertise with this method.  This might include a
    ///        description of the functionality, the input / output
    ///        arguments, expected values, etc.
    /// \param listener A pointer to the listener class.
    /// \param listenerMethod A pointer to the method to invoke.
    /// \param priority The priority of the event.
    template <class ListenerClass>
    void registerMethod(const std::string& name,
                        const ofJson& description,
                        ListenerClass* listener,
                        void (ListenerClass::*listenerMethod)(const void*),
                        int priority = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Register a no argument method callback.
    ///
    /// Each method needs a name, description, class and method. This method
    /// registers remote methods with the following signature:
    ///
    /// ~~~{.cpp}
    ///    void ListenerClass::listenerMethod();
    /// ~~~
    ///
    /// \param name The name of the class to be called by the client.
    /// \param description A JSON description of any information to
    ///        advertise with this method.  This might include a
    ///        description of the functionality, the input / output
    ///        arguments, expected values, etc.
    /// \param listener A pointer to the listener class.
    /// \param listenerMethod A pointer to the method to invoke.
    /// \param priority The priority of the event.
    template <class ListenerClass>
    void registerMethod(const std::string& name,
                        const ofJson& description,
                        ListenerClass* listener,
                        void (ListenerClass::*listenerMethod)(void),
                        int priority = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Unregister a method by name.
    /// \param method is the name of the method callback to be removed.
    /// \note If the given method does not exist, the unregister
    ///        request will be ignored.
    void unregisterMethod(const std::string& method);

    /// \brief Process a Request.
    /// \param pSender A pointer to the sender.  This might be a pointer
    ///        to a session cookie or WebSocket connection.  While not
    ///        required, this pointer is useful for returning
    ///        client-specific method results or responding updating
    ///        the calling client's session information.  The user is
    ///        responsible for using this sender information in
    ///        corresponding method callback.
    /// \param request The incoming Request from a client.
    /// \returns A success or error Response.
    Response processCall(const void* pSender, Request& request);

    /// \brief Process a Request.
    /// \param pSender A pointer to the sender.  This might be a pointer
    ///        to a session cookie or WebSocket connection.  While not
    ///        required, this pointer is useful for returning
    ///        client-specific method results or responding updating
    ///        the calling client's session information.  The user is
    ///        responsible for using this sender information in
    ///        corresponding method callback.
    /// \param request The incoming Request from a client.
    void processNotification(const void* pSender, Request& request);

    /// \brief Query the registry for the given method.
    /// \param method the name of the method to find.
    /// \returns true iff the given method is in the registry.
    bool hasMethod(const std::string& method) const;

    /// \brief Get a list of all method names and their descriptions.
    /// \returns a MethodDescriptionMap containting a map of the
    ///        method names and the method descriptions.
    MethodDescriptionMap methods() const;
    OF_DEPRECATED_MSG("Use methods() instead.", MethodDescriptionMap getMethods() const);

protected:
    /// \brief A shared pointer typedef for methods;
    typedef std::shared_ptr<Method> SharedMethodPtr;

    /// \brief A shared pointer typedef for no argument methods;
    typedef std::shared_ptr<NoArgMethod> SharedNoArgMethodPtr;

    /// \brief A method map.
    typedef std::map<std::string, SharedMethodPtr> MethodMap;

    /// \brief A void no argument method map.
    typedef std::map<std::string, SharedNoArgMethodPtr> NoArgMethodMap;

    /// \brief A method map iterator.
    typedef MethodMap::iterator MethodMapIter;

    /// \brief A no argument method map iterator.
    typedef NoArgMethodMap::iterator NoArgMethodMapIter;

    /// \brief Maps method names to their method pointers.
    MethodMap _methodMap;

    /// \brief Maps no argument method names to their method pointers.
    NoArgMethodMap _noArgMethodMap;

    /// \brief A mutext to ensure method map validity.
    mutable std::mutex _mutex;

};


template <class ListenerClass>
void MethodRegistry::registerMethod(const std::string& name,
                                    const ofJson& description,
                                    ListenerClass* listener,
                                    void (ListenerClass::*listenerMethod)(const void*, MethodArgs&),
                                    int priority)
{
    unregisterMethod(name);

    std::unique_lock<std::mutex> lock(_mutex);
    _methodMap[name] = SharedMethodPtr(new Method(name, description));
    _methodMap[name]->event.add(listener, listenerMethod, priority);
}

template <class ListenerClass>
void MethodRegistry::registerMethod(const std::string& name,
                                    const ofJson& description,
                                    ListenerClass* listener,
                                    void (ListenerClass::*listenerMethod)(MethodArgs&),
                                    int priority)
{
    unregisterMethod(name);

    std::unique_lock<std::mutex> lock(_mutex);
    _methodMap[name] = SharedMethodPtr(new Method(name, description));
    _methodMap[name]->event.add(listener, listenerMethod, priority);
}

template <class ListenerClass>
void MethodRegistry::registerMethod(const std::string& name,
                                    const ofJson& description,
                                    ListenerClass* listener,
                                    void (ListenerClass::*listenerMethod)(const void*),
                                    int priority)
{
    unregisterMethod(name);

    std::unique_lock<std::mutex> lock(_mutex);
    _noArgMethodMap[name] = SharedNoArgMethodPtr(new NoArgMethod(name, description));
    _noArgMethodMap[name]->event.add(listener, listenerMethod, priority);
}

template <class ListenerClass>
void MethodRegistry::registerMethod(const std::string& name,
                                    const ofJson& description,
                                    ListenerClass* listener,
                                    void (ListenerClass::*listenerMethod)(void),
                                    int priority)
{
    unregisterMethod(name);

    std::unique_lock<std::mutex> lock(_mutex);
    _noArgMethodMap[name] = SharedNoArgMethodPtr(new NoArgMethod(name, description));
    _noArgMethodMap[name]->event.add(listener, listenerMethod, priority);
}


} } // namespace ofx::JSONRPC
