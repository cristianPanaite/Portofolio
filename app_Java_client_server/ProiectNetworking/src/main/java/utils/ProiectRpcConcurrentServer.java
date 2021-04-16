package utils;

import rpcProtocol.ProiectRpcWorker;
import services.IProiectServices;

import java.net.Socket;

public class ProiectRpcConcurrentServer extends AbstractConcurrentServer {
    private IProiectServices proiectServices;
    public ProiectRpcConcurrentServer(int port, IProiectServices concursServer) {
        super(port);
        this.proiectServices=concursServer;
        System.out.println("Concurs - ConcursRpcConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        ProiectRpcWorker worker=new ProiectRpcWorker(proiectServices, client);

        Thread tw=new Thread(worker);
        return tw;
    }
}
