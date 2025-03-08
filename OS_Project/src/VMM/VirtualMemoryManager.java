package VMM;

import java.io.*;
import java.util.*;

class VirtualMemoryManager {
    private static final int PAGE_TABLE_SIZE = 256;
    private static final int FRAME_SIZE = 256;
    private static final int TLB_SIZE = 16;
    private static final int MEMORY_SIZE = PAGE_TABLE_SIZE * FRAME_SIZE;
    
    private byte[] physicalMemory = new byte[MEMORY_SIZE];
    private int[] pageTable = new int[PAGE_TABLE_SIZE];
    private LinkedHashMap<Integer, Integer> tlb = new LinkedHashMap<>(TLB_SIZE, 0.75f, true);
    private RandomAccessFile backingStore;
    
    private int pageFaults = 0;
    private int tlbHits = 0;
    private int nextFreeFrame = 0;

    public VirtualMemoryManager(String backingStoreFile) throws IOException {
        Arrays.fill(pageTable, -1);
        backingStore = new RandomAccessFile(backingStoreFile, "r");
    }

    private int getPhysicalAddress(int logicalAddress) throws IOException {
        int pageNumber = (logicalAddress >> 8) & 0xFF;
        int offset = logicalAddress & 0xFF;
        
        int frameNumber = tlb.getOrDefault(pageNumber, -1);
        if (frameNumber != -1) {
            tlbHits++;
        } else {
            frameNumber = pageTable[pageNumber];
            if (frameNumber == -1) {
                pageFaults++;
                frameNumber = handlePageFault(pageNumber);
            }
            updateTLB(pageNumber, frameNumber);
        }
        
        return (frameNumber * FRAME_SIZE) + offset;
    }

    private int handlePageFault(int pageNumber) throws IOException {
        if (nextFreeFrame >= PAGE_TABLE_SIZE) {
            throw new OutOfMemoryError("No more free frames");
        }
        
        backingStore.seek(pageNumber * FRAME_SIZE);
        backingStore.readFully(physicalMemory, nextFreeFrame * FRAME_SIZE, FRAME_SIZE);
        
        pageTable[pageNumber] = nextFreeFrame;
        return nextFreeFrame++;
    }

    private void updateTLB(int pageNumber, int frameNumber) {
        if (tlb.size() >= TLB_SIZE) {
            Iterator<Integer> iterator = tlb.keySet().iterator();
            iterator.next();
            iterator.remove();
        }
        tlb.put(pageNumber, frameNumber);
    }

    public void translateAddresses() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter number of addresses: ");
        int n = scanner.nextInt();
        
        System.out.println("Enter logical addresses:");
        for (int i = 0; i < n; i++) {
            int logicalAddress = scanner.nextInt();
            int physicalAddress = getPhysicalAddress(logicalAddress);
            byte value = physicalMemory[physicalAddress];
            System.out.printf("Logical Address: %d, Physical Address: %d, Value: %d\n", logicalAddress, physicalAddress, value);
        }
        scanner.close();
        
        System.out.printf("Page Fault Rate: %.2f%%\n", (pageFaults / (double) n) * 100);
        System.out.printf("TLB Hit Rate: %.2f%%\n", (tlbHits / (double) n) * 100);
    }

    public static void main(String[] args) {
        try {
            VirtualMemoryManager vmm = new VirtualMemoryManager("BACKING_STORE.bin");
            vmm.translateAddresses();
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
