#include "4g-epd1in54.h"


//Documentation says I need the following """C""" snippet to use NVIC. Not going to make a separate C file!! 
//I really hope this works.
extern "C"
{
  nrf_nvic_state_t nrf_nvic_state = {0}; 
}
/**
 * Creates EPD driver instance for SSD1681 GDEH0154D67 display.
 * @param epd_busy: MCU pin that EPD busy is connected to.
 * @param epd_reset: MCU pin that EPD reset is connected to.
 * @param epd_cs: MCU pin that EPD chip select (CS) is connected to.
 * @param epd_mosi: MCU pin that EPD Master Out/Slave In (MOSI) is connected to.
 * @param epd_miso: MCU pin that EPD Master In/Slave OUT (MISO) is connected to.
 * @param epd_sck: MCU pin that EPD Serial Clock (SCK) is connected to.
 * @param debug: Unused parameter - may introduce SEGGER_RTT debug logs in later revision.
 */
EPD_4::EPD_4(int epd_busy, int epd_reset, int epd_dc, 
            int epd_cs, int epd_mosi, int epd_miso, int epd_sck, bool debug)
{
  _reset_pin = epd_reset;
  _busy_pin = epd_busy;
  _cs_pin = epd_cs;
  _dc_pin = epd_dc;
  _spi_miso = epd_miso;
  _spi_mosi = epd_mosi;
  _spi_sck = epd_sck;
  _epd_spi = new SPIClass(NRF_SPIM2, _spi_miso, _spi_sck, _spi_mosi); //I do not want this instance to be destroyed unless I say so, so using "new"
  _epd_spi_settings = SPISettings(4000000, MSBFIRST, SPI_MODE0);
}

/**
 * Unloads the SPI instance for destruction, removes the GPIOTE instance from the defined busy pin.
 */
EPD_4::~EPD_4()
{
  _epd_spi->end();
  nrfx_gpiote_in_event_disable(_busy_pin);
  nrfx_gpiote_in_uninit(_busy_pin);
}

/**
 * Runs initialisation routine on EPD. Use this function to wake up EPD after running Sleep().
 * @param busy_cb Reference to ISR handler which will be called after Partial or Full refresh. Your function will be passed the pin, and polarity (direction) of the interrupt. 
 * @param pin polarity - ISR handler should input the pin, and the polarity, which will tell your handler what the busy line has done. 
 */
int EPD_4::Init(bool gray, void (*busy_cb)(uint32_t pin, nrf_gpiote_polarity_t polarity))
{
  uint32_t err_code;
  if(_first_init)
  {
    pinMode(_cs_pin, OUTPUT);
    //pinMode(_busy_pin, INPUT); Unncessary, will conflict with GPIOTE use of _busy_pin.
    pinMode(_dc_pin, OUTPUT);
    pinMode(_reset_pin, OUTPUT);
    _busy_cb = busy_cb; 
    _epd_spi->begin();
    _epd_spi->beginTransaction(_epd_spi_settings);
    err_code = CallBackInit();
    if(err_code == NRFX_SUCCESS)
    {
      _first_init = false;
    }
  }
  //Hardware Reset
  digitalWrite(_reset_pin, 0);
  delay(10);
  digitalWrite(_reset_pin, 1);
  delay(10);
  BusyWait();
  SendCommand(SW_RESET);
  BusyWait();
  _asleep = false;
  _gray = gray;
  /*
  WARNING, THESE COMMANDS ARE UNDEFINED FOR SSD1681!!
  Update :: Spoke to GoodDisplay, it is safe to comment out the next four lines. 
  SendCommand(0x74); //set analog block control       
  SendData(0x54);
  SendCommand(0x7E); //set digital block control          
  SendData(0x3B);
  */
  SendCommand(DRIVER_OUTPUT_CONTROL);     
  SendData(0xC7);
  SendData(0x00);
  SendData(0x00);
  SendCommand(DATA_ENTRY_MODE_SETTING);   
  SendData(0x03);
  SendCommand(SET_RAM_X_ADDRESS_START_END_POS); 
  SendData(0x00);
  SendData(EPD_WIDTH /8 - 1);   //EPD width / 8 - 1
  SendCommand(SET_RAM_Y_ADDRESS_START_END_POS);         
  SendData(0x00);   
  SendData(0x00);
  SendData(EPD_HEIGHT - 1);
  SendData((EPD_HEIGHT - 1) >> 8); 
  SendCommand(BORDER_WAVEFORM_CONTROL); 
  SendData(0x00);  
  if(gray)
  {
    SendCommand(VCOM_REG_WRITE);     //Setting VCOM Voltage
    SendData(_lut_4_gray[158]);    
    SendCommand(END_OPTION);    
    SendData(_lut_4_gray[153]);
    SendCommand(GATE_DRIVE_VOLTAGE_CONTROL);       
    SendData(_lut_4_gray[154]);
    SendCommand(SOURCE_DRIVE_VOLTAGE_CONTROL); //      
    SendData(_lut_4_gray[155]);    
    SendData(_lut_4_gray[156]);   
    SendData(_lut_4_gray[157]);   
    SetLookUpTable(_lut_4_gray); //Write 4 grayscale waveform 
  }
  else
  {
    SendCommand(BORDER_WAVEFORM_CONTROL);
    SendData(0x05);
    SendCommand(TEMPERATURE_SENSOR_CONTROL);
    SendData(0x80);
  }
  SendCommand(SET_RAM_X_ADDRESS_COUNTER);   // set RAM x address count to denary 0;
  SendData(0x00);
  SendCommand(SET_RAM_Y_ADDRESS_COUNTER);   // set RAM y address count to denary 199;    
  SendData(0xC7);
  SendData(0x00);
  BusyWait();
  err_code = NRF_SUCCESS;
  return err_code;
}
/**
 * Sends a hex command to the EPD. See Solomon SSD1681 datasheet for command table.
 * @param command 8 bit hex value representing command - e.g 0x10.
 */
