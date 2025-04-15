public class Student {
    // Instance variables
    String name;
    int roll;
    double cgpa;

    // Parameterized constructor
    public Student(String name, int roll, double cgpa) {
        this.name = name;
        this.roll = roll;
        this.cgpa = cgpa;
    }

    // Method to display student information
    public void displayInfo() {
        System.out.println("Student Name: " + name);
        System.out.println("Roll Number: " + roll);
        System.out.println("CGPA: " + cgpa);
    }

    public static void main(String[] args) {
        // Creating object using parameterized constructor
        Student s1 = new Student("Arman", 230623, 3.87);
        s1.displayInfo();
    }
}
