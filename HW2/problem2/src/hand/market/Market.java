package hand.market;

import hand.agent.Buyer;
import hand.agent.Seller;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

class Pair<K,V> {
    public K key;
    public V value;
    Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }
}

public class Market {
    public ArrayList<Buyer> buyers;
    public ArrayList<Seller> sellers;

    public Market(int nb, ArrayList<Double> fb, int ns, ArrayList<Double> fs) {
        buyers = createBuyers(nb, fb);
        sellers = createSellers(ns, fs);
    }

    private double pow(double a, int b){
        double result = 1;
        for (int i = 0; i < b; i++){
            result *= a;
        }
        return result;
    }
    
    private ArrayList<Buyer> createBuyers(int n, ArrayList<Double> f) {
        // TODO sub-problem 3
        if (f == null) {return null;}
        int fSize = f.size();
        ArrayList<Buyer> buyers = new ArrayList<>();
        for (int i = 1; i <= n; i++){
            double price = 0;
            double x = (double)i/n;
            for (int j = 0; j < fSize; j++){
                price += f.get(fSize - j - 1) * pow(x, j);
            }
            buyers.add(new Buyer(price));
        }
        return buyers;
    }

    private ArrayList<Seller> createSellers(int n, ArrayList<Double> f) {
        // TODO sub-problem 3
        if (f == null) {return null;}
        int fSize = f.size();
        ArrayList<Seller> sellers = new ArrayList<>();
        for (int i = 1; i <= n; i++){
            double price = 0;
            double x = (double)i/n;
            for (int j = 0; j < fSize; j++){
                price += f.get(fSize - j - 1) * pow(x, j);
            }
            sellers.add(new Seller(price));
        }
        return sellers;
    }

    private ArrayList<Pair<Seller, Buyer>> matchedPairs(int day, int round) {
        ArrayList<Seller> shuffledSellers = new ArrayList<>(sellers);
        ArrayList<Buyer> shuffledBuyers = new ArrayList<>(buyers);
        Collections.shuffle(shuffledSellers, new Random(71 * day + 43 * round + 7));
        Collections.shuffle(shuffledBuyers, new Random(67 * day + 29 * round + 11));
        ArrayList<Pair<Seller, Buyer>> pairs = new ArrayList<>();
        for (int i = 0; i < shuffledBuyers.size(); i++) {
            if (i < shuffledSellers.size()) {
                pairs.add(new Pair<>(shuffledSellers.get(i), shuffledBuyers.get(i)));
            }
        }
        return pairs;
    }

    public double simulate() {
        // TODO sub-problem 2 and 3
        for (int day = 1; day <= 1000; day++) { // do not change this line
            for (int round = 1; round <= 10; round++) { // do not change this line
                ArrayList<Pair<Seller, Buyer>> pairs = matchedPairs(day, round); // do not change this line
                for (Pair<Seller, Buyer> pair : pairs){
                    Seller seller = pair.key;
                    Buyer buyer = pair.value;
                    if (buyer.willTransact(seller.getExpectedPrice()) && seller.willTransact(buyer.getExpectedPrice())){
                        buyer.makeTransaction();
                        seller.makeTransaction();
                    }
                }
            }
            for (Buyer buyer : buyers){
                buyer.reflect();
            }
            for (Seller seller : sellers){
                seller.reflect();
            }
        }
        double priceSum = 0;
        for (Buyer buyer : buyers){
            priceSum += buyer.getExpectedPrice();
        }
        for (Seller seller : sellers){
            priceSum += seller.getExpectedPrice();
        }
        return priceSum / (buyers.size() + sellers.size());
    }
}
