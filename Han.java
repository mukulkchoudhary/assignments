import java.util.Scanner;

class MyClass {
    
    // Method to find absolute value of integer
    public int abs(int num) {
        if (num < 0) {
            return -num;
        }
        return num;
    }
    
    // Method to find absolute value of float
    public float abs(float num) {
        if (num < 0) {
            return -num;
        }
        return num;
    }
    
    // Method to find absolute value of double
    public double abs(double num) {
        if (num < 0) {
            return -num;
        }
        return num;
    }
}

public class AbsDemo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        MyClass obj = new MyClass();
        int choice;
        
        do {
            System.out.println("\n=== Absolute Value Calculator ===");
            System.out.println("1. Find absolute value of an Integer");
            System.out.println("2. Find absolute value of a Float");
            System.out.println("3. Find absolute value of a Double");
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            
            switch(choice) {
                case 1:
                    System.out.print("Enter an integer: ");
                    int intNum = sc.nextInt();
                    System.out.println("Absolute value of " + intNum + " = " + obj.abs(intNum));
                    break;
                    
                case 2:
                    System.out.print("Enter a float number: ");
                    float floatNum = sc.nextFloat();
                    System.out.println("Absolute value of " + floatNum + " = " + obj.abs(floatNum));
                    break;
                    
                case 3:
                    System.out.print("Enter a double number: ");
                    double doubleNum = sc.nextDouble();
                    System.out.println("Absolute value of " + doubleNum + " = " + obj.abs(doubleNum));
                    break;
                    
                case 4:
                    System.out.println("Exiting program. Thank you!");
                    break;
                    
                default:
                    System.out.println("Invalid choice! Please enter 1, 2, 3, or 4.");
            }
        } while(choice != 4);
        
        sc.close();
    }
}






import java.util.Scanner;

// Base class
class Call {
    protected int duration; // in minutes
    
    // Default constructor
    public Call() {
        this.duration = 0;
    }
    
    // Parameterized constructor
    public Call(int duration) {
        this.duration = duration;
    }
    
    // Getter and Setter
    public int getDuration() {
        return duration;
    }
    
    public void setDuration(int duration) {
        this.duration = duration;
    }
    
    // Method to calculate charges (to be overridden)
    public double calculateCharges() {
        return 0;
    }
    
    // Helper method to calculate cost based on rate per 2 minutes
    protected double calculateCost(double ratePer2Min) {
        // Calculate number of 2-minute blocks (ceil of duration/2)
        int blocks = (int) Math.ceil((double) duration / 2);
        return blocks * ratePer2Min;
    }
}

// LocalCall class (to 033 code)
class LocalCall extends Call {
    private boolean isNightTime;
    
    // Default constructor
    public LocalCall() {
        super();
        this.isNightTime = false;
    }
    
    // Parameterized constructor
    public LocalCall(int duration, boolean isNightTime) {
        super(duration);
        this.isNightTime = isNightTime;
    }
    
    // Getters and Setters
    public boolean isNightTime() {
        return isNightTime;
    }
    
    public void setNightTime(boolean isNightTime) {
        this.isNightTime = isNightTime;
    }
    
    // Rate: Rs 0.1 per 2 min (same for day and night)
    @Override
    public double calculateCharges() {
        return calculateCost(0.1);
    }
}

// STDCall class for long distance calls
class STDCall extends Call {
    private int destinationCode;
    private boolean isNightTime;
    
    // Default constructor
    public STDCall() {
        super();
        this.destinationCode = 0;
        this.isNightTime = false;
    }
    
    // Parameterized constructor
    public STDCall(int duration, int destinationCode, boolean isNightTime) {
        super(duration);
        this.destinationCode = destinationCode;
        this.isNightTime = isNightTime;
    }
    
    // Getters and Setters
    public int getDestinationCode() {
        return destinationCode;
    }
    
    public void setDestinationCode(int destinationCode) {
        this.destinationCode = destinationCode;
    }
    
    public boolean isNightTime() {
        return isNightTime;
    }
    
    public void setNightTime(boolean isNightTime) {
        this.isNightTime = isNightTime;
    }
    
