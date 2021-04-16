package controllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Control;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import model.User;
import service.Services;

public class LogInController extends Control {
    @FXML
    private TextField user;
    @FXML
    private TextField password;


    private Services service;

    public LogInController() { }

    public void setService(Services service){
        this.service = service;
    }

    public void logInHandle(ActionEvent actionEvent) {
        String usernameString = user.getText();
        String passwordString = password.getText();
        try{
            User u = service.getUserByCreditentials(usernameString, passwordString);
            try {
                Stage primaryStage = new Stage();
                FXMLLoader loader = new FXMLLoader();
                loader.setLocation(getClass().getResource("../Main.fxml"));
                Pane root;
                root = loader.load();
                MainFxController controller = loader.getController();
                controller.setService(service);
                controller.setUser(u);
                controller.init();

                Stage stage = (Stage) user.getScene().getWindow();
                stage.close();
                primaryStage.setScene(new Scene(root));
                primaryStage.setTitle("Salut, "+ u.getUsername() + "!");
                primaryStage.show();

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
}
