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
        const char* s,
        std::size_t byte_length,
        std::size_t symbol_length)
    : UnicodeView::EncodingImpl(s, byte_length, symbol_length)
{
    // this logic needs to be done here on a per-implementation basis since
    // virtual functions (compute_byte_length) shouldn't be called from base
    // class constructors
    if(m_byte_length == deus::NULL_POS)
    {
        compute_byte_length();
    }
}

UnicodeView::UTF8Impl::UTF8Impl(const UTF8Impl& other)
    : UnicodeView::EncodingImpl(other)
{
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

void UnicodeView::UTF8Impl::compute_byte_length()
{
    // null data
    if(m_data == nullptr)
    {
        m_byte_length = 0;
        m_symbol_length = 0;
        return;
    }

    // even though we could just use strlen on a UTF-8 string - we should
    // instead compute both raw length and symbol at the same time so this
    // iteration only has to happen once.
    const char* c = m_data;
    // TODO: this can be heavily optimized
    while(*c != 0x0)
    {

        // as the prophecy foretold
        c++;
    }
    // increment the raw length
}

void UnicodeView::UTF8Impl::compute_symbol_length()
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
        for(const char* c = m_data; c < m_data + m_byte_length - 1;)
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

            // TODO: need plus operator
            // TODO: continue here - need hex converter
            throw deus::UTF8Error(
                "Invalid leading byte in UTF-8 string: '" + character
            );
        }
    }
}

} // namespace deus
