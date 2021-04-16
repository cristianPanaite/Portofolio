package controllers;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Control;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import model.User;
import services.IProiectObserver;
import services.IProiectServices;
import services.ProiectException;

public class LogInController extends Control {
    @FXML
    private TextField user;
    @FXML
    private TextField password;

    IProiectServices service;
    Parent mainParent;

    MainFXController controller;
    public void setParent(Parent p){
        mainParent =p;
    }

    public void setService(IProiectServices service){
        this.service = service;
    }

    public void logInHandle(ActionEvent actionEvent) {

        String usernameString = user.getText();
        String passwordString = password.getText();
        try{
            User u = service.getUserByCreditentials(usernameString, passwordString, controller);
            try {
                Stage userStage = new Stage();
                userStage.setScene(new Scene(mainParent, 600, 500));
                userStage.setTitle("UserPage");
                userStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
                    @Override
                    public void handle(WindowEvent event) {
                        controller.logOut();
                        System.exit(0);
                    }
                });

                controller.setService(service);
                controller.setUser(u);
                controller.init();
                userStage.show();

                ((Node)(actionEvent.getSource())).getScene().getWindow().hide();

            }catch(Exception e){
                Alert alert=new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error ");
                alert.setContentText("Error while starting app "+e);
                alert.showAndWait();
            }
        } catch (Exception e) {
            Alert errorAlert = new Alert(Alert.AlertType.ERROR);
            errorAlert.setHeaderText("Eroare");
            errorAlert.setContentText("Nu exista acest username si aceasta parola");
            errorAlert.showAndWait();
        }
    }


    public void setMainController(MainFXController mainFXController) {
        controller = mainFXController;
    }
}
