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
#ifndef DEUS_UNICODEVIEW_HPP_
#define DEUS_UNICODEVIEW_HPP_

#include <cstdint>
#include <string>
#include <vector>

#include "deus/API.h"

#include "deus/Constants.hpp"
#include "deus/UnicodeStorage.hpp"


namespace deus
{
DEUS_VERSION_NS_BEGIN

/*!
 * \brief TODO:
 */
class UnicodeView
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    // TODO: DOC
    UnicodeView();

    // TODO: DOC
    // TODO: throw TypeError
    UnicodeView(const char* s, deus::Encoding encoding = deus::SOURCE_ENCODING);

    // TODO: DOC
    // TODO: throw TypeError
    // TODO: figure out byte/length vs c_str_length and null terminator
    UnicodeView(
            const char* s,
            std::size_t c_str_length,
            deus::Encoding encoding = deus::SOURCE_ENCODING);

    // TODO: DOC
    // TODO: throw TypeError
    // TODO: figure out byte/length vs c_str_length and null terminator
    UnicodeView(
            const char* s,
            std::size_t c_str_length,
            std::size_t symbol_length,
            deus::Encoding encoding = deus::SOURCE_ENCODING);

    // TODO:
    // TODO: throw TypeError
    UnicodeView(
            const std::string& s,
            deus::Encoding encoding = deus::SOURCE_ENCODING);

    // TODO:
    // TODO: throw TypeError
    UnicodeView(
            const std::string& s,
            std::size_t symbol_length,
            deus::Encoding encoding = deus::SOURCE_ENCODING);

    explicit UnicodeView(const deus::UnicodeStorage& storage);

    // TODO:
    UnicodeView(const UnicodeView& other);

