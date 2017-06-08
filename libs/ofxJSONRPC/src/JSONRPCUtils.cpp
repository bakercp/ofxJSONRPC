//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/JSONRPC/JSONRPCUtils.h"


namespace ofx {
namespace JSONRPC {


std::string JSONRPCUtils::toString(const ofJson& json, bool styled)
{
    std::string raw;

    if (styled)
    {
        raw = json.dump(4);
    }
    else
    {
        raw = json.dump();
    }

    return raw;
}


bool JSONRPCUtils::hasKey(const ofJson& json, const std::string& key)
{
    return json.find(key) != json.end();
}


bool JSONRPCUtils::hasKeyOfType(const ofJson& json,
                                const std::string& key,
                                ofJson::value_t type)
{
    auto i = json.find(key);

    if (i != json.end())
    {
        if (i->type() == type)
        {
            return true;
        }

        return false;
    }

    return false;
}


bool JSONRPCUtils::hasStringKey(const ofJson& json,
                                const std::string& key)
{
    return hasKeyOfType(json, key, ofJson::value_t::string);
}


bool JSONRPCUtils::hasIntegerKey(const ofJson& json,
                                 const std::string& key)
{
    return hasKeyOfType(json, key, ofJson::value_t::number_integer);
}


} } // namespace ofx::JSONRPC
