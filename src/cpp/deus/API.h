/*!
 * \file
 * \author David Saxon
 * \brief Provides specifics for passing Deus data through C interfaces.
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
#ifndef DEUS_CINTERFACE_H_
#define DEUS_CINTERFACE_H_


#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * \brief Defines the current version number of the Deus API.
 *
 * \note The API version is a single number because of it's use in the Deus
 *       namespace.
 */
#define DEUS_API_VERSION 0

#define DEUS_BUILD_VER_NS2(ver) v##ver
#define DEUS_BUILD_VER_NS(ver) DEUS_BUILD_VER_NS2(ver)

/*!
 * \brief The version namespace being used for the Deus API.
 */
#define DEUS_VERSION_NS DEUS_BUILD_VER_NS(DEUS_API_VERSION)

// TODO: DOC
#define DEUS_VERSION_NS_BEGIN
#ifndef IN_DOXYGEN
    #undef DEUS_VERSION_NS_BEGIN
    #define DEUS_VERSION_NS_BEGIN inline namespace DEUS_VERSION_NS {
#endif

// TODO: DOC
#define DEUS_VERSION_NS_END
#ifndef IN_DOXYGEN
    #undef DEUS_VERSION_NS_END
    #define DEUS_VERSION_NS_END }
#endif

/*!
 * \brief Marco used to force inlining of a function.
 */
#define DEUS_FORCE_INLINE inline
#if defined(_MSC_VER)
    #undef DEUS_FORCE_INLINE
    #define DEUS_FORCE_INLINE __forceinline
#elif defined(__clang__) || defined(__GNUC__) || defined(__INTEL_COMPILER)
    #undef DEUS_FORCE_INLINE
    #define DEUS_FORCE_INLINE static __attribute__((always_inline))
#endif

/*!
 * \brief Defines the value that represents ASCII encoding.
 */
#define kDeusEncodingASCII    1U
/*!
 * \brief Defines the value that represents UTF-8 encoding.
 */
#define kDeusEncodingUTF8     2U
/*!
 * \brief Defines the value that represents Little Endian UTF-16 encoding.
 */
#define kDeusEncodingUTF16_LE 4U
/*!
 * \brief Defines the value that represents Big Endian UTF-16 encoding.
 */
#define kDeusEncodingUTF16_BE 8U
/*!
 * \brief Defines the value that represents Little Endian UTF-32 encoding.
 */
#define kDeusEncodingUTF32_LE 16U
/*!
 * \brief Defines the value that represents Big Endian UTF-32 encoding.
 */
#define kDeusEncodingUTF32_BE 32U


#ifdef __cplusplus
}; // extern "C"
#endif

#endif
