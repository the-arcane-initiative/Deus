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
#include "deus/UnicodeView.hpp"

#include <cstring>
#include <iomanip>
#include <sstream>

#include "deus/unicode_view_impl/EncodingImpl.hpp"


namespace deus
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::UnicodeView()
    : m_encoding(deus::Encoding::kUTF8)
    , m_impl    (nullptr)
{
    m_impl = EncodingImpl::new_encoding(m_encoding, nullptr, 0, 0);
}

UnicodeView::UnicodeView(const char* s, deus::Encoding encoding)
    : m_encoding(encoding)
    , m_impl    (nullptr)
{
    m_impl = EncodingImpl::new_encoding(
        m_encoding,
        s,
        deus::NULL_POS,
        deus::NULL_POS
    );
}

UnicodeView::UnicodeView(
        const char* s,
        std::size_t c_str_length,
        deus::Encoding encoding)
    : m_encoding(encoding)
    , m_impl    (nullptr)
{
    m_impl = EncodingImpl::new_encoding(
        m_encoding,
        s,
        c_str_length + EncodingImpl::null_terminator_size(m_encoding),
        deus::NULL_POS
    );
}

UnicodeView::UnicodeView(
        const char* s,
        std::size_t c_str_length,
        std::size_t symbol_length,
        deus::Encoding encoding)
    : m_encoding(encoding)
    , m_impl    (nullptr)
{
    m_impl = EncodingImpl::new_encoding(
        m_encoding,
        s,
        c_str_length + EncodingImpl::null_terminator_size(m_encoding),
        symbol_length
    );
}

UnicodeView::UnicodeView(const std::string& s, deus::Encoding encoding)
    : m_encoding(encoding)
    , m_impl    (nullptr)
{
    m_impl = EncodingImpl::new_encoding(
        m_encoding,
        s.c_str(),
        s.length() + EncodingImpl::null_terminator_size(m_encoding),
        deus::NULL_POS
    );
}

UnicodeView::UnicodeView(const UnicodeView& other)
    : m_encoding(other.m_encoding)
    , m_impl    (nullptr)
{
    m_impl = EncodingImpl::copy_encoding(m_encoding, other.m_impl);
}

UnicodeView::UnicodeView(UnicodeView&& other)
    : m_encoding  (other.m_encoding)
    , m_impl      (other.m_impl)
{
    other.m_encoding   = deus::Encoding::kASCII;
    other.m_impl       = nullptr;
}

//------------------------------------------------------------------------------
//                                  DESTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::~UnicodeView()
{
    if(m_impl != nullptr)
    {
        delete m_impl;
    }
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

UnicodeView& UnicodeView::operator=(const UnicodeView& other)
{
    m_encoding = other.m_encoding;
    m_impl = EncodingImpl::copy_encoding(m_encoding, other.m_impl);

    return *this;
}

UnicodeView& UnicodeView::operator=(UnicodeView&& other)
{
    m_encoding   = other.m_encoding;
    m_impl       = other.m_impl;

    return *this;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

deus::Encoding UnicodeView::encoding() const
{
    return m_encoding;
}

std::size_t UnicodeView::length() const
{
    // lazy compute length?
    if(m_impl->m_symbol_length == deus::NULL_POS)
    {
        m_impl->compute_symbol_length();
    }
    return m_impl->m_symbol_length;
}

std::size_t UnicodeView::byte_length() const
{
    return m_impl->m_byte_length;
}

std::size_t UnicodeView::c_str_length() const
{
    if(m_impl->m_byte_length == 0)
    {
        return 0;
    }
    return
        m_impl->m_byte_length - EncodingImpl::null_terminator_size(m_encoding);
}

const char* UnicodeView::c_str() const
{
    return m_impl->m_data;
}

deus::UnicodeStorage UnicodeView::concatenate(const UnicodeView& s) const
{
    // TODO:
    return deus::UnicodeStorage("TODO: implement concatenate");
}

deus::UnicodeStorage UnicodeView::to_hex() const
{
    // this function doesn't require a encoding specific implementation
    // TODO: can potentially write code faster than std::hex?
    std::stringstream ss;
    ss
        << std::hex << std::uppercase
        << std::string(m_impl->m_data, m_impl->m_byte_length);
    return UnicodeView(ss.str(), deus::Encoding::kASCII);
}

} // namespace deus
