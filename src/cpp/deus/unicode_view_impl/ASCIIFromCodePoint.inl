/*!
 * \file
 * \author David Saxon
 * \brief Inline definitions for ASCII implementations of the from_code_point
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
#ifndef DEUS_UNICODEVIEWIMPL_ASCIIFROMCODEPOINT_INL_
#define DEUS_UNICODEVIEWIMPL_ASCIIFROMCODEPOINT_INL_

#include <vector>

#include "deus/Constants.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN
namespace ascii_inl
{

DEUS_FORCE_INLINE std::string from_code_point_naive(
        const std::vector<deus::CodePoint>& code_points)
{
    std::string ret(code_points.size(), '\0');

    for(std::size_t i = 0; i < code_points.size(); ++i)
    {
        deus::CodePoint code_point = code_points[i];
        // clamp
        if(code_point > 255U)
        {
            code_point = 255U;
        }
        // then just cast the bits
        ret[i] = (char) code_point;
    }

    return ret;
}

} // namespace ascii_inl
DEUS_VERSION_NS_END
} // namespace deus

#endif
