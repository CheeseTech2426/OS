#include "kernelUtil.h"


extern "C" void _start(BootInfo* bootInfo){


    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

        GlobalRenderer->Colour = 0x00a6ff;
        GlobalRenderer->Print("Welcome to CheeseOS");


    while(true);
}