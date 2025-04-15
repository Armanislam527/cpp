
import java.util.Scanner;

public class SumCalculator {

    // Method to calculate sum
    public int calculateSum(int a, int b, int c) {
        return a + b + c;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        SumCalculator calculator = new SumCalculator();

        // Taking user input
        System.out.print("Enter first number: ");
        int num1 = scanner.nextInt();

        System.out.print("Enter second number: ");
        int num2 = scanner.nextInt();

        System.out.print("Enter third number: ");
        int num3 = scanner.nextInt();

        // Calculating sum using method
        int sum = calculator.calculateSum(num1, num2, num3);

        // Displaying result
        System.out.println("The sum of the three numbers is: " + sum);

        scanner.close();
    }
}
