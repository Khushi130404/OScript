package VMM;

import java.io.*;

public class BackingStoreGenerator 
{
    public static void main(String[] args) 
    {
        try (RandomAccessFile file = new RandomAccessFile("BACKING_STORE.bin", "rw")) 
        {
            byte[] data = new byte[256 * 256]; 
            for (int i = 0; i < data.length; i++) 
            {
                data[i] = (byte) (i % 256); 
            }
            file.write(data);
            System.out.println("BACKING_STORE.bin file created successfully.");
        } 
        catch (IOException e) 
        {
            System.err.println("Error creating BACKING_STORE.bin: " + e.getMessage());
        }
    }
}
