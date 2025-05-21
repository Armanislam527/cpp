
public class DebugExample {

    public static void main(String[] args) {
        try {
            String str = null;
            System.out.println(str.length());
        } catch (ArithmeticException e) {
            System.err.println("Debugging Info: A null value was accessed.");
            e.printStackTrace();
        } finally {
            System.out.println("Execution continued without crashing.");
        }
    }
}
