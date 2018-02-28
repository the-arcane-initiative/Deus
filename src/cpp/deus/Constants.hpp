/*!
 * \file
 * \author David Saxon
 * \brief Provides the global constants used by the Deus library.
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
#ifndef DEUS_CONSTANTS_HPP_
#define DEUS_CONSTANTS_HPP_

#include <cstddef>
#include <cstdint>

#include "deus/API.h"


namespace deus
{

inline namespace DEUS_VERSION_NS
{

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

/*!
 * \brief Type that an be used to represent a Unicode code point.
 */
typedef uint32_t CodePoint;

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

/*!
 * \brief TODO: DOC
 */
enum class Encoding : uint64_t
{
    kASCII    = kDeusEncodingASCII,
    /// TODO: DOC
    kUTF8     = kDeusEncodingUTF8,
    // TODO: DOC
    /// TODO: DOC
    kUTF16_LE = kDeusEncodingUTF16_LE,
    /// TODO: DOC
    kUTF16_BE = kDeusEncodingUTF16_BE,
    /// TODO: DOC
    kUTF32_LE = kDeusEncodingUTF32_LE,
    /// TODO: DOC
    kUTF32_BE = kDeusEncodingUTF32_BE
    // TODO: support utf7?
};

//------------------------------------------------------------------------------
//                                ENCODING HELPER
//------------------------------------------------------------------------------

inline constexpr deus::Encoding determine_source_encoding()
{
    // Thanks to Kronikarz from: https://www.reddit.com/r/cpp/comments/75gohf/
    // i_just_found_a_use_for_the_poop_emoji_in_c/
    return
        (static_cast<unsigned char>("💩"[0]) == 0xF0 &&
         static_cast<unsigned char>("💩"[1]) == 0x9F &&
         static_cast<unsigned char>("💩"[2]) == 0x92 &&
         static_cast<unsigned char>("💩"[3]) == 0xA9)
            ?
            deus::Encoding::kUTF8
            :
        (static_cast<unsigned char>("💩"[0]) == 0xA9 &&
         static_cast<unsigned char>("💩"[1]) == 0xDC &&
         static_cast<unsigned char>("💩"[2]) == 0x3D &&
         static_cast<unsigned char>("💩"[3]) == 0xD8)
            ?
            deus::Encoding::kUTF16_LE
            :
        (static_cast<unsigned char>("💩"[0]) == 0xD8 &&
         static_cast<unsigned char>("💩"[1]) == 0x3D &&
         static_cast<unsigned char>("💩"[2]) == 0xDC &&
         static_cast<unsigned char>("💩"[3]) == 0xA9)
            ?
            deus::Encoding::kUTF16_BE
            :
        (static_cast<unsigned char>("💩"[0]) == 0xA9 &&
         static_cast<unsigned char>("💩"[1]) == 0xF4 &&
         static_cast<unsigned char>("💩"[2]) == 0x01 &&
         static_cast<unsigned char>("💩"[3]) == 0x00)
            ?
            deus::Encoding::kUTF32_LE
            :
        (static_cast<unsigned char>("💩"[0]) == 0x00 &&
         static_cast<unsigned char>("💩"[1]) == 0x01 &&
         static_cast<unsigned char>("💩"[2]) == 0xF4 &&
         static_cast<unsigned char>("💩"[3]) == 0xA9)
            ?
            deus::Encoding::kUTF32_BE
            :
            deus::Encoding::kASCII;
}

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

/*!
 * \brief Value used to signify an invalid string length or index.
 */
extern const std::size_t NULL_POS;

/*!
 * \brief The encoding type used by the compiler for the current source code.
 */
static constexpr deus::Encoding SOURCE_ENCODING = determine_source_encoding();

/*!
 * \brief Bitwise OR of the encodings that are ASCII compatible.
 */
extern const uint64_t ASCII_COMPATIBLE_ENCODINGS;

} // namespace DEUS_VERSION_NS
} // namespace deus

#endif
