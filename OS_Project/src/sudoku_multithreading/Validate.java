package sudoku_multithreading;

public class Validate 
{
    public static boolean isValidSet(int[] arr) 
    {
        boolean[] seen = new boolean[10]; 
        for (int num : arr) 
        {
            if (num < 1 || num > 9 || seen[num]) 
            {
                return false;
            }
            seen[num] = true;
        }
        return true;
    }
}
