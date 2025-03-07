package IPC;

import java.io.*;
import java.util.*;

public class IPC2 
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
                break;
            }

            String[] commandArgs = input.split("\\s+");

            ProcessBuilder processBuilder = new ProcessBuilder(commandArgs);
            processBuilder.inheritIO(); 

            try 
            {
                Process process = processBuilder.start(); 
                process.waitFor(); 
            } 
            catch (IOException e) 
            {
                System.out.println("Command execution failed: " + e.getMessage());
            } 
            catch (InterruptedException e) 
            {
                System.out.println("Process interrupted: " + e.getMessage());
            }
        }
        scanner.close();
    }
}
