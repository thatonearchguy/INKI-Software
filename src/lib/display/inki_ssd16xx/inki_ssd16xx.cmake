# SPDX-License-Identifier: Apache-2.0

if(CONFIG_INKI_SSD16XX)
  # Add ssd16xx_regs.h to the set of global include paths.
  zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}.)
  zephyr_library_sources(
    ssd16xx.c
    )
endif()
