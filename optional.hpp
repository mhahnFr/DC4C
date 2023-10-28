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

#ifndef optional_h
 #warning Wrong inclusion of "optional.hpp" redirected to #include "optional.h"!
 #include "optional.h"
#else
 #ifndef optional_hpp
 #define optional_hpp
 
 #if __cplusplus >= 201703L
  #include <optional>
  
  #define optional_methods_cxx(type, name)                                                         \
  namespace dc4c {                                                                                 \
  constexpr static inline auto to_cpp(const dc4c::optional_##name & self) -> std::optional<type> { \
      if (self.has_value) {                                                                        \
          return self.value;                                                                       \
      }                                                                                            \
      return std::nullopt;                                                                         \
  }                                                                                                \
                                                                                                   \
  constexpr static inline auto to_dc4c(const std::optional<type> & opt) -> dc4c::optional_##name { \
      if (opt.has_value()) {                                                                       \
          return { true, opt.value() };                                                            \
      }                                                                                            \
                                                                                                   \
      auto toReturn = dc4c::optional_##name();                                                     \
      toReturn.has_value = false;                                                                  \
      return toReturn;                                                                             \
  }                                                                                                \
  }
 #else
  #define optional_methods_cxx(type, name)
 #endif
 
 #define optional_namespace_begin namespace dc4c {
 #define optional_namespace_end   }
 #define optional_namespace_name  dc4c::

 #endif /* optional_hpp */
#endif
