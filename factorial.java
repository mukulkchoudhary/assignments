import java.util.Scanner;

public class Factorial {
    
    private static long[] factorialCache = new long[21];
    private static boolean[] computed = new boolean[21];
    
    public static long computeFactorial(int x) throws IllegalArgumentException {
        if (x < 0) {
            throw new IllegalArgumentException("Value of x must be positive");
        }
        
        if (x > 20) {
            throw new IllegalArgumentException("Result will overflow");
        }
        
        if (computed[x]) {
            return factorialCache[x];
        }
        
        long result = 1;
        for (int i = 1; i <= x; i++) {
            result = result * i;
        }
        
        factorialCache[x] = result;
        computed[x] = true;
        
        return result;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int choice;
        
        do {
            System.out.println("\n===== FACTORIAL CALCULATOR =====");
            System.out.println("1. Calculate Factorial");
            System.out.println("2. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            
            if (choice == 1) {
                System.out.print("Enter a number to find factorial: ");
                int num = sc.nextInt();
                
                try {
                    long result = computeFactorial(num);
                    System.out.println(num + "! = " + result);
                } 
                catch (IllegalArgumentException e) {
                    System.out.println("Error: " + e.getMessage());
                }
            }
            
        } while(choice != 2);
        
        System.out.println("Exiting...");
        sc.close();
    }
}