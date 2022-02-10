# SPDX-License-Identifier: Apache-2.0

if(XIPA_FS_NRF5XX)
  # Add ssd16xx_regs.h to the set of global include paths.
  #zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../)
  zephyr_library_sources(
    nrf_xip_nor.c
    )
endif()
