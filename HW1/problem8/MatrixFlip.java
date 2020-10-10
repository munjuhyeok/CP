public class MatrixFlip {
    public static void printFlippedMatrix(char[][] matrix) {
        // DO NOT change the skeleton code.
        // You can add codes anywhere you want.
        int num_row = matrix.length;
        int num_column = matrix[0].length;
        for (int i=0; i<num_row; i++){
            for(int j=0;j<num_column;j++){
                System.out.printf(Character.toString(matrix[num_row-i-1][num_column-j-1]));
            }
            System.out.println();
        }

    }
}