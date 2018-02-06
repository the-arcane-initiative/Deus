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
#include "deus/unicode_view_impl/EncodingImpl.hpp"

#include <cstring>

#include "deus/Constants.hpp"
#include "deus/Exceptions.hpp"
#include "deus/unicode_view_impl/ASCIIImpl.hpp"
#include "deus/unicode_view_impl/UTF8Impl.hpp"


namespace deus
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::EncodingImpl::EncodingImpl(
        const char* s,
        std::size_t byte_length,
        std::size_t symbol_length)
    : m_byte_length  (byte_length)
    , m_symbol_length(symbol_length)
    , m_data         (s)
{
}

UnicodeView::EncodingImpl::EncodingImpl(const EncodingImpl& other)
    : m_byte_length  (other.m_byte_length)
    , m_symbol_length(other.m_symbol_length)
    , m_data         (other.m_data)
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

UnicodeView::EncodingImpl::~EncodingImpl()
{
}

//------------------------------------------------------------------------------
//                            PUBLIC STATIC FUNCTIONS
//------------------------------------------------------------------------------

deus::UnicodeView::EncodingImpl* UnicodeView::EncodingImpl::new_encoding(
        deus::Encoding encoding,
        const char* s,
        std::size_t byte_length,
        std::size_t symbol_length)
{
    switch(encoding)
    {
        case deus::Encoding::kASCII:
        {
            return new deus::UnicodeView::ASCIIImpl(
                s,
                byte_length,
                symbol_length
            );
        }
        case deus::Encoding::kUTF8:
        {
            return new deus::UnicodeView::UTF8Impl(
                s,
                byte_length,
                symbol_length
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

deus::UnicodeView::EncodingImpl* UnicodeView::EncodingImpl::copy_encoding(
        deus::Encoding encoding,
        const EncodingImpl* other)
{
    switch(encoding)
    {
        case deus::Encoding::kASCII:
        {
            return new deus::UnicodeView::ASCIIImpl(
                *static_cast<const deus::UnicodeView::ASCIIImpl*>(other)
            );
        }
        case deus::Encoding::kUTF8:
        {
            return new deus::UnicodeView::UTF8Impl(
                *static_cast<const deus::UnicodeView::UTF8Impl*>(other)
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

std::size_t UnicodeView::EncodingImpl::null_terminator_size(
        deus::Encoding encoding)
{
    switch(encoding)
    {
        case deus::Encoding::kASCII:
        {
            return 1;
        }
        case deus::Encoding::kUTF8:
        {
            return 1;
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

} // namespace deus
