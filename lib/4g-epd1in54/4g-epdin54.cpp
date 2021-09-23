#include "4g-epd1in54.h"
#include "SEGGER_RTT.h"
#include "nrfx_config.h"
#include "SPI.h"
#include "nrfx_gpiote.h"
#include "nrf_svc.h"
#include "nrf_nvic.h"

extern "C"
{
  nrf_nvic_state_t nrf_nvic_state = {0};
}

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
  _epd_spi = new SPIClass(NRF_SPIM2, _spi_miso, _spi_sck, _spi_mosi);
  _epd_spi_settings = SPISettings(4000000, MSBFIRST, SPI_MODE0);
}

int EPD_4::Init(const unsigned char* lut, void (*busy_cb)(uint32_t pin, nrf_gpiote_polarity_t polarity))
{
  uint32_t err_code;
  if(first_init)
  {
    pinMode(_cs_pin, OUTPUT);
    pinMode(_busy_pin, INPUT);
    pinMode(_dc_pin, OUTPUT);
    pinMode(_reset_pin, OUTPUT);
    _busy_cb = busy_cb; 
    _epd_spi->begin();
    _epd_spi->beginTransaction(_epd_spi_settings);
    err_code = CallBackInit();
    if(err_code == NRF_SUCCESS)
    {
      first_init = false;
    }
  }
  //Hardware Reset
  digitalWrite(RST_PIN, 0);
  delay(10);
  digitalWrite(RST_PIN, 1);
  delay(10);
  BusyWait();
  SendCommand(SW_RESET);
  BusyWait();
  /*
  WARNING, THESE COMMANDS ARE UNDEFINED FOR SSD1681!!
  SendCommand(0x74); //set analog block control       
  SendData(0x54);
  SendCommand(0x7E); //set digital block control          
  SendData(0x3B);
  */
  SendCommand(DRIVER_OUTPUT_CONTROL);     
  SendData(0xC7);
  SendData(0x00);
  SendData(0x00);
  SendCommand(DATA_ENTRY_MODE_SETTING); //data entry mode       
  SendData(0x01);
  SendCommand(SET_RAM_X_ADDRESS_START_END_POS); //set Ram-X address start/end position   
  SendData(0x00);
  SendData(0x18);    //0x0C-->(18+1)*8=200
  SendCommand(SET_RAM_Y_ADDRESS_START_END_POS); //set Ram-Y address start/end position          
  SendData(0xC7);    //0xC7-->(199+1)=200
  SendData(0x00);
  SendData(0x00);
  SendData(0x00); 
  SendCommand(BORDER_WAVEFORM_CONTROL); //BorderWavefrom
  SendData(0x00);  
  SendCommand(VCOM_REG_WRITE);     //VCOM Voltage
  SendData(_lut_4_gray[158]);    //0x1C
  SendCommand(END_OPTION); //EOPQ    
  SendData(_lut_4_gray[153]);
  SendCommand(GATE_DRIVE_VOLTAGE_CONTROL); //VGH      
  SendData(_lut_4_gray[154]);
  SendCommand(SOURCE_DRIVE_VOLTAGE_CONTROL); //      
  SendData(_lut_4_gray[155]); //VSH1   
  SendData(_lut_4_gray[156]); //VSH2   
  SendData(_lut_4_gray[157]); //VSL   
  SetLookUpTable(_lut_4_gray); //LUT 
  SendCommand(SET_RAM_X_ADDRESS_COUNTER);   // set RAM x address count to 0;
  SendData(0x00);
  SendCommand(SET_RAM_Y_ADDRESS_COUNTER);   // set RAM y address count to 0X199;    
  SendData(0xC7);
  SendData(0x00);
  BusyWait();
  return err_code;
}

