/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */


#include <nrf52840.h>
#include <hal/nrf_ppi.h> 
#include <zephyr/types.h>
#include <sys/types.h>
#include <errno.h>
#include <hal/nrf_uarte.h>
//#include <nrfx_uarte.h>
//#include <nrfx_gpiote.h>
#include <hal/nrf_qspi.h>
#include <nrfx_ppi.h>
#include <nrfx_qspi.h>
#include "../../lp_uarte_dev.h"
#include "lib/d_vector/vector.h"
#include "lib/inki_gpiote/inki_gpiote.h"
#include <stdlib.h>

#define mod_name nrf_lp_uarte_drv_dev
#define drv_name lp_uarte_drv

#define LP_DRV_ERR_CHECK(rc, message) \
if(rc < 0) \
{ \
    LOG_INF(message); \
    return rc; \
} 

#define NRF_UARTE_STATE_UNINIT 1
#define NRF_UARTE_STATE_RX_NO_FT 2
#define NRF_UARTE_STATE_TX_NO_FT 3
#define NRF_UARTE_STATE_RX_FT 4
#define NRF_UARTE_STATE_TX_FT 5
#define NRF_UARTE_STATE_ERR 6
#define NRF_UARTE_STATE_RDY 7
#define NRF_UARTE_STATE_ACTIVE_NO_FT 8
#define NRF_UARTE_STATE_ACTIVE_FT 9

LOG_MODULE_DECLARE(lp_uarte_dev, 3);

#define PPI_CHANNELS_REQUIRED 4 
/** This is necessary as vector class is implemented type-agnostically.
 * 
 * Here we're just using vector to store pointers to PPI channels, so this is fine and will make code a lot more readable.
 * */
#define GET_PPI_FROM_VEC(vector, index, name) \
uint32_t* CONCAT(ppi_ptr_, index) = (uint32_t*)vector_get(&vector, index); \
nrf_ppi_channel_t* name = (nrf_ppi_channel_t*) *CONCAT(ppi_ptr_, index); \
free(CONCAT(ppi_ptr_, index)); \

#define FREE_REALLOC_PPI(vector, index, name) \
GET_PPI_FROM_VEC(vector, index, name); \
err_code = nrfx_ppi_channel_free(*name); \
LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error unassigning event from task"); \
err_code = nrfx_ppi_channel_alloc(name); \
LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error reallocating PPI channel"); \
uint32_t CONCAT(ppi_, index) = *name; \
err_code = vector_set(&vector, index, &CONCAT(ppi_, index)); \
LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error reallocating PPI channel"); \

nrf_uarte_config_t nrf_config;
NRF_UARTE_Type nrf_uarte_reg;
NRF_PPI_Type nrf_ppi_reg;
static NRF_QSPI_Type nrf_qspi_reg;
NRF_GPIOTE_Type nrf_gpiote_reg;

uint32_t ft_packets_recev;
struct vector ppi_channels;
uint32_t curr_state;
uint8_t curr_buf;
void* tx_buf0_ptr;
void* rx_buf0_ptr;
void* rx_buf1_ptr;

/* FUNCTION DEFINITIONS */

const int nrfx_err_to_zephyr_err(nrfx_err_t err_code);
static int nrf_lp_uarte_gpiote_rx_init(const struct lp_uarte_dev* dev, bool ft_en);
static int nrf_lp_uarte_gpiote_tx_init(const struct lp_uarte_dev* dev, bool ft_en);
static int nrf_lp_uarte_init(const struct lp_uarte_dev* dev);


const int nrfx_err_to_zephyr_err(nrfx_err_t err_code)
{
    switch (err_code)
    {
        case NRFX_ERROR_INVALID_LENGTH:
        {
            return -EINVAL;
        }
        case NRFX_ERROR_INTERNAL:
        {
            return -EINTR;
        }
        case NRFX_SUCCESS:
        {
            return 1;
            break;
        }
        case NRFX_ERROR_NO_MEM:
        {
            return -ENOMEM;
            break;
        }
        case NRFX_ERROR_BUSY:
        {
            return -EBUSY;
            break;
        }
        case NRFX_ERROR_INVALID_PARAM:
        {
            return -EINVAL;
            break;
        }
        case NRFX_ERROR_INVALID_STATE:
        {
            return -EINVAL;
            break;
        }
        case NRFX_ERROR_FORBIDDEN:
        {
            return -EPERM;
            break;
        }
        case NRFX_ERROR_INVALID_ADDR:
        {
            return -EINVAL;
            break;
        }
        case NRFX_ERROR_NULL:
        {
            return -ENOSTR;
            break;
        }
        case NRFX_ERROR_NOT_SUPPORTED:
        {
            return -ENOTSUP;
            break;
        }

    }
    return err_code;
}

