
interface Drawable {

    void draw();
}

class Circle implements Drawable {

    public void draw() {
        System.out.println("Drawing a circle");
    }

    public static void main(String[] args) {
        Drawable d = new Circle();
        d.draw();
    }
}
