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
#include <vector>

#include "deus/API.h"
#include "deus/Constants.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class UnicodeView;

/*!
 * \brief An Object used to store an Unicode string and an associated
 *        deus::UnicodeView.
 *
 * UnicodeStorage can be used when constructing Unicode strings and the
 * existence of the associated view means the any metadata that the view needs
 * to compute for the string (such as symbol length) only needs to be done once.
 *
 * This object can also be used to construct encoded strings from raw code
 * points
 */
class UnicodeStorage
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Constructs a new empty string with the given source encoding.
     *
     * \note While it might seem that the encoding of an empty string is
     *       irrelevant, it affects the size of the null terminator and this
     *       strings interaction with other strings.
     */
    explicit UnicodeStorage(deus::Encoding encoding = deus::SOURCE_ENCODING);

    /*!
     * \brief Constructs a new string by copying the string referenced by the
     *        given deus::UnicodeView.
     */
    UnicodeStorage(const deus::UnicodeView& view);

    /*!
     * \brief Constructs a new Unicode string in the given encoding from a list
     *        of Unicode code points.
     */
    UnicodeStorage(
            const std::vector<deus::CodePoint>& code_points,
            deus::Encoding encoding = deus::SOURCE_ENCODING);

    /*!
     * \brief Creates new storage containing the given string by moving it.
     *
     * \note The encoding parameter is not optional for this constructor, this
     *       is purely to avoid creating an ambiguous definition with
     *       UnicodeStorage(const deus::UnicodeView& view) which std::string
     *       can be implicitly casted to.
     *
     * \param str The string to move and use as the contents of the storage.
     * \param encoding The encoding of the given string.
     */
    UnicodeStorage(
            std::string&& str,
            deus::Encoding encoding);

    /*!
     * \brief Creates new storage containing the given string by moving it.
     *
     * \param str The string to move and use as the contents of the storage.
     * \param symbol_length The number of symbols in the string.
     * \param encoding The encoding of the given string.
     */
    UnicodeStorage(
            std::string&& str,
            std::size_t symbol_length,
            deus::Encoding encoding);

    /*!
     * \brief Constructs a copy of the given UnicodeStorage.
     */
    UnicodeStorage(const UnicodeStorage& other);

    /*!
     * \brief Constructs new UnicodeStorage by moving the resource of the other
     *        given UnicodeStorage.
     */
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

    /*!
     * \brief Returns whether this string and the other given string consist of
     *        the same code points.
     *
     * \note This is not explicit memory equality, if the other string has a
     *       different encoding, it will be converted to this encoding and then
     *       the symbols will be compared. So this function compares whether the
     *       strings represent the same information. For explicit memory
     *       equality see deus::UnicodeView::explicit_equals().
     */
    bool operator==(const UnicodeStorage& other) const;

    /*!
     * \brief Returns whether this string and the other given string do not
     *        consist of the same code points.
     */
    bool operator!=(const UnicodeStorage& other) const;

    /*!
     * \brief Returns whether this string and the other given string consist of
     *        the same code points.
     *
     * \note This is not explicit memory equality, if the other string has a
     *       different encoding, it will be converted to this encoding and then
     *       the symbols will be compared. So this function compares whether the
     *       strings represent the same information. For explicit memory
     *       equality see deus::UnicodeView::explicit_equals().
     */
    bool operator==(const deus::UnicodeView& other) const;

    /*!
     * \brief Returns whether this string and the other given string do not
     *        consist of the same code points.
     */
    bool operator!=(const deus::UnicodeView& other) const;

    /*!
     * \brief Implicitly converts this UnicodeStorage to a std::string.
     */
    operator std::string() const;

    /*!
     * \brief Implicitly converts this UnicodeStorage to a deus::UnicodeView.
     */
    operator deus::UnicodeView() const;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Returns the std::string that contains the data stored by this
     *        object.
     */
    const std::string& get_string() const;

    /*!
     * \brief Returns the dues::UnicodeView this storage is using to handle its
     *        string data.
     */
    const UnicodeView& get_view() const;

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    std::string m_str;
    std::unique_ptr<deus::UnicodeView> m_view;
};

DEUS_VERSION_NS_END
} // namespace deus

// TODO: Hash

#endif
