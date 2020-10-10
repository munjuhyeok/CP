public class IncreasingString {
    public static void printLongestIncreasingSubstringLength(String inputString) {
        // DO NOT change the skeleton code.
        // You can add codes anywhere you want.
        int idx = 0;
        int length = 0;
        int temp;
        while(true) {
            temp = length_of_increasing_substring_from_index(inputString, idx);
            idx += temp;
            if(length<temp){
                length = temp;
            }
            if(idx>=inputString.length()){
                break;
            }
        }
        System.out.println(length);
    }
    static int length_of_increasing_substring_from_index(String str, int idx){
        int count = 1;
        while(true){
            if(idx>=str.length()-1){
                break;
            }
            if(str.charAt(idx)<str.charAt(idx+1)){
                count++;
            }
            else{
                break;
            }
            idx++;
        }
        return count;
    }
}
