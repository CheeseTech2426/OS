#include "interrupts.h"

__attribute__((interrupt)) void PageFauld_Handler(struct interrupt_frame* frame){
    
    GlobalRenderer->Print("Page fauld detected");
    while(true);
}