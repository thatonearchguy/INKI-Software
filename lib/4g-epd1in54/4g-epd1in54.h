#include <Arduino.h>
#include "4g-epdif.h"
/**
 * @brief: Some parts of this code will be similar to Yehui's waveshare code
 *         as explained in 4g-epdif.h's header. This is the main driver function for
 *         GDE0H154D67 SSD1681 200x200 4 grayscale display.
*/
#ifndef EPDIN54_H_4G
#define EPDIN54_H_4G

#define EPD_WIDTH 200
#define EPD_HEIGHT 200

//EPD COMMAND TABLE - taken from SSD1681 datasheet
#define DRIVER_OUTPUT_CONTROL           0x01
#define GATE_DRIVE_VOLTAGE_CONTROL      0x03
#define SOURCE_DRIVE_VOLTAGE_CONTROL    0x04  
#define INITIAL_CODE_SET_OTP            0x08    //Program initial code setting
#define INITAL_CODE_WRITE_REG           0x09
#define INITAL_CODE_READ_REG            0x0A   
#define BOOSTER_SOFT_START_CONTROL      0x0C 
#define DEEP_SLEEP_MODE                 0x10    //00 - normal, 01 - DeepSleep1, 02 - DeepSleep2. BUSY-high, send HWRESET to exit
#define DATA_ENTRY_MODE_SETTING         0x11    //Define data entry sequence. Y decrement/X decrement / increment permutations
#define SW_RESET                        0x12    //Resets commands and parameters to SW default. RAM UNAFFECTED - BUSY high
#define HV_READY_DETECTION              0x14    
#define VCI_DETECTION                   0x15    //VCI Level detection
#define TEMPERATURE_SENSOR_CONTROL      0x18    //Temperature Sensor Selection (48h = ext, 80h = int)
#define TEMPERATURE_SENSOR_WRITE        0x1A    //Write to temperature register
#define TEMPERATURE_SENSOR_READ         0x1B    //Read from temperature register
#define TEMPERATURE_SENSOR_COMMAND      0x1C    //Write command to external temperature sensor
#define MASTER_ACTIVATION               0x20    //Activate display Update Sequence. BUSY Will be HIGH during operation. 
#define DISPLAY_UPDATE_CONTROL_1        0x21    //RAM Content for Display
#define DISPLAY_UPDATE_CONTROL_2        0x22
#define WRITE_RAM_1                     0x24    //SSD1681 - two buffers. 1->Black/White
#define WRITE_RAM_2                     0x26    //SSD1681 - two buffers. 2->Grays || Red
#define READ_RAM                        0x27
#define VCOM_SENSE                      0x28    //ENTER VCOM Sensing mode for length defined in 29h before reading VCOM value.
#define VCOM_SENSE_DURATION             0x29    //Stabling time between entering VCOM sensing mode and reading acquired.
#define PROGRAM_VCOM_OTP                0x2A    //Program VCOM register into OTP
#define VCOM_CONTROL_REG_WRITE          0x2B    //Reduce glitch when ACVCOM toggle -> data
#define VCOM_REG_WRITE                  0x2C    //Write VCOM register from MCU
#define OTP_REG_READ_DISP_OPT           0x2D    //Read register for display option. 
#define USER_ID_READ                    0x2E    //Read 10 byte UserID stored in OTP.
#define STATUS_BIT_READ                 0x2F    //Read IC status bit - HV ready/VCI detection flags
#define PROGRAM_WS_OTP                  0x30    //Program waveform OTP. Write framebuffer to RAM before sending this command. BUSY=high
#define LOAD_WS_OTP                     0x31    //Load waveform OTP. BUSY=high
#define WRITE_LUT_REGISTER              0x32    //Write LUT register
#define CRC_CALC                        0x34    //CRC calculation - BUSY high
#define CRC_STATUS_READ                 0x35    //CRC status read
#define PROGRAM_OTP_SELECTION           0x36    //Program OTP selection according to OTP selection control
#define WRITE_REG_DISP_OPT              0x37    //Write register for display option. 
#define WRITE_REG_USER_ID               0x38    //Write UserID register
#define OTP_PROGRAM_MODE                0x39    //00 - normal, 11 - internal generated OTP programming voltage. (FOLLOW EXACT CODE SEQUENCES)
#define BORDER_WAVEFORM_CONTROL         0x3C    //Set border waveform
#define END_OPTION                      0x3F    //Option for LUT end
#define READ_RAM_OPTION                 0x41    //Read RAM option - 0->RAM1, 1->RAM2
#define SET_RAM_X_ADDRESS_START_END_POS 0x44    //Specify start/end position of the window address in the X direction by an address unit for RAM
#define SET_RAM_Y_ADDRESS_START_END_POS 0x45    //Specify start/end position of the window address in the Y direction by an address unit for RAM
#define AUTO_WRITE_RED_RAM              0x46    //FOR REGULAR PATTERN
#define AUTO_WRITE_BW_RAM               0x47    //FOR REGULAR PATTERN
#define SET_RAM_X_ADDRESS_COUNTER       0x4E    //Set initial address counter for RAM X addresses
#define SET_RAM_Y_ADDRESS_COUNTER       0x4F    //Set initial address counter for RAM Y addresses
#define NOP                             0x7F    //No operation

