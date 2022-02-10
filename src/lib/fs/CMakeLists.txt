# Copyright: 2021 INKI-Systems Inc. - Licensed under GPL 3

zephyr_library_named(inki_xipa_fs)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
zephyr_library_sources(
    xipafs.c
)

if(CONFIG_INKI_XIPA_FS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/drivers/nrf_xip_nor/nrf_xip_nor.cmake})
    # Add more displays when the time comes!!
endif()


if(NOT CONFIG_INKI_XIPA_DRV_EXISTS)
    message( FATAL_ERROR "No driver selected for XIPA_FS!")
endif()

