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
#ifndef DEUS_UNICODESTORAGE_HPP_
#define DEUS_UNICODESTORAGE_HPP_

#include <cstdint>
#include <memory>
#include <string>

#include "deus/Constants.hpp"


namespace deus
{

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class UnicodeView;

/*!
 * \brief TODO:
 */
class UnicodeStorage
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    // TODO: DOC
    // TODO: throw TypeError
    UnicodeStorage(deus::Encoding encoding = deus::SOURCE_ENCODING);

    // TODO: DOC
    UnicodeStorage(const deus::UnicodeView& view);

    // TODO: DOC
    UnicodeStorage(const UnicodeStorage& other);

    // TODO: DOC
    UnicodeStorage(UnicodeStorage&& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~UnicodeStorage();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief UnicodeView assignment operator.
     */
    UnicodeStorage& operator=(const UnicodeView& view);

    /*!
     * \brief Copy assignment operator.
     */
    UnicodeStorage& operator=(const UnicodeStorage& other);

    /*!
     * \brief Move assignment operator.
     */
    UnicodeStorage& operator=(UnicodeStorage&& other);

    // TODO: re-enable
    // /*!
    //  * \brief TODO:
    //  */
    // bool operator==(const UnicodeStorage& other) const;

    // /*!
    //  * \brief TODO:
    //  */
    // bool operator!=(const UnicodeStorage& other) const;

    // TODO: DOC
    operator std::string() const;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    std::string m_str;
    // TODO: should this be a pointer?
    std::unique_ptr<deus::UnicodeView> m_view;
};

// TODO: Hash

} // namespace deus

#endif
