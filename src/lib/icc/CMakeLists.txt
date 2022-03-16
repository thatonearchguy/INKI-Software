# Copyright: 2021 INKI-Systems Inc. - Licensed under GPL 3

zephyr_library_named(inki_lp_uarte)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
zephyr_library_sources(
    lp_uarte.c
)

if(CONFIG_INKI_LP_UARTE)
    include(${CMAKE_CURRENT_SOURCE_DIR}/drivers/nrf_lp_uarte/nrf_lp_uarte.cmake})
    # Add more when the time comes!!
endif()


if(NOT CONFIG_INKI_LP_UARTE_DRV_EXISTS)
    message( FATAL_ERROR "No driver selected for LP_UartE!")
endif()

