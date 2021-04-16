package rpcProtocol;

import dto.InscrieriDTO;
import javafx.collections.ObservableList;
import model.DTOs.DTOPersoanaProbaId;
import model.DTOs.DTOProbaInscrieri;
import model.Person;
import model.Proba;
import model.User;
import services.IProiectObserver;
import services.IProiectServices;
import services.ProiectException;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.rmi.RemoteException;
import java.util.List;

public class ProiectRpcWorker implements Runnable, IProiectObserver {

    private IProiectServices server;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;
    public ProiectRpcWorker(IProiectServices server, Socket connection) {
        this.server = server;
        this.connection = connection;
        try{
            output=new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input=new ObjectInputStream(connection.getInputStream());
            connected=true;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // private static Response okResponse=new Response.Builder().type(ResponseType.OK).build();
    //  private static Response errorResponse=new Response.Builder().type(ResponseType.ERROR).build();
    private static Response okResponse=new Response.Builder().type(ResponseType.OK).build();
    private Response handleRequest(Request request){
        Response response=null;
        String handlerName="handle"+(request).type();
        System.out.println("HandlerName "+handlerName);
        try {
            Method method=this.getClass().getDeclaredMethod(handlerName, Request.class);
            response=(Response)method.invoke(this,request);
            System.out.println("Method "+handlerName+ " invoked");
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }

        return response;
    }

    private Response handleLOGIN(Request request){
        System.out.println("Login request ..."+request.type());
        User user=(User) request.data();
        try {
            User userRepo = server.getUserByCreditentials(user.getUsername(), user.getPassword(), this);
            return new Response.Builder().type(ResponseType.OK).data(userRepo).build();
        } catch (ProiectException e) {
            connected=false;
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleLOGOUT(Request request){
        System.out.println("Logout request...");
        User user=(User)request.data();
        try {
            server.logOut(user, this);
            connected=false;
            return okResponse;

        } catch (ProiectException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleGET_PROBE_INSCRIERI(Request request){
        System.out.println("Get request...");
        try{

            List<DTOProbaInscrieri> probeList = server.getAllProbaInscrieri();
            //TripDTO[] tripsDto = DTOUtils.getDTO(trips);
            return new Response.Builder().type(ResponseType.GET_PROBE_NUMARPART).data(probeList).build();

        }catch (ProiectException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }
    private Response handleGET_PROBE(Request request){
        System.out.println("Get request...");
        try{
            Iterable<Proba> probeList = server.getAllProba();
            //TripDTO[] tripsDto = DTOUtils.getDTO(trips);
            return new Response.Builder().type(ResponseType.GET_PROBE).data(probeList).build();

        }catch (ProiectException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }
    private Response handleGET_PARTICIPANTI_PROBA(Request request){
        System.out.println("Get request...");
        try{
            Proba p = (Proba) request.data();
            List<DTOPersoanaProbaId> probeList = server.getAllPersonProbaId(p);

            return new Response.Builder().type(ResponseType.GET_PARTICIPANTI_PROBA).data(probeList).build();

        }catch (ProiectException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private void sendResponse(Response response) throws IOException{
        System.out.println("sending response "+response);
        synchronized (output){
            output.writeObject(response);
            output.flush();
        }
}

    private Response handleINSCRIERE(Request request) throws ProiectException{
        System.out.println("Get request...");
        try{
            InscrieriDTO inscrieriDTO=(InscrieriDTO)request.data();
            List<Proba> proba = inscrieriDTO.getProbeList();
            String nume= inscrieriDTO.getNume();
            Long varsta = inscrieriDTO.getVarsta();
            User username = inscrieriDTO.getUsername();
            server.handleInscriere(nume, varsta,proba,username);
            return new Response.Builder().type(ResponseType.INSCRIERE).data(inscrieriDTO).build();

        }catch (ProiectException | RemoteException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }
    @Override
    public void run() {
        while(connected){
            try {
                Object request=input.readObject();
                Response response=handleRequest((Request)request);
                if (response!=null){
                    sendResponse(response);
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            System.out.println("Error "+e);
        }
    }


    @Override
    public void inscriereUpdate() throws ProiectException {
        Response response = new Response.Builder().type(ResponseType.UPDATE).data(null).build();
        try {
            sendResponse(response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
