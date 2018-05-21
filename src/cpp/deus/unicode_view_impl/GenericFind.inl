/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for generic implementations of the find function.
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
#ifndef DEUS_UNICODEVIEWIMPL_GENERICFIND_INL_
#define DEUS_UNICODEVIEWIMPL_GENERICFIND_INL_

#include <cstring>


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace generic_inl
{

DEUS_FORCE_INLINE std::size_t find_naive(
        const deus::UnicodeView& self,
        const deus::UnicodeView& s,
        std::size_t pos)
{
    // get the position in terms of bytes rather than symbols
    std::size_t byte_pos = pos;
    if(byte_pos != 0)
    {
        byte_pos = self.symbol_to_byte_index(pos);
    }

    // generic checks
    // --
    std::size_t self_size = self.c_str_length();
    if(byte_pos > self_size)
    {
        return deus::NULL_POS;
    }
    self_size -= byte_pos;
    // if(self_size == 0)
    // {
    //     return deus::NULL_POS;
    // }

    const std::size_t s_size = s.c_str_length();
    const char* s_data = s.c_str();
    if(s_size == 0)
    {
        return 0;
    }

    const char* self_data = self.c_str() + byte_pos;
    if(s_size > self_size)
    {
        return deus::NULL_POS;
    }
    // --

    std::size_t check_to = self_size - (s_size - 1);
    for(const char* c = self_data; c != (self_data + check_to); ++c)
    {
        if(std::memcmp(c, s_data, s_size) == 0)
        {
            return self.byte_to_symbol_index((c - self_data) + byte_pos);
        }
    }

    return deus::NULL_POS;
}

// TODO: write a version of the function that keeps track of the symbol index
//       while searching

} // namespace generic_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
