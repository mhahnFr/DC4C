/*
 * DC4C - Standard data containers for C
 *
 * Written in 2023 - 2024 by mhahnFr
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

#ifndef __DC4C_optional_h
 #warning Wrong inclusion of "optional.hpp" redirected to #include "optional.h"!
 #include "optional.h"
#else
 #ifndef __DC4C_optional_hpp
 #define __DC4C_optional_hpp
 
 #if __cplusplus >= 201703L
  #include <optional>
  
  #define __dc4c_optional_methods_cxx(type, name)                                                  \
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
  #define __dc4c_optional_methods_cxx(type, name)
 #endif
 
 #define __dc4c_optional_namespace_begin namespace dc4c {
 #define __dc4c_optional_namespace_end   }
 #define __dc4c_optional_namespace_name  dc4c::

 #endif /* __DC4C_optional_hpp */
#endif /* __DC4C_optional_h */
