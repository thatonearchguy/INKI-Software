# Copyright: 2021 INKI-Systems Inc. - Licensed under GPL 3

zephyr_library_named(inki_display)

if(CONFIG_INKI_SSD16XX)
    include(${CMAKE_CURRENT_SOURCE_DIR}/inki_ssd16xx/inki_ssd16xx.cmake})
    # Add more displays when the time comes!!
endif()
