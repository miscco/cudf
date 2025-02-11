/*
 * Copyright (c) 2021-2023, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <cudf/scalar/scalar.hpp>
#include <cudf/strings/strings_column_view.hpp>

#include <rmm/mr/device/per_device_resource.hpp>

namespace cudf {
namespace strings {
/**
 * @addtogroup strings_copy
 * @{
 * @file
 * @brief Strings APIs for copying strings.
 */

/**
 * @brief Repeat the given string scalar a given number of times
 *
 * An output string scalar is generated by repeating the input string by a number of times given by
 * the `repeat_times` parameter.
 *
 * In special cases:
 *  - If `repeat_times` is not a positive value, an empty (valid) string scalar will be returned.
 *  - An invalid input scalar will always result in an invalid output scalar regardless of the
 *    value of `repeat_times` parameter.
 *
 * @code{.pseudo}
 * Example:
 * s   = '123XYZ-'
 * out = repeat_strings(s, 3)
 * out is '123XYZ-123XYZ-123XYZ-'
 * @endcode
 *
 * @throw std::overflow_error if the size of the output string scalar exceeds the maximum value that
 *        can be stored by the scalar: `input.size() * repeat_times > max of size_type`
 *
 * @param input The scalar containing the string to repeat
 * @param repeat_times The number of times the input string is repeated
 * @param mr Device memory resource used to allocate the returned string scalar
 * @return New string scalar in which the input string is repeated
 */
std::unique_ptr<string_scalar> repeat_string(
  string_scalar const& input,
  size_type repeat_times,
  rmm::mr::device_memory_resource* mr = rmm::mr::get_current_device_resource());

/**
 * @brief Repeat each string in the given strings column a given number of times
 *
 * An output strings column is generated by repeating each string from the input strings column by
 * the number of times given by the `repeat_times` parameter.
 *
 * In special cases:
 *  - If `repeat_times` is not a positive number, a non-null input string will always result in
 *    an empty output string.
 *  - A null input string will always result in a null output string regardless of the value of the
 *    `repeat_times` parameter.
 *
 * @code{.pseudo}
 * Example:
 * strs = ['aa', null, '', 'bbc']
 * out  = repeat_strings(strs, 3)
 * out is ['aaaaaa', null, '', 'bbcbbcbbc']
 * @endcode
 *
 * @param input The column containing strings to repeat
 * @param repeat_times The number of times each input string is repeated
 * @param mr Device memory resource used to allocate the returned strings column
 * @return New column containing the repeated strings
 */
std::unique_ptr<column> repeat_strings(
  strings_column_view const& input,
  size_type repeat_times,
  rmm::mr::device_memory_resource* mr = rmm::mr::get_current_device_resource());

/**
 * @brief Repeat each string in the given strings column by the numbers of times given in another
 * numeric column
 *
 * An output strings column is generated by repeating each of the input string by a number of times
 * given by the corresponding row in a `repeat_times` numeric column.
 *
 * In special cases:
 *  - Any null row (from either the input strings column or the `repeat_times` column) will always
 *    result in a null output string.
 *  - If any value in the `repeat_times` column is not a positive number and its corresponding input
 *    string is not null, the output string will be an empty string.
 *
 * @code{.pseudo}
 * Example:
 * strs         = ['aa', null, '', 'bbc-']
 * repeat_times = [ 1,   2,     3,  4   ]
 * out          = repeat_strings(strs, repeat_times)
 * out is ['aa', null, '', 'bbc-bbc-bbc-bbc-']
 * @endcode
 *
 * @throw cudf::logic_error if the input `repeat_times` is not an integer type
 * @throw cudf::logic_error if the input columns have different sizes.
 *
 * @param input The column containing strings to repeat
 * @param repeat_times The column containing numbers of times that the corresponding input strings
 *                     are repeated
 * @param mr Device memory resource used to allocate the returned strings column
 * @return New column containing the repeated strings.
 */
std::unique_ptr<column> repeat_strings(
  strings_column_view const& input,
  column_view const& repeat_times,
  rmm::mr::device_memory_resource* mr = rmm::mr::get_current_device_resource());

/** @} */  // end of doxygen group
}  // namespace strings
}  // namespace cudf
