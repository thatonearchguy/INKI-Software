# Copyright (c) 2022 INKI-Systems Inc
# Licensed under GPL 3

zephyr_library_named(inki_icc)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
zephyr_library_sources(
    icc.c
)


if(NOT CONFIG_INKI_ICC_BKEND_EXISTS)
    message( FATAL_ERROR "No backend exists for ")
endif()

target_link_libraries(inki_icc, inki_lp_uarte)