void (*lp_uarte_rx_cb)(size_t len, void* data_ptr, void(*self)());
void (*lp_uarte_tx_cb)(void(*self)());


void gpiote_lp_uarte_handler()
{
    bool a = (curr_state = NRF_UARTE_STATE_RX_FT);
    void* curr_ptr = (curr_buf == 0) ? rx_buf1_ptr : rx_buf0_ptr; //buffer is immediately updated after RXSTARTED, so the buffer with currently relevant data on it is the OTHER one.
    if(a && NRF_GPIOTE->EVENTS_IN[0])
    {
        NRF_GPIOTE->EVENTS_IN[0] = 0;
        /** HACK: This is a dirty way to have the callback get the vectors within their own structs. */
        lp_uarte_rx_cb(0, curr_ptr, lp_uarte_rx_cb); //notify higher-level ISR that new packet is being transferred, QSPI write address must be updated.
        NRF_GPIOTE->TASKS_SET[2] = 1; //s1 high, ready to receive data without race conditions
    }
    if(NRF_GPIOTE->EVENTS_IN[3])
    {
        NRF_GPIOTE->EVENTS_IN[3] = 0;
        NRF_GPIOTE->TASKS_SET[2] = 1; //toggling S1 high to low to acknowledge end of transaction
        NRF_GPIOTE->TASKS_CLR[2] = 1;
        /** HACK: This is a dirty way to have the callback get the vectors within their own structs. */
        lp_uarte_rx_cb(nrf_uarte_reg.RXD.AMOUNT, curr_ptr, lp_uarte_rx_cb);
    }
}

ISR_DIRECT_DECLARE(uarte_rxtx_handler)
{
    bool started = nrf_uarte_event_check(&nrf_uarte_reg, NRF_UARTE_EVENT_RXSTARTED);
    if(started)
    {
        nrf_uarte_event_clear(&nrf_uarte_reg, NRF_UARTE_EVENT_RXSTARTED);
        if(curr_buf == 1) 
        {
            curr_buf = 0;
            nrf_uarte_rx_buffer_set(&nrf_uarte_reg, rx_buf0_ptr, CONFIG_INKI_LP_UARTE_RX_BUF_LEN);
        }
        else if (curr_buf == 0)
        {
            curr_buf = 1;
            nrf_uarte_rx_buffer_set(&nrf_uarte_reg, rx_buf1_ptr, CONFIG_INKI_LP_UARTE_RX_BUF_LEN);
        }
        //How do i return the pointer containing the newly received data -> done.
    }
    bool stopped = nrf_uarte_event_check(&nrf_uarte_reg, NRF_UARTE_EVENT_TXSTOPPED);
    if(stopped)
    {
        nrf_uarte_event_clear(&nrf_uarte_reg, NRF_UARTE_EVENT_TXSTOPPED);
        lp_uarte_tx_cb(lp_uarte_rx_cb);
    }
    ISR_DIRECT_PM();
    return 1;
}