    // TODO:
    UnicodeView(UnicodeView&& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~UnicodeView();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assignment operator.
     */
    UnicodeView& operator=(const UnicodeView& other);

    /*!
     * \brief Move assignment operator.
     */
    UnicodeView& operator=(UnicodeView&& other);

    /*!
     * \brief Returns whether this string and the other given string consist of
     *        the same code points.
     *
     * \note This is not explicit memory equality, if the other string has a
     *       different encoding, it will be converted to this encoding and then
     *       the symbols will be compared. So this function compares whether the
     *       strings represent the same information. For explicit memory
     *       equality see explicit_equals().
     */
    bool operator==(const UnicodeView& other) const;

    /*!
     * \brief Returns whether this string and the other given string do not
     *        consist of the same code points.
     */
    bool operator!=(const UnicodeView& other) const;

    /*!
     * \brief Returns whether this string and the other given string consist of
     *        the same code points.
     *
     * \note This is not explicit memory equality, if the other string has a
     *       different encoding, it will be converted to this encoding and then
     *       the symbols will be compared. So this function compares whether the
     *       strings represent the same information. For explicit memory
     *       equality see explicit_equals().
     */
    bool operator==(const UnicodeStorage& other) const;

    /*!
     * \brief Returns whether this string and the other given string do not
     *        consist of the same code points.
     */
    bool operator!=(const UnicodeStorage& other) const;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Returns the encoding type used by Unicode string.
     */
    deus::Encoding encoding() const;

    // TODO: is null function

    /*!
     * \brief Returns the number of symbols in the string.
     *
     * This is the number of symbols not the number of bytes. This differs from
     * strlen() or std::string::length() since these function simply return the
     * number of bytes in the string (minus the null terminator). Unicode
     * strings may use multiple bytes to encoding a single character (or symbol)
     * so the symbol length may be different from the byte length.
     *
     * \note For non-ASCII encodings this function will perform lazy computation
     *       to find the number of symbols in the string.
     */
    std::size_t length() const;

    /*!
     * \brief Returns the number of bytes in the internal string data of this
     *        UnicodeView, this also includes the null terminator bytes of the
     *        data.
     */
    std::size_t byte_length() const;

    /*!
     * \brief Returns the number of character bytes in the internal string, this
     *        is the same as byte_length() but does not include the bytes of the
     *        nullptr.
     *
     * This length should be used for the length of C-style strings acquired via
     * c_str().
     */
    std::size_t c_str_length() const;

    /*!
     * \brief Returns the C-style string of the internal data of this
     *        UnicodeView.
     *
     * This is effectively the pointer to the first byte of this UnicodeView's
     * internal data.
     */
    const char* c_str() const;

    /*!
     * \brief Returns a new std::string created from a copy of the data held
     *        within this string.
     */
    std::string std_string() const;

    /*!
     * \brief Checks whether this string and the other given string have the
     *        same memory representation.
     *
     * This means that this function will always return ```false``` for strings
     * with different encodings.
     *
     * \note This function will also take the memory of the null terminator into
     *       account when comparing strings.
     */
    bool explicit_equals(const deus::UnicodeView& other) const;

    /*!
     * \brief Returns whether this is an empty string (i.e. both length() and
     *        c_str_length() are 0).
     */
    bool empty() const;

    /*!
     * \brief Returns the size in bytes of the symbol in this string at the
     *        given index.
     *
     * \param If the given symbol index is greater than or equal to the symbol
     *        length of this string, deus::NULL_POS is returned.
     */
    std::size_t size_of_symbol(std::size_t symbol_index) const;

    /*!
     * \brief Returns the smallest number of bytes allowed in a symbol by this
     *        string's encoding.
     */
    std::size_t minimum_symbol_size() const;

    // TODO: currently this maps to minimum_symbol_size -> this could just be
    //       removed
    /*!
     * \brief Returns the number of bytes used for the null terminator for the
     *        encoding of this string's type.
     */
    std::size_t null_terminator_size() const;

    /*!
     * \brief Returns the index of the byte in this string that the given symbol
     *        starts at.
     *
     * \note If the given symbol index is greater than the number of symbols in
     *       the string then the minimum byte size of its encoding is used for
     *       symbols past the end of the string.
     */
    std::size_t symbol_to_byte_index(std::size_t symbol_index) const;

    /*!
     * \brief Returns the index of the symbol in this string that the given byte
     *        starts within.
     *
     * \note If the given byte index is greater than the number of bytes in the
     *       string then the minimum byte size of its encoding is used for
     *       symbols past the end of the string.
     */
    std::size_t byte_to_symbol_index(std::size_t byte_index) const;

    /*!
     * \brief Returns whether this string starts with the other given string.
     *
     * If the strings have different encodings the input string will be
     * internally converted to the encoding type of this string.
     */
    bool starts_with(const deus::UnicodeView& other) const;

    /*!
     * \brief Returns whether this string ends with the other given string.
     *
     * If the strings have different encodings the input string will be
     * internally converted to the encoding type of this string.
     */
    bool ends_with(const deus::UnicodeView& other) const;

    /*!
     * \brief Finds the first occurrence of the given string within this string.
     *
     * If the strings have different encodings the input string will be
     * internally converted to the encoding type of this string.
     *
     * \param s The subject to search for.
     * \param pos The index of the symbol in this string to start searching
     *            from.
     *
     * \return The symbol index of the start of the first occurrence of the
     *         subject in this string. If the subject is not found,
     *         deus::NULL_POS is returned.
     */
    std::size_t find(const deus::UnicodeView& s, std::size_t pos) const;

    /*!
     * \brief Find the last occurrence of the given string within this string.
     *
     * If the strings have different encodings the input string will be
     * internally converted to the encoding type of this string.
     *
     * \param s The subject to search for.
     * \param pos The index of the symbol in this string to start searching
     *            from.
     *
     * \return The symbol index of the start of the last occurrence of the
     *         subject in this string. If the subject is not found,
     *         deus::NULL_POS is returned.
     */
    std::size_t rfind(const deus::UnicodeView& s, std::size_t pos) const;

    /*!
     * \brief Finds all non-overlapping occurrences of the given string within
     *        this string.
     *
     * If the strings have different encodings the input string will be
     * internally converted to the encoding type of this string.
     *
     * \note This searching for only non-overlapping occurrences of the subject.
     *       For example, if the subject was "choochoo", and this string contain
     *       "choochoochoo", only on 1 occurrence of the subject will be found
     *       at index 0: ">choochoo<choo".
     *
     * \param s The subject to search for.
     * \param pos The index of the symbol in this string to start searching
     *            from.
     *
     * \return An array of the indices of the first symbol of each of the
     *         occurrences of the subject in the order that they appear in this
     *         string.
     */
    std::vector<std::size_t> find_all(
        const deus::UnicodeView& s,
        std::size_t pos) const;

    // TODO: rfind_all?

    // TODO: validate encoding

    /*!
     * \brief Returns a new string that is a result of converting this string
     *        from its current encoding to the given encoding.
     *
     * When converting from Unicode to ASCII any Unicode characters that do not
     * have ascii representations will be replaced by the substitute character:
     * ␚ (0x1A).
     */
    deus::UnicodeStorage convert(deus::Encoding encoding) const;

    /*!
     * \brief Returns a UnicodeView which is the result of converting this
     *        string to the given encoding *but only if this string is not
     *        already in the given encoding*.
     *
     * This function is useful for requiring a string to be in a encoding, but
     * avoiding extra overhead if it is already in that encoding.
     *
     * \param expected_encoding The encoding the returned string will be in.
     * \param storage Reference to empty storage that will be used to store the
     *                converted string, but only if a conversion is required.
     */
    const deus::UnicodeView& convert_if_not(
            deus::Encoding expected_encoding,
            deus::UnicodeStorage& storage) const;

    /*!
     * \brief Returns a UnicodeView which is guaranteed to have an encoding that
     *        matches an encoding in the allowed_encodings bit mask.
     *
     * If this encoding is not in the allowed_encodings, a UnicodeView will be
     * returned to a version of the string converted to the convert_encoding,
     * otherwise this UnicodeVIew is simply returned.
     *
     * \param allowed_encodings Bitmask of the encodings which do not need
     *                          converting by this operation.
     * \param convert_encoding The encoding to convert this string to if it is
     *                         not in the allowed_encodings.
     * \param storage Reference to empty storage that will be used to store the
     *                converted string, but only if a conversion is required.
     */
    const deus::UnicodeView& convert_if_not(
            uint64_t allowed_encodings,
            deus::Encoding convert_encoding,
            deus::UnicodeStorage& storage) const;

    /*!
     * \brief Returns a new UnicodeStorage which is the result of concatenating
     *        the given string to end of this string.
     *
     * If the strings have different encodings the resulting string will be in
     * the encoding of this string.
     */
    deus::UnicodeStorage concatenate(const UnicodeView& s) const;

    /*!
     * \brief Returns new UnicodeStorage which is the result of repeating this
     *        string n number of times.
     *
     * \throw deus::ValueError If the n parameter is negative.
     */
    deus::UnicodeStorage repeat(int32_t n) const;

    // TODO: DOC
    // std::vector<deus::UnicodeStorage> split(const deus::UnicodeView delimiter);

    /*!
     * \brief Returns a vector of the bytes (not symbols) of this string
     *        converted to their hex representation in string format.
     *
     * The returned vector will contain the same number of elements as bytes in
     * this string minus the byte(s) of the null terminator.
     *
     * \param prefix The string each hex element will be prefiex with, e.g.
     *               "0x7F" where "0x" is the prefix.
     * \param uppercase Whether the letters in the hex values (A, B, C, D, E, F)
     *                  will be uppercase.
     */
    std::vector<deus::UnicodeStorage> bytes_as_hex(
            const deus::UnicodeView& prefix = "0x",
            bool uppercase = true) const;

private:

    //--------------------------------------------------------------------------
    //                              PRIVATE CLASSES
    //--------------------------------------------------------------------------

    class EncodingImpl;
    class ASCIIImpl;
    class UTF8Impl;
    // TODO: other implementations

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // TODO: DOC
    EncodingImpl* m_impl;
};

DEUS_VERSION_NS_END
} // namespace deus


//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

//----------------------------CONCATENATE OPERATORS-----------------------------

/*!
 * \brief Operator for performing UnicodeView::concatenate().
 */
inline deus::UnicodeStorage operator+(
        const char* a,
        const deus::UnicodeView& b)
{
    return deus::UnicodeView(a).concatenate(b);
}

/*!
 * \brief Operator for performing UnicodeView::concatenate().
 */
inline deus::UnicodeStorage operator+(
        const deus::UnicodeView& a,
        const deus::UnicodeView& b)
{
    return a.concatenate(b);
}

//-------------------------------REPEAT OPERATORS-------------------------------

/*!
 * \brief Operator for performing UnicodeView::concatenate().
 */
inline deus::UnicodeStorage operator*(const deus::UnicodeView& a, int32_t n)
{
    return a.repeat(n);
}

//-------------------------------STREAM OPERATORS-------------------------------

/*!
 * \brief Appends the string contents of the given UnicodeView to the stream.
 */
inline std::ostream& operator<<(
        std::ostream& stream,
        const deus::UnicodeStorage& str)
{
    // TODO: is there anyway to find the internal type of the string so we can
    //       avoid conversion?
    stream << str.get_view().convert(deus::Encoding::kUTF8).get_string();
    return stream;
}

#endif
