// Define an interface

interface Shape {

    void draw();         // abstract method

    double getArea();    // abstract method
}

// Class implementing the interface
class Circle implements Shape {

    double radius;

    // Constructor
    Circle(double radius) {
        this.radius = radius;
    }

    // Implementing draw method
    public void draw() {
        System.out.println("Drawing a circle");
    }

    // Implementing getArea method
    public double getArea() {
        return Math.PI * radius * radius;
    }
}

// Another class implementing the same interface
class Rectangle implements Shape {

    double length, width;

    // Constructor
    Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }

    // Implementing draw method
    public void draw() {
        System.out.println("Drawing a rectangle");
    }

    // Implementing getArea method
    public double getArea() {
        return length * width;
    }
}

// Main class
public class InterfaceExample {

    public static void main(String[] args) {
        Shape circle = new Circle(5.0);
        circle.draw();
        System.out.println("Area of circle: " + circle.getArea());

        Shape rectangle = new Rectangle(4.0, 6.0);
        rectangle.draw();
        System.out.println("Area of rectangle: " + rectangle.getArea());
    }
}
