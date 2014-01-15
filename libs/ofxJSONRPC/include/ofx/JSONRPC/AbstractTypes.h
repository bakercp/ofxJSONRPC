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


#include <string>


namespace ofx {
namespace JSONRPC {


class MethodArgs;


class AbstractMethod
    /// \brief An abstract interface for method registration.
{
public:
    virtual ~AbstractMethod()
        ///< \brief Destroy the AbstractMethod.
    {
    }

    virtual bool invoke(MethodArgs& args) = 0;
        ///< \brief Invoke the method defined in this callback.
        ///< \param request the request parameters.
        ///< \param response the response data to be filled if needed.
        ///< \param error the error data to be filled if needed.
        ///< \returns true iff the method invocation was successful.
        ///< \note If the invocation was not successful, invoke will return
        ///<        false.  If needed, the invoked method can fill in the
        ///<        error data as well.

    virtual std::string getName() const = 0;
        ///< \brief Get the method name.
        ///< \returns the name of the method.

    virtual Json::Value getDescription() const = 0;
        ///< \brief Get the method's description.
        ///< \returns the name of the method.

};


} } // namespace ofx::JSONRPC
