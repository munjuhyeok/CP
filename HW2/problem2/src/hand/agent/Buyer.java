package hand.agent;

public class Buyer extends Agent {

    public Buyer(double maximumPrice) {
        super(maximumPrice);
    }

    @Override
    public boolean willTransact(double price) {
        // TODO sub-problem 1
        if (!hadTransaction && price <= expectedPrice){ return true; }
        return false;
    }

    @Override
    public void reflect() {
        // TODO sub-problem 1
        if(hadTransaction){
            expectedPrice = expectedPrice - adjustment;
        }else{
            expectedPrice = Math.min(expectedPrice + adjustment, priceLimit);
        }
        hadTransaction = false;
    }
}
