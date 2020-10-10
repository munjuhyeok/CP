public class FibonacciNumbers {
    public static void printFibonacciNumbers(int n) {
        // DO NOT change the skeleton code.
        // You can add codes anywhere you want.
        if(n==1){
            System.out.printf("0");
            return;
        }
        if(n==2){
            System.out.printf("0 1");
            return;
        }
        int[] Fib = new int[n];
        Fib[0] = 0;
        Fib[1] = 1;
        System.out.printf("0 1");
        for(int i=2;i<n;i++) {
            Fib[i] = Fib[i - 1] + Fib[i - 2];
            System.out.printf(" "+Fib[i]);
        }
    }
}