static int nrf_lp_uarte_gpiote_rx_init(const struct lp_uarte_dev* dev, bool ft_en)
{
    if(curr_state != ((ft_en) ? NRF_UARTE_STATE_RX_FT : NRF_UARTE_STATE_RX_NO_FT))
    {
        nrfx_err_t err_code;

        /* Configure GPIOTE channel 0 as event that occurs when S0 changes from digital lo to hi */
        NRF_GPIOTE->CONFIG[0] =  (GPIOTE_CONFIG_POLARITY_LoToHi << GPIOTE_CONFIG_POLARITY_Pos)
                    | (dev->p.s0_pin << GPIOTE_CONFIG_PSEL_Pos)
                    | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);
    
        /* Configure GPIOTE channel 1 as event that occurs when S0 changes from digital hi to lo. */
        NRF_GPIOTE->CONFIG[1] =  (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos)
                    | (dev->p.s0_pin << GPIOTE_CONFIG_PSEL_Pos)
                    | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);

        /* Configure GPIOTE channel 2 as a task for S1 to be toggled (to save GPIOTE channels) */  
        NRF_GPIOTE->CONFIG[2] =  (GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos)
                    | (dev->p.s1_pin << GPIOTE_CONFIG_PSEL_Pos)
                    | (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos);

        /* Configure GPIOTE channel 3 as an event triggered by S2 going from digital lo to hi */  
        NRF_GPIOTE->CONFIG[3] =  (GPIOTE_CONFIG_POLARITY_LoToHi << GPIOTE_CONFIG_POLARITY_Pos)
                    | (dev->p.s2_pin << GPIOTE_CONFIG_PSEL_Pos)
                    | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);

        // Interrupt on S2 lo to hi, or if in enhanced filetransfer mode enable interrupt on initial S0 ready state, to set correct QSPI registers
        // for incremental packet write and setup PPI connection.  
        NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN0_Msk | GPIOTE_INTENCLR_IN2_Msk | GPIOTE_INTENCLR_IN3_Msk | GPIOTE_INTENCLR_IN4_Msk | GPIOTE_INTENCLR_IN5_Msk;

        inki_gpiote_register_isr(gpiote_lp_uarte_handler);

        //Could probably do |= but this is more readable.
        if(ft_en) NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN3_Msk | GPIOTE_INTENSET_IN0_Msk;
        else NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN3_Msk;

        // Clear all events.
        for(int i = 0; i < ARRAY_SIZE(NRF_GPIOTE->EVENTS_IN); i++)
        {
            NRF_GPIOTE->EVENTS_IN[i] = 0;
        }

        GET_PPI_FROM_VEC(ppi_channels, 0, vec_ppi_0);
        //nrf_uarte_subscribe_set(&nrf_uarte_reg, NRF_UARTE_TASK_STARTRX, *vec_ppi); nrf53 specific
        err_code = nrfx_ppi_channel_assign(*vec_ppi_0, (uint32_t)&NRF_GPIOTE->EVENTS_IN[0], nrf_uarte_task_address_get(&nrf_uarte_reg, NRF_UARTE_TASK_STARTRX)); //assigning S0 lo-hi to radio RX begin. 
        LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error assigning S0 rising edge event to STARTRX task");

        GET_PPI_FROM_VEC(ppi_channels, 1, vec_ppi_1);
        //nrf_uarte_subscribe_set(&nrf_uarte_reg, NRF_UARTE_TASK_STOPRX, *vec_ppi);
        err_code = nrfx_ppi_channel_assign(*vec_ppi_1, (uint32_t)&NRF_GPIOTE->EVENTS_IN[1], nrf_uarte_task_address_get(&nrf_uarte_reg, NRF_UARTE_TASK_STOPRX));
        LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error assigning S0 falling edge event to STOPRX task");

        if(ft_en)
        {
            GET_PPI_FROM_VEC(ppi_channels, 2, vec_ppi_2);
            //nrf_uarte_publish_set(&nrf_uarte_reg, NRF_UARTE_EVENT_RXSTARTED, *vec_ppi);
            err_code = nrfx_ppi_channel_assign(*vec_ppi_2, nrf_uarte_event_address_get(&nrf_uarte_reg, NRF_UARTE_EVENT_ENDRX), nrf_qspi_task_address_get(&nrf_qspi_reg, NRF_QSPI_TASK_WRITESTART));
            LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error assigning ENDRX event to QSPI write task configured by ISR.");

            GET_PPI_FROM_VEC(ppi_channels, 3, vec_ppi_3);
            //nrf_uarte_publish_set(&nrf_uarte_reg, NRF_UARTE_EVENT_RXSTARTED, *vec_ppi);
            err_code = nrfx_ppi_channel_assign(*vec_ppi_3, nrf_qspi_event_address_get(&nrf_qspi_reg, NRF_QSPI_EVENT_READY), (uint32_t)&NRF_GPIOTE->TASKS_CLR[2]);
            LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error assigning QSPI write complete event to S1 falling edge task");
        }

        else
        {
            GET_PPI_FROM_VEC(ppi_channels, 2, vec_ppi_2);
            //nrf_uarte_publish_set(&nrf_uarte_reg, NRF_UARTE_EVENT_RXSTARTED, *vec_ppi);
            err_code = nrfx_ppi_channel_assign(*vec_ppi_2, nrf_uarte_event_address_get(&nrf_uarte_reg, NRF_UARTE_EVENT_RXSTARTED), (uint32_t)&NRF_GPIOTE->TASKS_SET[2]);
            LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error assigning RXSTARTED event to S1 rising edge task");

            //if enhanced filetransfer mode is activated, the ISR will manually trigger S1 rising edge to prevent race conditions. Other microcontroller will wait until this pin goes up before transferring any data, guaranteeing that no data is lost. 
            GET_PPI_FROM_VEC(ppi_channels, 3, vec_ppi_3);
            //nrf_uarte_publish_set(&nrf_uarte_reg, NRF_UARTE_EVENT_RXSTARTED, *vec_ppi);
            err_code = nrfx_ppi_channel_assign(*vec_ppi_3, nrf_uarte_event_address_get(&nrf_uarte_reg, NRF_UARTE_EVENT_ENDRX), (uint32_t)&NRF_GPIOTE->TASKS_CLR[2]);
            LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error assigning S1 hi to lo to ENDRX");
        }

        IRQ_DIRECT_CONNECT(UARTE0_UART0_IRQn, 4, uarte_rxtx_handler, 0);
        irq_enable(UARTE0_UART0_IRQn);
        nrf_uarte_int_enable(&nrf_uarte_reg, NRF_UARTE_INT_TXSTOPPED_MASK);

        curr_state = (ft_en) ? NRF_UARTE_STATE_RX_FT : NRF_UARTE_STATE_RX_NO_FT;
    }
    return 1;
}