void EPD_4::SendCommand(unsigned char command)
{
  digitalWrite(_dc_pin, LOW);
  digitalWrite(_cs_pin, LOW);
  _epd_spi->transfer(command);
  digitalWrite(_cs_pin, HIGH);  
}
/**
 * Sends data to the EPD. See Solomon SSD1681 datasheet for valid commands and expected data.
 * @param command 8 bit hex value representing data - e.g 0x10.
 */
void EPD_4::SendData(unsigned char data)
{
  digitalWrite(_dc_pin, HIGH);
  digitalWrite(_cs_pin, LOW);
  _epd_spi->transfer(data);
  digitalWrite(_cs_pin, HIGH);
}
/**
 * Waits for BUSY line to become low indicating EPD is no longer busy and is ready for command input by blocking main thread.
 */
void EPD_4::BusyWait(void)
{
  while(digitalRead(_busy_pin) == HIGH)
  {
    delay(10);
  }
}
/**
 * Writes the 153 byte OTP waveform data to the EPD. Done automatically during Init().
 * @param lut 159 byte char array with waveform and key lookup values.
 */
void EPD_4::SetLookUpTable(const unsigned char* lut)
{
  SendCommand(WRITE_LUT_REGISTER);
  for(uint8_t count = 0; count < 153; count ++)
  {
    SendData(lut[count]);
  }
}
/**
 * Waits for the EPD to refresh without blocking main thread. Enables GPIOTE interrupt that will call interrupt handler specified by busy_cb in Init(). Callback function should disable interrupt once serviced to prevent erroneous interrupts.
 */
void EPD_4::BusyCallBack(void)
{
  nrfx_gpiote_in_event_enable(_busy_pin, true);
}
/**
 * Initialises interrupt that will call busy_cb when BUSY line goes to LOW.  
 */
nrfx_err_t EPD_4::CallBackInit(void)
{
  //Assuming GPIOTE driver is already loaded.
  uint8_t _softdevice_status;
  sd_softdevice_is_enabled(&_softdevice_status);
  if(_softdevice_status == 1) {} //Find out which softdevice wrappers needed for gpiote function?? 
  //This might not work because of the softdevice - might be unreliable. Hopefully ~300ms refresh should be ok.
  nrfx_err_t err_code;
  if(!nrfx_gpiote_is_init())
  {
    err_code = nrfx_gpiote_init(2);
    if(err_code != NRFX_SUCCESS)
    {
      return err_code;
    }
  }
  //We want to sense when the BUSY line is going from HIGH to LOW, implying that the
  //EPD is no longer busy. This will then fire an interrupt to the specified callback
  //function, whose pointer is stored in _busy_cb.
  nrfx_gpiote_in_config_t cb_int_config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
  cb_int_config.pull = NRF_GPIO_PIN_PULLUP;
  cb_int_config.hi_accuracy = true;
  //nrfx_gpiote_evt_handler_t is typedef void, so can be casted safetly.
  err_code = nrfx_gpiote_in_init(_busy_pin, &cb_int_config, (nrfx_gpiote_evt_handler_t) _busy_cb);
  return err_code;
}
/**
 * Full EPD refresh - takes ~2 seconds. Calls ISR handler specified in Init()
 */
void EPD_4::FullUpdate(void)
{   
  SendCommand(DISPLAY_UPDATE_CONTROL_2); //Display Update Control
  SendData(0xF7);   
  SendCommand(MASTER_ACTIVATION); //Activate Display Update Sequence
  BusyWait();
}
/**
 * Partial EPD refresh - takes ~300 milliseconds. Calls ISR handler specified in Init()
 */
