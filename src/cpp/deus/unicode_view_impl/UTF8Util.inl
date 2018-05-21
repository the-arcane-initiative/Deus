/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for internal UTF-8 utility functions.
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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8UTIL_INL_
#define DEUS_UNICODEVIEWIMPL_UTF8UTIL_INL_


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace utf8_inl
{

// this performs the same functionality as size_of_symbol, expect it just
// returns the number of bytes of the symbol contained at the start of the given
// data. This means internal functions can use this version the avoid any extra
// overhead and/or cyclic calls
DEUS_FORCE_INLINE std::size_t bytes_in_symbol(const char* symbol_data)
{
    if((*symbol_data & 0x80) == 0)
    {
        return 1;
    }
    if((*symbol_data & 0xE0) == 0xC0)
    {
        return 2;
    }
    if((*symbol_data & 0xF0) == 0xE0)
    {
        return 3;
    }
    return 4;
}


static std::vector<unsigned char> build_jump_table()
{
    std::vector<unsigned char> jump_table(16, 1);
    jump_table[12] = 2;
    jump_table[13] = 2;
    jump_table[14] = 3;
    jump_table[15] = 4;
    return jump_table;
}
// table that can be used to look up how many bytes to jump to the next symbol
// for the given bytes
static std::vector<unsigned char> g_jump_table = build_jump_table();


} // namespace utf8_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
