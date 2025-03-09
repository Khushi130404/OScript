#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_TABLE_SIZE 256
#define FRAME_SIZE 256
#define TLB_SIZE 16
#define MEMORY_SIZE (PAGE_TABLE_SIZE * FRAME_SIZE)

unsigned char physicalMemory[MEMORY_SIZE];
int pageTable[PAGE_TABLE_SIZE];
int tlb[TLB_SIZE][2];
int tlbIndex = 0;

int pageFaults = 0, tlbHits = 0, nextFreeFrame = 0;

void initPageTable() 
{
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) 
    {
        pageTable[i] = -1;
    }
    for (int i = 0; i < TLB_SIZE; i++) 
    {
        tlb[i][0] = -1;
        tlb[i][1] = -1;
    }
}

void updateTLB(int pageNumber, int frameNumber) 
{
    tlb[tlbIndex][0] = pageNumber;
    tlb[tlbIndex][1] = frameNumber;
    tlbIndex = (tlbIndex + 1) % TLB_SIZE;
}

int getFrameFromTLB(int pageNumber) 
{
    for (int i = 0; i < TLB_SIZE; i++) 
    {
        if (tlb[i][0] == pageNumber) 
        {
            tlbHits++;
            return tlb[i][1];
        }
    }
    return -1;
}

int handlePageFault(int pageNumber, FILE *backingStore) 
{
    if (nextFreeFrame >= PAGE_TABLE_SIZE) 
    {
        fprintf(stderr, "Out of memory error\n");
        exit(EXIT_FAILURE);
    }

    fseek(backingStore, pageNumber * FRAME_SIZE, SEEK_SET);
    if (fread(physicalMemory + (nextFreeFrame * FRAME_SIZE), sizeof(char), FRAME_SIZE, backingStore) != FRAME_SIZE) 
    {
        fprintf(stderr, "I/O Error: Error reading page %d from BACKING_STORE.bin\n", pageNumber);
        exit(EXIT_FAILURE);
    }
    pageTable[pageNumber] = nextFreeFrame;
    return nextFreeFrame++;
}

int getPhysicalAddress(int logicalAddress, FILE *backingStore) 
{
    int pageNumber = (logicalAddress >> 8) & 0xFF;
    int offset = logicalAddress & 0xFF;

    int frameNumber = getFrameFromTLB(pageNumber);

    if (frameNumber == -1) 
    {
        frameNumber = pageTable[pageNumber];
        if (frameNumber == -1) 
        {
            pageFaults++;
            frameNumber = handlePageFault(pageNumber, backingStore);
        }
        updateTLB(pageNumber, frameNumber);
    }
    return (frameNumber * FRAME_SIZE) + offset;
}

int main() 
{
    FILE *backingStore = fopen("BACKING_STORE.bin", "rb");
    if (!backingStore) 
    {
        fprintf(stderr, "Error: BACKING_STORE.bin not found\n");
        return 1;
    }

    initPageTable();

    int n;
    printf("Enter number of addresses: ");
    scanf("%d", &n);

    printf("Enter logical addresses:\n");
    for (int i = 0; i < n; i++) 
    {
        int logicalAddress;
        scanf("%d", &logicalAddress);
        
        int physicalAddress = getPhysicalAddress(logicalAddress, backingStore);
        printf("Logical Address: %d, Physical Address: %d, Value: %d\n",logicalAddress, physicalAddress, physicalMemory[physicalAddress]);
    }

    printf("Page Fault Rate: %.2f%%\n", (pageFaults / (double)n) * 100);
    printf("TLB Hit Rate: %.2f%%\n", (tlbHits / (double)n) * 100);

    fclose(backingStore);
    return 0;
}