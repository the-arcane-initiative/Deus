#ifndef DEUS_PERFORMANCETESTS_UTIL_HPP_
#define DEUS_PERFORMANCETESTS_UTIL_HPP_

#include <cstddef>

#include <deus/Constants.hpp>
#include <deus/UnicodeView.hpp>


namespace deus_perf_util
{

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

enum class StringSize
{
    kShort,
    kMedium,
    kLong,
    kExtraLong,
    kMixed
};

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

// Resets all generator functions
void clear_generators();

// Generates a random sequence of dynamically allocated strings of deterministic
// lengths.
void gen_rand_dyn_strs(
        deus::Encoding encoding,
        deus_perf_util::StringSize string_size);

// Returns the next randomly generated dynamically allocated string in the
// the sequence. note: the gen_rand_dyn_strs function must have been called
// first
const char* get_next_rand_dyn_str(std::size_t& byte_length);

// Generates a random sequence of dynamically allocated strings of deterministic
// length store within UnicodeViews.
void gen_rand_dyn_views(
        deus::Encoding encoding,
        deus_perf_util::StringSize string_size);

// Returns the next randomly generated dynamically allocated string inside a
// view in the sequence. note: the gen_rand_dyn_views function must have been
// called first
const deus::UnicodeView& get_next_rand_dyn_view();


} // namespace deus_perf_util

#endif
