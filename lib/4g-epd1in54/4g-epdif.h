#ifndef EPDIF_H
#define EPDIF_H

#include <Arduino.h>

// Pin definition
#define RST_PIN         36
#define DC_PIN          38
#define CS_PIN          39 //EPD-CS, not SRAM-CS as SRAM will not be used on the final product.
#define BUSY_PIN        35

class EPDInterface_4 {
public:
    EPDInterface_4(void);
    ~EPDInterface_4(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMS(unsigned int delaytime);
    static void SPITransfer(unsigned char data);
};

#endif