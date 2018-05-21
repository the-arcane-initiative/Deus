/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for UTF-8 implementations of the
 *        byte_to_symbol_index function.
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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8BYTETOSYMBOLINDEX_INL_
#define DEUS_UNICODEVIEWIMPL_UTF8BYTETOSYMBOLINDEX_INL_

#include <codecvt>
#include <locale>

#include "deus/Constants.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace utf8_inl
{

DEUS_FORCE_INLINE std::size_t byte_to_symbol_index_naive(
        const deus::UnicodeView& self,
        std::size_t byte_index)
{
    // generic checks
    // --
    if(byte_index >= self.c_str_length())
    {
        return self.length() + (byte_index - self.c_str_length());
    }
    // --

    const char* data = self.c_str();
    std::size_t current_byte = 0;
    std::size_t symbol_counter = 0;
    while(current_byte < byte_index)
    {
        current_byte += utf8_inl::bytes_in_symbol(data + current_byte);
        if(current_byte > byte_index)
        {
            return symbol_counter;
        }
        ++symbol_counter;
    }
    return symbol_counter;
}

DEUS_FORCE_INLINE std::size_t byte_to_symbol_index_wstring_convert(
        const deus::UnicodeView& self,
        std::size_t byte_index)
{
    // generic checks
    // --
    if(byte_index >= self.c_str_length())
    {
        return self.length() + (byte_index - self.c_str_length());
    }
    // --

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    std::string str(self.c_str(), byte_index);
    std::wstring wstr = convert.from_bytes(str);

    return wstr.length();
}

DEUS_FORCE_INLINE std::size_t byte_to_symbol_index_word_batching(
        const deus::UnicodeView& self,
        std::size_t byte_index)
{
    // generic checks
    // --
    if(byte_index >= self.c_str_length())
    {
        return self.length() + (byte_index - self.c_str_length());
    }
    // --

    // TODO: I think there's potential for this to be faster

    const char* data = self.c_str();
    std::size_t result = 0;
    utf8_inl::compute_symbol_length_word_batching(
        data,
        byte_index + 1, // this length should include the "null terminator"
        result
    );
    // we still have to determine if we stopped midday through the final byte
    if(result > 0 && (data[byte_index] & 0xC0) == 0x80)
    {
        return result - 1;
    }
    return result;
}

} // namespace utf8_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
