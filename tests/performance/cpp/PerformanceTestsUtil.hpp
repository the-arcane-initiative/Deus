#ifndef DEUS_PERFORMANCETESTS_UTIL_HPP_
#define DEUS_PERFORMANCETESTS_UTIL_HPP_

#include <cstddef>


namespace deus_perf_util
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

// Resets all generator functions
void clear_generators();

// Returns a random dynamically allocated string of a deterministic varying
// length
void gen_rand_dyn_str(const char** str, std::size_t& byte_length);

} // namespace deus_perf_util

#endif
