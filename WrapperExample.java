
public class WrapperExample {

    public static void main(String[] args) {
        Integer num = Integer.valueOf(10);
        int value = num.intValue();
        int num2 = value / 2;
        System.out.println("Wrapper Object: " + num);
        System.out.println("Primitive Value: " + value);
        System.out.println("Division Result: " + num2);
    }
}
