public class NumberCounter {
    public static void countNumbers(String str0, String str1, String str2) {
        // DO NOT change the skeleton code.
        // You can add codes anywhere you want.
        int str = Integer.parseInt(str0)*Integer.parseInt(str1)*Integer.parseInt(str2);
        int count;
        for (char i = '0'; i <= '9'; i++) {
            count = 0;
            for (char j : Integer.toString(str).toCharArray()) {
                if (i == j) {
                    count++;
                }
            }
            if (count == 0) {
                continue;
            }
            printNumberCount(i-'0',count);
        }
    }

    private static void printNumberCount(int number, int count) {
        System.out.printf("%d: %d times\n", number, count);
    }
}
