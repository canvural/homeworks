/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mergenumbers;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

/**
 *
 * @author can
 */
public class MergeNumbers
{
    
    private static final int[][] NEIGHBOURS = {
                  {-1, 0}, 
        { 0, -1},          { 0, +1},
                  {+1, 0}
    };

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        int[][] grid = {{2, 0, 1, 1, 0, 8}, {2, 1, 0, 2, 4, 0}, {1, 2, 1, 2, 1, 3}, {2, 3, 2, 0, 1, 0}, {0, 0, 5, 8, 7, 2}, {2, 0, 1, 1, 0, 0}};
    
        for(int[] row : grid) {
            printRow(row);
        }
        mergeNumbers(grid, 3,3,1, false);
        for(int[] row : grid) {
            printRow(row);
        }
    }
    
    public static void printRow(int[] row) {
        for (int i : row) {
            System.out.print(i);
            System.out.print("\t");
        }
        System.out.println();
    }
    
    public static void mergeNumbers(int[][] grid, int row, int column, int nextNumber, boolean bypass)
    {
        if(grid[row][column] != 0 && !bypass) {
            return;
        }
        
        grid[row][column] = nextNumber;
        
        int rowSize = grid.length;
        int columnSize = grid[row].length;
        
        ArrayList<int[]> toBeZerod = new ArrayList<>();
                        
        Queue<int[]> q = new LinkedList<>();
        
        int[] temp = {row, column};
        
        q.add(temp);
        toBeZerod.add(temp);
        
        while(!q.isEmpty()) {
            int[] elem = q.remove();
            int i = elem[0], j = elem[1];
            
            for (int[] offset : NEIGHBOURS) {
                if(isValid(i + offset[0], j + offset[1], columnSize, rowSize)) {
                    int[] tmp = {i + offset[0], j + offset[1]};
                    
                    if(grid[tmp[0]][tmp[1]] == nextNumber && !isInList(toBeZerod, tmp)) {
                        q.add(tmp);
                        toBeZerod.add(tmp);
                    }
                }
            }
            System.out.println("Done");
        }
        
        if(toBeZerod.size() < 3) {
            return;
        }
        
        for(int[] zero : toBeZerod) {
            grid[zero[0]][zero[1]] = 0;
        }
        
        grid[row][column] = nextNumber++;
        
        mergeNumbers(grid, row, column, nextNumber, true);
    }
    
    public static boolean isValid(int x, int y, int width, int height) {
        return x >= 0 && y >= 0 && y < width && x < height;
    }
    
    public static boolean isInList(
        final ArrayList<int[]> list, final int[] candidate){

        for(final int[] item : list){
            if(Arrays.equals(item, candidate)){
                return true;
            }
        }
        return false;
    }
}
