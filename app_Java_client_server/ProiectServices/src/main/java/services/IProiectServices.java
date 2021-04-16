package services;

import javafx.collections.ObservableList;
import model.DTOs.DTOPersoanaProbaId;
import model.DTOs.DTOProbaInscrieri;
import model.Inscriere;
import model.Person;
import model.Proba;
import model.User;

import java.rmi.RemoteException;
import java.util.List;

public interface IProiectServices {
    public Iterable<User> getAllUsers();
    public Iterable<Person> getAllPerson();
    public Iterable<Proba> getAllProba() throws ProiectException;
    public Iterable<Inscriere> getAllInscriere();

    public User getUserByCreditentials (String usernameString, String passwordString, IProiectObserver client) throws ProiectException;
    public List<DTOProbaInscrieri> getAllProbaInscrieri() throws ProiectException;
    public List<DTOPersoanaProbaId> getAllPersonProbaId(Proba p) throws ProiectException;
    public void handleInscriere(String nume, Long varsta, List<Proba> probe, User u) throws ProiectException, RemoteException;

    public void logOut(User u, IProiectObserver client) throws ProiectException;
}
