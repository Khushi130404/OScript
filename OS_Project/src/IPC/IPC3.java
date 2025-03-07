package IPC;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class IPC3 
{
    public static void main(String[] args) 
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String lastCommand = null; 

        while (true) 
        {
            System.out.print("osh> ");
            try 
            {
                String input = reader.readLine().trim();

                if (input.equals("exit")) 
                {
                    break; 
                }

                if (input.equals("!!")) 
                {
                    if (lastCommand == null) 
                    {
                        System.out.println("No commands in history.");
                        continue;
                    } 
                    else 
                    {
                        input = lastCommand; 
                        System.out.println(input); 
                    }
                }

                lastCommand = input;
                executeCommand(input);

            } 
            catch (IOException e) 
            {
                System.err.println("Error reading input: " + e.getMessage());
            }
        }
    }

    private static void executeCommand(String input) 
    {
        String[] command = input.split("\\s+");

        try 
        {
            ProcessBuilder processBuilder = new ProcessBuilder(command);
            processBuilder.inheritIO(); 
            Process process = processBuilder.start();
            process.waitFor(); 
        } 
        catch (IOException e) 
        {
            System.err.println("Execution failed: " + e.getMessage());
        } 
        catch (InterruptedException e) 
        {
            Thread.currentThread().interrupt();
        }
    }
}
