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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8IMPL_HPP_
#define DEUS_UNICODEVIEWIMPL_UTF8IMPL_HPP_

#include "deus/API.h"
#include "deus/UnicodeView.hpp"
#include "deus/unicode_view_impl/EncodingImpl.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN

/*!
 * \brief The implementation of UTF-8 encoding specific logic for the
 *        deus::UnicodeView class.
 */
class UnicodeView::UTF8Impl
    : public UnicodeView::EncodingImpl
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Constructs a new UTF-8 encoding implementation using he given
     *        parameters.
     */
    UTF8Impl(
            const deus::UnicodeView& view,
            std::size_t byte_length,
            std::size_t symbol_length,
            const char* s);

    // deleted
    UTF8Impl(const UTF8Impl&) = delete;
    UTF8Impl(UTF8Impl&&) = delete;

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~UTF8Impl();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    // deleted
    UTF8Impl& operator=(const UTF8Impl&) = delete;
    UTF8Impl& operator=(UTF8Impl&&) = delete;
    bool operator==(const UTF8Impl&) const = delete;
    bool operator!=(const UTF8Impl&) const = delete;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void compute_byte_length() const override;

    virtual void compute_symbol_length() const override;

    virtual std::size_t size_of_symbol(std::size_t symbol_index) const override;

    virtual std::size_t symbol_to_byte_index(
            std::size_t symbol_index) const override;

    virtual std::size_t byte_to_symbol_index(
            std::size_t byte_index) const override;

    virtual deus::UnicodeStorage convert(
            deus::Encoding encoding) const override;
};

DEUS_VERSION_NS_END
} // namespace deus

//------------------------------------------------------------------------------
//                             INLINE IMPLEMENTATIONS
//------------------------------------------------------------------------------

#include "deus/unicode_view_impl/UTF8Util.inl"
#include "deus/unicode_view_impl/UTF8FromCodePoint.inl"
#include "deus/unicode_view_impl/UTF8ComputeByteLength.inl"
#include "deus/unicode_view_impl/UTF8ComputeSymbolLength.inl"
#include "deus/unicode_view_impl/UTF8SymbolToByteIndex.inl"
#include "deus/unicode_view_impl/UTF8ByteToSymbolIndex.inl"
#include "deus/unicode_view_impl/UTF8ConvertToASCII.inl"


#endif
