import java.util.Scanner;

public class OddSum2D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter number of rows: ");
        int rows = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int cols = sc.nextInt();
        
        int[][] matrix = new int[rows][cols];
        int sum = 0;
        
        System.out.println("Enter elements of matrix:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = sc.nextInt();
                if (matrix[i][j] % 2 != 0) {
                    sum = sum + matrix[i][j];
                }
            }
        }
        
        System.out.println("\nMatrix:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(matrix[i][j] + "\t");
            }
            System.out.println();
        }
        
        System.out.println("\nSum of all odd numbers: " + sum);
        sc.close();
    }
}






import java.util.Scanner;

public class MatrixTranspose {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter number of rows: ");
        int rows = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int cols = sc.nextInt();
        
        int[][] matrix = new int[rows][cols];
        int[][] transpose = new int[cols][rows];
        
        System.out.println("Enter elements of matrix:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = sc.nextInt();
            }
        }
        
        // Calculating transpose
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                transpose[j][i] = matrix[i][j];
            }
        }
        
        System.out.println("\nOriginal Matrix:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(matrix[i][j] + "\t");
            }
            System.out.println();
        }
        
        System.out.println("\nTranspose Matrix:");
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                System.out.print(transpose[i][j] + "\t");
            }
            System.out.println();
        }
        
        sc.close();
    }
}






import java.util.Scanner;

class Matrix {
    private int[][] data;
    private int rows;
    private int cols;
    
    // Constructor for NxN matrix
    public Matrix(int n) {
        this.rows = n;
        this.cols = n;
        data = new int[n][n];
    }
    
    // Constructor for MxN matrix
    public Matrix(int m, int n) {
        this.rows = m;
        this.cols = n;
        data = new int[m][n];
    }
    
    // Get data from user
    public void get_Data() {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter elements for " + rows + "x" + cols + " matrix:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = sc.nextInt();
            }
        }
    }
    
    // Print matrix
    public void print_Mat() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(data[i][j] + "\t");
            }
            System.out.println();
        }
    }
    
    // Add two matrices
    public Matrix add_Mat(Matrix m) {
        if (this.rows != m.rows || this.cols != m.cols) {
            System.out.println("Matrices cannot be added! Dimensions mismatch.");
            return null;
        }
        
        Matrix result = new Matrix(this.rows, this.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = this.data[i][j] + m.data[i][j];
            }
        }
        return result;
    }
    
    // Multiply two matrices
    public Matrix mult_Mat(Matrix m) {
        if (this.cols != m.rows) {
            System.out.println("Matrices cannot be multiplied! Columns of first must equal rows of second.");
            return null;
        }
        
        Matrix result = new Matrix(this.rows, m.cols);
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < this.cols; k++) {
                    result.data[i][j] = result.data[i][j] + (this.data[i][k] * m.data[k][j]);
                }
            }
        }
        return result;
    }
}

public class MatrixDemo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.println("--- First Matrix ---");
        System.out.print("Enter number of rows: ");
        int r1 = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int c1 = sc.nextInt();
        Matrix m1 = new Matrix(r1, c1);
        m1.get_Data();
        
        System.out.println("\n--- Second Matrix ---");
        System.out.print("Enter number of rows: ");
        int r2 = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int c2 = sc.nextInt();
        Matrix m2 = new Matrix(r2, c2);
        m2.get_Data();
        
        int choice;
        do {
            System.out.println("\n--- Matrix Operations ---");
            System.out.println("1. Print First Matrix");
            System.out.println("2. Print Second Matrix");
            System.out.println("3. Add Matrices");
            System.out.println("4. Multiply Matrices");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            
            switch(choice) {
                case 1:
                    System.out.println("First Matrix:");
                    m1.print_Mat();
                    break;
                case 2:
                    System.out.println("Second Matrix:");
                    m2.print_Mat();
                    break;
                case 3:
                    Matrix sum = m1.add_Mat(m2);
                    if (sum != null) {
                        System.out.println("Sum of Matrices:");
                        sum.print_Mat();
                    }
                    break;
                case 4:
                    Matrix product = m1.mult_Mat(m2);
                    if (product != null) {
                        System.out.println("Product of Matrices:");
                        product.print_Mat();
                    }
                    break;
                case 5:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Invalid choice!");
            }
        } while(choice != 5);
        
        sc.close();
    }
}





import java.util.Scanner;

class MathOperation {
    // Static instance variable
    public static final double PI = 3.14159;
    
    // Static method to multiply two numbers
    public static double mul(double a, double b) {
        return a * b;
    }
    
    // Static method to divide two numbers
    public static double div(double a, double b) {
        if (b == 0) {
            System.out.println("Error: Division by zero!");
            return 0;
        }
        return a / b;
    }
}

public class CircleArea {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter the diameter of the circle: ");
        double diameter = sc.nextDouble();
        
        // Calculate radius from diameter
        double radius = MathOperation.div(diameter, 2);
        
        // Area of full circle = π * r²
        double fullArea = MathOperation.mul(MathOperation.PI, MathOperation.mul(radius, radius));
        
        // Area of half circle = (π * r²) / 2
        double halfArea = MathOperation.div(fullArea, 2);
        
        System.out.println("\n--- Calculation Details ---");
        System.out.println("Diameter: " + diameter);
        System.out.println("Radius: " + radius);
        System.out.println("Value of PI: " + MathOperation.PI);
        System.out.println("Full circle area: " + fullArea);
        System.out.println("Half circle area: " + halfArea);
        
        sc.close();
    }
}
