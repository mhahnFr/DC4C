/*
 * DC4C - Standard data containers for C
 *
 * Copyright (C) 2023 - 2024  mhahnFr
 *
 * This file is part of DC4C.
 *
 * DC4C is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DC4C is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * DC4C, see the file LICENSE.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __DC4C_pair_h
 #warning Wrong inclusion of "pair.hpp" redirected to #include "pair.h"!
 #include "pair.h"
#else
 #ifndef __DC4C_pair_hpp
 #define __DC4C_pair_hpp
 
 #include <utility>
 
 #define pair_methods_cxx(type1, type2, name)                                           \
 namespace dc4c {                                                                       \
 static inline auto to_cpp(const dc4c::pair_##name & self) -> std::pair<type1, type2> { \
     return std::make_pair(self.first, self.second);                                    \
 }                                                                                      \
                                                                                        \
 static inline auto to_dc4c(const std::pair<type1, type2> & p) -> dc4c::pair_##name {   \
     return make_pair_##name(p.first, p.second);                                        \
 }                                                                                      \
 }
 
 #define pair_namespace_begin namespace dc4c {
 #define pair_namespace_end   ; }
 #define pair_namespace_name  dc4c::

 #endif /* __DC4C_pair_hpp */
#endif /* __DC4C_pair_h */
