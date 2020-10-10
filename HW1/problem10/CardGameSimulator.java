import java.util.Scanner;

public class CardGameSimulator {
    private static final Player[] players = new Player[2];

    public static void simulateCardGame(String inputA, String inputB) {
        // DO NOT change the skeleton code.
        // You can add codes anywhere you want.
        Player playerA = new Player("A", inputA.split(" "));
        Player playerB = new Player("B", inputB.split(" "));
        Card temp = playerA.getLargestCard(' ');
        Card current_card = temp.copy();
        playerA.playCard(temp);
        while(true){
            current_card = playerB.seeCard(current_card);
            if(current_card.getNumber() == -1){
                printLoseMessage(playerB);
                break;
            }
            current_card = playerA.seeCard(current_card);
            if(current_card.getNumber() == -1){
                printLoseMessage(playerA);
                break;
            }
        }
    }

    private static void printLoseMessage(Player player) {
        System.out.printf("Player %s loses the game!\n", player);
    }
}


class Player {
    private String name;
    private Card[] deck;
    public Player(String name, String[] deck){
        this.name = name;
        int num_cards = deck.length;
        this.deck = new Card[num_cards];
        for(int i=0;i<num_cards;i++){
            this.deck[i] = new Card(deck[i]);
        }
    }
    public Card getLargestCard(char shape) {  //return shape as space if no such shape
        Card largestCard = new Card(-1,' ');
        if (shape == ' ') { //game start, pick largest card with any shape(prefer O)
            for (Card card : deck) {
                if (card.getNumber() > largestCard.getNumber()) {
                    largestCard = card;
                }
                else if (card.getNumber() == largestCard.getNumber() && card.getShape()=='O'){
                    largestCard = card;
                }
            }
        }
        else{
            for (Card card : deck) {
                if (card.getShape() == shape && card.getNumber() >= largestCard.getNumber()) {
                    largestCard = card;
                }
            }
        }
        return largestCard;
    }
    public Card seeCard(Card preCard) {
        int preCardNumber = preCard.getNumber();
        char preCardShape = preCard.getShape();
        Card temp;
        for (Card card:deck){
            if (card.getNumber() == preCardNumber) {
                temp = card.copy();
                playCard(card);
                return temp;
            }
        }
        Card largestCard = getLargestCard(preCardShape);
        if(largestCard.getNumber()==-1){
            return largestCard;
        }
        temp = largestCard.copy();
        playCard(largestCard);
        return temp;
    }

    public void playCard(Card card) {
        System.out.printf("Player %s: %s\n", name, card);
        card.useCard();
    }

    @Override
    public String toString() {
        return name;
    }
}


class Card {
    private int number;
    private char shape;
    public Card(String input){
        number = input.charAt(0)-'0';
        shape = input.charAt(1);
    }
    public Card(int number, char shape){
        this.number = number;
        this.shape = shape;
    }
    public void useCard(){
        number = -1;
        shape = ' ';
    }
    public int getNumber(){
        return number;
    }
    public char getShape(){
        return shape;
    }
    public Card copy(){
        return new Card(number, shape);
    }

    @Override
    public String toString() {
        return "" + number + shape;
    }
}
