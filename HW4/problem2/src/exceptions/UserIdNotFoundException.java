package exceptions;

public class UserIdNotFoundException extends Exception{
    public UserIdNotFoundException(){
    }
    public UserIdNotFoundException(String msg) {super(msg);}
}
