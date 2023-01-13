/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */


/*
 _      ____  __ __   ____  ____  ______    ___ 
| |    |    \|  |  | /    ||    \|      |  /  _]
| |    |  o  )  |  ||  o  ||  D  )      | /  [_ 
| |___ |   _/|  |  ||     ||    /|_|  |_||    _]
|     ||  |  |  :  ||  _  ||    \  |  |  |   [_ 
|     ||  |  |     ||  |  ||  .  \ |  |  |     |
|_____||__|   \__,_||__|__||__|\_| |__|  |_____|

𝙇𝙤𝙬-𝙋𝙤𝙬𝙚𝙧 𝙐𝙣𝙞𝙫𝙚𝙧𝙨𝙖𝙡 𝘼𝙨𝙮𝙣𝙘𝙝𝙧𝙤𝙣𝙤𝙪𝙨 𝙍𝙚𝙘𝙚𝙞𝙫𝙚𝙧-𝙏𝙧𝙖𝙣𝙨𝙢𝙞𝙩𝙩𝙚𝙧

*/

#include "lp_uarte.h"
#include "lp_uarte_dev.h"
#include "lp_uarte_cfg.h"
#include <sys/crc.h>


LOG_LEVEL_SET(LOG_LEVEL_INF);

#define LP_ERR_CHECK(logger, message, rc) \
if(rc < 0) \
{ \
    LOG_INST_ERR(logger, message); \
    return rc; \
}

//#define CONTAINER_OF(MemberPtr, StrucType, MemberName) ((StrucType*)( (char*)(MemberPtr) - offsetof(StrucType, MemberName)))

#define GET_ITM_FROM_VEC(vector, index, name) \
void(** CONCAT(vec_pos_, index))()  = (void(**)())vector_get(&vector, index); \
void(* name)()  = (void(*)()) *CONCAT(vec_pos_, index); \
free(CONCAT(vec_pos_, index)) \


uint32_t crcTable[256];

struct private_ptr
{
    bool init;
    char rx_buffer_0[CONFIG_INKI_LP_UARTE_RX_BUF_LEN];
    char rx_buffer_1[CONFIG_INKI_LP_UARTE_RX_BUF_LEN];
    char tx_buffer[CONFIG_INKI_LP_UARTE_TX_BUF_LEN];
    struct lp_uarte_dev dev;
    int64_t ft_bytes_left;
    void (*rx_callbacks[CONFIG_INKI_LP_UARTE_CB_PTRS])();
    void (*tx_callbacks[CONFIG_INKI_LP_UARTE_CB_PTRS])();
    uint16_t rx_occupied;
    uint16_t tx_occupied;
    void(* main_rx_callback)(size_t len, void* data, void(*self)());
    void(* main_tx_callback)(void(*self)());
};


/* Function prototypes */
static int lp_uarte_verify_pins(struct lp_uarte_dev_params* p);
static int lp_uarte_verify_bools(struct lp_uarte_dev_params* p);
static int lp_uarte_verify_pointers(struct lp_uarte_dev_params* p);
int lp_uarte_verify_params(struct lp_uarte_dev_params* p);
void main_lp_uarte_rx_cb(size_t len, void* data_ptr, void* troll_ptr);
void main_lp_uarte_tx_cb(void* troll_ptr);
volatile int lp_uarte_assemble_pkt(struct lp_uarte* lp, void* data_in, size_t data_len);
volatile static int lp_uarte_decode_pkt(struct lp_uarte* lp, void* pkt_in, void* data_out, size_t pkt_len);


/**
 * @brief Basic sanity checks on pin numbers - checking if they're duplicated
 * or otherwise invalid.
 * 
 * @param p dev parameter struct
 * @return 1 if valid, negative err code otherwise.
 */
static int lp_uarte_verify_pins(struct lp_uarte_dev_params* p)
{
    uint32_t check_arr[7] = {p->rts_pin, p->cts_pin, p->tx_pin, p->rx_pin, p->s0_pin, p->s1_pin, p->s2_pin};
    for(int i = 0; i < ARRAY_SIZE(check_arr); i++)
    {
        for(int x = 0; x < ARRAY_SIZE(check_arr); x++)
        {
            if((x!=i)&&(check_arr[x] == check_arr[i])) return -EINVAL;
        }
    }
    return 1;
}

/**
 * @brief Verify the booleans are correct
 * 
 * @param p dev parameter struct 
 * @return 1 if valid. 
 */
static int lp_uarte_verify_bools(struct lp_uarte_dev_params* p)
{
    if((p->even_parity) && (p->odd_parity)) return -EINVAL;
    return 1;
}

