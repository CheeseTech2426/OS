#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo) {
    
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    
    BasicRenderer 
    GlobalRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);
//    
// Welocome Text & RAM
    
    // Welcome Text
    
    GlobalRenderer.CursorPosition = {0, GlobalRenderer.CursorPosition.Y + 16};
    GlobalRenderer.Colour = 0x00a6ff;
    GlobalRenderer.Print("            Welcome to TuhnuOS!");
    GlobalRenderer.CursorPosition = {0,  GlobalRenderer.CursorPosition.Y + 16};
    GlobalRenderer.Print("        ---------------------------      ");
    GlobalRenderer.CursorPosition = {0,   GlobalRenderer.CursorPosition.Y + 16};
    GlobalRenderer.Print("Hello and thank you for choosing TuhnuOS!");
    GlobalRenderer.CursorPosition = {0, GlobalRenderer.CursorPosition.Y + 16};
    GlobalRenderer.Print("I hope you like it as much as I did designing this!");
    GlobalRenderer.CursorPosition = {0, GlobalRenderer.CursorPosition.Y + 16};
    GlobalRenderer.Print("And don't fear to send your feedback.");
    GlobalRenderer.CursorPosition = {0, 
    GlobalRenderer.CursorPosition.Y + 16};
    GlobalRenderer.Print("If you spot a bug, please send your feedback!");
    GlobalRenderer.CursorPosition = {0, GlobalRenderer.CursorPosition.Y + 128 / 2};
    
   
    // RAM

  //  GlobalRenderer.Colour = 0xdcff00;
   // GlobalRenderer.Print("            RAM");
   // GlobalRenderer.CursorPosition = {0, GlobalRenderer.CursorPosition.Y + 16};
   // GlobalRenderer.Print("       -------------");
   // GlobalRenderer.CursorPosition = {0,  GlobalRenderer.CursorPosition.Y + 16};
   // GlobalRenderer.Print("Free RAM: ");
    //GlobalRenderer.Print(to_string(GlobalAllocator.GetFreeRAM() / 1024));
   // GlobalRenderer.Print(" KB ");
   // GlobalRenderer.CursorPosition = {0, GlobalRenderer.CursorPosition.Y + 16};
  //  GlobalRenderer.Print("Used RAM: ");
  //  GlobalRenderer.Print(to_string(GlobalAllocator.GetUsedRAM() / 1024);
  //  GlobalRenderer.Print(" KB ");
  //  GlobalRenderer.CursorPosition = {0, GlobalRenderer.CursorPosition.Y + 16};
   // GlobalRenderer.Print("Reserved RAM: ");
   // GlobalRenderer.Print(to_string(GlobalAllocator.GetReservedRAM() / 1024));
   // GlobalRenderer.Print(" KB ");
    //GlobalRenderer.CursorPosition = {0, GlobalRenderer.CursorPosition.Y + 16};

//
    while(true);
} 