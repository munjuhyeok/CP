public class PrimeNumbers {
    public static void printPrimeNumbers(int n) {
        // DO NOT change the skeleton code.
        // You can add codes anywhere you want.
        int count = 1;
        System.out.printf("2");
        int cur_num = 3;
        while(true){
            if(count == n) return;
            if(is_prime(cur_num)){
                System.out.printf(" "+cur_num);
                count++;
            }
            cur_num++;
        }
    }
    static boolean is_prime(int n){
        int count = 0;
        for (int i=2;i<n;i++){
            if(n % i == 0){
                count++;
            }
        }
        if(count == 0) return true;
        return false;
    }
}
