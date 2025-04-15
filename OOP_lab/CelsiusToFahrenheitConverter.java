
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class CelsiusToFahrenheitConverter extends JFrame {

    private JTextField celsiusField;
    private JLabel resultLabel;

    public CelsiusToFahrenheitConverter() {
        setTitle("Celsius to Fahrenheit Converter");
        setSize(350, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(3, 2, 10, 10));
        JLabel celsiusLabel = new JLabel("Enter Celsius:");
        celsiusField = new JTextField();
        JButton convertButton = new JButton("Convert");
        resultLabel = new JLabel("Fahrenheit: ");
        convertButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                convertTemperature();
            }
        });
        add(celsiusLabel);
        add(celsiusField);
        add(convertButton);
        add(resultLabel);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private void convertTemperature() {
        try {
double celsius = Double.parseDouble(celsiusField.getText());
 double fahrenheit = (celsius * 9 / 5) + 32;
 resultLabel.setText("Fahrenheit: " + fahrenheit);
 } catch (NumberFormatException e) {
 resultLabel.setText("Invalid Input!");
 }
 }
 public static void main(String[] args) {
 new CelsiusToFahrenheitConverter();
 }
}