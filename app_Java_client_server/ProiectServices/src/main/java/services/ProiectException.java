package services;

public class ProiectException extends Exception{
    public ProiectException() {
    }

    public ProiectException(String message) {
        super(message);
    }

    public ProiectException(String message, Throwable cause) {
        super(message, cause);
    }
}