void EPD_4::PartUpdate(void)
{
  SendCommand(DISPLAY_UPDATE_CONTROL_2); //Display Update Control 
  SendData(0xFF);   
  SendCommand(MASTER_ACTIVATION); //Activate Display Update Sequence
  //BusyCallBack();
  BusyWait();      
}
/**
 * Hybrid EPD refresh - will perform "threshold" number of partial EPD refreshes before a Full EPD refresh. Calls ISR handler specified in Init().
 * @param threshold Number of partial refreshes to perform before cleaning display with full refresh.
 */
void EPD_4::HybridRefresh(uint8_t threshold)
{
  if(threshold > _partial_refreshes)
  {
    PartUpdate();
    _partial_refreshes++;
  }
  else 
  {
    FullUpdate();
    _partial_refreshes = 0;
  }
}
/**
 * Puts EPD in deep sleep mode 1 (1uA typical consumption) Use Init() to wake EPD.
 */
void EPD_4::Sleep(void)
{  
  SendCommand(DEEP_SLEEP_MODE); //enter deep sleep
  SendData(0x01); //Deep sleep mode 1 - retains RAM data, can try Deep Sleep Mode 2...
  digitalWrite(_reset_pin, LOW); 
  _asleep = true;
}
/**
 *   Takes in hex 2-bit colour pattern and turns the entire screen that colour. 
 *   Note: Uses Full refresh!
 * @param  color Hex char - 0x00 = Black, 0x02 = Dark Gray, 0x01 = Light Gray, 0x03 = White
 * 
 */  
void EPD_4::BlanketBomb(unsigned char color)
{
  SetMemoryWindow(0, 0, 199, 199);
  SendCommand(WRITE_RAM_1);
  for (int j = 0; j < 200; j++) {
    for (int i = 0; i < 200 / 8; i++) {
      SendData(color<<1);
    }
  }
  SetMemoryWindow(0, 0, 199, 199);
  SendCommand(WRITE_RAM_2);
  for (int j = 0; j < 200; j++) {
    for (int i = 0; i < 200 / 8; i++) {
      SendData(color&0x01);
      //This bitwise operation will set the second bit to zero, and leave the first bit
      //if it is 1.
    }
  }
  SendCommand(DISPLAY_UPDATE_CONTROL_2); //Display Update Control
  SendData(0xF7);   
  SendCommand(MASTER_ACTIVATION); //Activate Display Update Sequence
  BusyWait();
}
/**
 *    Copies split buffers for 4 grayscale into display RAM. Does not update display. Calling thread is responsible for sorting colour information into the buffers!. Coordinates are ZERO-BASED!
 *    @param ram1_buffer Split data buffer for RAM1
 *    @param ram2_buffer Split data buffer for RAM2
 *    @param x Starting x-coordinate
 *    @param y Starting y-coordinate 
 *    @param x_end End x-coordinate
 *    @param y_end End y-coordinate
 * 
 */
void EPD_4::CopyFrameBufferToRAM(const unsigned char* ram1_buffer, const unsigned char* ram2_buffer, 
                                int x, int y, int x_end, int y_end)
  
{
  /*
  4 Grayscale operation:
  RAM 1 |  RAM 2   Colour
  ______|__________________
  0     |  0       Black
  1     |  0       Dark Gray
  0     |  1       Light Gray
  1     |  1       White
  */
  if (ram1_buffer == NULL || ((ram2_buffer == NULL)&&(_gray==true)) || x < 0 || y < 0) 
  {
    return;
  }

  x &= 0xF8;
  x_end &= 0xF8;
  if(_asleep)
  {
    Init(_gray, _busy_cb);
  }
  SetMemoryWindow(x, y, x_end, y_end);
  //Writing RAM Contents!
  SendCommand(WRITE_RAM_1);
  for (int j = 0; j < y_end - y + 1; j++) {
      for (int i = 0; i < (x_end - x + 1) / 8; i++) {
          SendData(ram1_buffer[i + j * ((x_end - x) / 8)]);
      }
  }
  if(_gray)
  {
    SetMemoryWindow(x, y, x_end, y_end); //This might be unnecessary - test this.
    SendCommand(WRITE_RAM_2);
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
            SendData(ram2_buffer[i + j * ((x_end - x) / 8)]);
        }
    }
  }
  
  
}

void EPD_4::SetMemoryWindow(int x_start, int y_start, int x_end, int y_end)
{
  SendCommand(SET_RAM_X_ADDRESS_START_END_POS);
  SendData((x_start >> 3) & 0xFF); //Generating memory unit
  SendData((x_end >> 3) & 0xFF);
  SendCommand(SET_RAM_Y_ADDRESS_START_END_POS);
  SendData(y_start & 0xFF);
  SendData((y_start >> 8) & 0xFF);
  SendData(y_end & 0xFF);
  SendData((y_end >> 8) & 0xFF);
  SendCommand(SET_RAM_X_ADDRESS_COUNTER);
  SendData((x_start >> 3) & 0xFF);
  SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
  SendData(y_start & 0xFF);
  SendData((y_start >> 8) & 0xFF);
  BusyWait();
}