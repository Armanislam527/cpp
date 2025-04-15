// Base class

class Animal {

    void makeSound() {
        System.out.println("The animal makes a sound");
    }
}

// Derived class
class Dog extends Animal {

    @Override
    void makeSound() {
        System.out.println("The dog barks");
    }
}

// Main class
public class MethodOverridingExample {

    public static void main(String[] args) {
        Animal myAnimal = new Animal();  // Base class object
        Animal myDog = new Dog();        // Polymorphism: Base reference, Derived object

        myAnimal.makeSound();  // Output: The animal makes a sound
        myDog.makeSound();     // Output: The dog barks (method overridden)
    }
}
