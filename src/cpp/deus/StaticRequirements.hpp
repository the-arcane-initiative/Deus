/*!
 * \file
 * \author David Saxon
 * \brief Provides macros for compile requirements on source/compiler encodings.
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
#ifndef DEUS_STATICREQUIREMENTS_HPP_
#define DEUS_STATICREQUIREMENTS_HPP_

/*!
 * \brief Use of this macro anywhere within a project will check at compile time
 *        whether the compiler encodes string literals using UTF-8.
 *
 * Thanks to Kronikarz from: https://www.reddit.com/r/cpp/comments/75gohf/
 * i_just_found_a_use_for_the_poop_emoji_in_c/
 */
#define DEUS_REQUIRE_SOURCE_UTF8                                               \
    static_assert(                                                             \
        (static_cast<unsigned char>("💩"[0]) == 0xF0) &&                       \
        (static_cast<unsigned char>("💩"[1]) == 0x9F) &&                       \
        (static_cast<unsigned char>("💩"[2]) == 0x92) &&                       \
        (static_cast<unsigned char>("💩"[3]) == 0xA9),                         \
        "Source or compiler is not UTF-8 compliant."                           \
    );

// TODO: other encodings

#endif
