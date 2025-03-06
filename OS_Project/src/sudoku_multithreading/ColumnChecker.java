package sudoku_multithreading;

public class ColumnChecker implements Runnable 
{
    private int[][] sudoku;
    private int index;
    private boolean[] results;

    public ColumnChecker(int[][] sudoku, int index, boolean[] results) 
    {
        this.sudoku = sudoku;
        this.index = index;
        this.results = results;
    }

    @Override
    public void run() 
    {
        for (int i = 0; i < sudoku.length; i++) 
        {
            int[] column = new int[sudoku.length];
            for (int j = 0; j < sudoku.length; j++) 
            {
                column[j] = sudoku[j][i];
            }
            if (!Validate.isValidSet(column)) 
            {
                results[index] = false;
                return;
            }
        }
        results[index] = true;
    }
}
