import controllers.LogInController;
import controllers.MainFXController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import rpcProtocol.ProiectServicesRpcProxy;
import services.IProiectServices;

import java.io.IOException;
import java.util.Properties;

public class StartRpcClientFX extends Application {

    private static int defaultConcursPort = 55555;
    private static String defaultServer = "localhost";

    @Override
    public void start(Stage primaryStage) throws Exception {
//        System.out.println("In start");
//        Properties clientProps = new Properties();
//        try {
//            clientProps.load(StartRpcClientFX.class.getResourceAsStream("/concursClient.properties"));
//            System.out.println("Client properties set. ");
//            clientProps.list(System.out);
//        } catch (IOException e) {
//            System.err.println("Cannot find concursClient.properties " + e);
//            return;
//        }
//
//        String serverIP = clientProps.getProperty("concurs.server.host", defaultServer);
//        int serverPort = defaultConcursPort;
//
//        try {
//            serverPort = Integer.parseInt(clientProps.getProperty("concurs.server.port"));
//        } catch (NumberFormatException ex) {
//            System.err.println("Wrong port number " + ex.getMessage());
//            System.out.println("Using default port: " + defaultConcursPort);
//        }
//        System.out.println("Using server IP " + serverIP);
//        System.out.println("Using server port " + serverPort);
//
//        IProiectServices server = new ProiectServicesRpcProxy(serverIP, serverPort);

        ApplicationContext factory = new ClassPathXmlApplicationContext("classpath:springClient.xml");
        IProiectServices server=(IProiectServices)factory.getBean("proiectService");

        FXMLLoader loader = new FXMLLoader(getClass().getClassLoader().getResource("LogIn.fxml"));
        Parent root=loader.load();
        LogInController ctrl = loader.getController();
        ctrl.setService(server);

        FXMLLoader cloader = new FXMLLoader(
                getClass().getClassLoader().getResource("Main.fxml"));
        Parent croot=cloader.load();
        MainFXController mainFXController = cloader.getController();
        ctrl.setMainController(mainFXController);
        ctrl.setParent(croot);
        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
