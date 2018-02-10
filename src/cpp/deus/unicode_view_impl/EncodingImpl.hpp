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
#ifndef DEUS_UNICODEVIEWIMPL_ENCODINGIMPL_HPP_
#define DEUS_UNICODEVIEWIMPL_ENCODINGIMPL_HPP_

#include "deus/UnicodeView.hpp"


namespace deus
{

/*!
 * \brief TODO:
 */
class UnicodeView::EncodingImpl
{
public:

    //--------------------------------------------------------------------------
    //                             PUBLIC ATTRIBUTES
    //--------------------------------------------------------------------------

    // TODO: DOC
    mutable std::size_t m_ref_count;
    // TODO: DOC
    deus::Encoding m_encoding;
    // TODO: DOC
    mutable std::size_t m_byte_length;
    // TODO: DOC
    mutable std::size_t m_symbol_length;
    // TODO: DOC
    const char* m_data;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    // TODO:
    EncodingImpl(
            deus::Encoding encoding,
            std::size_t byte_length,
            std::size_t symbol_length,
            const char* s);

    EncodingImpl(const EncodingImpl&) = delete;
    EncodingImpl(EncodingImpl&&) = delete;

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~EncodingImpl();

    //--------------------------------------------------------------------------
    //                          PUBLIC STATIC FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Constructs a new encoding implementation from the provided
     *        encoding type.
     *
     * \param encoding The encoding type to construct a new implementation for.
     * \param s The string data that the new encoding will use.
     * \param byte_length The number of bytes in the string data (including the
     *                    null terminator). If the byte length is not yet known
     *                    this will be represented by deus::NULL_POS.
     * \param symbol_length The number f actual character symbols in the string.
     *                      If the symbol length is not yet known this will be
     *                      represented by deus::NULL_POS.
     *
     * \throw deus::TypeError If the given encoding type is not a recognized
     *                        encoding.
     */
    static deus::UnicodeView::EncodingImpl* new_encoding(
            deus::Encoding encoding,
            std::size_t byte_length,
            std::size_t symbol_length,
            const char* s);

    /*!
     * \brief Returns the size in bytes of the given encoding's null terminator.
     */
    static std::size_t null_terminator_size(deus::Encoding encoding);

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    EncodingImpl& operator=(const EncodingImpl&) = delete;
    EncodingImpl& operator=(EncodingImpl&&) = delete;
    bool operator==(const EncodingImpl&) const = delete;
    bool operator!=(const EncodingImpl&) const = delete;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    // TODO: DOC
    virtual void compute_byte_length() const = 0;

    // TODO: DOC
    virtual void compute_symbol_length() const = 0;
};

} // namespace deus

#endif
