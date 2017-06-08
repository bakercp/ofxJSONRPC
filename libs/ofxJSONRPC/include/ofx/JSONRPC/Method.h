//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "json.hpp"
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
            const ofJson& description = nullptr);

    /// \brief Destory the Method.
    virtual ~Method_();

    /// \brief Get the method name.
    /// \returns the name of the method.
    const std::string& name() const;
    OF_DEPRECATED_MSG("Use name() instead.", std::string getName() const);

    /// \brief Get the method's description.
    /// \returns the name of the method.
    const ofJson& description() const;
    OF_DEPRECATED_MSG("Use description() instead.", ofJson getDescription() const);

    /// \brief The public event available for subscription.
    EventType event;

private:
    /// \brief The method's name.
    std::string _name;

    /// \brief A description of the method's functionality.
    ofJson _description;

};


typedef Method_<ofEvent<MethodArgs> > Method;
typedef Method_<ofEvent<void> > NoArgMethod;


template<typename ArgType>
Method_<ArgType>::Method_(const std::string& name,
                          const ofJson& description):
    _name(name),
    _description(description)
{
}


template<typename ArgType>
inline Method_<ArgType>::~Method_()
{
}


template<typename ArgType>
inline const std::string& Method_<ArgType>::name() const
{
    return _name;
}


template<typename ArgType>
inline std::string Method_<ArgType>::getName() const
{
    return _name;
}


template<typename ArgType>
inline const ofJson& Method_<ArgType>::description() const
{
    return _description;
}


template<typename ArgType>
inline ofJson Method_<ArgType>::getDescription() const
{
    return _description;
}


} } // namespace ofx::JSONRPC
