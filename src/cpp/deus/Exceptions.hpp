/*!
 * \file
 * \author David Saxon
 * \brief Defines the exceptions that can be thrown by the Deus library.
 *
 * \copyright Copyright (c) 2018, The Arcane Initiative
 *            All rights reserved.
 *
 * \license BSD 3-Clause License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef DEUS_EXCEPTIONS_HPP_
#define DEUS_EXCEPTIONS_HPP_

#include <stdexcept>
#include <string>

// TODO: REMOVE ME
#include <iostream>


namespace deus
{

//------------------------------------------------------------------------------
//                                   DEUS ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Base exception type which is derived from std::runtime_error that all
 *        exceptions thrown by the Deus library inherit from.
 */
class DeusError
    : public std::runtime_error
{
public:

    DeusError(const std::string& what_arg)
        : std::runtime_error(what_arg)
    {
    }

    virtual ~DeusError() throw()
    {
    }
};

//------------------------------------------------------------------------------
//                                   TYPE ERROR
//------------------------------------------------------------------------------

/*!
 * \brief An error specifying that invalid type has been used for an operation.
 */
class TypeError
    : public deus::DeusError
{
public:

    TypeError(const std::string& what_arg)
        : deus::DeusError(what_arg)
    {
    }

    virtual ~TypeError() throw()
    {
    }
};

//------------------------------------------------------------------------------
//                                 ENCODING ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Base exception type that more specific encoding errors are derived
 *        from.
 */
class EncodingError
    : public deus::DeusError
{
public:

    EncodingError(const std::string& what_arg)
        : deus::DeusError(what_arg)
    {
    }

    virtual ~EncodingError() throw()
    {
    }
};

//------------------------------------------------------------------------------
//                                  ASCII ERROR
//------------------------------------------------------------------------------

/*!
 * \brief An error relating to ASCII encoded data.
 */
class ASCIIError
    : public deus::EncodingError
{
public:

    ASCIIError(const std::string& what_arg)
        : deus::EncodingError(what_arg)
    {
    }

    virtual ~ASCIIError() throw()
    {
    }
};

//------------------------------------------------------------------------------
//                                   UTF8 ERROR
//------------------------------------------------------------------------------

/*!
 * \brief An error relating to UTF-8 encoded data.
 */
class UTF8Error
    : public deus::EncodingError
{
public:

    UTF8Error(const std::string& what_arg)
        : deus::EncodingError(what_arg)
    {
        // TODO: REMOVE ME
        std::cout << "UTF8Error what: " << what_arg << std::endl;
    }

    virtual ~UTF8Error() throw()
    {
    }
};

} // namespace deus

#endif
