/*!
 * \file
 * \author David Saxon
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
#ifndef DEUS_UNICODEVIEWIMPL_UTF8IMPL_HPP_
#define DEUS_UNICODEVIEWIMPL_UTF8IMPL_HPP_

#include "deus/UnicodeView.hpp"
#include "deus/unicode_view_impl/EncodingImpl.hpp"


namespace deus
{

/*!
 * \brief The implementation of UTF-8 encoding specific logic for the
 *        deus::UnicodeView class.
 */
class UnicodeView::UTF8Impl
    : public UnicodeView::EncodingImpl
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Constructs a new UTF-8 encoding implementation using he given
     *        parameters.
     */
    UTF8Impl(
            std::size_t byte_length,
            std::size_t symbol_length,
            const char* s);

    // deleted
    UTF8Impl(const UTF8Impl&) = delete;
    UTF8Impl(UTF8Impl&&) = delete;

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~UTF8Impl();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    // deleted
    UTF8Impl& operator=(const UTF8Impl&) = delete;
    UTF8Impl& operator=(UTF8Impl&&) = delete;
    bool operator==(const UTF8Impl&) const = delete;
    bool operator!=(const UTF8Impl&) const = delete;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void compute_byte_length() const override;

    virtual void compute_symbol_length() const override;

private:

    //--------------------------------------------------------------------------
    //                          PRIVATE STATIC FUNCTIONS
    //--------------------------------------------------------------------------

    //-------------------COMPUTE BYTE LENGTH IMPLEMENTATIONS--------------------

    static void compute_byte_length_naive(
            const char* in_data,
            std::size_t& out_byte_length,
            std::size_t& out_symbol_length);
};

//------------------------------------------------------------------------------
//                                GLOBAL FUNCTIONS
//------------------------------------------------------------------------------

namespace utf8_impl
{

//-----------------------FROM CODE POINT IMPLEMENTATIONS------------------------

std::string from_code_point_naive(
        const std::vector<deus::CodePoint>& code_points);

//---------------------COMPUTE BYTE LENGTH IMPLEMENTATIONS----------------------

void compute_byte_length_naive(
        const char* in_data,
        std::size_t& out_byte_length,
        std::size_t& out_symbol_length);

void compute_byte_length_wstring_convert(
        const char* in_data,
        std::size_t& out_byte_length,
        std::size_t& out_symbol_length);

// TODO:
void compute_byte_length_byte_jump(
        const char* in_data,
        std::size_t& out_byte_length,
        std::size_t& out_symbol_length);

void compute_byte_length_word_batching(
        const char* in_data,
        std::size_t& out_byte_length,
        std::size_t& out_symbol_length);

void compute_byte_length_simd_batching(
        const char* in_data,
        std::size_t& out_byte_length,
        std::size_t& out_symbol_length);

} // namespace utf8_impl
} // namespace deus

#endif
