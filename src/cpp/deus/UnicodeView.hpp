/*!
 * \file
 * \author David Saxon
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
#ifndef DEUS_UNICODEVIEW_HPP_
#define DEUS_UNICODEVIEW_HPP_

#include <cstdint>
#include <string>

#include "deus/Constants.hpp"
#include "deus/UnicodeStorage.hpp"


namespace deus
{

/*!
 * \brief TODO:
 */
class UnicodeView
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    // TODO: DOC
    UnicodeView();

    // TODO: DOC
    // TODO: throw TypeError
    UnicodeView(const char* s, deus::Encoding encoding = deus::SOURCE_ENCODING);

    // TODO: DOC
    // TODO: throw TypeError
    // TODO: figure out byte/length vs c_str_length and null terminator
    UnicodeView(
            const char* s,
            std::size_t c_str_length,
            deus::Encoding encoding = deus::SOURCE_ENCODING);

    // TODO: DOC
    // TODO: throw TypeError
    // TODO: figure out byte/length vs c_str_length and null terminator
    UnicodeView(
            const char* s,
            std::size_t c_str_length,
            std::size_t symbol_length,
            deus::Encoding encoding = deus::SOURCE_ENCODING);

    // TODO:
    // TODO: throw TypeError
    explicit UnicodeView(
            const std::string& s,
            deus::Encoding encoding = deus::SOURCE_ENCODING);

    explicit UnicodeView(const deus::UnicodeStorage& storage);

    // TODO:
    UnicodeView(const UnicodeView& other);

    // TODO:
    UnicodeView(UnicodeView&& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~UnicodeView();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assignment operator.
     */
    UnicodeView& operator=(const UnicodeView& other);

    /*!
     * \brief Move assignment operator.
     */
    UnicodeView& operator=(UnicodeView&& other);

    // TODO: equals should check symbols only...?

    // TODO: +=

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Returns the encoding type used by Unicode string.
     */
    deus::Encoding encoding() const;

    // TODO: is null function

    /*!
     * \brief Returns the number of symbols in the string.
     *
     * This is the number of symbols not the number of bytes. This differs from
     * strlen() or std::string::length() since these function simply return the
     * number of bytes in the string (minus the null terminator). Unicode
     * strings may use multiple bytes to encoding a single character (or symbol)
     * so the symbol length may be different from the byte length.
     *
     * \note For non-ASCII encodings this function will perform lazy computation
     *       to find the number of symbols in the string.
     */
    std::size_t length() const;

    // TODO: DOC
    std::size_t byte_length() const;

    // TODO: DOC
    std::size_t c_str_length() const;

    // TODO: DOC
    const char* c_str() const;

    // TODO: validate encoding

    // TODO: DOC
    deus::UnicodeStorage concatenate(const UnicodeView& s) const;

    // TODO: DOC
    deus::UnicodeStorage to_hex() const;

private:

    //--------------------------------------------------------------------------
    //                              PRIVATE CLASSES
    //--------------------------------------------------------------------------

    class EncodingImpl;
    class ASCIIImpl;
    class UTF8Impl;
    // TODO: other implementations

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // TODO: DOC
    EncodingImpl* m_impl;
};

} // namespace deus

// TODO: could move this to an inline file?

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

// TODO: DOC
inline deus::UnicodeStorage operator+(
        const char* a,
        const deus::UnicodeView& b)
{
    return deus::UnicodeView(a).concatenate(b);
}

// TODO: DOC
inline deus::UnicodeStorage operator+(
        const deus::UnicodeView& a,
        const deus::UnicodeView& b)
{
    return a.concatenate(b);
}

// TODO: DOC
inline deus::UnicodeStorage operator+(
        const deus::UnicodeStorage& a,
        const char* b)
{
    return a.get_view().concatenate(deus::UnicodeView(b));
}

// TODO: DOC
inline deus::UnicodeStorage operator+(
        const deus::UnicodeStorage& a,
        const deus::UnicodeStorage& b)
{
    return a.get_view().concatenate(b.get_view());
}

#endif
