
import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class LargestNumberApplet extends Applet implements ActionListener {

    TextField num1, num2, num3;
    Button findLargest;
    Label result;

    public void init() {
        setLayout(new FlowLayout());
        add(new Label("Enter 3 numbers: "));
        num1 = new TextField(5);
        num2 = new TextField(5);
        num3 = new TextField(5);
        add(num1);
        add(num2);
        add(num3);
        findLargest = new Button("Find Largest");
        add(findLargest);
        result = new Label("Largest Number: ");
        add(result);
        findLargest.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
        try {
            int n1 = Integer.parseInt(num1.getText());
            int n2 = Integer.parseInt(num2.getText());
            int n3 = Integer.parseInt(num3.getText());
            int largest = Math.max(n1, Math.max(n2, n3));
            result.setText("Largest Number: " + largest);
        } catch (NumberFormatException ex) {
            result.setText("Invalid input! Enter numeric values.");
        }
    }
}
