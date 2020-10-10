package bank;

public class Session {

    private String sessionKey;
    private Bank bank;
    private boolean valid;
    Session(String sessionKey,Bank bank){
        this.sessionKey = sessionKey;
        this.bank = bank;
        valid = true;
    }

    public boolean deposit(int amount) {
        //TODO: Problem 1.2
        if(!valid) {return false;}
        return bank.deposit(sessionKey,amount);
    }

    public boolean withdraw(int amount) {
        //TODO: Problem 1.2
        if(!valid) {return false;}
        return bank.withdraw(sessionKey, amount);
    }

    public boolean transfer(String targetId, int amount) {
        //TODO: Problem 1.2
        if(!valid) {return false;}
        return bank.transfer(sessionKey, targetId, amount);
    }

    public void setValid(boolean valid) {
        this.valid = valid;
    }
}