void EPD_4::SendCommand(unsigned char command)
{
  digitalWrite(_dc_pin, LOW);
  digitalWrite(_cs_pin, LOW);
  _epd_spi->transfer(command);
  digitalWrite(_cs_pin, HIGH);  
}
void EPD_4::SendData(unsigned char data)
{
  digitalWrite(_dc_pin, HIGH);
  digitalWrite(_cs_pin, LOW);
  _epd_spi->transfer(data);
  digitalWrite(_cs_pin, HIGH);
}
void EPD_4::BusyWait(void)
{
  while(digitalRead(_busy_pin) == HIGH)
  {
    delay(10);
  }
}

void EPD_4::SetLookUpTable(const unsigned char* lut)
{
  SendCommand(WRITE_LUT_REGISTER);
  for(uint8_t count = 0; count < 153; count ++)
  {
    SendData(lut[count]);
  }
}

nrfx_err_t EPD_4::BusyCallBack(void)
{
  nrfx_gpiote_in_event_enable(_busy_pin, true);
}

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
    if(err_code != NRF_SUCCESS)
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

void EPD_4::FullUpdate(void)
{   
  SendCommand(DISPLAY_UPDATE_CONTROL_2); //Display Update Control
  SendData(0xF7);   
  SendCommand(MASTER_ACTIVATION); //Activate Display Update Sequence
  BusyCallBack();
}
void EPD_4::PartUpdate(void)
{
  SendCommand(DISPLAY_UPDATE_CONTROL_2);//Display Update Control 
  SendData(0xFF);   
  SendCommand(MASTER_ACTIVATION); //Activate Display Update Sequence
  BusyCallBack();      
}
void EPD_4::Sleep(void)
{  
  SendCommand(DEEP_SLEEP_MODE); //enter deep sleep
  SendData(0x01); //Deep sleep mode 1 - retains RAM data.
}

void EPD_4::CopyFrameBufferToRAM(const unsigned char* image_buffer, int x, int y, 
                                int image_width, int image_height)
  
  {



  }
///////////////////////////Part update//////////////////////////////////////////////
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  unsigned int i;  
  unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
  x_start=x_start/8;//
  x_end=x_start+PART_LINE/8-1; 
  
  y_start1=0;
  y_start2=y_start;
  if(y_start>=256)
  {
    y_start1=y_start2/256;
    y_start2=y_start2%256;
  }
  y_end1=0;
  y_end2=y_start+PART_COLUMN-1;
  if(y_end2>=256)
  {
    y_end1=y_end2/256;
    y_end2=y_end2%256;    
  }   
//Reset
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay 
    
  SendCommand(0x3C); //BorderWavefrom
  SendData(0x80);  
//  
  SendCommand(0x44);       // set RAM x address start/end, in page 35
  SendData(x_start);    // RAM x address start at 00h;
  SendData(x_end);    // RAM x address end at 0fh(15+1)*8->128 
  SendCommand(0x45);       // set RAM y address start/end, in page 35
  SendData(y_start2);    // RAM y address start at 0127h;
  SendData(y_start1);    // RAM y address start at 0127h;
  SendData(y_end2);    // RAM y address end at 00h;
  SendData(y_end1);    // ????=0 


  SendCommand(0x4E);   // set RAM x address count to 0;
  SendData(x_start); 
  SendCommand(0x4F);   // set RAM y address count to 0X127;    
  SendData(y_start2);
  SendData(y_start1);
  
  
   SendCommand(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     SendData(pgm_read_byte(&datas[i]));
   } 
   EPD_Part_Update();

}