static int nrf_lp_uarte_gpiote_tx_init(const struct lp_uarte_dev* dev, bool ft_en)
{
    nrfx_err_t err_code;
    if(curr_state != ((ft_en) ? NRF_UARTE_STATE_TX_FT : NRF_UARTE_STATE_TX_NO_FT))
    {
        inki_gpiote_remove_isr(gpiote_lp_uarte_handler);
         /* Configure GPIOTE channel 0 as a task for S0 to be actuated as toggle to save GPIOTE channels */
        NRF_GPIOTE->CONFIG[0] =  (GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos)
                    | (dev->p.s0_pin << GPIOTE_CONFIG_PSEL_Pos)
                    | (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos);
    
        /* Configure GPIOTE channel 1 as event that occurs when S1 changes from digital lo to hi. */
        NRF_GPIOTE->CONFIG[1] =  (GPIOTE_CONFIG_POLARITY_LoToHi << GPIOTE_CONFIG_POLARITY_Pos)
                    | (dev->p.s1_pin << GPIOTE_CONFIG_PSEL_Pos)
                    | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);

        /* Configure GPIOTE channel 2 as event that occurs when S1 changes from digital hi to lo. */
        NRF_GPIOTE->CONFIG[2] =  (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos)
                    | (dev->p.s1_pin << GPIOTE_CONFIG_PSEL_Pos)
                    | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);

        /* Configure GPIOTE channel 3 as a task for S2 to be actuated as toggle to save GPIOTE channels */
        NRF_GPIOTE->CONFIG[3] =  (GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos)
                    | (dev->p.s2_pin << GPIOTE_CONFIG_PSEL_Pos)
                    | (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos);



        // Interrupt on S1 lo to hi in enhanced filetransfer mode to set tx_buffer after every successful write.
        NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN0_Msk | GPIOTE_INTENCLR_IN2_Msk | GPIOTE_INTENCLR_IN3_Msk | GPIOTE_INTENCLR_IN4_Msk | GPIOTE_INTENCLR_IN5_Msk;

        //Could probably do |= but this is more readable.
        //if(ft_en) NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN2_Msk;
        //else NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN4_Msk;

        
        for(int i = 0; i < ARRAY_SIZE(NRF_GPIOTE->EVENTS_IN); i++)
        {
            NRF_GPIOTE->EVENTS_IN[i] = 0;
        }

        GET_PPI_FROM_VEC(ppi_channels, 0, vec_ppi_0);
        //nrf_uarte_subscribe_set(&nrf_uarte_reg, NRF_UARTE_TASK_STOPRX, *vec_ppi);
        err_code = nrfx_ppi_channel_assign(*vec_ppi_0, (uint32_t)&NRF_GPIOTE->EVENTS_IN[2], nrf_uarte_task_address_get(&nrf_uarte_reg, NRF_UARTE_TASK_STARTTX));
        LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error assigning S1 rising edge event to STARTTX task");


        GET_PPI_FROM_VEC(ppi_channels, 1, vec_ppi_1);
        //nrf_uarte_publish_set(&nrf_uarte_reg, NRF_UARTE_EVENT_RXSTARTED, *vec_ppi);
        err_code = nrfx_ppi_channel_assign(*vec_ppi_1, nrf_uarte_event_address_get(&nrf_uarte_reg, NRF_UARTE_EVENT_ENDTX), (uint32_t)&NRF_GPIOTE->TASKS_CLR[0]);
        LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Error assigning ENDTX event to S0 falling edge task");

        IRQ_DIRECT_CONNECT(UARTE0_UART0_IRQn, 4, uarte_rxtx_handler, 0);
        irq_enable(UARTE0_UART0_IRQn);
        nrf_uarte_int_enable(&nrf_uarte_reg, NRF_UARTE_INT_TXSTOPPED_MASK);

        FREE_REALLOC_PPI(ppi_channels, 2, vec_ppi_2);
        FREE_REALLOC_PPI(ppi_channels, 3, vec_ppi_3);

        curr_state = (ft_en) ? NRF_UARTE_STATE_TX_FT : NRF_UARTE_STATE_TX_NO_FT;
    }
    return 1;
}

