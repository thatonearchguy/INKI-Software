# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(NO_BUILD_TYPE_WARNING 1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(inki_firmware)

enable_language(ASM)

set(WAMR_BUILD_PLATFORM "zephyr")
set(WAMR_BUILD_TARGET "THUMBV7")
set(WAMR_BUILD_INTERP 0)
set(WAMR_BUILD_AOT 1)
set(WAMR_BUILD_JIT 0)
set(WAMR_BUILD_APP_FRAMEWORK 1)
set(WAMR_BUILD_SHARED_MEMORY 1)
set(WAMR_BUILD_LIBC_WASI 0)
set(WAMR_BUILD_LIBC_BUILTIN 1)
set(WAMR_BUILD_FAST_INTERP 0)
set(WAMR_BUILD_LIB_PTHREAD 0)
set(WAMR_BUILD_MULTI_MODULE 1)
set(WAMR_BUILD_MINI_LOADER 0)
set (WAMR_BUILD_APP_LIST WAMR_APP_BUILD_BASE)

add_definitions(-DMARK_ONE=1)

set (LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_conf.h
    CACHE STRING "" FORCE)

set (WAMR_ROOT_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm)

set (MCUBOOT_DIR $ENV{ZEPHYR_BASE}/../bootloader/mcuboot)

add_compile_options(-fdata-sections -ffunction-sections)
add_link_options(-Wl,--gc-sections)

add_subdirectory(lvgl)
include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake) 

file(GLOB_RECURSE app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})

file(GLOB_RECURSE inki_libs src/lib/*/*.c src/lib/*/*.h)
target_sources(app PRIVATE ${inki_libs})

target_sources(app PRIVATE ${WAMR_RUNTIME_LIB_SOURCE})

set(PM_STATIC_YML_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/pm_static.yml
  )

list(APPEND ZEPHYR_EXTRA_MODULES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/display
)

target_link_libraries(app PUBLIC lvgl -lgcc)