/**
 * @brief Verify pointers are safe
 * 
 * @param p dev parameter struct
 * @return 1 if all valid, negative err code otherwise.
 */
static int lp_uarte_verify_pointers(struct lp_uarte_dev_params* p)
{
    if(p->tx_buf_ptr == NULL || p->rx_buf0_ptr == NULL || p->rx_buf1_ptr == NULL || p->tx_cb == NULL || p->rx_cb == NULL)
    {
        return -EINVAL;
    }
    return 1;
} 

/**
 * @brief Basic sanity checks on a provided parameter struct
 * 
 * @param p dev parameter struct
 * @return 1 if valid, negative err code if invalid.
 */
int lp_uarte_verify_params(struct lp_uarte_dev_params* p)
{
    int rc = 1;
    rc = lp_uarte_verify_bools(p);
    rc = lp_uarte_verify_pointers(p);
    rc = lp_uarte_verify_pins(p);
    rc = (p->start_byte == p->end_byte) ? -1 : 1;
    return rc;
}

/**
 * @brief Initialise low power UART peripheral with DMA
 * 
 * @param lp lp_uarte object
 * @return 1 on success, -EINVAL with invalid parameters.
 */
int lp_uarte_init(struct lp_uarte* lp)
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;


    /** Underlying device driver should not be aware of front-end uarte parameters, so this seems dumb but is intentional. 
     * The callbacks should be lp_uarte's own functions - so we take a limited subset of 
     * shared parameters here, validate them, then add the functions we need. 
     * This will also allow multiple modules to register their own callbacks/notifiers to events. 
     * */
    ptr->dev.p.tx_pin = lp->param.tx_pin;
    ptr->dev.p.rx_pin = lp->param.rx_pin;
    ptr->dev.p.cts_pin = lp->param.cts_pin;
    ptr->dev.p.s0_pin = lp->param.s0_pin;
    ptr->dev.p.s1_pin = lp->param.s1_pin;
    ptr->dev.p.s2_pin = lp->param.s2_pin;
    ptr->dev.p.start_byte = lp->param.start_byte;
    ptr->dev.p.end_byte = lp->param.end_byte;
    ptr->dev.p.flow_control = lp->param.flow_control;
    ptr->dev.p.even_parity = lp->param.even_parity;
    ptr->dev.p.odd_parity = lp->param.odd_parity;
    ptr->dev.p.baud = lp->param.baud;

    ptr->dev.p.tx_buf_ptr = ptr->tx_buffer;
    ptr->dev.p.rx_buf0_ptr = ptr->rx_buffer_0;
    ptr->dev.p.rx_buf1_ptr = ptr->rx_buffer_1;

    /** TODO: Register callbacks to lp_uarte functions */

    int rc = lp_uarte_verify_params(&lp->param);
    LP_ERR_CHECK(lp->log, "Invalid parameters detected.", rc);

    memset(ptr->rx_buffer_0, 0, sizeof(ptr->rx_buffer_0));
    memset(ptr->rx_buffer_1, 0, sizeof(ptr->rx_buffer_1));
    memset(ptr->tx_buffer, 0, sizeof(ptr->tx_buffer));

    rc = lp_uarte_dev_init(&ptr->dev);
    LP_ERR_CHECK(lp->log, "Could not initialise LP-UART device backend", rc);

    ptr->rx_occupied = 0;
    ptr->tx_occupied = 0;
    ptr->main_rx_callback = main_lp_uarte_rx_cb;
    ptr->main_tx_callback = main_lp_uarte_tx_cb;

    return 1;
}

/**
 * @brief Prepare the underlying hardware to transmit a packet of data.
 * 
 * @param lp LP_UARTE object
 * @return 1 on success
 */
int lp_uarte_tx(struct lp_uarte* lp, void* data, size_t len)
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    //memcpy()
    if(ptr->ft_bytes_left == -1)
    {
        lp_uarte_dev_tx_fin(&ptr->dev);
    }
    if(lp_uarte_assemble_pkt(lp, data, len))
    {
        lp_uarte_dev_pkt_tx_rdy(&ptr->dev);
    }
    else return -EINVAL;
    if(lp_uarte_dev_ft_status(&ptr->dev) == 1)
    {
        if((ptr->ft_bytes_left - len)>=0)
        {
            ptr->ft_bytes_left -= len;
        }
        else
        {
            return -EINVAL;
        }
    }
    if(ptr->ft_bytes_left == 0)
    {
        ptr->ft_bytes_left = -1;
    }
    return 1;
}

