/*
    TinyOLED.h - Library for using Display OLED 128x32 0.91 I2C SSD1306 with AtTiny85.
    Note that you need to use Spence Konde's ATTiny Core and TinyI2CMaster library for these routines to work.
    
    Created by Hernán Rodríguez - hernan.rod.98@gmail.com - March 13, 2021.
    
    CC BY 4.0
    Licensed under a Creative Commons Attribution 4.0 International license: 
    http://creativecommons.org/licenses/by/4.0/
*/

#include "TinyOLED.h"
#include "Arduino.h"
#include "TinyI2CMaster.h"
#include "avr/pgmspace.h"

TinyOLED::TinyOLED(){}

void TinyOLED::init(){
    TinyI2C.init();     // initialize i2c bus

    sendCommand(0xAE);  // set power off
    delay(10);

    sendCommand(0xAF);  // set power on
    delay(10);

    sendCommand(0xA6);  // set normal display
    sendCommand(0x20);  // set addressing mode
    sendCommand(0x02);  // set page addressing mode
    
    clear();
    sendCommand(0xA8);  // multiplexer
    sendCommand(0x1F);
    sendCommand(0xDA);  // com Pins
    sendCommand(0x02);

    setCursorXY(0,0);
    sendCommand(0x8D);  // charge pump
    sendCommand(0x14);
}

void TinyOLED::clear(){
    for(byte page=0; page<8; page++) {  
        setCursorXY(0, page);     
        for(byte column=0; column<128; column++){  // clear all columns
            sendData(0);    
        }
    }
    setCursorXY(0,0); 
}

void TinyOLED::setCursorXY(byte X, byte Y){
    sendCommand(0x00 + (8*X & 0x0F));     // set column lower address
    sendCommand(0x10 + ((8*X>>4)&0x0F));  // set column higher address
    sendCommand(0xB0 + Y);                // set page address  
}

void TinyOLED::printChar(char c){
    // ignore unused ASCII characters
    if(c < 32 || c > 127)
        c='*'; // indicate characters that can't be displayed
    
    for(byte i=0; i<8; i++) 
        sendData(pgm_read_byte(&BasicFont[c-32][i])); // font array starts at 0, ASCII starts at 32. Hence the translation      
}

void TinyOLED::printString(const char *str){
    byte count=0;
    while(str[count])
        printChar(str[count++]);     
}

void TinyOLED::printNumber(int num){
    byte i=0;
    byte buffer[3] = "";
    
    if(num == 0)
        printChar('0');
    
    while(num > 0){
        buffer[i++] = num%10;
        num /= 10;
    }

    while(i > 0){
        printChar('0'+ buffer[i-1]);
        i--;
    }
}

void TinyOLED::sendCommand(byte cmd){
    TinyI2C.start(OLED_ADDRESS, 0);
    TinyI2C.write(0x80); // cmd mode
    TinyI2C.write(cmd);
    TinyI2C.stop();
}

void TinyOLED::sendData(byte data){
    TinyI2C.start(OLED_ADDRESS, 0);
    TinyI2C.write(0x40); // data mode
    TinyI2C.write(data);
    TinyI2C.stop();
}

TinyOLED TinyOled = TinyOLED(); // preinstantiate object