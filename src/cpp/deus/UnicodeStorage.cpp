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
#include "deus/UnicodeStorage.hpp"

#include "deus/Exceptions.hpp"
#include "deus/UnicodeView.hpp"
#include <deus/unicode_view_impl/ASCIIImpl.hpp>
#include <deus/unicode_view_impl/UTF8Impl.hpp>


namespace deus
{
inline namespace DEUS_VERSION_NS
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UnicodeStorage::UnicodeStorage(deus::Encoding encoding)
    : m_str ("")
    , m_view(new deus::UnicodeView(m_str, encoding))
{
}

UnicodeStorage::UnicodeStorage(const deus::UnicodeView& view)
    : m_str (view.c_str(), view.c_str_length())
    , m_view(new deus::UnicodeView(
        m_str.c_str(),
        view.c_str_length(),
        view.length(),
        view.encoding()
    ))
{
}

UnicodeStorage::UnicodeStorage(
        const std::vector<deus::CodePoint>& code_points,
        deus::Encoding encoding)
    : m_view(nullptr)
{
    switch(encoding)
    {
        case deus::Encoding::kASCII:
        {
            m_str = deus::ascii_impl::from_code_point_naive(code_points);
            break;
        }
        case deus::Encoding::kUTF8:
        {
            m_str = deus::utf8_impl::from_code_point_naive(code_points);
            break;
        }
        case deus::Encoding::kUTF16_LE:
        {
            throw deus::NotImplementedError(
                "Constructing UnicodeStorage from code points for little "
                "endian UTF-16 data has not yet been implemented."
            );
        }
        case deus::Encoding::kUTF16_BE:
        {
            throw deus::NotImplementedError(
                "Constructing UnicodeStorage from code points for big "
                "endian UTF-16 data has not yet been implemented."
            );
        }
        case deus::Encoding::kUTF32_LE:
        {
            throw deus::NotImplementedError(
                "Constructing UnicodeStorage from code points for little "
                "endian UTF-32 data has not yet been implemented."
            );
        }
        case deus::Encoding::kUTF32_BE:
        {
            throw deus::NotImplementedError(
                "Constructing UnicodeStorage from code points for big "
                "endian UTF-32 data has not yet been implemented."
            );
        }
        // TODO: not implemented error
        default:
        {
            throw deus::TypeError(
                "Unrecognized Unicode encoding: " +
                std::to_string(static_cast<unsigned>(encoding))
            );
        }
    }

    m_view.reset(new deus::UnicodeView(m_str, encoding));
}

UnicodeStorage::UnicodeStorage(const UnicodeStorage& other)
    : m_str (other.m_str)
    , m_view(new deus::UnicodeView(
        m_str.c_str(),
        other.m_view->c_str_length(),
        other.m_view->length(),
        other.m_view->encoding()
    ))
{
}

UnicodeStorage::UnicodeStorage(std::string&& str, deus::Encoding encoding)
    : m_str(std::move(str))
    , m_view(new UnicodeView(m_str, encoding))
{
}

UnicodeStorage::UnicodeStorage(
        std::string&& str,
        std::size_t symbol_length,
        deus::Encoding encoding)
    : m_str(std::move(str))
    , m_view(new UnicodeView(m_str, symbol_length, encoding))
{
}

UnicodeStorage::UnicodeStorage(UnicodeStorage&& other)
    : m_str (std::move(other.m_str))
    , m_view(new deus::UnicodeView(
        m_str,
        other.m_view->length(),
        other.m_view->encoding()
    ))
{
    other.m_view = nullptr;
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

UnicodeStorage::~UnicodeStorage()
{
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

UnicodeStorage& UnicodeStorage::operator=(const UnicodeView& view)
{
    m_str = std::string(view.c_str(), view.c_str_length());
    m_view.reset(new deus::UnicodeView(
        m_str.c_str(),
        view.c_str_length(),
        view.length(),
        view.encoding()
    ));
    return *this;
}

UnicodeStorage& UnicodeStorage::operator=(const UnicodeStorage& other)
{
    m_str  = other.m_str;
    m_view.reset(new deus::UnicodeView(
        m_str.c_str(),
        other.m_view->c_str_length(),
        other.m_view->length(),
        other.m_view->encoding()
    ));
    return *this;
}

UnicodeStorage& UnicodeStorage::operator=(UnicodeStorage&& other)
{
    m_str  = std::move(other.m_str);
    m_view.reset(new deus::UnicodeView(
        m_str,
        other.m_view->length(),
        other.m_view->encoding()
    ));

    return *this;
}

bool UnicodeStorage::operator==(const UnicodeStorage& other) const
{
    // just use the UnicodeView
    return m_view == other.m_view;
}

bool UnicodeStorage::operator!=(const UnicodeStorage& other) const
{
    return !((*this) == other);
}

UnicodeStorage::operator std::string() const
{
    return m_str;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

const std::string& UnicodeStorage::get_string() const
{
    return m_str;
}

const UnicodeView& UnicodeStorage::get_view() const
{
    return *m_view;
}

} // namespace DEUS_VERSION_NS
} // namespace deus
