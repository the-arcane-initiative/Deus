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


namespace deus
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::ASCIIImpl::ASCIIImpl(
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

UnicodeView::ASCIIImpl::ASCIIImpl(const ASCIIImpl& other)
    : UnicodeView::EncodingImpl(other)
{
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

void UnicodeView::ASCIIImpl::compute_byte_length()
{
    if(m_data == nullptr)
    {
        m_byte_length = 0;
        m_symbol_length = 0;
        return;
    }
    // can just use strlen here (maybe use FFS length if its faster?)
    m_symbol_length = strlen(m_data);
    m_byte_length = m_symbol_length + 1;
}

void UnicodeView::ASCIIImpl::compute_symbol_length()
{
    // just use raw length
    if(m_byte_length == 0)
    {
        m_symbol_length = 0;
    }
    else
    {
        m_symbol_length = m_byte_length - 1;
    }
}

} // namespace deus
