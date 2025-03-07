package IPC;

import java.io.*;
import java.util.*;

public class IPC5 
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);

        while (true) 
        {
            System.out.print("osh> "); 
            String input = scanner.nextLine().trim();

            if (input.equalsIgnoreCase("exit")) 
            {
                System.out.println("Exiting shell...");
                break;
            }

            String[] commands = input.split("\\|"); // Split commands by '|'

            if (commands.length == 1) 
            {
                executeCommand(commands[0].trim(), null);
            }
            else if (commands.length == 2) 
            {
                executePipedCommands(commands[0].trim(), commands[1].trim());
            } 
            else 
            {
                System.out.println("Only single pipe (|) is supported.");
            }
        }

        scanner.close();
    }

    private static void executeCommand(String command, OutputStream outputStream) 
    {
        String[] cmdArray = command.split(" ");
        try 
        {
            ProcessBuilder processBuilder = new ProcessBuilder(cmdArray);
            Process process = processBuilder.start();

            if (outputStream != null) 
            {
                try (InputStream processOutput = process.getInputStream();
                     BufferedOutputStream bos = new BufferedOutputStream(outputStream)) 
                {
                    processOutput.transferTo(bos);
                }
            } 
            else 
            {
            
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) 
                {
                    String line;
                    while ((line = reader.readLine()) != null) 
                    {
                        System.out.println(line);
                    }
                }
            }
            process.waitFor();
        } 
        catch (IOException | InterruptedException e) 
        {
            System.out.println("Error executing command: " + command);
        }
    }

    private static void executePipedCommands(String cmd1, String cmd2) 
    {
        try 
        {
            ProcessBuilder pb1 = new ProcessBuilder(cmd1.split(" "));
            ProcessBuilder pb2 = new ProcessBuilder(cmd2.split(" "));

            Process p1 = pb1.start();
            Process p2 = pb2.start();

            try (InputStream p1Output = p1.getInputStream();
                 OutputStream p2Input = p2.getOutputStream()) 
            {
                p1Output.transferTo(p2Input);
            }

            p1.waitFor();
            p2.waitFor();

            try (BufferedReader reader = new BufferedReader(new InputStreamReader(p2.getInputStream()))) 
            {
                String line;
                while ((line = reader.readLine()) != null) 
                {
                    System.out.println(line);
                }
            }
        } 
        catch (IOException | InterruptedException e) 
        {
            System.out.println("Error executing piped commands.");
        }
    }
}
