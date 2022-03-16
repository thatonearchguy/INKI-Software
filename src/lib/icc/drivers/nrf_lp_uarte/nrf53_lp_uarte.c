/*
    // Initialise GPIOTE to listen for rising and falling edges on S0
    nrfx_gpiote_in_config_t gpiote_re_config; //rising edge config
    gpiote_re_config.hi_accuracy = true;
    gpiote_re_config.is_watcher = false;
    gpiote_re_config.sense = NRF_GPIOTE_POLARITY_LOTOHI;

    nrfx_gpiote_in_config_t gpiote_fe_config; //falling edge config
    gpiote_fe_config.hi_accuracy = true;
    gpiote_fe_config.is_watcher = false;
    gpiote_fe_config.sense = NRF_GPIOTE_POLARITY_HITOLO;

    nrfx_gpiote_out_config_t gpiote_out_tgle_config;
    gpiote_out_tgle_config.action = NRF_GPIOTE_POLARITY_TOGGLE;
    gpiote_out_tgle_config.init_state = NRF_GPIOTE_INITIAL_VALUE_LOW;
    gpiote_out_tgle_config.task_pin = true;
*/

/* This code will not work because I can't set two GPIOTE channels for one pin (one for sensing lo-hi, one for sensing hi-lo which should completely be fine given they're going to be oscillating at WELL below 4MHZ. 
See this link: https://devzone.nordicsemi.com/f/nordic-q-a/64181/gpiote-two-events-for-the-same-pin


    err_code = nrfx_gpiote_in_init(dev->p.s0_pin, &gpiote_re_config, NULL); //No callback function as we are using PPI
    LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Could not initialise GPIOTE pin S0 rising edge");
    err_code = nrfx_gpiote_in_init(dev->p.s0_pin, &gpiote_fe_config, NULL);
    LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Could not initialise GPIOTE pin S0 falling edge");

    err_code = nrfx_gpiote_in_init(dev->p.s1_pin, &gpiote_out_tgle_config, NULL); //No callback function as we are using PPI
    LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Could not initialise GPIOTE S1");
    
    err_code = nrfx_gpiote_in_init(dev->p.s2_pin, &gpiote_out_tgle_config, NULL); 
    LP_DRV_ERR_CHECK(nrfx_err_to_zephyr_err(err_code), "Could not initialise GPIOTE S2");

*/