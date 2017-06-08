//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/JSONRPC/MethodArgs.h"


namespace ofx {
namespace JSONRPC {


MethodArgs::MethodArgs(HTTP::ServerEventArgs& evt,
                       const ofJson& params):
    HTTP::ServerEventArgs(evt),
    params(params),
    result(nullptr),
    error(Error())
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
    ss << JSONRPCUtils::toString(Error::toJSON(error), styled) << std::endl;

    return ss.str();
}


} } // namespace ofx::JSONRPC
