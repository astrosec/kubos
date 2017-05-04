# Copyright 2015 ARM Limited
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

message("suppressing warnings from stm32cubef4")

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set_target_properties(stm32cubef4
        PROPERTIES COMPILE_FLAGS "-Wno-sign-compare -Wno-unused-variable -Wno-unused-parameter"
    )
endif()