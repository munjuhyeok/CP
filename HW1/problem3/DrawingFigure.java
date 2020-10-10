public class DrawingFigure {
    public static void drawFigure(int n) {
        // DO NOT change the skeleton code.
        for (int i=0;i<n;i++) {
            System.out.println("/".repeat(4*(5-i))+"*".repeat(8*i)+"\\".repeat(4*(5-i)));
        }
        // You can add codes anywhere you want.
    }
}
