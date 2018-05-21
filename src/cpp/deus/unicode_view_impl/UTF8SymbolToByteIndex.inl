/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for UTF-8 implementations of the
 *        symbol_to_byte_index function.
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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8SYMBOLTOBYTEINDEX_INL_
#define DEUS_UNICODEVIEWIMPL_UTF8SYMBOLTOBYTEINDEX_INL_


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace utf8_inl
{

DEUS_FORCE_INLINE std::size_t symbol_to_byte_index_naive(
        const deus::UnicodeView& self,
        std::size_t symbol_index)
{
    // generic checks
    // --
    if(symbol_index >= self.length())
    {
        return self.c_str_length() + (symbol_index - self.length());
    }
    // --

    const char* data = self.c_str();
    std::size_t current_symbol = 0;
    std::size_t byte_counter = 0;
    while(current_symbol != symbol_index)
    {
        byte_counter += utf8_inl::bytes_in_symbol(data + byte_counter);
        ++current_symbol;
    }
    return byte_counter;
}

// TODO: can write a word batching version that checks whether we've reached the
//       symbol index or not
//       However for now this implementation seems suspiciously fast.

} // namespace utf8_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