/**
 * @brief Initialise NRF family UARTE - parameters should have been validated beforehand with lp_uarte_verify_params(). 
 * 
 * @param dev UARTE device structure
 * @return 1 on success, negative err code otherwise.
 */
static int nrf_lp_uarte_init(const struct lp_uarte_dev* dev)
{
    nrfx_err_t err_code;
    /* initialising vector storing PPI pointers */
    vector_init(&ppi_channels, PPI_CHANNELS_REQUIRED, sizeof(nrf_ppi_channel_t*));
    /* Configuring NRF PPI peripheral to sync events to S0, S1, S2 GPIO events. */
    /* We will need at least four PPI channels I think */
    for(int i = 0; i < PPI_CHANNELS_REQUIRED; i ++)
    {
        nrf_ppi_channel_t* c;
        err_code = nrfx_ppi_channel_alloc(c);
        if(err_code == NRFX_SUCCESS)
        {
            uint32_t ptr = (uint32_t) c;
            vector_push_back(&ppi_channels, &ptr);
        }
        else
        {
            vector_deinit(&ppi_channels);
            return -nrfx_err_to_zephyr_err(err_code);
        }
    }

    //err_code = nrfx_gpiote_init((uint8_t)3);
    //if(err_code != NRFX_SUCCESS || err_code != NRFX_ERROR_INVALID_STATE ) return nrfx_err_to_zephyr_err(err_code);
    tx_buf0_ptr = dev->p.tx_buf_ptr;
    rx_buf0_ptr = dev->p.rx_buf0_ptr;
    rx_buf1_ptr = dev->p.rx_buf1_ptr;
    /* Configuring UARTE peripheral */
    nrf_config.hwfc = (dev->p.flow_control) ? NRF_UARTE_HWFC_ENABLED : NRF_UARTE_HWFC_DISABLED;
    nrf_config.parity = ((dev->p.even_parity)||(dev->p.odd_parity)) ? NRF_UARTE_PARITY_INCLUDED : NRF_UARTE_PARITY_EXCLUDED;
    nrf_config.stop = NRF_UARTE_STOP_TWO; //safer than one bit
    nrf_uarte_enable(&nrf_uarte_reg);
    nrf_uarte_configure(&nrf_uarte_reg, &nrf_config);
    #if defined(CONFIG_SOC_SERIES_NRF53X) 
    if(dev->p.odd_parity == true) nrf_uarte_reg.CONFIG |= (1 << 8);
    #endif
    nrf_uarte_txrx_pins_set(&nrf_uarte_reg, dev->p.tx_pin, dev->p.rx_pin);
    if(dev->p.flow_control) nrf_uarte_hwfc_pins_set(&nrf_uarte_reg, dev->p.rts_pin, dev->p.cts_pin);
    /** TODO: Find nice way to validate user-defined baud rate. For now let's just set it to maximum baud rate as we want to maximise data throughput. */
    nrf_uarte_baudrate_set(&nrf_uarte_reg, NRF_UARTE_BAUDRATE_1000000);

    nrf_uarte_rx_buffer_set(&nrf_uarte_reg, rx_buf0_ptr, CONFIG_INKI_LP_UARTE_RX_BUF_LEN);
    curr_buf = 0;

    lp_uarte_rx_cb = dev->p.rx_cb;
    lp_uarte_tx_cb = dev->p.tx_cb;

    err_code = inki_gpiote_init();
    if(err_code < 0) return -EINVAL;

    err_code = nrf_lp_uarte_gpiote_rx_init(dev, false);    
    /* PPI not required for S2 - we are generating interrupt if S2 goes high, as this signifies the end of the data. */
    curr_state = NRF_UARTE_STATE_RX_NO_FT;


    return 1;

}

