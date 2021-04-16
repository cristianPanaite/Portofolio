package services;

import model.Person;
import model.Proba;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface IProiectObserver extends Remote {
    void inscriereUpdate() throws ProiectException, RemoteException;
}
