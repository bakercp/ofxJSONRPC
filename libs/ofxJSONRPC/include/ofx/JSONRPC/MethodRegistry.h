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


#pragma once


#if (_MSC_VER)
#include <memory>
#else
#include <tr1/memory>
// import smart pointers utils into std
namespace std {
#if __cplusplus<201103L
	using std::tr1::shared_ptr;
	using std::tr1::weak_ptr;
	using std::tr1::enable_shared_from_this;
#endif
	using std::tr1::static_pointer_cast;
	using std::tr1::dynamic_pointer_cast;
	using std::tr1::const_pointer_cast;
	using std::tr1::__dynamic_cast_tag;
}
#endif


#include <map>
#include <string>
#include <json/json.h>
#include "Poco/Mutex.h"
#include "ofx/JSONRPC/AbstractTypes.h"
#include "ofx/JSONRPC/Method.h"
#include "ofx/JSONRPC/Response.h"
#include "ofx/JSONRPC/Request.h"


namespace ofx {
namespace JSONRPC {


class MethodRegistry
    /// \brief A MethodRegistry is a thread-safe method callback manager.
    /// \details Additionally, a MethodRegistry is in charge of invoking
    ///         methods by name using the method signature defined in Method.
{
public:
    typedef std::map<std::string, Json::Value> MethodDescriptionMap;
        ///< \brief A typedef mapping method names to method descriptions.

    typedef std::map<std::string, Json::Value>::iterator MethodDescriptionMapIter;
        ///< \brief A typedef for a MethodDescriptionMap iterator.

    MethodRegistry();
        ///< \brief Create a MethodRegistry.

    virtual ~MethodRegistry();
        ///< \brief Destroy the MethodRegistry.

    template <typename MethodClass>
    void registerMethod(MethodClass* pObject,
                        typename Method<MethodClass>::MethodPtr pMethod,
                        const std::string& name,
                        const Json::Value& description = Json::Value::null);
        ///< \brief Registers a method callback.
        ///< \param pObject A pointer to the class instance.
        ///< \param pMethod A pointer to the class instance method with the
        ///<        MethodPtr method signature..
        ///< \param name The method's name.
        ///< \param description A description of the method's functionality.

    void unregisterMethod(const std::string& method);
        ///< \brief Unregister a method by name.
        ///< \param method is the name of the method callback to be removed.
        ///< \note If the given method does not exist, the unregister
        ///<        request will be ignored.

    Response processCall(const Request& request);
        ///< \brief Process a Request.
        ///< \param request The incoming Request from a client.
        ///< \returns A success or error Response.

    void processNotification(const Request& request);
        ///< \brief Process a Request.
        ///< \param request The incoming Request from a client.

    bool hasMethod(const std::string& method) const;
        ///< \brief Query the registry for the given method.
        ///< \param method the name of the method to find.
        ///< \returns true iff the given method is in the registry.

    MethodDescriptionMap getMethods() const;
        ///< \brief Get a list of all method names and their descriptions.
        ///< \returns a MethodDescriptionMap containting a map of the
        ///<        method names and the method descriptions.

protected:
    typedef std::shared_ptr<AbstractMethod> SharedMethodPtr;
        ///< \brief A shared pointer typedef to simplify pointer memory management.

    typedef std::map<std::string, SharedMethodPtr> MethodMap;
        ///< \brief A method map.

    typedef std::map<std::string, SharedMethodPtr>::iterator MethodMapIter;
        ///< \brief A method map iterator.

    MethodMap _methodMap;
        ///< \brief Maps method names to their method pointers.

    mutable Poco::Mutex _mutex;
        ///< \brief A mutext to ensure method map validity.
    
};


template <typename MethodClass>
void MethodRegistry::registerMethod(MethodClass* pObject,
                                    typename Method<MethodClass>::MethodPtr pMethod,
                                    const std::string& name,
                                    const Json::Value& description)
{
    SharedMethodPtr p = SharedMethodPtr(new Method<MethodClass>(pObject,
                                                                pMethod,
                                                                name,
                                                                description));

    Poco::Mutex::ScopedLock lock(_mutex);
    _methodMap[name] = p; // shared pointer will release an existing method ptr
}


} } // namespace ofx::JSONRPC
