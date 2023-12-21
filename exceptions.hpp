// -*- C++ -*-
//
// Copyright 2023 Dmitry Igrishin
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DMITIGR_WINBASE_EXCEPTIONS_HPP
#define DMITIGR_WINBASE_EXCEPTIONS_HPP

#include "../base/exceptions.hpp"
#include "windows.hpp"

#include <string>
#include <system_error>

namespace dmitigr::winbase {

// -----------------------------------------------------------------------------
// Exception
// -----------------------------------------------------------------------------

/**
 * @ingroup errors
 *
 * @brief The generic exception class.
 */
class Exception : public dmitigr::Exception {
  using dmitigr::Exception::Exception;
};

// -----------------------------------------------------------------------------
// Sys_exception
// -----------------------------------------------------------------------------

/**
 * @ingroup errors
 *
 * @brief An exception thrown on system error.
 */
class Sys_exception final : public Exception {
public:
  /// The constructor.
  Sys_exception(const DWORD ev, const std::string& what)
    : Exception{std::system_category()
        .default_error_condition(static_cast<int>(ev)), what}
  {}

  /// @overload
  Sys_exception(const LSTATUS ev, const std::string& what)
    : Sys_exception{static_cast<DWORD>(ev), what}
  {}

  /// @overload
  explicit Sys_exception(const std::string& what)
    : Sys_exception{GetLastError(), what}
  {}

};

} // namespace dmitigr::winbase

#endif  // DMITIGR_WINBASE_EXCEPTIONS_HPP
