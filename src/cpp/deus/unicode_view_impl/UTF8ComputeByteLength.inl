/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for UTF-8 implementations of the
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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8COMPUTEBYTELENGTH_INL_
#define DEUS_UNICODEVIEWIMPL_UTF8COMPUTEBYTELENGTH_INL_

#include <cstring>


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace utf8_inl
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
    out_byte_length = 0;
    out_byte_length = strlen(in_data) + 1;
}

} // namespace utf8_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
