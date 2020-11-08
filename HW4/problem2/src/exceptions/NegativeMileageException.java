package exceptions;

public class NegativeMileageException extends Exception{
    public NegativeMileageException(){
    }
    public NegativeMileageException(String msg){super(msg);}
}
