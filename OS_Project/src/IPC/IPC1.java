package IPC;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class IPC1
{
    public static void main(String[] args) 
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        boolean shouldRun = true;

        while (shouldRun) 
        {
            System.out.print("osh> ");
            System.out.flush();

            try 
            {
                String input = reader.readLine();
                if (input == null || input.trim().isEmpty()) 
                {
                    continue;
                }

                if (input.equalsIgnoreCase("exit")) 
                {
                    shouldRun = false;
                    continue;
                }

                
                StringTokenizer tokenizer = new StringTokenizer(input);
                String[] command = new String[tokenizer.countTokens()];
                int i = 0;
                while (tokenizer.hasMoreTokens()) {
                    command[i++] = tokenizer.nextToken();
                }

                
                ProcessBuilder processBuilder = new ProcessBuilder(command);
                processBuilder.inheritIO();
                Process process = processBuilder.start();
                process.waitFor();

            } 
            catch (IOException | InterruptedException e) 
            {
                System.out.println("Error executing command: " + e.getMessage());
            }
        }
    }
}
