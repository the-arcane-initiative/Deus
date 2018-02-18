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
#include <locale>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "deus/Constants.hpp"
#include "deus/Exceptions.hpp"
#include "deus/util/SIMDUtil.hpp"


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

        // TODO: need to keep this implementation for benchi marking
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

        // as the prophecy foretold
        c++;
        ++out_byte_length;
    }
    // increment one more time for the null terminator
    ++out_byte_length;
}

void compute_byte_length_wstring_convert(
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

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    std::string str(in_data);
    std::wstring wstr = convert.from_bytes(str);

    out_byte_length = str.length() + 1;
    out_symbol_length = wstr.length();
}

namespace compute_byte_length_byte_jump__util
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

} // namespace compute_byte_length_byte_jump__util

void compute_byte_length_byte_jump(
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

    const char* byte_ptr = in_data;
    while((*byte_ptr) != 0x0)
    {

        // use the jump table to determine how many bytes we should jump to the
        // next symbol
        const char jump_index = ((*byte_ptr) >> 4) & 0x0F;
        const std::size_t jump = static_cast<std::size_t>(
            compute_byte_length_byte_jump__util::g_jump_table[jump_index]
        );

        byte_ptr += jump;
        ++out_symbol_length;
    }
    out_byte_length = static_cast<std::size_t>(byte_ptr - in_data) + 1;
}