    // Get rate based on destination code and time
    private double getRate() {
        if (destinationCode == 11) { // 011 code
            if (isNightTime) {
                return 0.5; // Night time: Rs 0.5 per 2 min
            } else {
                return 1.0; // Day time: Rs 1 per 2 min
            }
        } else if (destinationCode == 22) { // 022 code
            if (isNightTime) {
                return 0.5; // Night time: Rs 0.5 per 2 min
            } else {
                return 1.5; // Day time: Rs 1.5 per 2 min
            }
        } else if (destinationCode == 44) { // 044 code
            if (isNightTime) {
                return 0.4; // Night time: Rs 0.4 per 2 min
            } else {
                return 0.75; // Day time: Rs 0.75 per 2 min
            }
        } else {
            return 0; // Invalid code
        }
    }
    
    @Override
    public double calculateCharges() {
        double rate = getRate();
        if (rate == 0) {
            System.out.println("Invalid STD code!");
            return 0;
        }
        return calculateCost(rate);
    }
}

// Driver class
public class BillingSystem {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.println("=== Telephone Billing System ===");
        System.out.println("Call Types:");
        System.out.println("1. Local Call (to 033 code)");
        System.out.println("2. STD Call");
        System.out.print("Enter your choice: ");
        int choice = sc.nextInt();
        
        if (choice == 1) {
            System.out.print("Enter call duration (in minutes): ");
            int duration = sc.nextInt();
            
            System.out.print("Enter call time (1 for Day Time 6:00-22:00, 2 for Night Time 22:01-5:59): ");
            int timeChoice = sc.nextInt();
            boolean isNight = (timeChoice == 2);
            
            LocalCall localCall = new LocalCall(duration, isNight);
            
            System.out.println("\n--- Local Call Bill ---");
            System.out.println("Destination Code: 033");
            System.out.println("Duration: " + duration + " minutes");
            System.out.println("Time Period: " + (isNight ? "Night (22:01-5:59)" : "Day (6:00-22:00)"));
            System.out.println("Rate: Rs 0.1 per 2 minutes");
            System.out.println("Total Charges: Rs " + localCall.calculateCharges());
            
        } else if (choice == 2) {
            System.out.print("Enter call duration (in minutes): ");
            int duration = sc.nextInt();
            
            System.out.println("\nSTD Destination Codes:");
            System.out.println("1. 011 (Delhi)");
            System.out.println("2. 022 (Mumbai)");
            System.out.println("3. 044 (Chennai)");
            System.out.print("Select destination code: ");
            int codeChoice = sc.nextInt();
            
            int destCode = 0;
            String destName = "";
            switch(codeChoice) {
                case 1:
                    destCode = 11;
                    destName = "011 (Delhi)";
                    break;
                case 2:
                    destCode = 22;
                    destName = "022 (Mumbai)";
                    break;
                case 3:
                    destCode = 44;
                    destName = "044 (Chennai)";
                    break;
                default:
                    System.out.println("Invalid code!");
                    sc.close();
                    return;
            }
            
            System.out.print("Enter call time (1 for Day Time 6:00-22:00, 2 for Night Time 22:01-5:59): ");
            int timeChoice = sc.nextInt();
            boolean isNight = (timeChoice == 2);
            
            STDCall stdCall = new STDCall(duration, destCode, isNight);
            
            System.out.println("\n--- STD Call Bill ---");
            System.out.println("Destination Code: " + destName);
            System.out.println("Duration: " + duration + " minutes");
            System.out.println("Time Period: " + (isNight ? "Night (22:01-5:59)" : "Day (6:00-22:00)"));
            
            // Display rate based on destination and time
            if (destCode == 11) {
                System.out.println("Rate: " + (isNight ? "Rs 0.5" : "Rs 1.0") + " per 2 minutes");
            } else if (destCode == 22) {
                System.out.println("Rate: " + (isNight ? "Rs 0.5" : "Rs 1.5") + " per 2 minutes");
            } else if (destCode == 44) {
                System.out.println("Rate: " + (isNight ? "Rs 0.4" : "Rs 0.75") + " per 2 minutes");
            }
            
            System.out.println("Total Charges: Rs " + stdCall.calculateCharges());
            
        } else {
            System.out.println("Invalid choice!");
        }
        
