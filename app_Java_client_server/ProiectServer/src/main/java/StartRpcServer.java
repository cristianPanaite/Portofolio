import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import services.IProiectServices;
import services.ProiectException;
import utils.AbstractServer;
import utils.ProiectRpcConcurrentServer;

import java.io.IOException;
import java.util.Properties;

public class StartRpcServer {
    private static int defaultPort=55555;

    public static void main(String[] args) throws ProiectException {
        /*Properties serverProps=new Properties();
        try {
            serverProps.load(StartRpcServer.class.getResourceAsStream("/concursServer.properties"));
            System.out.println("Server properties set. ");
            serverProps.list(System.out);
        } catch (IOException e) {
            System.err.println("Cannot find chatserver.properties "+e);
            return;
        }

        IProiectServices proiectServiceImpl = getService();
        //proiectServiceImpl.getAllUsers().forEach(System.out::println);
        int proiectServerPort=defaultPort;
        try {
            proiectServerPort = Integer.parseInt(serverProps.getProperty("concurs.server.port"));
        }catch (NumberFormatException nef){
            System.err.println("Wrong  Port Number"+nef.getMessage());
            System.err.println("Using default port "+defaultPort);
        }
        System.out.println("Starting server on port: "+proiectServerPort);
        AbstractServer server = new ProiectRpcConcurrentServer(proiectServerPort, proiectServiceImpl);
        try {
            server.start();
        } catch (ProiectException e) {
            System.err.println("Error starting the server" + e.getMessage());
        }finally {
            try {
                server.stop();
            }catch(ProiectException e){
                System.err.println("Error stopping server "+e.getMessage());
            }
        }*/
        ApplicationContext context=new ClassPathXmlApplicationContext("ProiectConfig.xml");
        System.out.println("Waiting for clients...");
    }

    static IProiectServices getService() throws ProiectException {

        ApplicationContext context=new ClassPathXmlApplicationContext("ProiectConfig.xml");
        return context.getBean(IProiectServices.class);

    }
}
