#include "PageFrameAllocater.h"


uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool Initialized = false;
PageFrameAllocater GlobalAllocator;

void PageFrameAllocater::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescriptorSize) {
    if(Initialized) return;

    Initialized = true;

    uint64_t mMapEntries = mMapSize / mMapDescriptorSize;

    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for(int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescriptorSize));
        if(desc->type == 7) { // type = EfiConventionalMemory
            if(desc->numPages * 4096 > largestFreeMemSegSize){
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        } 
    }

    uint64_t memorySize = GetMemorySize(mMap, mMapEntries, mMapDescriptorSize);
    freeMemory = memorySize;
    uint64_t bitmapSize = memorySize / 4096 / 8 + 1;

    InitBitmap(bitmapSize, largestFreeMemSeg);

    LockPages(&PageBitmap, PageBitmap.Size / 4096 + 1);

    
    for(int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescriptorSize));
        if(desc->type != 7){ //not EfiConventionalMemory
            ReservePages(desc->physAddr, desc->numPages);
        }
    }   
}

void PageFrameAllocater::InitBitmap(size_t bitmapSize, void* bufferAddress) {
        PageBitmap.Size = bitmapSize;
        PageBitmap.Buffer = (uint8_t*)bufferAddress;
        for(int i = 0; i < bitmapSize; i++){
            *(uint8_t*)(PageBitmap.Buffer + i) = 0;
        }
}

void* PageFrameAllocater::RequestPage(){
    for(uint64_t index = 0; index < PageBitmap.Size * 8; index++){
        if(PageBitmap[index] == true) continue;
        LockPage((void*)(index * 4096));
        return (void*)(index * 4096);
    }

    return NULL; // Page Frame Swap to file
}

void PageFrameAllocater::FreePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == false) return;
    PageBitmap.Set(index, false);
    freeMemory += 4096;
    usedMemory -= 4096;
}

void PageFrameAllocater::FreePages(void* address, uint64_t pageCount){
    for(int t = 0; t < pageCount; t++){
        FreePage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocater::LockPage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == true) return;
    PageBitmap.Set(index, true);
    freeMemory -= 4096;
    usedMemory += 4096;
}

void PageFrameAllocater::LockPages(void* address, uint64_t pageCount){
    for(int t = 0; t < pageCount; t++){
        LockPage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocater::UnreservePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == false) return;
    PageBitmap.Set(index, false);
    freeMemory += 4096;
    reservedMemory -= 4096;
}

void PageFrameAllocater::UnreservePages(void* address, uint64_t pageCount){
    for(int t = 0; t < pageCount; t++){
        UnreservePage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocater::ReservePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == true) return;
    PageBitmap.Set(index, true);
    freeMemory -= 4096;
    reservedMemory += 4096;
}

void PageFrameAllocater::ReservePages(void* address, uint64_t pageCount){
    for(int t = 0; t < pageCount; t++){
        ReservePage((void*)((uint64_t)address + (t * 4096)));
    }
}

uint64_t PageFrameAllocater::GetFreeRAM(){
    return freeMemory;
}

uint64_t PageFrameAllocater::GetUsedRAM(){
    return usedMemory;
}

uint64_t PageFrameAllocater::GetReservedRAM(){
    return reservedMemory;
}