        sc.close();
    }
}







import java.util.Scanner;
import java.util.ArrayList;

// Base Staff class
class Staff {
    private int code;
    private String name;
    
    // Default constructor
    public Staff() {
        this.code = 0;
        this.name = "";
    }
    
    // Parameterized constructor
    public Staff(int code, String name) {
        this.code = code;
        this.name = name;
    }
    
    // Getters and Setters
    public int getCode() {
        return code;
    }
    
    public void setCode(int code) {
        this.code = code;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    // Method to display details
    public void displayDetails() {
        System.out.println("Code: " + code);
        System.out.println("Name: " + name);
    }
    
    // Method to input details
    public void inputDetails(Scanner sc) {
        System.out.print("Enter Code: ");
        this.code = sc.nextInt();
        sc.nextLine(); // Consume newline
        System.out.print("Enter Name: ");
        this.name = sc.nextLine();
    }
}

// Teacher class (inherits from Staff)
class Teacher extends Staff {
    private String subject;
    private String publication;
    
    // Default constructor
    public Teacher() {
        super();
        this.subject = "";
        this.publication = "";
    }
    
    // Parameterized constructor
    public Teacher(int code, String name, String subject, String publication) {
        super(code, name);
        this.subject = subject;
        this.publication = publication;
    }
    
    // Getters and Setters
    public String getSubject() {
        return subject;
    }
    
    public void setSubject(String subject) {
        this.subject = subject;
    }
    
    public String getPublication() {
        return publication;
    }
    
    public void setPublication(String publication) {
        this.publication = publication;
    }
    
    @Override
    public void displayDetails() {
        super.displayDetails();
        System.out.println("Subject: " + subject);
        System.out.println("Publication: " + publication);
    }
    
    public void inputDetails(Scanner sc) {
        super.inputDetails(sc);
        System.out.print("Enter Subject: ");
        this.subject = sc.nextLine();
        System.out.print("Enter Publication: ");
        this.publication = sc.nextLine();
    }
}

// Officer class (inherits from Staff)
class Officer extends Staff {
    private String grade;
    
    // Default constructor
    public Officer() {
        super();
        this.grade = "";
    }
    
    // Parameterized constructor
    public Officer(int code, String name, String grade) {
        super(code, name);
        this.grade = grade;
    }
    
    // Getters and Setters
    public String getGrade() {
        return grade;
    }
    
    public void setGrade(String grade) {
        this.grade = grade;
    }
    
    @Override
    public void displayDetails() {
        super.displayDetails();
        System.out.println("Grade: " + grade);
    }
    
    public void inputDetails(Scanner sc) {
        super.inputDetails(sc);
        System.out.print("Enter Grade: ");
        this.grade = sc.nextLine();
    }
}

// Typist class (inherits from Staff)
class Typist extends Staff {
    private int speed;
    
    // Default constructor
    public Typist() {
        super();
        this.speed = 0;
    }
    
    // Parameterized constructor
    public Typist(int code, String name, int speed) {
        super(code, name);
        this.speed = speed;
    }
    
    // Getters and Setters
    public int getSpeed() {
        return speed;
    }
    
    public void setSpeed(int speed) {
        this.speed = speed;
    }
    
    @Override
    public void displayDetails() {
        super.displayDetails();
        System.out.println("Typing Speed: " + speed + " wpm");
    }
    
    public void inputDetails(Scanner sc) {
        super.inputDetails(sc);
        System.out.print("Enter Typing Speed (wpm): ");
        this.speed = sc.nextInt();
        sc.nextLine(); // Consume newline
    }
}

// RegularTypist class (inherits from Typist)
class RegularTypist extends Typist {
    private double remuneration;
    
    // Default constructor
    public RegularTypist() {
        super();
        this.remuneration = 0;
    }
    
    // Parameterized constructor
    public RegularTypist(int code, String name, int speed, double remuneration) {
        super(code, name, speed);
        this.remuneration = remuneration;
    }
    
    // Getters and Setters
    public double getRemuneration() {
        return remuneration;
    }
    
    public void setRemuneration(double remuneration) {
        this.remuneration = remuneration;
    }
    