void compute_byte_length_word_batching(
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

    const char* byte_ptr = in_data;

    constexpr std::size_t word_size = sizeof(std::size_t);
    // naive check the first bits until we're word aligned
    std::size_t next_check = 0;
    for(;((std::size_t) byte_ptr & (word_size - 1)) != 0; ++byte_ptr)
    {
        ++out_byte_length;
        // TODO: could optmisie this to use a jump?
        if(next_check <= 0)
        {
            // null terminator?
            if(*byte_ptr == '\0')
            {
                return;
            }

            // single character byte
            if((*byte_ptr & 0x80) == 0)
            {
                next_check = 0;
            }
            // 2 byte character
            else if((*byte_ptr & 0xE0) == 0xC0)
            {
                next_check = 1;
            }
            // 3 byte character
            else if((*byte_ptr & 0xF0) == 0xE0)
            {
                next_check = 2;
            }
            // 4 byte character
            else if((*byte_ptr & 0xF8) == 0xF0)
            {
                next_check = 3;
            }
            else
            {
                deus::UnicodeView character(
                    byte_ptr,
                    1,
                    deus::Encoding::kASCII
                );
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

    // read word-aligned - even though we may have "read" the first few bytes it
    // it won't affect the following algorithim since the read byte have the
    // format 10xxxxxx
    const std::size_t* word_ptr = (std::size_t*) byte_ptr;

    // set zero checking magic numbers based on word size
    constexpr std::size_t high_magic =
        (word_size > 4)
        ?
        0x8080808080808080L
        :
        0x80808080UL;
    constexpr std::size_t low_magic =
        (word_size > 4)
        ?
        0x0101010101010101L
        :
        0x01010101UL;

    for(;;)
    {
        std::size_t word = *word_ptr++;

        // TODO: all of these needs support based on word size
        // TODO: should make template speciailisation versions of these
        // functions for word size?

        // TODO: this is part of the algorithim (where we "zero" out invalid)
        //       bytes is affected by endianness

        bool exit_loop = false;
        if(((word - low_magic) & high_magic) != 0)
        {
            const char* check = (const char*) (word_ptr - 1);

            if(check[0] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 1;
                exit_loop = true;
                word |= 0x8080808080808080;
                word &= 0x8080808080808080;
            }
            else if(check[1] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 2;
                exit_loop = true;
                word |= 0x8080808080808000;
                word &= 0x80808080808080FF;
            }
            else if(check[2] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 3;
                exit_loop = true;
                word |= 0x8080808080800000;
                word &= 0x808080808080FFFF;
            }
            else if(check[3] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 4;
                exit_loop = true;
                word |= 0x8080808080000000;
                word &= 0x8080808080FFFFFF;
            }
            else if(word_size > 4)
            {
                if(check[4] == 0)
                {
                    out_byte_length =
                        static_cast<std::size_t>(check - in_data) + 5;
                    exit_loop = true;
                    word |= 0x8080808000000000;
                    word &= 0x80808080FFFFFFFF;
                }
                else if(check[5] == 0)
                {
                    out_byte_length =
                        static_cast<std::size_t>(check - in_data) + 6;
                    exit_loop = true;
                    word |= 0x8080800000000000;
                    word &= 0x808080FFFFFFFFFF;
                }
                else if(check[6] == 0)
                {
                    out_byte_length =
                        static_cast<std::size_t>(check - in_data) + 7;
                    exit_loop = true;
                    word |= 0x8080000000000000;
                    word &= 0x8080FFFFFFFFFFFF;
                }
                else if(check[7] == 0)
                {
                    out_byte_length =
                        static_cast<std::size_t>(check - in_data) + 8;
                    exit_loop = true;
                    word |= 0x8000000000000000;
                    word &= 0x80FFFFFFFFFFFFFF;
                }
            }

            // misfire - continue
        }

        // bias for ascii strings
        std::size_t symbol_counter = word & 0x8080808080808080;
        if(!exit_loop && symbol_counter == 0)
        {
            out_symbol_length += 8;
            continue;
        }

        // TODO: I feel like there's a faster way to do this that we dont't have
        //       to byte-wise operations
        // count all the symbols that don't have the format 10xxxxxx, since
        // these are supplementary bytes
        symbol_counter = symbol_counter & (((~word) & 0x4040404040404040) << 1);
        symbol_counter = ~symbol_counter;
        symbol_counter = (symbol_counter >> 7) & 0x0101010101010101;

        const char* h_add = (const char*) (&symbol_counter);
        out_symbol_length +=
            h_add[0] + h_add[1] + h_add[2] + h_add[3] +
            h_add[4] + h_add[5] + h_add[6] + h_add[7];

        // iterations done?
        if(exit_loop)
        {
            return;
        }
    }
}

void compute_byte_length_simd_batching(
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

    const char* byte_ptr = in_data;

    constexpr std::size_t word_size = sizeof(std::size_t);
    // naive check the first bits until we're word aligned
    std::size_t next_check = 0;
    for(;((std::size_t) byte_ptr & (word_size - 1)) != 0; ++byte_ptr)
    {
        ++out_byte_length;
        // TODO: could optmisie this to use a jump?
        if(next_check <= 0)
        {
            // null terminator?
            if(*byte_ptr == '\0')
            {
                return;
            }

            // single character byte
            if((*byte_ptr & 0x80) == 0)
            {
                next_check = 0;
            }
            // 2 byte character
            else if((*byte_ptr & 0xE0) == 0xC0)
            {
                next_check = 1;
            }
            // 3 byte character
            else if((*byte_ptr & 0xF0) == 0xE0)
            {
                next_check = 2;
            }
            // 4 byte character
            else if((*byte_ptr & 0xF8) == 0xF0)
            {
                next_check = 3;
            }
            else
            {
                deus::UnicodeView character(
                    byte_ptr,
                    1,
                    deus::Encoding::kASCII
                );
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

    // read word-aligned - even though we may have "read" the first few bytes it
    // it won't affect the following algorithim since the read byte have the
    // format 10xxxxxx
    const std::size_t* word_ptr = (std::size_t*) byte_ptr;

    // set up bit-wise magic
    deus::SimdInt64 simd_high_magic;
    simd_high_magic.integral[0] = 0x8080808080808080L;
    simd_high_magic.integral[1] = 0x8080808080808080L;
    deus::SimdInt64 simd_low_magic;
    simd_low_magic.integral[0] = 0x0101010101010101L;
    simd_low_magic.integral[1] = 0x0101010101010101L;

    deus::SimdInt64 simd_one;
    simd_one.integral[0] = 0x01;
    simd_one.integral[1] = 0x01;

    deus::SimdInt64 simd_max;
    simd_max.integral[0] = 0xFFFFFFFFFFFFFFFF;
    simd_max.integral[1] = 0xFFFFFFFFFFFFFFFF;

    deus::SimdInt64 magic_1;
    magic_1.integral[0] = 0x8080808080808080;
    magic_1.integral[1] = 0x8080808080808080;

    deus::SimdInt64 magic_2;
    magic_2.integral[0] = 0x7F7F7F7F7F7F7F7F;
    magic_2.integral[1] = 0x7F7F7F7F7F7F7F7F;

    deus::SimdInt64 magic_3;
    magic_3.integral[0] = 0x4040404040404040;
    magic_3.integral[1] = 0x4040404040404040;


    for(;;)
    {
        deus::SimdInt64 simd_word;
        simd_word.integral[0] = *word_ptr++;
        simd_word.integral[1] = *word_ptr++;

        // TODO: this is part of the algorithim (where we "zero" out invalid)
        //       bytes is affected by endianness

        bool exit_loop = false;
        __m128i s0 = _mm_sub_epi64(simd_word.simd, simd_low_magic.simd);
        if(_mm_test_all_zeros(s0, simd_high_magic.simd) == 0)
        {
            const char* check = (const char*) (word_ptr - 2);

            if(check[0] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 1;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x8080808080808080;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0x8080808080808080;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[1] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 2;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x8080808080808000;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0x80808080808080FF;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[2] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 3;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x8080808080800000;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0x808080808080FFFF;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[3] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 4;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x8080808080000000;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0x8080808080FFFFFF;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[4] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 5;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x8080808000000000;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0x80808080FFFFFFFF;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[5] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 6;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x8080800000000000;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0x808080FFFFFFFFFF;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[6] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 7;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x8080000000000000;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0x8080FFFFFFFFFFFF;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[7] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 8;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x8000000000000000;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0x80FFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[8] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 9;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x0000000000000000;
                clear_or.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0xFFFFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x8080808080808080;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[9] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 10;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x0000000000000000;
                clear_or.integral[1] = 0x8080808080808000;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0xFFFFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x80808080808080FF;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[10] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 11;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x0000000000000000;
                clear_or.integral[1] = 0x8080808080800000;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0xFFFFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x808080808080FFFF;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[11] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 12;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x0000000000000000;
                clear_or.integral[1] = 0x8080808080000000;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0xFFFFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x8080808080FFFFFF;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[12] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 13;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x0000000000000000;
                clear_or.integral[1] = 0x8080808000000000;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0xFFFFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x80808080FFFFFFFF;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[13] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 14;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x0000000000000000;
                clear_or.integral[1] = 0x8080800000000000;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0xFFFFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x808080FFFFFFFFFF;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[14] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 15;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x0000000000000000;
                clear_or.integral[1] = 0x8080000000000000;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0xFFFFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x8080FFFFFFFFFFFF;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }
            else if(check[15] == 0)
            {
                out_byte_length =
                    static_cast<std::size_t>(check - in_data) + 16;
                exit_loop = true;

                deus::SimdInt64 clear_or;
                clear_or.integral[0] = 0x0000000000000000;
                clear_or.integral[1] = 0x8000000000000000;
                simd_word.simd = _mm_or_si128(simd_word.simd, clear_or.simd);

                deus::SimdInt64 clear_and;
                clear_and.integral[0] = 0xFFFFFFFFFFFFFFFF;
                clear_and.integral[1] = 0x80FFFFFFFFFFFFFF;
                simd_word.simd = _mm_and_si128(simd_word.simd, clear_and.simd);
            }

            // misfire - continue
        }

        // bias for ascii strings
        deus::SimdInt64 symbol_counter;
        symbol_counter.simd = _mm_and_si128(
            simd_word.simd,
            magic_1.simd
        );

        if(!exit_loop &&
           symbol_counter.integral[0] == 0 &&
           symbol_counter.integral[1] == 0)
        {
            out_symbol_length += 16;
            continue;
        }

        // count all the symbols that don't have the format 10xxxxxx, since
        // these are supplementary bytes
        deus::SimdInt64 bit_2;
        bit_2.simd = _mm_and_si128(
            _mm_xor_ps(simd_word.simd, simd_max.simd),
            magic_3.simd
        );

        // this add works as a replacement for bit shift (since there's no
        // intrinsic for it)
        bit_2.simd = _mm_add_epi64(bit_2.simd, magic_3.simd);

        symbol_counter.simd = _mm_and_si128(symbol_counter.simd, bit_2.simd);
        symbol_counter.simd = _mm_xor_ps(symbol_counter.simd, simd_max.simd);
        symbol_counter.simd = _mm_and_si128(symbol_counter.simd, magic_1.simd);

        // no intrinsic bitwise shift (only byte-wise shift)
        symbol_counter.integral[0] = symbol_counter.integral[0] >> 7;
        symbol_counter.integral[1] = symbol_counter.integral[1] >> 7;

        const char* h_add = (const char*) (&symbol_counter.integral[0]);
        out_symbol_length +=
            h_add[0]  + h_add[1]  + h_add[2]  + h_add[3] +
            h_add[4]  + h_add[5]  + h_add[6]  + h_add[7] +
            h_add[8]  + h_add[9]  + h_add[10] + h_add[11] +
            h_add[12] + h_add[13] + h_add[14] + h_add[15];


        // deus::SimdInt64 result;

        // TODO: can reduce this shit to byte-wise
        // there's not horizontal add for 8 bytes

        // result.simd = _mm_and_si128(symbol_counter.simd, simd_one.simd);
        // out_symbol_length += result.integral[0] + result.integral[1];

        // result.simd = _mm_and_si128(
        //     _mm_srli_si128(symbol_counter.simd, 1),
        //     simd_one.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // result.simd = _mm_and_si128(
        //     _mm_srli_si128(symbol_counter.simd, 2),
        //     simd_one.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // result.simd = _mm_and_si128(
        //     _mm_srli_si128(symbol_counter.simd, 3),
        //     simd_one.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // result.simd = _mm_and_si128(
        //     _mm_srli_si128(symbol_counter.simd, 4),
        //     simd_one.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // result.simd = _mm_and_si128(
        //     _mm_srli_si128(symbol_counter.simd, 5),
        //     simd_one.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // result.simd = _mm_and_si128(
        //     _mm_srli_si128(symbol_counter.simd, 6),
        //     simd_one.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // result.simd = _mm_and_si128(
        //     _mm_srli_si128(symbol_counter.simd, 7),
        //     simd_one.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];





        // symbol_counter = symbol_counter & (((~word) & 0x4040404040404040) << 1);
        // symbol_counter = ~symbol_counter;
        // out_symbol_length +=
        //     ((symbol_counter >> 7 ) & 0x01) +
        //     ((symbol_counter >> 15) & 0x01) +
        //     ((symbol_counter >> 23) & 0x01) +
        //     ((symbol_counter >> 31) & 0x01) +
        //     ((symbol_counter >> 39) & 0x01) +
        //     ((symbol_counter >> 47) & 0x01) +
        //     ((symbol_counter >> 55) & 0x01) +
        //     ((symbol_counter >> 63) & 0x01);

        // deus::SimdInt64 mask;
        // mask.integral[0] = 0x00000000000000C0;
        // mask.integral[1] = 0x00000000000000C0;
        // deus::SimdInt64 compare;
        // compare.integral[0] = 0x0000000000000080;
        // compare.integral[1] = 0x0000000000000080;

        // deus::SimdInt64 result;
        // result.integral[0] = 0;
        // result.integral[1] = 0;

        // // --
        // result.simd = _mm_cmpneq_ps(
        //     _mm_and_si128(simd_word.simd, mask.simd),
        //     compare.simd
        // );
        // // TODO: simd this?
        // out_symbol_length += result.integral[0] + result.integral[1];

        // // --
        // mask.integral[0] = 0x000000000000C000;
        // mask.integral[1] = 0x000000000000C000;
        // compare.integral[0] = 0x0000000000008000;
        // compare.integral[1] = 0x0000000000008000;
        // result.simd = _mm_cmpneq_ps(
        //     _mm_and_si128(simd_word.simd, mask.simd),
        //     compare.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // // --
        // mask.integral[0] = 0x0000000000C00000;
        // mask.integral[1] = 0x0000000000C00000;
        // compare.integral[0] = 0x0000000000800000;
        // compare.integral[1] = 0x0000000000800000;
        // result.simd = _mm_cmpneq_ps(
        //     _mm_and_si128(simd_word.simd, mask.simd),
        //     compare.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // // --
        // mask.integral[0] = 0x00000000C0000000;
        // mask.integral[1] = 0x00000000C0000000;
        // compare.integral[0] = 0x0000000080000000;
        // compare.integral[1] = 0x0000000080000000;
        // result.simd = _mm_cmpneq_ps(
        //     _mm_and_si128(simd_word.simd, mask.simd),
        //     compare.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // // --
        // mask.integral[0] = 0x000000C000000000;
        // mask.integral[1] = 0x000000C000000000;
        // compare.integral[0] = 0x0000008000000000;
        // compare.integral[1] = 0x0000008000000000;
        // result.simd = _mm_cmpneq_ps(
        //     _mm_and_si128(simd_word.simd, mask.simd),
        //     compare.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // // --
        // mask.integral[0] = 0x0000C00000000000;
        // mask.integral[1] = 0x0000C00000000000;
        // compare.integral[0] = 0x0000800000000000;
        // compare.integral[1] = 0x0000800000000000;
        // result.simd = _mm_cmpneq_ps(
        //     _mm_and_si128(simd_word.simd, mask.simd),
        //     compare.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // // --
        // mask.integral[0] = 0x00C0000000000000;
        // mask.integral[1] = 0x00C0000000000000;
        // compare.integral[0] = 0x0080000000000000;
        // compare.integral[1] = 0x0080000000000000;
        // result.simd = _mm_cmpneq_ps(
        //     _mm_and_si128(simd_word.simd, mask.simd),
        //     compare.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];

        // // --
        // mask.integral[0] = 0xC000000000000000;
        // mask.integral[1] = 0xC000000000000000;
        // compare.integral[0] = 0x8000000000000000;
        // compare.integral[1] = 0x8000000000000000;
        // result.simd = _mm_cmpneq_ps(
        //     _mm_and_si128(simd_word.simd, mask.simd),
        //     compare.simd
        // );
        // out_symbol_length += result.integral[0] + result.integral[1];


        // iterations done?
        if(exit_loop)
        {
            return;
        }
    }
}

} // namespace utf8_impl
} // namespace deus
