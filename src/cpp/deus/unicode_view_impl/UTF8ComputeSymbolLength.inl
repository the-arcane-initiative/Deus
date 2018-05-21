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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8COMPUTESYMBOLLENGTH_INL_
#define DEUS_UNICODEVIEWIMPL_UTF8COMPUTESYMBOLLENGTH_INL_

#include <codecvt>
#include <locale>

#include "deus/Exceptions.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace utf8_inl
{

DEUS_FORCE_INLINE void compute_symbol_length_naive(
        const char* in_data,
        std::size_t in_byte_length,
        std::size_t& out_symbol_length)
{
    out_symbol_length = 0;
    std::size_t next_check = 0;
    for(std::size_t i = 0; i < in_byte_length - 1; ++i)
    {
        const char* c = in_data + i;

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
                next_check = 2;
            }
            // 4 byte character
            else if((*c & 0xF8) == 0xF0)
            {
                next_check = 3;
            }
            else
            {
                deus::UnicodeView character(c, 1, deus::Encoding::kASCII);
                throw deus::UTF8Error(
                    "Invalid leading byte in UTF-8 string: '" + character +
                    ": <" + character.bytes_as_hex().front() + ">"
                );
            }

            ++out_symbol_length;
        }
        else
        {
            --next_check;
        }
    }
}

DEUS_FORCE_INLINE void compute_symbol_length_wstring_convert(
        const char* in_data,
        std::size_t in_byte_length,
        std::size_t& out_symbol_length)
{
    out_symbol_length = 0;
    // null data?
    if(in_data == nullptr)
    {
        return;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    std::string str(in_data, in_byte_length - 1);
    std::wstring wstr = convert.from_bytes(str);

    out_symbol_length = wstr.length();
}

DEUS_FORCE_INLINE void compute_symbol_length_byte_jump(
        const char* in_data,
        std::size_t in_byte_length,
        std::size_t& out_symbol_length)
{
    out_symbol_length = 0;
    for(std::size_t i = 0; i < in_byte_length - 1;)
    {
        const char* byte_ptr = in_data + i;
        // use the jump table to determine how many bytes we should jump to the
        // next symbol
        const char jump_index = ((*byte_ptr) >> 4) & 0x0F;
        const std::size_t jump =
            static_cast<std::size_t>(utf8_inl::g_jump_table[jump_index]);

        i += jump;
        ++out_symbol_length;
    }
}

DEUS_FORCE_INLINE void compute_symbol_length_word_batching(
        const char* in_data,
        std::size_t in_byte_length,
        std::size_t& out_symbol_length)
{
    out_symbol_length = 0;
    std::size_t start_addr = (std::size_t) in_data;
    constexpr std::size_t word_size = sizeof(std::size_t);

    // determine the point of word alignment
    std::size_t align_at = word_size - (start_addr % word_size);

    // naive check the first bits until we're word aligned
    std::size_t iterate_to = align_at;
    if(in_byte_length - 1 < align_at)
    {
        iterate_to = in_byte_length - 1;
    }

    std::size_t i = 0;
    while(i < iterate_to)
    {
        const char* byte_ptr = in_data + i;
        // use the jump table to determine how many bytes we should jump to the
        // next symbol
        const char jump_index = ((*byte_ptr) >> 4) & 0x0F;
        const std::size_t jump =
            static_cast<std::size_t>(utf8_inl::g_jump_table[jump_index]);

        i += jump;
        ++out_symbol_length;
    }
    i = iterate_to;
    // complete
    if(i >= in_byte_length - 1)
    {
        return;
    }

    // magic numbers
    constexpr std::size_t magic_1 =
        (word_size > 4)
        ?
        0x8080808080808080L
        :
        0x80808080UL;
    constexpr std::size_t magic_2 =
        (word_size > 4)
        ?
        0x0101010101010101L
        :
        0x01010101UL;
    constexpr std::size_t magic_3 =
        (word_size > 4)
        ?
        0x4040404040404040L
        :
        0x40404040UL;

    // TODO: should replace literal 8s for word size

    // calculate when the final iteration will occur
    std::size_t final_iteration = (in_byte_length - i) / word_size;
    final_iteration = i + (final_iteration * word_size) - 8;

    // calculate how many bytes need masking on the final iterator -- at least
    // one byte (the null terminator) always needs masking on the final
    // iteration
    std::size_t mask_size = (std::size_t) (in_data + in_byte_length);
    mask_size = ((mask_size - 1) % word_size) * 8;

    // TODO: word size?
    const std::size_t end_or_mask =
        0x8080808080808080UL & (0xFFFFFFFFFFFFFFFF << mask_size);
    std::size_t and_shift = 0xFFFFFFFFFFFFFFFF >> (64 - mask_size);
    // compiler bug? 0xFFFFFFFFFFFFFFFF >> (64 - 0) does not equal
    // 0x0000000000000000 (but 0xFFFFFFFFFFFFFFFF >> 64 does...)
    if(mask_size == 0)
    {
        and_shift = 0;
    }
    std::size_t end_and_mask = 0x8080808080808080UL | and_shift;

    // read word-aligned - even though we may have "read" the first few bytes it
    // it won't affect the following algorithm since the read bytes have the
    // format 10xxxxxx
    for(; i < in_byte_length; i += word_size)
    {
        std::size_t word = *((std::size_t*) (in_data + i));

        // apply the final iteration mask?
        if(in_byte_length - i <= word_size)
        {
            word |= end_or_mask;
            word &= end_and_mask;
        }

        // bias for ascii strings
        std::size_t symbol_counter = word & magic_1;
        if(symbol_counter == 0)
        {
            out_symbol_length += word_size;
            continue;
        }

        // count all the symbols that don't have the format 10xxxxxx, since
        // these are supplementary bytes
        symbol_counter = symbol_counter & (((~word) & magic_3) << 1);
        symbol_counter = ~symbol_counter;
        symbol_counter = (symbol_counter >> 7) & magic_2;

        const char* h_add = (const char*) (&symbol_counter);
        out_symbol_length +=
            h_add[0] + h_add[1] + h_add[2] + h_add[3];
        if(word_size > 4)
        {
            out_symbol_length +=
                h_add[4] + h_add[5] + h_add[6] + h_add[7];
        }
    }
}

} // namespace utf8_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
