// Base class

class Room {

    double length;
    double width;

    // Constructor to initialize length and width
    Room(double length, double width) {
        this.length = length;
        this.width = width;
    }

    // Method to calculate area
    double calculateArea() {
        return length * width;
    }
}

// Derived class
class RoomWithHeight extends Room {

    double height;

    // Constructor to initialize length, width, and height
    RoomWithHeight(double length, double width, double height) {
        super(length, width); // calling the constructor of the superclass (Room)
        this.height = height;
    }

    // Method to calculate volume
    double calculateVolume() {
        return length * width * height;
    }
}

// Main class
public class AreaVolumeCalculator {

    public static void main(String[] args) {
        // Creating an object of the derived class
        RoomWithHeight room = new RoomWithHeight(10.0, 15.0, 8.0);

        // Calculating and displaying area and volume
        double area = room.calculateArea();
        double volume = room.calculateVolume();

        System.out.println("Area of the room: " + area + " sq units");
        System.out.println("Volume of the room: " + volume + " cubic units");
    }
}
