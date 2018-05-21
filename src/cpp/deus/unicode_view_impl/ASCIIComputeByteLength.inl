/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for ASCII implementations of the
 *        compute_byte_length function.
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
#ifndef DEUS_UNICODEVIEWIMPL_ASCIICOMPUTEBYTELENGTH_INL_
#define DEUS_UNICODEVIEWIMPL_ASCIICOMPUTEBYTELENGTH_INL_

#include <cstring>
#include <string>


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace ascii_inl
{

DEUS_FORCE_INLINE void compute_byte_length_naive(
        const char* in_data,
        std::size_t& out_byte_length)
{
    out_byte_length = 0;
    for(const char* c = in_data; (*c) != '\0'; ++c, ++out_byte_length);
    // final increment for null pointer
    ++out_byte_length;
}

DEUS_FORCE_INLINE void compute_byte_length_strlen(
        const char* in_data,
        std::size_t& out_byte_length)
{
    out_byte_length = strlen(in_data) + 1;
}

DEUS_FORCE_INLINE void compute_byte_length_std_string(
        const char* in_data,
        std::size_t& out_byte_length)
{
    std::string s(in_data);
    out_byte_length = s.length() + 1;
}

DEUS_FORCE_INLINE void compute_byte_length_word_batching(
        const char* in_data,
        std::size_t& out_byte_length)
{
    out_byte_length = 0;
    const char* byte_ptr = in_data;

    constexpr std::size_t word_size = sizeof(std::size_t);
    // naive check the first bits until we're word aligned
    for(;((std::size_t) byte_ptr & (word_size - 1)) != 0; ++byte_ptr)
    {
        if(*byte_ptr == '\0')
        {
            out_byte_length = static_cast<std::size_t>(byte_ptr - in_data) + 1;
            return;
        }
    }

    // read word-aligned
    const std::size_t* word_ptr = (std::size_t*) byte_ptr;

    // set magic numbers based on word size
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

        // TODO: this can cause false positives - we might be able to use better
        //       magic number checks
        if(((word - low_magic) & high_magic) != 0)
        {
            const char* check = (const char*) (word_ptr - 1);

            if(check[0] == 0)
            {
                out_byte_length = static_cast<std::size_t>(check - in_data) + 1;
                return;
            }
            if(check[1] == 0)
            {
                out_byte_length = static_cast<std::size_t>(check - in_data) + 2;
                return;
            }
            if(check[2] == 0)
            {
                out_byte_length = static_cast<std::size_t>(check - in_data) + 3;
                return;
            }
            if(check[3] == 0)
            {
                out_byte_length = static_cast<std::size_t>(check - in_data) + 4;
                return;
            }
            if(word_size > 4)
            {
                if(check[4] == 0)
                {
                    out_byte_length =
                        static_cast<std::size_t>(check - in_data) + 5;
                    return;
                }
                if(check[5] == 0)
                {
                    out_byte_length =
                        static_cast<std::size_t>(check - in_data) + 6;
                    return;
                }
                if(check[6] == 0)
                {
                    out_byte_length =
                        static_cast<std::size_t>(check - in_data) + 7;
                    return;
                }
                if(check[7] == 0)
                {
                    out_byte_length =
                        static_cast<std::size_t>(check - in_data) + 8;
                    return;
                }
            }

            // misfire - continue
        }
    }
}

} // namespace ascii_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
