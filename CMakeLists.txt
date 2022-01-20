# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(NO_BUILD_TYPE_WARNING 1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(inki_firmware)

enable_language(ASM)

set(WAMR_BUILD_PLATFORM "zephyr")
set(WAMR_BUILD_TARGET "THUMBV7_VFP")
set(WAMR_BUILD_INTERP 1)
set(WAMR_BUILD_AOT 1)
set(WAMR_BUILD_JIT 0)
set(WAMR_BUILD_LIBC_WASI 0)
set(WAMR_BUILD_LIBC_BUILTIN 1)
set(WAMR_BUILD_FAST_INTERP 1)
set(WAMR_BUILD_LIB_PTHREAD 1)
set(WAMR_BUILD_MULTI_MODULE 1)
set(WAMR_BUILD_MINI_LOADER 1)

set (LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_conf.h
    CACHE STRING "" FORCE)

set (WAMR_ROOT_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm)


add_subdirectory(lvgl)
include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake) 

file(GLOB_RECURSE app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})

file(GLOB_RECURSE disk_lib src/lib/*/*.c src/lib/*/*.h)
target_sources(app PRIVATE ${disk_lib})

list(APPEND ZEPHYR_EXTRA_MODULES
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/display
)

target_link_libraries(app PUBLIC lvgl -lgcc)
