#include "mouse.h"

void MouseWait(){
    uint64_t timeout = 100000;
    while(timeout--){
        if((inb(0x64) & 0b1) == 0){
            return;
        }    
    } 
}

void MouseWaitInput(){
    uint64_t timeout = 100000;
    while(timeout--){
        if(inb(0x64) & 0b1){
            return;
        }    
    } 
}

void MouseWrite(uint8_t value){
    MouseWait();
    outb(0x64, 0xD4);
    MouseWait();
    outb(0x60, value);
}

uint8_t MouseRead(){
    MouseWaitInput();
    return inb(0x60);
}

void InitPS2Mouse(){
    outb(0x64, 0xA8); // Enabling the Auxiliary device - mouse
    MouseWait();
    outb(0x64, 0x20); // Tells the Keyboard controller that we want to send a command to the Mouse.com
    MouseWaitInput();
    uint8_t status = inb(0x60);
    status |= 0b10;
    MouseWait();
    outb(0x64, 0x60);
    MouseWait();
    outb(0x60, status); // Setting the correct bit is the "compaq" status byte

    MouseWrite(0xF6);
    MouseRead();
    
    MouseWrite(0xF4);
    MouseRead();
}