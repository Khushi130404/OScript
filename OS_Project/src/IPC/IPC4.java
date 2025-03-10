package IPC;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class IPC4 
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);

        while (true) 
        {
            System.out.print("osh> ");
            String input = scanner.nextLine().trim();
            if (input.equals("exit")) break;

            try 
            {
                List<String> command = new ArrayList<>();
                String outputFile = null, inputFile = null;

                String[] tokens = input.split("\\s+");
                for (int i = 0; i < tokens.length; i++) 
                {
                    if (tokens[i].equals(">")) 
                    {
                        outputFile = tokens[i + 1];
                        i++;
                    } 
                    else if (tokens[i].equals("<")) 
                    {
                        inputFile = tokens[i + 1];
                        i++;
                    } 
                    else 
                    {
                        command.add(tokens[i]);
                    }
                }

                ProcessBuilder pb = new ProcessBuilder(command);

                if (inputFile != null) 
                {
                    pb.redirectInput(new File(inputFile));
                }
                
                if (outputFile != null) 
                {
                    pb.redirectOutput(new File(outputFile));
                } 
                else 
                {
                    pb.redirectOutput(ProcessBuilder.Redirect.PIPE);
                }

                Process process = pb.start();

                if (outputFile == null) 
                {
                    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                    String line;
                    while ((line = reader.readLine()) != null) 
                    {
                        System.out.println(line);
                    }
                }

                process.waitFor();
            } 
            catch (Exception e) 
            {
                System.out.println("Error: " + e.getMessage());
            }
        }

        scanner.close();
    }
}
