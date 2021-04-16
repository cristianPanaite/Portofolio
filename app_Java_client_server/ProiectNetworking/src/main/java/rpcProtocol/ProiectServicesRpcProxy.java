package rpcProtocol;

import dto.InscrieriDTO;
import javafx.application.Platform;
import model.DTOs.DTOPersoanaProbaId;
import model.DTOs.DTOProbaInscrieri;
import model.Inscriere;
import model.Person;
import model.Proba;
import model.User;
import services.IProiectObserver;
import services.IProiectServices;
import services.ProiectException;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.rmi.RemoteException;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ProiectServicesRpcProxy implements IProiectServices {
    private String host;
    private int port;

    private IProiectObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private BlockingQueue<Response> qresponses;
    private volatile boolean finished;
    public ProiectServicesRpcProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses=new LinkedBlockingQueue<Response>();
    }
    private void closeConnection() {
        finished=true;
        try {
            input.close();
            output.close();
            connection.close();
            client=null;
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void sendRequest(Request request)throws ProiectException {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new ProiectException("Error sending object "+e);
        }

    }

    private Response readResponse() throws ProiectException {
        Response response=null;
        try{

            response=qresponses.take();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }
    private void initializeConnection() throws ProiectException {
        try {
            connection=new Socket(host,port);
            output=new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input=new ObjectInputStream(connection.getInputStream());
            finished=false;
            startReader();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private void startReader(){
        Thread tw=new Thread(new ReaderThread());
        tw.start();
    }


    private void handleUpdate(Response response){
        try{
            client.inscriereUpdate();
        } catch (ProiectException | RemoteException e) {
            e.printStackTrace();
        }
    }

    private boolean isUpdate(Response response){
        return response.type() == ResponseType.UPDATE; // response.type()== ResponseType.FRIEND_LOGGED_OUT || response.type()== ResponseType.FRIEND_LOGGED_IN || response.type()== ResponseType.NEW_MESSAGE;
    }

    @Override
    public Iterable<User> getAllUsers() {
        return null;
    }

    @Override
    public Iterable<Person> getAllPerson() {
        return null;
    }

    @Override
    public Iterable<Proba> getAllProba() throws ProiectException {
        Request req=new Request.Builder().type(RequestType.GET_PROBE).data(null).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new ProiectException(err);
        }
        List<Proba> listDTO= (List<Proba>)response.data();
        return listDTO;
    }

    @Override
    public Iterable<Inscriere> getAllInscriere() {
        return null;
    }

    @Override
    public User getUserByCreditentials(String usernameString, String passwordString, IProiectObserver client) throws ProiectException {
        initializeConnection();
        User user = new User(usernameString, passwordString);
        Request req=new Request.Builder().type(RequestType.LOGIN).data(user).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()== ResponseType.OK){
            this.client=client;
            User userFind = (User) response.data();
            return userFind;
        }
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            closeConnection();
            throw new ProiectException(err);
        }
        throw new ProiectException();
    }

    @Override
    public List<DTOProbaInscrieri> getAllProbaInscrieri() throws ProiectException{

        Request req=new Request.Builder().type(RequestType.GET_PROBE_INSCRIERI).data(null).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new ProiectException(err);
        }
        List<DTOProbaInscrieri> listDTO= (List<DTOProbaInscrieri>)response.data();
        return listDTO;
    }

    @Override
    public void handleInscriere(String nume, Long varsta, List<Proba> probe, User u) throws ProiectException{
        InscrieriDTO dtoI= new InscrieriDTO(nume, varsta, probe , u);
        Request req=new Request.Builder().type(RequestType.INSCRIERE).data(dtoI).build();
        sendRequest(req);
        Response response=readResponse();
        System.out.println("Response: " + response);
    }

    @Override
    public void logOut(User u, IProiectObserver client) throws ProiectException {
        Request req=new Request.Builder().type(RequestType.LOGOUT).data(u).build();
        sendRequest(req);
        Response response=readResponse();
        closeConnection();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new ProiectException(err);
        }
    }

    @Override
    public List<DTOPersoanaProbaId> getAllPersonProbaId(Proba p) throws ProiectException {
        Request req=new Request.Builder().type(RequestType.GET_PARTICIPANTI_PROBA).data(p).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new ProiectException(err);
        }
        List<DTOPersoanaProbaId> listDTO= (List<DTOPersoanaProbaId>)response.data();
        return listDTO;
    }

    private class ReaderThread implements Runnable{
        public void run() {
            while(!finished){
                try {
                    Object response=input.readObject();
                    System.out.println("response received "+response);
                    if (isUpdate((Response)response)){
                        handleUpdate((Response)response);
                    }else{

                        try {
                            qresponses.put((Response)response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException e) {
                    System.out.println("Reading error "+e);
                } catch (ClassNotFoundException e) {
                    System.out.println("Reading error "+e);
                }
            }
        }
    }



}
