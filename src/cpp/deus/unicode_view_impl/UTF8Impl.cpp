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

#include <sstream>

#include "deus/Constants.hpp"
#include "deus/Exceptions.hpp"


namespace deus
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::UTF8Impl::UTF8Impl(
        std::size_t byte_length,
        std::size_t symbol_length,
        const char* s)
    : UnicodeView::EncodingImpl(
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
    utf8_impl::compute_byte_length_naive(
        m_data,
        m_byte_length,
        m_symbol_length
    );
}

void UnicodeView::UTF8Impl::compute_symbol_length() const
{
    // just use raw length
    if(m_byte_length == 0)
    {
        m_symbol_length = 0;
    }
    else
    {
        m_symbol_length = 0;

        // TODO: need to keep this implementation for benching marking
        // TODO: can be heavily optmised
        // for(std::size_t i = 0; i < m_byte_length; ++i)
        for(const char* c = m_data; c != (m_data + m_byte_length - 1);)
        {
            // TODO: validate data

            ++m_symbol_length;
            // single character byte
            if((*c & 0x80) == 0)
            {
                ++c;
                continue;
            }
            // 2 byte character
            if((*c & 0xE0) == 0xC0)
            {
                c += 2;
                continue;
            }
            // 3 byte character
            if((*c & 0xF0) == 0xE0)
            {
                c += 3;
                continue;
            }
            // 4 byte character
            if((*c & 0xF8) == 0xF0)
            {
                c += 4;
                continue;
            }

            deus::UnicodeView character(c, 1, deus::Encoding::kASCII);
            throw deus::UTF8Error(
                "Invalid leading byte in UTF-8 string: '" + character + ": <" +
                character.to_hex() + ">"
            );
        }
    }
}

//------------------------------------------------------------------------------
//                                GLOBAL FUNCTIONS
//------------------------------------------------------------------------------

namespace utf8_impl
{

//---------------------COMPUTE BYTE LENGTH IMPLEMENTATIONS----------------------

void compute_byte_length_naive(
        const char* in_data,
        std::size_t& out_byte_length,
        std::size_t& out_symbol_length)
{
    out_byte_length = 0;
    out_symbol_length = 0;
    // null data?
    if(in_data == nullptr)
    {
        return;
    }

    // even though we could just use strlen on a UTF-8 string - we should
    // instead compute both byte length and symbol at the same time so this
    // iteration only has to happen once.
    const char* c = in_data;
    std::size_t next_check = 0;
    while(*c != 0x0)
    {
        // determine UTF-8 symbols
        if(next_check <= 0)
        {
            // single character byte
            if((*c & 0x80) == 0)
            {
                next_check = 0;
            }
            // 2 byte character
            else if((*c & 0xE0) == 0xC0)
            {
                next_check = 1;
            }
            // 3 byte character
            else if((*c & 0xF0) == 0xE0)
            {
                out_symbol_length += 3;
                next_check = 2;
            }
            // 4 byte character
            else if((*c & 0xF8) == 0xF0)
            {
                out_symbol_length += 4;
                next_check = 3;
            }
            else
            {
                deus::UnicodeView character(c, 1, deus::Encoding::kASCII);
                throw deus::UTF8Error(
                    "Invalid leading byte in UTF-8 string: '" + character +
                    ": <" + character.to_hex() + ">"
                );
            }

            out_symbol_length += next_check + 1;
        }
        else
        {
            --next_check;
        }

        // as the prophecy foretold
        c++;
        ++out_byte_length;
    }
    // increment one more time for the null terminator
    ++out_byte_length;
}

} // namespace utf8_impl
} // namespace deus
