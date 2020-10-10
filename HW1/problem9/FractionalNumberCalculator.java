public class FractionalNumberCalculator {
    public static void printCalculationResult(String equation) {
        // DO NOT change the skeleton code.
        // You can add codes anywhere you want.
        String[] eqn = equation.split(" ");
        int[] numerators = {1,1};
        int[] denominators = {1,1};
        String[] term1 = eqn[0].split("/");
        String operator = eqn[1];
        String[] term2 = eqn[2].split("/");
        numerators[0] = Integer.parseInt(term1[0]);
        numerators[1] = Integer.parseInt(term2[0]);

        if(term1.length==2){
            denominators[0] = Integer.parseInt(term1[1]);
        }
        if(term2.length==2){
            denominators[1] = Integer.parseInt(term2[1]);
        }
        FractionalNumber a = new FractionalNumber(numerators[0],denominators[0]);
        FractionalNumber b = new FractionalNumber(numerators[1],denominators[1]);
        FractionalNumber result = a.calc(operator,b);
        result.print_value();
    }
}

class FractionalNumber {
    private int numerator;
    private int denominator;
    FractionalNumber(int numerator, int denominator){
        this.numerator = numerator/gcd(numerator,denominator);
        this.denominator = denominator/gcd(numerator,denominator);
    }
    static int gcd(int a,int b){
        if(a%b==0){
            return Math.abs(b);
        }
        return gcd(b,a%b);
    }
    public FractionalNumber calc(String operator, FractionalNumber number){
        if(operator.equals("+")){
            return new FractionalNumber(numerator*number.denominator+denominator*number.numerator,denominator*number.denominator);
        }
        else if(operator.equals("-")){
            return new FractionalNumber(numerator*number.denominator-denominator*number.numerator,denominator*number.denominator);
        }
        else if(operator.equals("*")){
            return new FractionalNumber(numerator*number.numerator,denominator*number.denominator);
        }
        else {
            return new FractionalNumber(numerator*number.denominator, denominator*number.numerator);
        }
    }
    public void print_value(){
        if(denominator==1){
            System.out.println(numerator);
        }
        else {
            System.out.println(numerator+"/"+denominator);
        }
    }
}