/**
 * @brief Enables filetransfer mode on TX to streamline a file transfer. 
 * 
 * @param lp LP_UARTE object
 * @param total_file_size File size of file to transfer
 * @return 1 on success
 */
int lp_uarte_ft_en(struct lp_uarte* lp, size_t total_file_size)
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    ptr->ft_bytes_left = total_file_size;
    return 1;
}

/**
 * @brief Prepare the underlying hardware to receive a packet of data.
 * 
 * @param lp LP_UARTE object
 * @return 1 on success
 */
int lp_uarte_rx(struct lp_uarte* lp)
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    int rc = lp_uarte_dev_pkt_rx_rdy(&ptr->dev);
    return rc;
}

void main_lp_uarte_rx_cb(size_t len, void* data_ptr, void* troll_ptr)
{
    //This is a dirty hack to get the struct containing the particular instance's function pointers. 
    struct private_ptr* ptr = CONTAINER_OF(troll_ptr, struct private_ptr, rx_buffer_0);
    struct lp_uarte* lp = CONTAINER_OF(ptr, struct lp_uarte, private_ptr);
    void* pkt_data_ptr;
    lp_uarte_decode_pkt(lp, data_ptr, pkt_data_ptr, len);
    if(pkt_data_ptr == NULL) return -EINVAL;
    for(int i = 0; i < ptr->rx_occupied; i++)
    {
        //Iterate through and execute every callback
        (*ptr->rx_callbacks[i])(pkt_data_ptr, len);
    }
}


void main_lp_uarte_tx_cb(void* troll_ptr)
{
    //This is a dirty hack to get the struct containing the particular instance's function pointers. 
    struct private_ptr* ptr = CONTAINER_OF(troll_ptr, struct private_ptr, tx_buffer);
    for(int i = 0; i < ptr->tx_occupied; i++)
    {
        //Iterate through and execute every callback. 
        (*ptr->tx_callbacks[i])();
    }
}

/**
 * @brief Register an interrupt service routine in  
 * the list of RX service routines. 
 * 
 * @param lp LP_UARTE object
 * @return 1 on success, negative err code if the list is full 
 */
int lp_uarte_register_rx_isr(struct lp_uarte* lp, void (*func_ptr)())
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    if(ptr->rx_occupied + 1 < CONFIG_INKI_LP_UARTE_CB_PTRS)
    {
        ptr->rx_callbacks[ptr->rx_occupied] = func_ptr;
        ptr->rx_occupied ++;
        return 1;
    }
    else return -ENOSPC;
}

/**
 * @brief Register an interrupt service routine in  
 * the list of TX service routines. 
 * 
 * @param lp LP_UARTE object
 * @return 1 on success, negative err code if the list is full 
 */
int lp_uarte_register_tx_isr(struct lp_uarte* lp, void (*func_ptr)())
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    if(ptr->tx_occupied + 1 < CONFIG_INKI_LP_UARTE_CB_PTRS)
    {
        ptr->tx_callbacks[ptr->tx_occupied] = func_ptr;
        ptr->tx_occupied ++;
        return 1;
    }
    else return -ENOSPC;
}

/**
 * @brief Remove a particular registered interrupt service routine from 
 * the list of TX service routines. 
 * 
 * @param lp LP_UARTE object
 * @return 1 on success, negative err-code otherwise 
 */
int lp_uarte_remove_tx_isr(struct lp_uarte* lp, void (*func_ptr)())
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    int foundindex = -1;
    for(int i = 0; i < ptr->tx_occupied - 1; i ++)
    {
        if(ptr->tx_callbacks[i] == func_ptr)
        {
            foundindex = i;
        }
    }
    if(foundindex == -1) return -ENOENT;
    uint32_t start_offset = foundindex*sizeof(void(*)());
    if(foundindex < ptr->tx_occupied - 1)
    {
        uint32_t move_offset = (foundindex+1)*sizeof(void(*)());
        memmove(ptr->tx_callbacks+start_offset, ptr->tx_callbacks+move_offset, (ptr->tx_occupied - (foundindex+1))*sizeof(void(*)()));
    }
    else
    {
        memset(ptr->tx_callbacks + start_offset, 0, sizeof(void(*)()));
    }
    --ptr->tx_occupied;
    return 1;
}

/**
 * @brief Remove a particular registered interrupt service routine from 
 * the list of RX service routines. 
 * 
 * @param lp LP_UARTE object
 * @return 1 on success, negative err code otherwise 
 */
