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

#include <codecvt>
#include <cstring>
#include <locale>
#include <sstream>
#include <unordered_map>
#include <vector>

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
    utf8_impl::compute_byte_length_strlen(m_data, m_byte_length);
}

void UnicodeView::UTF8Impl::compute_symbol_length() const
{
    utf8_impl::compute_symbol_length_word_batching(
        m_data,
        m_byte_length,
        m_symbol_length
    );
}

//------------------------------------------------------------------------------
//                                GLOBAL FUNCTIONS
//------------------------------------------------------------------------------

namespace utf8_impl
{

//-----------------------FROM CODE POINT IMPLEMENTATIONS------------------------

std::string from_code_point_naive(
        const std::vector<deus::CodePoint>& code_points)
{
    // TODO: reserve 4 times the size and then copy?

    // reserve to the maximum size
    char* str = new char[( code_points.size() * 4) + 1];

    std::size_t str_index = 0;
    for(std::size_t i = 0; i < code_points.size(); ++i)
    {
        deus::CodePoint code_point = code_points[i];
        if(code_point <= 0x0000007F)
        {
            // treat as is
            str[str_index] = (char) (code_point & 0x7F);
            ++str_index;
            continue;
        }
        if(code_point <= 0x000007FF)
        {
            str[str_index] = (char)
                (((code_point >> 6) & 0x0000001F) | 0x000000C0);
            str[str_index + 1] = (char)
                ((code_point & 0x0000003F) | 0x00000080);
            str_index += 2;
            continue;
        }
        if(code_point <= 0x0000FFFF)
        {
            str[str_index] = (char)
                (((code_point >> 12) & 0x0000000F) | 0x000000E0);
            str[str_index + 1] = (char)
                (((code_point >> 6) & 0x0000003F) | 0x00000080);
            str[str_index + 2] = (char)
                ((code_point & 0x0000003F) | 0x00000080);
            str_index += 3;
            continue;
        }

        str[str_index] = (char)
            (((code_point >> 18) & 0x00000007) | 0x000000F0);
        str[str_index + 1] = (char)
            (((code_point >> 12) & 0x0000003F) | 0x00000080);
        str[str_index + 2] = (char)
            (((code_point >> 6) & 0x0000003F) | 0x00000080);
        str[str_index + 3] = (char)
            ((code_point & 0x0000003F) | 0x00000080);
        str_index += 4;
    }
    str[str_index] = '\0';

    return std::string(str, str_index);
}

//---------------------COMPUTE BYTE LENGTH IMPLEMENTATIONS----------------------

void compute_byte_length_naive(
        const char* in_data,
        std::size_t& out_byte_length)
{
    out_byte_length = 0;
    if(in_data == nullptr)
    {
        return;
    }

    for(const char* c = in_data; (*c) != '\0'; ++c, ++out_byte_length);
    // final increment for null pointer
    ++out_byte_length;
}

void compute_byte_length_strlen(
        const char* in_data,
        std::size_t& out_byte_length)
{
    out_byte_length = 0;
    if(in_data == nullptr)
    {
        return;
    }

    out_byte_length = strlen(in_data) + 1;
}

//--------------------COMPUTE SYMBOL LENGTH IMPLEMENTATIONS---------------------

void compute_symbol_length_naive(
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
                    ": <" + character.to_hex() + ">"
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

void compute_symbol_length_wstring_convert(
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

namespace compute_symbol_length_byte_jump__util
{

static std::vector<unsigned char> build_jump_table()
{
    std::vector<unsigned char> jump_table(16, 1);
    jump_table[12] = 2;
    jump_table[13] = 2;
    jump_table[14] = 3;
    jump_table[15] = 4;
    return jump_table;
}

static std::vector<unsigned char> g_jump_table = build_jump_table();

} // namespace compute_symbol_length_byte_jump__util

void compute_symbol_length_byte_jump(
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

    for(std::size_t i = 0; i < in_byte_length - 1;)
    {
        const char* byte_ptr = in_data + i;
        // use the jump table to determine how many bytes we should jump to the
        // next symbol
        const char jump_index = ((*byte_ptr) >> 4) & 0x0F;
        const std::size_t jump = static_cast<std::size_t>(
            compute_symbol_length_byte_jump__util::g_jump_table[jump_index]
        );

        i += jump;
        ++out_symbol_length;
    }
}

void compute_symbol_length_word_batching(
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
    std::size_t naive_remainder = 0;
    std::size_t i = 0;
    while(i < iterate_to)
    {
        const char* byte_ptr = in_data + i;
        // use the jump table to determine how many bytes we should jump to the
        // next symbol
        const char jump_index = ((*byte_ptr) >> 4) & 0x0F;
        const std::size_t jump = static_cast<std::size_t>(
            compute_symbol_length_byte_jump__util::g_jump_table[jump_index]
        );

        i += jump;
        ++out_symbol_length;
        naive_remainder = jump - 1;
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
    // dumb compiler bug? 0xFFFFFFFFFFFFFFFF >> (64 - 0) does not equal
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

} // namespace utf8_impl
} // namespace deus