    @Override
    public void displayDetails() {
        super.displayDetails();
        System.out.println("Remuneration: Rs. " + remuneration);
    }
    
    public void inputDetails(Scanner sc) {
        super.inputDetails(sc);
        System.out.print("Enter Remuneration: ");
        this.remuneration = sc.nextDouble();
        sc.nextLine(); // Consume newline
    }
}

// CasualTypist class (inherits from Typist)
class CasualTypist extends Typist {
    private double dailyWages;
    
    // Default constructor
    public CasualTypist() {
        super();
        this.dailyWages = 0;
    }
    
    // Parameterized constructor
    public CasualTypist(int code, String name, int speed, double dailyWages) {
        super(code, name, speed);
        this.dailyWages = dailyWages;
    }
    
    // Getters and Setters
    public double getDailyWages() {
        return dailyWages;
    }
    
    public void setDailyWages(double dailyWages) {
        this.dailyWages = dailyWages;
    }
    
    @Override
    public void displayDetails() {
        super.displayDetails();
        System.out.println("Daily Wages: Rs. " + dailyWages);
    }
    
    public void inputDetails(Scanner sc) {
        super.inputDetails(sc);
        System.out.print("Enter Daily Wages: ");
        this.dailyWages = sc.nextDouble();
        sc.nextLine(); // Consume newline
    }
}

// Driver class
public class EmployeeDatabase {
    private static ArrayList<Staff> employees = new ArrayList<>();
    private static Scanner sc = new Scanner(System.in);
    
    public static void main(String[] args) {
        int choice;
        
        do {
            System.out.println("\n=== Employee Database System ===");
            System.out.println("1. Add Employee");
            System.out.println("2. Display All Employees");
            System.out.println("3. Search Employee by Code");
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            sc.nextLine(); // Consume newline
            
            switch(choice) {
                case 1:
                    addEmployee();
                    break;
                case 2:
                    displayAllEmployees();
                    break;
                case 3:
                    searchEmployee();
                    break;
                case 4:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Invalid choice!");
            }
        } while(choice != 4);
        
        sc.close();
    }
    
    private static void addEmployee() {
        System.out.println("\n--- Add Employee ---");
        System.out.println("1. Teacher");
        System.out.println("2. Officer");
        System.out.println("3. Regular Typist");
        System.out.println("4. Casual Typist");
        System.out.print("Select employee type: ");
        int type = sc.nextInt();
        sc.nextLine(); // Consume newline
        
        switch(type) {
            case 1:
                Teacher teacher = new Teacher();
                teacher.inputDetails(sc);
                employees.add(teacher);
                System.out.println("Teacher added successfully!");
                break;
            case 2:
                Officer officer = new Officer();
                officer.inputDetails(sc);
                employees.add(officer);
                System.out.println("Officer added successfully!");
                break;
            case 3:
                RegularTypist regularTypist = new RegularTypist();
                regularTypist.inputDetails(sc);
                employees.add(regularTypist);
                System.out.println("Regular Typist added successfully!");
                break;
            case 4:
                CasualTypist casualTypist = new CasualTypist();
                casualTypist.inputDetails(sc);
                employees.add(casualTypist);
                System.out.println("Casual Typist added successfully!");
                break;
            default:
                System.out.println("Invalid employee type!");
        }
    }
    
    private static void displayAllEmployees() {
        if (employees.isEmpty()) {
            System.out.println("\nNo employees in database!");
            return;
        }
        
        System.out.println("\n--- All Employees ---");
        for (int i = 0; i < employees.size(); i++) {
            System.out.println("\nEmployee " + (i + 1) + ":");
            employees.get(i).displayDetails();
            System.out.println("-------------------");
        }
    }
    
    private static void searchEmployee() {
        if (employees.isEmpty()) {
            System.out.println("\nNo employees in database!");
            return;
        }
        
        System.out.print("\nEnter employee code to search: ");
        int searchCode = sc.nextInt();
        boolean found = false;
        
        for (Staff employee : employees) {
            if (employee.getCode() == searchCode) {
                System.out.println("\nEmployee Found:");
                employee.displayDetails();
                found = true;
                break;
            }
        }
        
        if (!found) {
            System.out.println("Employee with code " + searchCode + " not found!");
        }
    }
}