static int nrf_lp_uarte_ft_start(const struct lp_uarte_dev* dev)
{
    curr_state = NRF_UARTE_STATE_ACTIVE_FT;
    return 1;
}

static int nrf_get_ft_status()
{
    return (curr_state == NRF_UARTE_STATE_ACTIVE_FT || curr_state == NRF_UARTE_STATE_RX_FT || curr_state == NRF_UARTE_STATE_TX_FT) ? 1 : 0;
}

static int nrf_lp_uarte_deinit(const struct lp_uarte_dev* dev)
{
    //Disabling UARTE peripheral and hence unloading all configs
    nrf_uarte_disable(&nrf_uarte_reg);
    //Clearing all stored ISRS
    inki_gpiote_remove_isr(gpiote_lp_uarte_handler);
    //Freeing PPI channels
    for(int i = 0; i < PPI_CHANNELS_REQUIRED; i ++)
    {
        GET_PPI_FROM_VEC(ppi_channels, i, vec_ppi);
        nrfx_ppi_channel_free(*vec_ppi);
    }
    vector_deinit(&ppi_channels);
    return 1;
}

static int nrf_lp_uarte_tx_fin(const struct lp_uarte_dev* dev)
{
    NRF_GPIOTE->TASKS_SET[3];
    NRF_GPIOTE->TASKS_CLR[3];
    curr_state = NRF_UARTE_STATE_ACTIVE_NO_FT;
    int rc = nrf_lp_uarte_gpiote_rx_init(dev, false);
    return rc;
}

static int nrf_lp_uarte_tx(const struct lp_uarte_dev* dev)
{
    int rc = nrf_lp_uarte_gpiote_tx_init(dev, nrf_get_ft_status()==1);
    LP_DRV_ERR_CHECK(rc, "Couldn't initialise LP-UARTE in TX mode");
    nrf_uarte_tx_buffer_set(&nrf_uarte_reg, tx_buf0_ptr, CONFIG_INKI_LP_UARTE_TX_BUF_LEN);
    NRF_GPIOTE->TASKS_OUT[0] = 1; //trigger S0 to high, with preconfigured PPI this will get the ball rolling 
    return 1;
}

static int nrf_lp_uarte_rx(const struct lp_uarte_dev* dev)
{
    
    int rc = nrf_lp_uarte_gpiote_rx_init(dev, nrf_get_ft_status()==1);
    LP_DRV_ERR_CHECK(rc, "Couldn't initialise LP-UARTE in RX mode");
    nrf_uarte_rx_buffer_set(&nrf_uarte_reg, rx_buf0_ptr, CONFIG_INKI_LP_UARTE_RX_BUF_LEN);

    curr_buf = 0;

    return 1;
}

static const struct lp_uarte_dev_api nrf_lp_uarte_api = {
    .tx = nrf_lp_uarte_tx,
    .rx = nrf_lp_uarte_rx,
    .init = nrf_lp_uarte_init,
    .deinit = nrf_lp_uarte_deinit,
    .ft_start = nrf_lp_uarte_ft_start,
    .ft_status = nrf_get_ft_status,
    .tx_fin = nrf_lp_uarte_tx_fin,
};

int lp_uarte_drv_init(struct lp_uarte_dev* dev)
{
    dev->api = &nrf_lp_uarte_api;
    return 1;
}