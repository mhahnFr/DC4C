/*
 * DC4C - Standard data containers for C
 *
 * Written in 2023 - 2025 by mhahnFr
 *
 * This file is part of DC4C.
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along with DC4C,
 * see the file LICENSE. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef __DC4C_pair_h
 #warning Wrong inclusion of "pair.hpp" redirected to #include "pair.h"!
 #include "pair.h"
#else
 #ifndef __DC4C_pair_hpp
 #define __DC4C_pair_hpp
 
 #include <utility>

 /**
  * Defines the C++ helper functions for the pair.
  *
  * @param type1 the first contained type
  * @param type2 the second contained type
  * @param name the name of the pair
  */
 #define __dc4c_pair_methods_cxx(type1, type2, name)                            \
 namespace dc4c {                                                               \
 static inline std::pair<type1, type2> to_cpp(const dc4c::pair_##name & self) { \
     return std::make_pair(self.first, self.second);                            \
 }                                                                              \
                                                                                \
 static inline dc4c::pair_##name to_dc4c(const std::pair<type1, type2> & p) {   \
     return make_pair_##name(p.first, p.second);                                \
 }                                                                              \
 }

 /** The beginning of the namespace. */
 #define __dc4c_pair_namespace_begin namespace dc4c {
 /** The end of the namespace.       */
 #define __dc4c_pair_namespace_end   ; }
 /** The prefix of the namespace.    */
 #define __dc4c_pair_namespace_name  dc4c::

 #endif /* __DC4C_pair_hpp */
#endif /* __DC4C_pair_h */
