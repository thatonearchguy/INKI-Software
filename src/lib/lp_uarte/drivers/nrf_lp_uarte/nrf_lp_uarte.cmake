# Copyright (c) 2022 INKI-Systems Inc
# Licensed under GPL 3
#
#	Licensed under GPL 3


if(LP_UARTE_NRF52)

  zephyr_library_sources(
    nrf_lp_uarte.c
    )
endif()
if(LP_UARTE_NRF53)

  zephyr_library_sources(
    nrf53_lp_uarte.c
    )
endif()
