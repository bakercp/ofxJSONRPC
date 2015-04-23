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
#include "ofx/JSONRPC/Error.h"
#include "ofx/JSONRPC/MethodArgs.h"


namespace ofx {
namespace JSONRPC {


/// \brief A method callback class for registering JSONRPC methods.
template<typename EventType>
class Method_
{
public:
    /// \brief Create a Method Callback
    /// \param name The method's name.
    /// \param description A description of the method's functionality.
    Method_(const std::string& name,
            const Json::Value& description = Json::Value::null);

    /// \brief Destory the Method.
    virtual ~Method_();

    /// \brief Get the method name.
    /// \returns the name of the method.
    std::string getName() const;

    /// \brief Get the method's description.
    /// \returns the name of the method.
    Json::Value getDescription() const;

    /// \brief The public event available for subscription.
    EventType event;

private:
    /// \brief The method's name.
    std::string _name;

    /// \brief A description of the method's functionality.
    Json::Value _description;

};


typedef Method_<ofEvent<MethodArgs> > Method;
typedef Method_<ofEvent<void> > NoArgMethod;


template<typename ArgType>
Method_<ArgType>::Method_(const std::string& name,
                          const Json::Value& description):
    _name(name),
    _description(description)
{
}


template<typename ArgType>
inline Method_<ArgType>::~Method_()
{
}


template<typename ArgType>
inline std::string Method_<ArgType>::getName() const
{
    return _name;
}


template<typename ArgType>
inline Json::Value Method_<ArgType>::getDescription() const
{
    return _description;
}


} } // namespace ofx::JSONRPC
