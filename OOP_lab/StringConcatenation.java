
import java.util.Scanner;

public class StringConcatenation {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Get first string from user
        System.out.print("Enter the first string: ");
        String str1 = scanner.nextLine();

        // Get second string from user
        System.out.print("Enter the second string: ");
        String str2 = scanner.nextLine();
        // Concatenate the strings
        String result = str1 + str2;

        // Display the result
        System.out.println("Concatenated string: " + result);

        scanner.close();
    }
}
