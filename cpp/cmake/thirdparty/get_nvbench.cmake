# =============================================================================
# Copyright (c) 2023, NVIDIA CORPORATION.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
# in compliance with the License. You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the License
# is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
# or implied. See the License for the specific language governing permissions and limitations under
# the License.
# =============================================================================

# This function finds nvbench and applies any needed patches.
function(find_and_configure_nvbench)

  include(${rapids-cmake-dir}/cpm/nvbench.cmake)
  include(${rapids-cmake-dir}/cpm/package_override.cmake)

  set(cudf_patch_dir "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/patches")
  rapids_cpm_package_override("${cudf_patch_dir}/nvbench_override.json")

  rapids_cpm_nvbench()

endfunction()

find_and_configure_nvbench()
