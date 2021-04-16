package controllers;

import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.stage.Window;
import model.DTOs.DTOPersoanaProbaId;
import model.DTOs.DTOProbaInscrieri;
import model.Proba;
import model.User;
import service.Services;

import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;

public class MainFxController extends Control {

    @FXML
    public TableView<Proba> tableProbe;
    @FXML
    public TableColumn<Proba, Long> idColumnProbe;
    @FXML
    public TableColumn<Proba, String> stilColumnProbe;
    @FXML
    public TableColumn<Proba, String> distantaColumnProbe;

    ////
    @FXML
    public TableView<DTOPersoanaProbaId> persoaneTable;
    @FXML
    public TableColumn<DTOPersoanaProbaId, Long> varstaColumn;
    @FXML
    public TableColumn<DTOPersoanaProbaId, String> nameColumn;
    @FXML
    public TableColumn<DTOPersoanaProbaId, Long> probIdColumn;
    @FXML
    public TextField numeField;
    @FXML
    public TextField varstaField;
    @FXML
    public TableView<Proba> tableProbeInscriere;
    @FXML
    public TableColumn<Proba, Long> idColumnProbeInscriere;
    @FXML
    public TableColumn<Proba, String> stilColumnProbeInscriere;
    @FXML
    public TableColumn<Proba, String> distantaColumnProbeInscriere;
    @FXML
    public Button addInscriereButton;
    @FXML
    public Button logOutButton;

    private Services service;
    private User user;

    @FXML
    TableView<DTOProbaInscrieri> tableCurrentSituation;
    @FXML
    public TableColumn<DTOProbaInscrieri, String> distantaColumn;
    @FXML
    public TableColumn<DTOProbaInscrieri, String> stilColumn;
    @FXML
    public TableColumn<DTOProbaInscrieri, Integer> numarPersoaneInscriseColumn;

    public void setService(Services service) {
        this.service = service;
    }

    public void setUser(User u) {
        this.user = u;
    }

    ObservableList<DTOProbaInscrieri> modelProbaNrInscrieri = FXCollections.observableArrayList();
    ObservableList<DTOPersoanaProbaId> modelPersoanaProbaId = FXCollections.observableArrayList();
    ObservableList<Proba> modelProba = FXCollections.observableArrayList();
    ObservableList<Proba> modelProbaInscriere = FXCollections.observableArrayList();

    TableView.TableViewSelectionModel<Proba> selectionModel;
    ObservableList<Proba> selectedItems;

    TableView.TableViewSelectionModel<Proba> selectionModelInscriere;
    ObservableList<Proba> selectedItemsInscriere;

    public void init() {
        /// init first screen
        tableCurrentSituation.setItems(modelProbaNrInscrieri);
        List<DTOProbaInscrieri> dtoProbaInscrieriList = service.getAllProbaInscrieri();
        modelProbaNrInscrieri.setAll(dtoProbaInscrieriList);
        this.distantaColumn.setCellValueFactory(new PropertyValueFactory<DTOProbaInscrieri, String>("ProbaDistanta"));
        this.stilColumn.setCellValueFactory(new PropertyValueFactory<DTOProbaInscrieri, String>("ProbaStil"));
        this.numarPersoaneInscriseColumn.setCellValueFactory(new PropertyValueFactory<DTOProbaInscrieri, Integer>("NumberOfInscrieri"));

        /// init personPrebeId table

        persoaneTable.setItems(modelPersoanaProbaId);
        this.nameColumn.setCellValueFactory(new PropertyValueFactory<DTOPersoanaProbaId, String>("Name"));
        this.varstaColumn.setCellValueFactory(new PropertyValueFactory<DTOPersoanaProbaId, Long>("Varsta"));
        this.probIdColumn.setCellValueFactory(new PropertyValueFactory<DTOPersoanaProbaId, Long>("ProbaId"));


        /// init probe second screen
        tableProbe.setItems(modelProba);
        List<Proba> probe = (List<Proba>) service.getAllProba();
        modelProba.setAll(probe);
        this.idColumnProbe.setCellValueFactory(new PropertyValueFactory<Proba, Long>("Id"));
        this.distantaColumnProbe.setCellValueFactory(new PropertyValueFactory<Proba, String>("Distanta"));
        this.stilColumnProbe.setCellValueFactory(new PropertyValueFactory<Proba, String>("Stil"));
        selectionModel = tableProbe.getSelectionModel();
        selectedItems = selectionModel.getSelectedItems();
        selectionModel.clearSelection();
        selectedItems.addListener(new ListChangeListener<Proba>() {
            @Override
            public void onChanged(Change<? extends Proba> change) {
                List<DTOPersoanaProbaId> dtoPersoanaProbaIds = service.getAllPersonProbaId(selectedItems);
                modelPersoanaProbaId.setAll(dtoPersoanaProbaIds);
            }
        });

        /// init probe third screen
        tableProbeInscriere.setItems(modelProbaInscriere);
        modelProbaInscriere.setAll(probe);
        this.idColumnProbeInscriere.setCellValueFactory(new PropertyValueFactory<Proba, Long>("Id"));
        this.distantaColumnProbeInscriere.setCellValueFactory(new PropertyValueFactory<Proba, String>("Distanta"));
        this.stilColumnProbeInscriere.setCellValueFactory(new PropertyValueFactory<Proba, String>("Stil"));
        tableProbeInscriere.getSelectionModel().setSelectionMode(
                SelectionMode.MULTIPLE
        );
        selectionModelInscriere = tableProbeInscriere.getSelectionModel();

        selectedItemsInscriere = selectionModelInscriere.getSelectedItems();
        selectionModelInscriere.clearSelection();
    }


    public void handleInscriere(MouseEvent mouseEvent) {
        String nume = numeField.getText();
        long varsta = 0L;
        try{
            varsta = Long.parseLong(varstaField.getText());
        }catch (Error e){
            Alert alert=new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error ");
            alert.setContentText("Error while starting app "+e);
            alert.showAndWait();
        }
        List<Proba> probe = selectedItemsInscriere;
        try{

            service.handleInscriere(nume, varsta, probe);

            Alert alert=new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Inscriere efectuata cu succes");
            alert.setContentText("Inscrierea a avut loc cu succes");
            alert.showAndWait();
        }
        catch(Exception e){
            Alert alert=new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error ");
            alert.setContentText("Error while starting app "+e);
            alert.showAndWait();
        }


    }

    public void logOutHandle(MouseEvent mouseEvent) {
        Stage scene = (Stage) logOutButton.getScene().getWindow();
        Alert alert=new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("La revedere");
        alert.setContentText("Ai parasit aplicatia!");
        alert.showAndWait();
        scene.close();
    }

    public void updateTable(Event event) {
        /// update
        if(service != null)
            modelProbaNrInscrieri.setAll(service.getAllProbaInscrieri());
    }
}
