public class CharacterCounter {
    public static void countCharacter(String str) {
        // DO NOT change the skeleton code.
        // You can add codes anywhere you want.
        int count;
        for(char i='a';i<='z';i++){
            count=0;
            for(char j:str.toCharArray()){
                if(i==j){
                    count++;
                };
            }
            if(count==0){
                continue;
            }
            printCount(i, count);
        }
    }

    private static void printCount(char character, int count) {
        System.out.printf("%c: %d times\n", character, count);
    }
}