void EPD_HW_Init_4GRAY(void)
{
  EPD_W21_RST_0;     
  delay(10); 
  EPD_W21_RST_1; //hard reset  
  delay(10);  

  Epaper_READBUSY();
  SendCommand(0x12); // soft reset
  Epaper_READBUSY();

  SendCommand(0x74); //set analog block control       
  SendData(0x54);
  SendCommand(0x7E); //set digital block control          
  SendData(0x3B);
  
  SendCommand(0x01); //Driver output control      
  SendData(0xC7);
  SendData(0x00);
  SendData(0x00);

  SendCommand(0x11); //data entry mode       
  SendData(0x01);

  SendCommand(0x44); //set Ram-X address start/end position   
  SendData(0x00);
  SendData(0x18);    //0x0C-->(18+1)*8=200

  SendCommand(0x45); //set Ram-Y address start/end position          
  SendData(0xC7);    //0xC7-->(199+1)=200
  SendData(0x00);
  SendData(0x00);
  SendData(0x00); 

  SendCommand(0x3C); //BorderWavefrom
  SendData(0x00);  


  SendCommand(0x2C);     //VCOM Voltage
  SendData(LUT_DATA_4Gray[158]);    //0x1C


  SendCommand(0x3F); //EOPQ    
  SendData(LUT_DATA_4Gray[153]);
  
  SendCommand(0x03); //VGH      
  SendData(LUT_DATA_4Gray[154]);

  SendCommand(0x04); //      
  SendData(LUT_DATA_4Gray[155]); //VSH1   
  SendData(LUT_DATA_4Gray[156]); //VSH2   
  SendData(LUT_DATA_4Gray[157]); //VSL   
   
  EPD_select_LUT(LUT_DATA_4Gray); //LUT 
  
  SendCommand(0x4E);   // set RAM x address count to 0;
  SendData(0x00);
  SendCommand(0x4F);   // set RAM y address count to 0X199;    
  SendData(0xC7);
  SendData(0x00);
  Epaper_READBUSY();
}
unsigned char In2bytes_Out1byte_RAM1(unsigned char data1,unsigned char data2)
{
  unsigned int i; 
  unsigned char TempData1,TempData2;
  unsigned char outdata=0x00;
  TempData1=data1;
  TempData2=data2;
  
    for(i=0;i<4;i++)
     { 
        outdata=outdata<<1;
        if( ((TempData1&0xC0)==0xC0) || ((TempData1&0xC0)==0x40))
           outdata=outdata|0x01;
        else 
          outdata=outdata|0x00;

        TempData1=TempData1<<2;

        //delay_us(5) ; 
     }

    for(i=0;i<4;i++)
     { 
        outdata=outdata<<1;
         if((TempData2&0xC0)==0xC0||(TempData2&0xC0)==0x40)
           outdata=outdata|0x01;
        else 
          outdata=outdata|0x00;

        TempData2=TempData2<<2;

       // delay_us(5) ; 
     }
     return outdata;
}
unsigned char In2bytes_Out1byte_RAM2(unsigned char data1,unsigned char data2)
{
  unsigned int i; 
  unsigned char TempData1,TempData2;
  unsigned char outdata=0x00;
TempData1=data1;
TempData2=data2;
  
    for(i=0;i<4;i++)
     { 
        outdata=outdata<<1;
        if( ((TempData1&0xC0)==0xC0) || ((TempData1&0xC0)==0x80))
           outdata=outdata|0x01;
        else 
          outdata=outdata|0x00;

        TempData1=TempData1<<2;

       // delay_us(5) ; 
     }

    for(i=0;i<4;i++)
     { 
        outdata=outdata<<1;
         if((TempData2&0xC0)==0xC0||(TempData2&0xC0)==0x80)
           outdata=outdata|0x01;
        else 
          outdata=outdata|0x00;

        TempData2=TempData2<<2;

        //delay_us(5) ; 
     }
     return outdata;
}
//296*128
void EPD_WhiteScreen_ALL_4GRAY(const unsigned char *datas)
{
   unsigned int i;
   unsigned char tempOriginal;   
  
  
    SendCommand(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<5000*2;i+=2)
   {               
    tempOriginal= In2bytes_Out1byte_RAM1( *(datas+i),*(datas+i+1));
     SendData(~tempOriginal); 
   }
   
   SendCommand(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<5000*2;i+=2)
   {               
    tempOriginal= In2bytes_Out1byte_RAM2( *(datas+i),*(datas+i+1));
     SendData(~tempOriginal); 
   }
   EPD_Update_4GRAY();   
}
void EPD_Update_4GRAY(void)
{   
  SendCommand(0x22); 
  SendData(0xC7);   
  SendCommand(0x20); 
  Epaper_READBUSY();  

}




//////////////////////////////////END//////////////////////////////////////////////////
