/*
 * DC4C - Standard data containers for C
 *
 * Copyright (C) 2023  mhahnFr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef pair_h
 #warning Wrong inclusion of "pair.hpp" redirected to #include "pair.h"!
 #include "pair.h"
#else
 #ifndef pair_hpp
 #define pair_hpp
 
 #include <utility>
 
 #define pair_methods_cxx(type1, type2, name)                                                     \
 namespace dc4c {                                                                                 \
 constexpr static inline auto to_cpp(const dc4c::pair_##name & self) -> std::pair<type1, type2> { \
     return std::make_pair(self.first, self.second);                                              \
 }                                                                                                \
                                                                                                  \
 constexpr static inline auto to_dc4c(const std::pair<type1, type2> & p) -> dc4c::pair_##name {   \
     return make_pair_##name(p.first, p.second);                                                  \
 }                                                                                                \
 }
 
 #define pair_namespace_begin namespace dc4c {
 #define pair_namespace_end   ; }
 #define pair_namespace_name  dc4c::

 #endif /* pair_hpp */
#endif
