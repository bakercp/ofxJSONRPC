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
        

class Method: public AbstractMethod
    /// \brief A method callback class for registering JSONRPC methods.
{
public:
    Method(const std::string& name,
           const Json::Value& description = Json::Value::null);
        ///< \brief Create a Method Callback
        ///< \param pObject A pointer to the class instance.
        ///< \param pMethod A pointer to the class instance method with the
        ///<        MethodPtr method signature..
        ///< \param name The method's name.
        ///< \param description A description of the method's functionality.

    virtual ~Method();
        ///< \brief Destory the Method.

    virtual std::string getName() const;

    virtual Json::Value getDescription() const;

private:
    std::string _name;
        ///< \brief The method's name.

    Json::Value _description;
        ///< \brief A description of the method's functionality.

};


inline Method::Method(const std::string& name,
                            const Json::Value& description):
    _name(name),
    _description(description)
{
}


inline Method::~Method()
{
}


inline std::string Method::getName() const
{
    return _name;
}


inline Json::Value Method::getDescription() const
{
    return _description;
}


} } // namespace ofx::JSONRPC
