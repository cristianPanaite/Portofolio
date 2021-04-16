package utils;

import services.ProiectException;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.rmi.ServerException;

public abstract class AbstractServer {
    private int port;
    private ServerSocket server=null;
    public AbstractServer( int port){
        this.port=port;
    }

    public void start() throws ProiectException {
        try{
            server=new ServerSocket(port);
            while(true){
                System.out.println("Waiting for clients ...");
                Socket client=server.accept();
                System.out.println("Client connected ...");
                processRequest(client);
            }
        } catch (IOException e) {
            throw new ProiectException("Starting server errror ",e);
        }finally {
            try{
                server.close();
            } catch (IOException e) {
                throw new ProiectException("Closing server error ", e);
            }
        }
    }

    protected abstract  void processRequest(Socket client);
    public void stop() throws ProiectException {
        try {
            server.close();
        } catch (IOException e) {
            throw new ProiectException("Closing server error ", e);
        }
    }
}