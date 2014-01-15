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


#include <json/json.h>
#include "Poco/Exception.h"
#include "ofx/JSONRPC/AbstractTypes.h"
#include "ofx/JSONRPC/Error.h"
#include "ofx/JSONRPC/MethodArgs.h"


namespace ofx {
namespace JSONRPC {
        

template<class MethodClass>
class Method: public AbstractMethod
    /// \brief A method callback class for registering JSONRPC methods.
{
public:
    typedef bool (MethodClass::*MethodPtr)(MethodArgs& args);
        ///< \brief A typedef for a method signature.
        ///< \details Methods of this type receieve a request.  Upon successful
        ///<        completion of the call, the response object should be filled
        ///<        and the method should return true.  Upon failure, the error
        ///<        object should be filled and the the method shoudl return
        ///<        false.

    Method(MethodClass* pObject,
           MethodPtr pMethod,
           const std::string& name,
           const Json::Value& description = Json::Value::null);
        ///< \brief Create a Method Callback
        ///< \param pObject A pointer to the class instance.
        ///< \param pMethod A pointer to the class instance method with the
        ///<        MethodPtr method signature..
        ///< \param name The method's name.
        ///< \param description A description of the method's functionality.

    virtual ~Method();
        ///< \brief Destory the Method.

    virtual bool invoke(MethodArgs& args);

    virtual std::string getName() const;

    virtual Json::Value getDescription() const;

private:
    MethodClass* _pObject;
        ///< \brief A pointer to the class instance.

    MethodPtr _pMethod;
        ///< \brief A pointer to the class instance method.

    std::string _name;
        ///< \brief The method's name.

    Json::Value _description;
        ///< \brief A description of the method's functionality.

};


template<class MethodClass>
Method<MethodClass>::Method(MethodClass* pObject,
                            MethodPtr pMethod,
                            const std::string& name,
                            const Json::Value& description):
    _pObject(pObject),
    _pMethod(pMethod),
    _name(name),
    _description(description)
{
}


template<class MethodClass>
Method<MethodClass>::~Method()
{
}


template<class MethodClass>
bool Method<MethodClass>::invoke(MethodArgs& args)
{
    return (_pObject->*_pMethod)(args);
}


template<class MethodClass>
std::string Method<MethodClass>::getName() const
{
    return _name;
}


template<class MethodClass>
Json::Value Method<MethodClass>::getDescription() const
{
    return _description;
}


} } // namespace ofx::JSONRPC
