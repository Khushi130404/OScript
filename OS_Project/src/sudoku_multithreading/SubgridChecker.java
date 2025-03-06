package sudoku_multithreading;

public class SubgridChecker implements Runnable 
{
    private int[][] sudoku;
    private int startRow, startCol, index;
    private boolean[] results;

    public SubgridChecker(int[][] sudoku, int startRow, int startCol, int index, boolean[] results) 
    {
        this.sudoku = sudoku;
        this.startRow = startRow;
        this.startCol = startCol;
        this.index = index;
        this.results = results;
    }

    @Override
    public void run() 
    {
        int[] subgrid = new int[9];
        int k = 0;
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                subgrid[k++] = sudoku[startRow + i][startCol + j];
            }
        }
        results[index] = Validate.isValidSet(subgrid);
    }
}
