/*
 * DC4C - Standard data containers for C
 *
 * Written in 2023 - 2026 by mhahnFr
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

#ifndef _dc4c_optional_h
 #warning Wrong inclusion of "optional.hpp" redirected to #include "optional.h"!
 #include "optional.h"
#else
 #ifndef _dc4c_optional_hpp
 #define _dc4c_optional_hpp
 
 #if __cplusplus >= 201703L
  #include <optional>

  /**
   * Defines the C++ helper functions into the namespace @c dc4c .
   *
   * @param type the contained type
   * @param name the name of the C optional
   */
  #define _dc4c_optional_methods_cxx(type, name)                                                  \
  namespace dc4c {                                                                                 \
  constexpr static inline auto to_cpp(const optional_##name & self) -> std::optional<type> { \
      if (self.has_value) {                                                                        \
          return self.value;                                                                       \
      }                                                                                            \
      return std::nullopt;                                                                         \
  }                                                                                                \
                                                                                                   \
  constexpr static inline auto to_dc4c(const std::optional<type> & opt) -> optional_##name { \
      if (opt.has_value()) {                                                                       \
          return { true, opt.value() };                                                            \
      }                                                                                            \
                                                                                                   \
      auto toReturn = optional_##name();                                                     \
      toReturn.has_value = false;                                                                  \
      return toReturn;                                                                             \
  }                                                                                                \
  }
 #else
  #define _dc4c_optional_methods_cxx(type, name)
 #endif

 #endif /* _dc4c_optional_hpp */
#endif /* _dc4c_optional_h */
