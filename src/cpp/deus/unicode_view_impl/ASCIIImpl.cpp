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
#include "deus/unicode_view_impl/ASCIIImpl.hpp"

#include <cstring>

#include "deus/Constants.hpp"
#include "deus/Exceptions.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::ASCIIImpl::ASCIIImpl(
        const deus::UnicodeView& view,
        std::size_t byte_length,
        std::size_t symbol_length,
        const char* s)
    : UnicodeView::EncodingImpl(
        view,
        deus::Encoding::kASCII,
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

UnicodeView::ASCIIImpl::~ASCIIImpl()
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UnicodeView::ASCIIImpl::compute_byte_length() const
{
    ascii_inl::compute_byte_length_strlen(m_data, m_byte_length);
}

void UnicodeView::ASCIIImpl::compute_symbol_length() const
{
    // just use byte length
    if(m_byte_length == 0)
    {
        m_symbol_length = 0;
    }
    else
    {
        m_symbol_length = m_byte_length - 1;
    }
}

std::size_t UnicodeView::ASCIIImpl::size_of_symbol(
        std::size_t symbol_index) const
{
    // all symbols are exactly one byte
    return 1;
}

std::size_t UnicodeView::ASCIIImpl::symbol_to_byte_index(
            std::size_t symbol_index) const
{
    // nothing clever needs doing for ASCII
    return symbol_index;
}

std::size_t UnicodeView::ASCIIImpl::byte_to_symbol_index(
        std::size_t byte_index) const
{
    // nothing clever needs doing for ASCII
    return byte_index;
}

deus::UnicodeStorage UnicodeView::ASCIIImpl::convert(
        deus::Encoding encoding) const
{
    switch(encoding)
    {
        case deus::Encoding::kASCII:
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
