#include "4g-epdif.h"
#include "SPI.h"

/**
*  @brief   :   Parts of this driver are built in the same way as 
*               the Waveshare EPD driver by Yehui as there are many identical operations
*               between my driver and the Waveshare one, despite the different display controllers.
*               These controllers are so similar that I have no choice but to duplicate some code. 
*               I decided to change a few things to improve this driver, hence I am writing this code.
*  @author  :   Yuvraj Dubey, with help from GoodDisplay's sample code for GDEH0154D67 and Yehui from Waveshare's code for SSD1608.
*
*/

EPDInterface_4::EPDInterface_4() {};
EPDInterface_4::~EPDInterface_4() {};

void EPDInterface_4::DigitalWrite(int pin, int value)
{
    digitalWrite(pin, value);
}

int EPDInterface_4::DigitalRead(int pin)
{
    return digitalRead(pin);
}
/**
*   @brief  :   This is a proxy function for delay, can be implemented directly
*               with Nordic delay functions, but the implementation is very good
                and I don't want to reinvent the wheel.
*/
void EPDInterface_4::DelayMS(unsigned int ms)
{
    delay(ms);
}

void EPDInterface_4::SPITransfer(unsigned char data)
{
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(data);
    digitalWrite(CS_PIN, HIGH);
}