int lp_uarte_remove_rx_isr(struct lp_uarte* lp, void (*func_ptr)())
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    int foundindex = -1;
    for(int i = 0; i < ptr->rx_occupied - 1; i ++)
    {
        if(ptr->rx_callbacks[i] == func_ptr)
        {
            foundindex = i;
        }
    }
    if(foundindex == -1) return -ENOENT;
    uint32_t start_offset = foundindex*sizeof(void(*)());
    if(foundindex < ptr->rx_occupied - 1)
    {
        uint32_t move_offset = (foundindex+1)*sizeof(void(*)());
        memmove(ptr->rx_callbacks+start_offset, ptr->rx_callbacks+move_offset, (ptr->rx_occupied - (foundindex+1))*sizeof(void(*)()));
    }
    else
    {
        memset(ptr->rx_callbacks + start_offset, 0, sizeof(void(*)()));
    }
    --ptr->rx_occupied;
    return 1;
}

/**
 * @brief Remove all the registered TX interrupt service routines in one go. 
 * 
 * @param lp LP_UARTE object
 * @return 1 on success 
 */
int lp_uarte_clear_all_rx_isrs(struct lp_uarte* lp)
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    memset(ptr->rx_callbacks, 0, ptr->rx_occupied * sizeof(void(*)()));
    ptr->rx_occupied = 0;
    return 1;
}

/**
 * @brief Remove all the registered TX interrupt service routines in one go. 
 * 
 * @param lp LP_UARTE object
 * @return 1 on success. 
 */
int lp_uarte_clear_all_tx_isrs(struct lp_uarte* lp)
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    memset(ptr->tx_callbacks, 0, ptr->tx_occupied * sizeof(void(*)()));
    ptr->tx_occupied = 0;
    return 1;
}

/**
 * @brief Volatile function to wrap some data in a packet for transmission. It must be volatile as 
 * the driver is directly modifying our buffers and we don't want compiler to make guesses on the
 * contents.
 *  
 * 
 * @param lp lp_uarte object
 * @param data_in Pointer to data to assemble
 * @param data_len Length of data in "data_in"
 * @return 1 on success 
 */
volatile int lp_uarte_assemble_pkt(struct lp_uarte* lp, void* data_in, size_t data_len)
{
    struct private_ptr* ptr = (struct private_ptr*) lp->private_ptr;
    memcpy(ptr->tx_buffer, CONFIG_INKI_LP_UARTE_IDENTIFIER, sizeof(CONFIG_INKI_LP_UARTE_IDENTIFIER));
    memcpy(ptr->tx_buffer + sizeof(CONFIG_INKI_LP_UARTE_IDENTIFIER), data_in, data_len);
    char crc_res[4];
    volatile int a = snprintf(crc_res, 4, "%i", crc32_ieee(data_in, data_len + ARRAY_SIZE(CONFIG_INKI_LP_UARTE_IDENTIFIER)));
    memcpy(ptr->tx_buffer + sizeof(CONFIG_INKI_LP_UARTE_IDENTIFIER) + data_len, crc_res, 4);
    //ignore unused int error, using it to prevent compiler optimising snprintf instruction.

    return (volatile int)1;   
}


/**
 * @brief Volatile function to decode incoming packet, and providing the pointer of the data with
 * packet information stripped. 
 * 
 * @param lp lp_uarte object
 * @param pkt_in Pointer to packet to decode
 * @param data_out Pointer to finished data.
 * @param pkt_len Length of packet
 * @return 1 on success, negative err code otherwise. In all cases, pointer to data is provided,
 * but please check err code to see if data is valid or not. 
 */
volatile static int lp_uarte_decode_pkt(struct lp_uarte* lp, void* pkt_in, void* data_out, size_t pkt_len)
{
    char crc_char[4];
    int errno;
    int rc;
    memcpy(crc_char, (char*)pkt_in + pkt_len - 4, 4);
    uint32_t num = (uint32_t) strtoul(crc_char, NULL, 10);
    if (num == __UINT32_MAX__ && errno == ERANGE)
    {
        rc = -1;
        LOG_INST_ERR(lp->log, "RX CRC failure");

    }
    else if(num != crc32_ieee((char*)pkt_in + sizeof(CONFIG_INKI_LP_UARTE_IDENTIFIER), pkt_len - 4 - sizeof(CONFIG_INKI_LP_UARTE_IDENTIFIER))) 
    {
        rc = -2;
        LOG_INST_ERR(lp->log, "RX CRC mismatch");
    }
    else
    {
        data_out = (char*)pkt_in + sizeof(CONFIG_INKI_LP_UARTE_IDENTIFIER);
    }
    return rc;
}
