
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class CelsiusToFahrenheitConverter extends JFrame {

    private JTextField getcel;
    private JLabel temp;

    public CelsiusToFahrenheitConverter() {
        setTitle("Temperature Conveerter");
        setSize(350, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(3, 2));
        JLabel celciusLabel = new JLabel("Celcius:");
        getcel = new JTextField();
        temp = new JLabel(" ");
        JButton convertButton = new JButton("Convert");
        convertButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    double celcius = Double.parseDouble(getcel.getText().trim());
                    double fahrenheit = (celcius * 9 / 5) + 32;
                    temp.setText("Fahrenheit: " + fahrenheit);
                } catch (NumberFormatException ex) {
                    temp.setText("Invalid input");
                }
            }
        });
        add(celciusLabel);
        add(getcel);
        add(convertButton);
        add(temp);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public static void main(String[] args) {
        new CelsiusToFahrenheitConverter();
    }
}
