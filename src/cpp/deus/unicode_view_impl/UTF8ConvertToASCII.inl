/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for UTF-8 implementations of the convert_to_ascii
 *        function.
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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8CONVERTTOASCII_HPP_
#define DEUS_UNICODEVIEWIMPL_UTF8CONVERTTOASCII_HPP_


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace utf8_inl
{

DEUS_FORCE_INLINE deus::UnicodeStorage convert_to_ascii_naive(
        const char* in_data,
        std::size_t in_byte_length,
        std::size_t in_symbol_length)
{
    std::string converted;
    converted.reserve(in_symbol_length);

    for(std::size_t i = 0; i < in_byte_length - 1;)
    {
        const unsigned char* c = (const unsigned char*) (in_data + i);
        if((*c) <= 0x7F)
        {
            // just use as is
            converted.push_back(*c);
            ++i;
        }
        else
        {
            // use substitution
            converted.push_back('\x1A');
            // use the jump table to determine how many bytes we should jump
            // to the next symbol
            const char jump_index = ((*c) >> 4) & 0x0F;
            const std::size_t jump =
                static_cast<std::size_t>(utf8_inl::g_jump_table[jump_index]);
            i += jump;
        }
    }

    return deus::UnicodeStorage(
        std::move(converted),
        in_symbol_length,
        deus::Encoding::kASCII
    );
}

} // namespace utf8_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
