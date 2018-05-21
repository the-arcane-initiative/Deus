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

#include "deus/Exceptions.hpp"
#include "deus/unicode_view_impl/EncodingImpl.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::UnicodeView()
    : m_impl(nullptr)
{
    m_impl = EncodingImpl::new_encoding(
        *this,
        "",
        1,
        0,
        deus::Encoding::kUTF8
    );
}

UnicodeView::UnicodeView(const char* s, deus::Encoding encoding)
    : m_impl(nullptr)
{
    // don't allow null strings
    if(s == nullptr)
    {
        throw deus::ValueError(
            "UnicodeView cannot be constructed using a null pointer"
        );
    }

    m_impl = EncodingImpl::new_encoding(
        *this,
        s,
        deus::NULL_POS,
        deus::NULL_POS,
        encoding
    );
}

UnicodeView::UnicodeView(
        const char* s,
        std::size_t c_str_length,
        deus::Encoding encoding)
    : m_impl(nullptr)
{
    // don't allow null strings
    if(s == nullptr)
    {
        throw deus::ValueError(
            "UnicodeView cannot be constructed using a null pointer"
        );
    }

    m_impl = EncodingImpl::new_encoding(
        *this,
        s,
        c_str_length + EncodingImpl::null_terminator_size(encoding),
        deus::NULL_POS,
        encoding
    );
}

UnicodeView::UnicodeView(
        const char* s,
        std::size_t c_str_length,
        std::size_t symbol_length,
        deus::Encoding encoding)
    : m_impl(nullptr)
{
    // don't allow null strings
    if(s == nullptr)
    {
        throw deus::ValueError(
            "UnicodeView cannot be constructed using a null pointer"
        );
    }

    m_impl = EncodingImpl::new_encoding(
        *this,
        s,
        c_str_length + EncodingImpl::null_terminator_size(encoding),
        symbol_length,
        encoding
    );
}

UnicodeView::UnicodeView(const std::string& s, deus::Encoding encoding)
    : m_impl(nullptr)
{
    m_impl = EncodingImpl::new_encoding(
        *this,
        s.c_str(),
        s.length() + EncodingImpl::null_terminator_size(encoding),
        deus::NULL_POS,
        encoding
    );
}

UnicodeView::UnicodeView(
        const std::string& s,
        std::size_t symbol_length,
        deus::Encoding encoding)
    : m_impl(nullptr)
{
    m_impl = EncodingImpl::new_encoding(
        *this,
        s.c_str(),
        s.length() + EncodingImpl::null_terminator_size(encoding),
        symbol_length,
        encoding
    );
}

UnicodeView::UnicodeView(const deus::UnicodeStorage& storage)
    : m_impl(storage.get_view().m_impl)
{
    if(m_impl != nullptr)
    {
        ++m_impl->m_ref_count;
    }
}

UnicodeView::UnicodeView(const UnicodeView& other)
    : m_impl(other.m_impl)
{
    if(m_impl != nullptr)
    {
        ++m_impl->m_ref_count;
    }
}

UnicodeView::UnicodeView(UnicodeView&& other)
    : m_impl(other.m_impl)
{
    other.m_impl = nullptr;
}

//------------------------------------------------------------------------------
//                                  DESTRUCTORS
//------------------------------------------------------------------------------

