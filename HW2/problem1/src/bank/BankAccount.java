package bank;

import bank.event.*;

class BankAccount {
    private Event[] events = new Event[maxEvents];
    final static int maxEvents = 100;
    private String id;
    private String password;
    private int balance;
    private int index; //index for events

    BankAccount(String id, String password, int balance) {
        //TODO: Problem 1.1
        this.id = id;
        this.password = password;
        this.balance = balance;
        index = 0;
    }

    boolean authenticate(String password) {
        //TODO: Problem 1.1
        return this.password.equals(password);
    }

    void deposit(int amount) {
        //TODO: Problem 1.1
        balance += amount;
        events[index++] = new DepositEvent();
    }

    boolean withdraw(int amount) {
        //TODO: Problem 1.1
        if(balance >= amount){
            balance -= amount;
            events[index++] = new WithdrawEvent();
            return true;
        }
        return false;
    }

    void receive(int amount) {
        //TODO: Problem 1.1
        balance += amount;
        events[index++] = new ReceiveEvent();
    }

    boolean send(int amount) {
        //TODO: Problem 1.1
        if(balance >= amount){
            balance -= amount;
            events[index++] = new SendEvent();
            return true;
        }
        return false;
    }

    public String getId() {
        return id;
    }

    public String getPassword() {
        return password;
    }

    public int getBalance() {
        return balance;
    }

    public Event[] getEvents() {
        Event[] recordedEvents = new Event[index];
        for (int i = 0; i < index; i++){
            recordedEvents[i] = events[i];
        }
        return recordedEvents;
    }
}