/*

4 Grayscale operation:

RAM 1 |  RAM 2   Colour
______|__________________
0     |  0       Black
1     |  0       Dark Gray
0     |  1       Light Gray
1     |  1       White
      |
*/

class EPD_4 : EPDInterface_4 {
public:
    EPD_4(int epd_busy, int epd_reset, int epd_dc, 
          int epd_cs, int epd_mosi, int epd_miso, int epd_sck, bool debug);
    ~EPD_4();
    int Init(const unsigned char* lut, void (*busy_cb)(uint32_t pin, nrf_gpiote_polarity_t polarity));
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void BusyWait(void);
    nrfx_err_t BusyCallBack(void);
    void Reset(void);
    void CopyFrameBufferToRAM(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
    );
    void BlanketBomb(unsigned char color);
    void FullUpdate(void);
    void PartUpdate(void);
    void Sleep(void);
    void HybridRefresh(int threshold);

private:
    void (*_busy_cb)(uint32_t pin, nrf_gpiote_polarity_t polarity);
    nrfx_err_t CallBackInit(void);
    void SetLookUpTable(const unsigned char* lut);
    unsigned int _reset_pin;
    unsigned int _dc_pin;
    unsigned int _cs_pin;
    unsigned int _busy_pin;
    unsigned int _spi_miso;
    unsigned int _spi_mosi;
    unsigned int _spi_sck;
    bool first_init = true;
    const unsigned char* _lut_mono;
    const unsigned char _lut_4_gray[159] = {
    0x40, 0x48, 0x80, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
    0x8,  0x48, 0x10, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
    0x2,  0x48, 0x4,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
    0x20, 0x48, 0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
    0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
    0xA,  0x19, 0x0,  0x3,  0x8,  0x0,  0x0,  0x14, 0x1,  0x0,  0x14, 0x1,  
    0x0,  0x3,  0xA,  0x3,  0x0,  0x8,  0x19, 0x0,  0x0,  0x1,  0x0,  0x0,  
    0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  
    0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  
    0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  
    0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  
    0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0,  0x0,  0x0,  0x22, 0x17, 0x41, 
    0x0,  0x32, 0x1C
    };  
    unsigned int _partials;
    SPIClass* _epd_spi;
    SPISettings _epd_spi_settings;
};

#endif 


#define EPD_W21_MOSI_0  digitalWrite(SDI_Pin,LOW)
#define EPD_W21_MOSI_1  digitalWrite(SDI_Pin,HIGH) 

#define EPD_W21_CLK_0 digitalWrite(SCK_Pin,LOW)
#define EPD_W21_CLK_1 digitalWrite(SCK_Pin,HIGH)

#define EPD_W21_CS_0 digitalWrite(CS_Pin,LOW)
#define EPD_W21_CS_1 digitalWrite(CS_Pin,HIGH)

#define EPD_W21_DC_0  digitalWrite(DC_Pin,LOW)
#define EPD_W21_DC_1  digitalWrite(DC_Pin,HIGH)
#define EPD_W21_RST_0 digitalWrite(RES_Pin,LOW)
#define EPD_W21_RST_1 digitalWrite(RES_Pin,HIGH)
#define isEPD_W21_BUSY digitalRead(BUSY_Pin)
//296*128///////////////////////////////////////

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES 25// =200/8
#define MAX_COLUMN_BYTES 200

#define ALLSCREEN_GRAGHBYTES 5000

////////FUNCTION//////
void driver_delay_us(unsigned int xus);
void driver_delay(unsigned long xms);
void DELAY_S(unsigned int delaytime);     
void SPI_Delay(unsigned char xrate);


//EPD
void Epaper_READBUSY(void);
void SPI_Write(unsigned char value);

void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Part_Init(void); //Local refresh initialization

void EPD_Part_Update(void); 
void EPD_Update(void);

void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);
//Display 
void EPD_WhiteScreen_ALL(const unsigned char * datas);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);
void EPD_Dis_Part_myself(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
                         unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
                         unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
                         unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
                         unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
                         unsigned int PART_COLUMN,unsigned int PART_LINE
                        );
void EPD_HW_Init_4GRAY(void);    
void EPD_Update_4GRAY(void);                         
void EPD_WhiteScreen_ALL_4GRAY(const unsigned char *datas);