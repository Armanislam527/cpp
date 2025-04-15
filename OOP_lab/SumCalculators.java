
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class SumCalculators extends JFrame {

    private JLabel num1label, num2label;
    private JTextField resultField;

    public SumCalculators() {
        setTitle("Sum Calculator");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));
        num1label = new JLabel("Number 1:");
        JTextField num1Field = new JTextField();
        num2label = new JLabel("Number 2:");
        JTextField num2Field = new JTextField();
        JButton addButton = new JButton("Calculate Sum");
        resultField = new JTextField("Result:");
        resultField.setEditable(false);
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    double num1 = Double.parseDouble(num1Field.getText().trim());
                    double num2 = Double.parseDouble(num2Field.getText().trim());
                    double sum = num1 + num2;
                    resultField.setText("Sum: " + sum);

                } catch (NumberFormatException ex) {
                    resultField.setText("Invalid input");
                }
            }
        });
        add(num1label);
        add(num1Field);
        add(num2label);
        add(num2Field);
        add(addButton);
        add(resultField);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public static void main(String[] args) {
        new SumCalculators();
    }
}
