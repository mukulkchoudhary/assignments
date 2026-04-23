import java.util.Scanner;

public class EmailValidator {
    
    public static void validateEmail(String email) throws IllegalArgumentException {
        if (email == null || email.isEmpty()) {
            throw new IllegalArgumentException("Email cannot be empty");
        }
        
        if (!email.contains("@")) {
            throw new IllegalArgumentException("Invalid email: Must contain '@' symbol");
        }
        
        if (!email.contains(".")) {
            throw new IllegalArgumentException("Invalid email: Must contain '.' symbol");
        }
        
        int atIndex = email.indexOf('@');
        int lastDotIndex = email.lastIndexOf('.');
        
        if (atIndex == 0) {
            throw new IllegalArgumentException("Invalid email: No characters before '@'");
        }
        
        if (atIndex == email.length() - 1) {
            throw new IllegalArgumentException("Invalid email: No domain name after '@'");
        }
        
        if (lastDotIndex < atIndex) {
            throw new IllegalArgumentException("Invalid email: '.' must appear after '@'");
        }
        
        if (lastDotIndex == email.length() - 1) {
            throw new IllegalArgumentException("Invalid email: No domain extension after '.'");
        }
        
        if (lastDotIndex - atIndex <= 1) {
            throw new IllegalArgumentException("Invalid email: Domain name too short");
        }
        
        System.out.println("Valid email address!");
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int choice;
        
        do {
            System.out.println("\n===== EMAIL VALIDATOR =====");
            System.out.println("1. Validate Email");
            System.out.println("2. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            sc.nextLine();
            
            if (choice == 1) {
                System.out.print("Enter email address: ");
                String email = sc.nextLine();
                
                try {
                    validateEmail(email);
                } 
                catch (IllegalArgumentException e) {
                    System.out.println("Exception: " + e.getMessage());
                }
            }
            
        } while(choice != 2);
        
        System.out.println("Exiting...");
        sc.close();
    }
}