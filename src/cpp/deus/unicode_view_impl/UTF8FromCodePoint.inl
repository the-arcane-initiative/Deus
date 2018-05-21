/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for UTF-8 implementations of the from_code_point
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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8FROMCODEPOINT_INL_
#define DEUS_UNICODEVIEWIMPL_UTF8FROMCODEPOINT_INL_

#include <vector>


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace utf8_inl
{

DEUS_FORCE_INLINE std::string from_code_point_naive(
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

} // namespace utf8_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
