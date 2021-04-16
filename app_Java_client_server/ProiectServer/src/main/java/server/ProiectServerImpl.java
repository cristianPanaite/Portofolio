package server;

import javafx.collections.ObservableList;
import model.DTOs.DTOPersoanaProbaId;
import model.DTOs.DTOProbaInscrieri;
import model.Inscriere;
import model.Person;
import model.Proba;
import model.User;
import repository.InscriereRepository;
import repository.PersonRepository;
import repository.ProbaRepository;
import repository.UserRepository;
import services.IProiectObserver;
import services.IProiectServices;
import services.ProiectException;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ProiectServerImpl implements IProiectServices {
    private UserRepository userRepository;
    private PersonRepository personRepository;
    private ProbaRepository probaRepository;
    private InscriereRepository inscriereRepository;
    private Map<Long, IProiectObserver> loggedClients;


    public ProiectServerImpl(UserRepository userRepository, PersonRepository personRepository, ProbaRepository probaRepository, InscriereRepository inscriereRepository) {
        this.userRepository = userRepository;
        this.personRepository = personRepository;
        this.probaRepository = probaRepository;
        this.inscriereRepository = inscriereRepository;
        loggedClients = new ConcurrentHashMap<>();
    }

    public synchronized Iterable<User> getAllUsers(){
        return userRepository.findAll();
    }
    public synchronized Iterable<Person> getAllPerson(){
        return personRepository.findAll();
    }
    public synchronized Iterable<Proba> getAllProba(){
        return probaRepository.findAll();
    }
    public synchronized Iterable<Inscriere> getAllInscriere(){
        return inscriereRepository.findAll();
    }

    public synchronized User getUserByCreditentials(String usernameString, String passwordString, IProiectObserver client) throws ProiectException {
        User u = userRepository.findByUsernameAndPassword(usernameString, passwordString);
        try{
            if (loggedClients.get(u.getId()) != null)
                throw new ProiectException("User already logged in.");
            loggedClients.put(u.getId(), client);
            return u;
        }catch(Exception e){
            throw new ProiectException(e.getMessage());
        }

    }

    public synchronized List<DTOProbaInscrieri> getAllProbaInscrieri() throws ProiectException{
        Iterable<Proba> probe = probaRepository.findAll();
        List<DTOProbaInscrieri> dtoOut = new ArrayList<>();
        for(Proba p : probe){
            Integer noOfInscrieriForProba = probaRepository.countInscrieri(p);
            dtoOut.add(new DTOProbaInscrieri(p, noOfInscrieriForProba));
        }
        return dtoOut;
    }

    public synchronized List<DTOPersoanaProbaId> getAllPersonProbaId(Proba p) {
        List<DTOPersoanaProbaId> out = new ArrayList<>();
        List<Person> personList = probaRepository.getAllParticipantsForAProba(p.getId());
        for(Person person : personList){
            out.add(new DTOPersoanaProbaId(person, p.getId()));
        }

        return out;
    }

    public synchronized void handleInscriere(String nume, Long varsta, List<Proba> probe, User u) throws ProiectException, RemoteException {
        Person p = personRepository.getByNumeAndVarsta(nume, varsta);
        if(p == null){
            p = new Person(nume, varsta);
            personRepository.add(p);
            Inscriere inscriere = new Inscriere(personRepository.getByNumeAndVarsta(nume, varsta), probe);
            inscriereRepository.add(inscriere);
        }
        else{
            Inscriere inscriere = inscriereRepository.findByPersonId(p.getId());
            if(inscriere == null){
                inscriere = new Inscriere(p, probe);
                inscriereRepository.add(inscriere);
            }
            else{
                Inscriere newInscriere = new Inscriere(p, probe);
                inscriereRepository.update(newInscriere, inscriere.getId());
            }
        }
        this.notifyClients(u);

    }
    private final int defaultThreadsNo = 5;
    private void notifyClients(User u) throws ProiectException, RemoteException {
        ExecutorService executor = Executors.newFixedThreadPool(defaultThreadsNo);
        loggedClients.get(u.getId()).inscriereUpdate();
        for (Long userId : loggedClients.keySet()){
            IProiectObserver client = loggedClients.get(userId);
            if(client != null && !userId.equals(u.getId())){
                executor.execute(() -> {
                    try {
                        System.out.println("Notifying [" + userId + "] ");
                        client.inscriereUpdate();
                    } catch (ProiectException | RemoteException e) {
                        System.err.println("Error notifying friend " + e);
                    }
                });
            }
        }
        executor.shutdown();

    }

    @Override
    public void logOut(User u, IProiectObserver client) {
        if (loggedClients.get(u.getId()) != null) {
            loggedClients.remove(u.getId());
        }
    }

}
