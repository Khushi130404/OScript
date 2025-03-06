package sudoku_multithreading;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Sudoku 
{
    private static final int SIZE = 9;
    private static final int SUBGRID_SIZE = 3;
    private static final int NUM_THREADS = 11;
    private static boolean[] results = new boolean[NUM_THREADS];

    private static int[][] sudoku = 
    {
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

    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(NUM_THREADS);

        executor.execute(new RowChecker(0));
        executor.execute(new ColumnChecker(1));
        
        int index = 2;
        for (int i = 0; i < SIZE; i += SUBGRID_SIZE) {
            for (int j = 0; j < SIZE; j += SUBGRID_SIZE) {
                executor.execute(new SubgridChecker(i, j, index));
                index++;
            }
        }

        executor.shutdown();
        while (!executor.isTerminated()) {}

        for (boolean result : results) {
            if (!result) {
                System.out.println("Invalid Sudoku Solution!");
                return;
            }
        }
        System.out.println("Valid Sudoku Solution!");
    }

    static class RowChecker implements Runnable {
        private int index;

        RowChecker(int index) {
            this.index = index;
        }

        @Override
        public void run() {
            for (int i = 0; i < SIZE; i++) {
                if (!isValidSet(sudoku[i])) {
                    results[index] = false;
                    return;
                }
            }
            results[index] = true;
        }
    }

    static class ColumnChecker implements Runnable {
        private int index;

        ColumnChecker(int index) {
            this.index = index;
        }

        @Override
        public void run() {
            for (int i = 0; i < SIZE; i++) {
                int[] column = new int[SIZE];
                for (int j = 0; j < SIZE; j++) {
                    column[j] = sudoku[j][i];
                }
                if (!isValidSet(column)) {
                    results[index] = false;
                    return;
                }
            }
            results[index] = true;
        }
    }

    static class SubgridChecker implements Runnable {
        private int startRow, startCol, index;

        SubgridChecker(int startRow, int startCol, int index) {
            this.startRow = startRow;
            this.startCol = startCol;
            this.index = index;
        }

        @Override
        public void run() {
            int[] subgrid = new int[SIZE];
            int k = 0;
            for (int i = 0; i < SUBGRID_SIZE; i++) {
                for (int j = 0; j < SUBGRID_SIZE; j++) {
                    subgrid[k++] = sudoku[startRow + i][startCol + j];
                }
            }
            results[index] = isValidSet(subgrid);
        }
    }

    private static boolean isValidSet(int[] arr) {
        boolean[] seen = new boolean[SIZE + 1];
        for (int num : arr) {
            if (num < 1 || num > SIZE || seen[num]) {
                return false;
            }
            seen[num] = true;
        }
        return true;
    }
}