UnicodeView::~UnicodeView()
{
    if(m_impl != nullptr)
    {
        if(m_impl->m_ref_count <= 1)
        {
            delete m_impl;
            m_impl = nullptr;
        }
        else
        {
            --m_impl->m_ref_count;
        }
    }
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

UnicodeView& UnicodeView::operator=(const UnicodeView& other)
{
    m_impl = other.m_impl;
    if(m_impl != nullptr)
    {
        ++m_impl->m_ref_count;
    }

    return *this;
}

UnicodeView& UnicodeView::operator=(UnicodeView&& other)
{
    m_impl = other.m_impl;
    other.m_impl = nullptr;

    return *this;
}

bool UnicodeView::operator==(const UnicodeView& other) const
{
    deus::UnicodeStorage converted;
    deus::UnicodeView other_view = other;

    // different encodings?
    if(other.encoding() != encoding())
    {
        converted = other.convert(encoding());
        other_view = converted.get_view();
    }

    return std::memcmp(c_str(), other_view.c_str(), c_str_length()) == 0;
}

bool UnicodeView::operator!=(const UnicodeView& other) const
{
    return !((*this) == other);
}

bool UnicodeView::operator==(const UnicodeStorage& other) const
{
    return (*this) == other.get_view();
}

bool UnicodeView::operator!=(const UnicodeStorage& other) const
{
    return !((*this) == other);
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

deus::Encoding UnicodeView::encoding() const
{
    return m_impl->m_encoding;
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
        m_impl->m_byte_length -
        EncodingImpl::null_terminator_size(m_impl->m_encoding);
}

const char* UnicodeView::c_str() const
{
    return m_impl->m_data;
}

std::string UnicodeView::std_string() const
{
    return std::string(m_impl->m_data, m_impl->m_byte_length - 1);
}

bool UnicodeView::explicit_equals(const deus::UnicodeView& other) const
{
    // encodings different?
    if(encoding() != other.encoding())
    {
        return false;
    }

    // sizes different
    if(byte_length() != other.byte_length())
    {
        return false;
    }

    // compare
    return
        std::memcmp(m_impl->m_data, other.m_impl->m_data, byte_length()) == 0;
}

bool UnicodeView::empty() const
{
    return c_str_length() == 0;
}

std::size_t UnicodeView::size_of_symbol(std::size_t symbol_index) const
{
    return m_impl->size_of_symbol(symbol_index);
}

std::size_t UnicodeView::minimum_symbol_size() const
{
    return deus::UnicodeView::EncodingImpl::minimum_symbol_size(encoding());
}

std::size_t UnicodeView::null_terminator_size() const
{
    return deus::UnicodeView::EncodingImpl::null_terminator_size(encoding());
}

std::size_t UnicodeView::symbol_to_byte_index(std::size_t symbol_index) const
{
    return m_impl->symbol_to_byte_index(symbol_index);
}

std::size_t UnicodeView::byte_to_symbol_index(std::size_t byte_index) const
{
    return m_impl->byte_to_symbol_index(byte_index);
}

bool UnicodeView::starts_with(const deus::UnicodeView& other) const
{
    // sub string greater? - fast fail
    if(other.length() > length())
    {
        return false;
    }

    // different encodings?
    deus::UnicodeStorage converted;
    deus::UnicodeView other_view = other.convert_if_not(encoding(), converted);

    // just use memcmp for the fastest result
    return std::memcmp(
        c_str(),
        other_view.c_str(),
        other_view.c_str_length()
    ) == 0;
}

bool UnicodeView::ends_with(const deus::UnicodeView& other) const
{
    // sub string greater? - fast fail
    if(other.length() > length())
    {
        return false;
    }

    // zero length? - fast succeed
    if(other.length() == 0)
    {
        return true;
    }

    // different encodings?
    deus::UnicodeStorage converted;
    deus::UnicodeView other_view = other.convert_if_not(encoding(), converted);

    // just use memcmp for the fastest result
    return std::memcmp(
        c_str() + c_str_length() - other_view.c_str_length(),
        other_view.c_str(),
        other_view.c_str_length()
    ) == 0;
}

std::size_t UnicodeView::find(const deus::UnicodeView& s, std::size_t pos) const
{
    // different encodings?
    deus::UnicodeStorage converted;
    deus::UnicodeView s_view = s.convert_if_not(encoding(), converted);

    return m_impl->find(s_view, pos);
}

std::size_t UnicodeView::rfind(
        const deus::UnicodeView& s,
        std::size_t pos) const
{
    // different encodings?
    deus::UnicodeStorage converted;
    deus::UnicodeView s_view = s.convert_if_not(encoding(), converted);

    return m_impl->rfind(s_view, pos);
}

std::vector<std::size_t> UnicodeView::find_all(
    const deus::UnicodeView& s,
    std::size_t pos) const
{
    // different encodings?
    deus::UnicodeStorage converted;
    deus::UnicodeView s_view = s.convert_if_not(encoding(), converted);

    return m_impl->find_all(s_view, pos);
}

deus::UnicodeStorage UnicodeView::convert(deus::Encoding encoding) const
{
    return m_impl->convert(encoding);
}

const deus::UnicodeView& UnicodeView::convert_if_not(
        deus::Encoding expected_encoding,
        deus::UnicodeStorage& storage) const
{
    if(encoding() != expected_encoding)
    {
        storage = convert(expected_encoding);
        return storage.get_view();
    }
    return *this;
}

const deus::UnicodeView& UnicodeView::convert_if_not(
        uint64_t allowed_encodings,
        deus::Encoding convert_encoding,
        deus::UnicodeStorage& storage) const
{
    if(static_cast<uint64_t>(encoding()) & allowed_encodings)
    {
        storage = convert(convert_encoding);
        return storage.get_view();
    }
    return *this;
}

deus::UnicodeStorage UnicodeView::concatenate(const UnicodeView& s) const
{
    // different encodings?
    deus::UnicodeStorage converted;
    deus::UnicodeView other_view = s.convert_if_not(encoding(), converted);

    // actually concatenate the strings
    std::string a = std_string();
    a += other_view.std_string();

    // return new storage
    return deus::UnicodeStorage(std::move(a), encoding());
}

deus::UnicodeStorage UnicodeView::repeat(int32_t n) const
{
    // don't support negative multiplication
    if(n < 0)
    {
        throw deus::ValueError(
            "UnicodeView::repeat cannot operate for negative values."
        );
    }

    // allocate
    std::string result;
    result.reserve(c_str_length() * n);

    // insert
    std::string s = std_string();
    for(int32_t i = 0; i < n; ++i)
    {
        result.insert(result.end(), s.begin(), s.end());
    }

    // return storage
    return deus::UnicodeStorage(
        std::move(result),
        length() * n,
        encoding()
    );
}

// std::vector<deus::UnicodeStorage> UnicodeView::split(
//         const deus::UnicodeView delimiter)
// {
//     // TODO: just use find all
// }

std::vector<deus::UnicodeStorage> UnicodeView::bytes_as_hex(
        const deus::UnicodeView& prefix,
        bool uppercase) const
{
    // TODO: I'm sure I can write a much faster version of this
    // this function doesn't require a encoding specific implementation
    std::vector<deus::UnicodeStorage> ret;
    ret.reserve(c_str_length());
    // set up the stream
    std::stringstream ss;
    ss << std::hex;
    if(uppercase)
    {
        ss << std::uppercase;
    }
    // convert each characeter
    for(const char* c = m_impl->m_data;
        c != m_impl->m_data + c_str_length();
        ++c)
    {
        // clear
        ss.str("");
        // convert
        const uint32_t as_unsigned = *((const unsigned char*) c);
        ss << prefix << as_unsigned;
        // insert
        std::string hex = ss.str();
        ret.emplace_back(
            std::move(hex),
            prefix.length() + hex.length(),
            deus::Encoding::kASCII
        );
    }

    return ret;
}

DEUS_VERSION_NS_END
} // namespace deus
