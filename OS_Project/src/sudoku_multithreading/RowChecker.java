package sudoku_multithreading;

public class RowChecker implements Runnable 
{
    private int[][] sudoku;
    private int index;
    private boolean[] results;

    public RowChecker(int[][] sudoku, int index, boolean[] results) 
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
            if (!Validate.isValidSet(sudoku[i])) 
            {
                results[index] = false;
                return;
            }
        }
        results[index] = true;
    }
}
