/*!
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
#include "deus/unicode_view_impl/UTF8Impl.hpp"

#include <codecvt>
#include <cstring>
#include <locale>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "deus/Constants.hpp"
#include "deus/Exceptions.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN

//------------------------------------------------------------------------------
//                               UTILITY FUNCTIONS
//------------------------------------------------------------------------------

namespace
{

// this performs the same functionality as size_of_symbol, expect it just
// returns the number of bytes of the symbol contained at the start of the given
// data. This means internal functions can use this version the avoid any extra
// overhead and/or cyclic calls
static std::size_t bytes_in_symbol(const char* symbol_data)
{
    if((*symbol_data & 0x80) == 0)
    {
        return 1;
    }
    if((*symbol_data & 0xE0) == 0xC0)
    {
        return 2;
    }
    if((*symbol_data & 0xF0) == 0xE0)
    {
        return 3;
    }
    return 4;
}

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::UTF8Impl::UTF8Impl(
        const deus::UnicodeView& view,
        std::size_t byte_length,
        std::size_t symbol_length,
        const char* s)
    : UnicodeView::EncodingImpl(
        view,
        deus::Encoding::kUTF8,
        byte_length,
        symbol_length,
        s
    )
{
    // this logic needs to be done here on a per-implementation basis since
    // virtual functions (compute_byte_length) shouldn't be called from base
    // class constructors
    if(m_byte_length == deus::NULL_POS)
    {
        compute_byte_length();
    }
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

UnicodeView::UTF8Impl::~UTF8Impl()
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UnicodeView::UTF8Impl::compute_byte_length() const
{
    utf8_inl::compute_byte_length_strlen(m_data, m_byte_length);
}

void UnicodeView::UTF8Impl::compute_symbol_length() const
{
    utf8_inl::compute_symbol_length_word_batching(
        m_data,
        m_byte_length,
        m_symbol_length
    );
}

std::size_t UnicodeView::UTF8Impl::size_of_symbol(
        std::size_t symbol_index) const
{
    if(symbol_index >= m_view.length())
    {
        return deus::NULL_POS;
    }
    // get the byte to check from
    return bytes_in_symbol(m_data + symbol_to_byte_index(symbol_index));
}

std::size_t UnicodeView::UTF8Impl::symbol_to_byte_index(
            std::size_t symbol_index) const
{
    // TODO:
    return utf8_inl::symbol_to_byte_index_naive(m_view, symbol_index);
}

std::size_t UnicodeView::UTF8Impl::byte_to_symbol_index(
        std::size_t byte_index) const
{
    return utf8_inl::byte_to_symbol_index_word_batching(m_view, byte_index);
}

deus::UnicodeStorage UnicodeView::UTF8Impl::convert(
        deus::Encoding encoding) const
{
    switch(encoding)
    {
        case deus::Encoding::kASCII:
        {
            return utf8_inl::convert_to_ascii_naive(
                m_data,
                m_byte_length,
                m_view.length()
            );
        }
        case deus::Encoding::kUTF8:
        {
            // string can be left as is
            return deus::UnicodeStorage(m_view);
        }
        case deus::Encoding::kUTF16_LE:
        {
            throw deus::NotImplementedError(
                "deus::UnicodeView::convert is not yet supported for ASCII "
                "to little endian UTF-16 conversions."
            );
        }
        case deus::Encoding::kUTF16_BE:
        {
            throw deus::NotImplementedError(
                "deus::UnicodeView::convert is not yet supported for ASCII "
                "to big endian UTF-16 conversions."
            );
        }
        case deus::Encoding::kUTF32_LE:
        {
            throw deus::NotImplementedError(
                "deus::UnicodeView::convert is not yet supported for ASCII "
                "to little endian UTF-32 conversions."
            );
        }
        case deus::Encoding::kUTF32_BE:
        {
            throw deus::NotImplementedError(
                "deus::UnicodeView::convert is not yet supported for ASCII "
                "to big endian UTF-32 conversions."
            );
        }
        default:
        {
            throw deus::TypeError(
                "Unrecognized Unicode encoding: " +
                std::to_string(static_cast<unsigned>(encoding))
            );
        }
    }
}

DEUS_VERSION_NS_END
} // namespace deus
