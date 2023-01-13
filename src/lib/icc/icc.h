/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */

#ifndef INKI_ICC
#define INKI_ICC

#include <stdlib.h>
#include <stdio.h>
#include "lib/d_vector/vector.h"
#include "lib/d_stack/stack.h"
#include <logging/log.h>
#include <logging/log_instance.h>
#include <net.h>

#define ICC_NAME "inki_icc"




//Default value will be hybrid - balancing data throughput with power consumption...
//Depending on demands of the ICC link, the connection can be downgraded to LP_UARTE and upgraded to SPI_DMA at stupidly high clockspeeds for 2-3MB/s data transfer which will most certainly max out the LTE link. 
typedef enum
{
    LP_UARTE = 1,
    FAST_UARTE = 2,
    SPI_DMA = 3,
    HYBRID = 4,
    //Can add more in the future
} icc_backend;


//Validation for which backends are available on the system via KConfig
struct icc_params
{
    icc_backend chosen_backend;


};

struct inki_icc
{
    LOG_INSTANCE_PTR_DECLARE(log);
    struct icc_params;
    void* private_ptr;
};

//Rename to appropriate ICC parameters.
//MAC Address, link information, statistics etc required. 
struct eth_context {
	uint8_t recv[NET_ETH_MTU + ETH_HDR_LEN];
	uint8_t send[NET_ETH_MTU + ETH_HDR_LEN];
	uint8_t mac_addr[6];
	struct net_linkaddr ll_addr;
	struct net_if *iface;
	const char *if_name;
	k_tid_t rx_thread;
	struct z_thread_stack_element *rx_stack;
	size_t rx_stack_size;
	int dev_fd;
	bool init_done;
	bool status;
	bool promisc_mode;

#if defined(CONFIG_NET_STATISTICS_ETHERNET)
	struct net_stats_eth stats;
#endif
#if defined(CONFIG_ETH_NATIVE_POSIX_PTP_CLOCK)
	const struct device *ptp_clock;
#endif
};

#define INKI_ICC_INIT(_name)  \
LOG_INSTANCE_REGISTER(ICC_NAME, _name, CONFIG_INKI_ICC_LOGLEVEL);  \
struct inki_icc _name = {  \
            LOG_INSTANCE_PTR_INIT(log, ICC_NAME, _name)  \
}




#endif