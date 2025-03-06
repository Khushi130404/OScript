package sudoku_multithreading;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Sudoku 
{
    private static final int SIZE = 9;
    private static final int SUBGRID_SIZE = 3;
    private static final int NUM_THREADS = 11;
    static boolean[] results = new boolean[NUM_THREADS];

    static int[][] sudoku = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
    };

    public static void main(String[] args) 
    {
        ExecutorService executor = Executors.newFixedThreadPool(NUM_THREADS);

        executor.execute(new RowChecker(sudoku, 0, results));
        executor.execute(new ColumnChecker(sudoku, 1, results));

        int index = 2;
        for (int i = 0; i < SIZE; i += SUBGRID_SIZE) 
        {
            for (int j = 0; j < SIZE; j += SUBGRID_SIZE) 
            {
                executor.execute(new SubgridChecker(sudoku, i, j, index, results));
                index++;
            }
        }

        executor.shutdown();
        while (!executor.isTerminated()) 
        {
        	// wait
        	// Eat 5-star, Do nothing 😎
        }

        
        for (boolean result : results) 
        {
            if (!result) 
            {
                System.out.println("Invalid Sudoku Solution!");
                return;
            }
        }
        System.out.println("Valid Sudoku Solution!");
    }
}

