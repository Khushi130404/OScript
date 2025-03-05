package Bank;

import java.io.*;
import java.util.*;

public class BankersAlgorithm 
{
    private int numCustomers;
    private int numResources;
    private int[] available;
    private int[][] maximum;
    private int[][] allocation;
    private int[][] need;

    public BankersAlgorithm(int numCustomers, int numResources, int[] available, int[][] maximum) 
    {
        this.numCustomers = numCustomers;
        this.numResources = numResources;
        this.available = available;
        this.maximum = maximum;
        this.allocation = new int[numCustomers][numResources];
        this.need = new int[numCustomers][numResources];

        for (int i = 0; i < numCustomers; i++) 
        {
            for (int j = 0; j < numResources; j++) 
            {
                need[i][j] = maximum[i][j];
            }
        }
    }

    public synchronized int requestResources(int customerNum, int[] request) 
    {    
        for (int i = 0; i < numResources; i++) 
        {
            if (request[i] > need[customerNum][i]) 
            {
                System.out.println("Request exceeds maximum need. Denied.");
                return -1;
            }
        }

        for (int i = 0; i < numResources; i++) 
        {
            if (request[i] > available[i]) 
            {
                System.out.println("Not enough resources available. Denied.");
                return -1;
            }
        }

        for (int i = 0; i < numResources; i++) 
        {
            available[i] -= request[i];
            allocation[customerNum][i] += request[i];
            need[customerNum][i] -= request[i];
        }

        if (isSafe()) 
        {
            System.out.println("Request granted.");
            return 0;
        } 
        else 
        {
            for (int i = 0; i < numResources; i++) 
            {
                available[i] += request[i];
                allocation[customerNum][i] -= request[i];
                need[customerNum][i] += request[i];
            }
            System.out.println("Request denied (unsafe state).");
            return -1;
        }
    }

    public synchronized void releaseResources(int customerNum, int[] release) 
    {
        for (int i = 0; i < numResources; i++) 
        {
            allocation[customerNum][i] -= release[i];
            available[i] += release[i];
            need[customerNum][i] += release[i];
        }
        System.out.println("Resources released.");
    }

    private boolean isSafe() 
    {
        boolean[] finished = new boolean[numCustomers];
        int[] work = Arrays.copyOf(available, numResources);
        int count = 0;

        while (count < numCustomers) 
        {
            boolean found = false;
            for (int i = 0; i < numCustomers; i++) 
            {
                if (!finished[i]) 
                {
                    boolean canAllocate = true;
                    for (int j = 0; j < numResources; j++) 
                    {
                        if (need[i][j] > work[j]) 
                        {
                            canAllocate = false;
                            break;
                        }
                    }

                    if (canAllocate) 
                    {
                        for (int j = 0; j < numResources; j++) 
                        {
                            work[j] += allocation[i][j];
                        }
                        finished[i] = true;
                        found = true;
                        count++;
                    }
                }
            }
            if (!found) return false;
        }
        return true;
    }

    public void printState() 
    {
        System.out.println("\nCurrent State:");
        System.out.println("Available Resources: " + Arrays.toString(available));
        System.out.println("Maximum:");
        printMatrix(maximum);
        System.out.println("Allocation:");
        printMatrix(allocation);
        System.out.println("Need:");
        printMatrix(need);
    }

    private void printMatrix(int[][] matrix) 
    {
        for (int[] row : matrix) 
        {
            System.out.println(Arrays.toString(row));
        }
    }

    public static void main(String[] args) throws IOException 
    {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of resource types: ");
        int numResources = scanner.nextInt();

        System.out.print("Enter the number of customers: ");
        int numCustomers = scanner.nextInt();

        int[] available = new int[numResources];
        System.out.println("Enter available resources for each type:");
        for (int i = 0; i < numResources; i++) 
        {
            available[i] = scanner.nextInt();
        }

        int[][] maximum = new int[numCustomers][numResources];
        System.out.println("Enter maximum resource demand for each customer:");
        for (int i = 0; i < numCustomers; i++) 
        {
            System.out.print("Customer " + i + ": ");
            for (int j = 0; j < numResources; j++) 
            {
                maximum[i][j] = scanner.nextInt();
            }
        }

        BankersAlgorithm bank = new BankersAlgorithm(numCustomers, numResources, available, maximum);
        scanner.nextLine();

        while (true) 
        {
            System.out.print("\nEnter command: ");
            String command = scanner.nextLine();
            String[] parts = command.split(" ");

            try 
            {
                if (parts[0].equalsIgnoreCase("RQ")) 
                {
                    int customerNum = Integer.parseInt(parts[1]);
                    int[] request = Arrays.stream(Arrays.copyOfRange(parts, 2, parts.length)).mapToInt(Integer::parseInt).toArray();
                    bank.requestResources(customerNum, request);
                } 
                else if (parts[0].equalsIgnoreCase("RL")) 
                {
                    int customerNum = Integer.parseInt(parts[1]);
                    int[] release = Arrays.stream(Arrays.copyOfRange(parts, 2, parts.length)).mapToInt(Integer::parseInt).toArray();
                    bank.releaseResources(customerNum, release);
                } 
                else if (parts[0].equals("*")) 
                {
                    bank.printState();
                } 
                else if (parts[0].equalsIgnoreCase("exit")) 
                {
                    break;
                } 
                else 
                {
                    System.out.println("Invalid command. Use 'RQ', 'RL', '*' or 'exit'.");
                }
            } 
            catch (Exception e) 
            {
                System.out.println("Invalid input. Please try again.");
            }
        }
        scanner.close();
    }
}

// Example Rum :-
//Enter the number of resource types: 3
//Enter the number of customers: 5
//Enter available resources for each type:
//10 5 7
//Enter maximum resource demand for each customer:
//Customer 0: 7 5 3
//Customer 1: 3 2 2
//Customer 2: 9 0 2
//Customer 3: 2 2 2
//Customer 4: 4 3 3
//
//Enter command: RQ 1 1 0 2
//Request granted.
//
//Enter command: *
//Current State:
//Available Resources: [9, 5, 5]
//Maximum:
//[7, 5, 3]
//[3, 2, 2]
//[9, 0, 2]
//[2, 2, 2]
//[4, 3, 3]
//Allocation:
//[0, 0, 0]
//[1, 0, 2]
//[0, 0, 0]
//[0, 0, 0]
//[0, 0, 0]
//Need:
//[7, 5, 3]
//[2, 2, 0]
//[9, 0, 2]
//[2, 2, 2]
//[4, 3, 3]
//
//Enter command: exit
