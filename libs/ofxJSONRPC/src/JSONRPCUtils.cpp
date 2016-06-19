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
