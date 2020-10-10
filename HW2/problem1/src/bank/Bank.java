package bank;

import bank.event.Event;
import security.*;
import security.key.*;

public class Bank {
    private int numAccounts = 0;
    final static int maxAccounts = 100;
    private BankAccount[] accounts = new BankAccount[maxAccounts];
    private String[] ids = new String[maxAccounts];

    public void createAccount(String id, String password) {
        createAccount(id, password, 0);
    }

    public void createAccount(String id, String password, int initBalance) {
        int accountId = numAccounts;
        accounts[accountId] = new BankAccount(id, password, initBalance);
        ids[accountId] = id;
        numAccounts+=1;
    }

    public BankAccount getAccount(String id, String password){
        BankAccount account = find(id);
        if(account == null || !account.authenticate(password)){
            return null;
        }

        return  account;
    }

    public boolean deposit(String id, String password, int amount) {
        //TODO: Problem 1.1
        BankAccount account = getAccount(id, password);
        if(account != null){
            account.deposit(amount);
            return true;
        }
        return false;
    }

    public boolean withdraw(String id, String password, int amount) {
        //TODO: Problem 1.1
        BankAccount account = getAccount(id, password);
        if(account != null){
            return account.withdraw(amount);
        }
        return false;
    }

    public boolean transfer(String sourceId, String password, String targetId, int amount) {
        //TODO: Problem 1.1
        BankAccount sourceAccount = getAccount(sourceId, password);
        BankAccount targetAccount = find(targetId);
        if(sourceAccount != null && targetAccount != null){
            if(sourceAccount.send(amount)) { targetAccount.receive(amount); }
        }
        return false;
    }

    public Event[] getEvents(String id, String password) {
        //TODO: Problem 1.1
        BankAccount account = getAccount(id, password);
        if(account != null){
            return account.getEvents();
        }
        return null;
    }

    public int getBalance(String id, String password) {
        //TODO: Problem 1.1
        BankAccount account = getAccount(id, password);
        if(account != null){
            return account.getBalance();
        }
        return -1;
    }

    private static String randomUniqueStringGen(){
        return Encryptor.randomUniqueStringGen();
    }
    private BankAccount find(String id) {
        for (int i = 0; i < numAccounts; i++) {
            if(ids[i].equals(id)){return accounts[i];};
        }
        return null;
    }
    final static int maxSessionKey = 100;
    int numSessionKey = 0;
    String[] sessionKeyArr = new String[maxSessionKey];
    BankAccount[] bankAccountmap = new BankAccount[maxSessionKey];
    String generateSessionKey(String id, String password){
        BankAccount account = find(id);
        if(account == null || !account.authenticate(password)){
            return null;
        }
        String sessionkey = randomUniqueStringGen();
        sessionKeyArr[numSessionKey] = sessionkey;
        bankAccountmap[numSessionKey] = account;
        numSessionKey += 1;
        return sessionkey;
    }
    BankAccount getAccount(String sessionkey){
        for(int i = 0 ;i < numSessionKey; i++){
            if(sessionKeyArr[i] != null && sessionKeyArr[i].equals(sessionkey)){
                return bankAccountmap[i];
            }
        }
        return null;
    }

    boolean deposit(String sessionkey, int amount) {
        //TODO: Problem 1.2
        BankAccount account = getAccount(sessionkey);
        if(account != null){
            account.deposit(amount);
        }
        return false;
    }

    boolean withdraw(String sessionkey, int amount) {
        //TODO: Problem 1.2
        BankAccount account = getAccount(sessionkey);
        if(account != null){
            return account.withdraw(amount);
        }
        return false;
    }

    boolean transfer(String sessionkey, String targetId, int amount) {
        //TODO: Problem 1.2
        BankAccount sourceAccount = getAccount(sessionkey);
        BankAccount targetAccount = find(targetId);
        if(sourceAccount != null && targetAccount != null){
            if(sourceAccount.send(amount)) { targetAccount.receive(amount); }
        }
        return false;
    }

    private int numApps = 0;
    final static int maxApps = 10000;
    private String[] AppIds = new String[maxApps];
    private BankSymmetricKey[] symmetricKeys = new BankSymmetricKey[maxApps];
    private int findAppId(String AppId) {
        for (int i = 0; i < numApps; i++) {
            if(AppIds[i].equals(AppId)){return i;};
        }
        return -1;
    }
    private BankSecretKey secretKey;
    public BankPublicKey getPublicKey(){
        BankKeyPair keypair = Encryptor.publicKeyGen();
        secretKey = keypair.deckey;
        return keypair.enckey;
    }

    public void fetchSymKey(Encrypted<BankSymmetricKey> encryptedKey, String AppId){
        //TODO: Problem 1.3
        if(encryptedKey == null) {return;}
        BankSymmetricKey symmetricKey = encryptedKey.decrypt(secretKey);
        if (symmetricKey != null){
            int appIndex = findAppId(AppId);
            if(appIndex == -1){
                AppIds[numApps] = AppId;
                symmetricKeys[numApps] = symmetricKey;
                numApps++;
            } else {
                symmetricKeys[appIndex] = symmetricKey;
            }
        }
    }

    public Encrypted<Boolean> processRequest(Encrypted<Message> messageEnc, String AppId){
        //TODO: Problem 1.3
        if(messageEnc == null) { return null; }
        int appIndex = findAppId(AppId);
        if (appIndex == -1){ return null; }

        BankSymmetricKey symmetricKey = symmetricKeys[appIndex];

        Message message = messageEnc.decrypt(symmetricKey);
        if (message == null){ return null; }

        int amount = message.getAmount();
        String id = message.getId();
        String password = message.getPassword();
        String requestType = message.getRequestType();
        if(requestType.equals("deposit")){
            return new Encrypted<Boolean>(deposit(id, password, amount), symmetricKey);
        }else if(requestType.equals("withdraw")){
            withdraw(id, password, amount);
        }
        return null;
    }
}