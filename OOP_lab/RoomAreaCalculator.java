
public class RoomAreaCalculator {

    // Method 1: Area with int parameters
    public int calculateArea(int length, int width) {
        return length * width;
    }

    // Method 2: Area with double parameters
    public double calculateArea(double length, double width) {
        return length * width;
    }

    public static void main(String[] args) {
        RoomAreaCalculator areaCalc = new RoomAreaCalculator();

        // Using int version
        int area1 = areaCalc.calculateArea(10, 15);
        System.out.println("Area of the room (int version): " + area1 + " sq units");

        // Using double version
        double area2 = areaCalc.calculateArea(12.5, 18.3);
        System.out.println("Area of the room (double version): " + area2 + " sq units");
    }
}
