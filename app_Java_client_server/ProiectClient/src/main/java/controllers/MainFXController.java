package controllers;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import model.DTOs.DTOPersoanaProbaId;
import model.DTOs.DTOProbaInscrieri;
import model.Proba;
import model.User;
import services.IProiectObserver;
import services.IProiectServices;
import services.ProiectException;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class MainFXController extends UnicastRemoteObject implements IProiectObserver, Serializable {


    public MainFXController() throws RemoteException {

    }
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

    private IProiectServices service;
    private User user;

    @FXML
    TableView<DTOProbaInscrieri> tableCurrentSituation;
    @FXML
    public TableColumn<DTOProbaInscrieri, String> distantaColumn;
    @FXML
    public TableColumn<DTOProbaInscrieri, String> stilColumn;
    @FXML
    public TableColumn<DTOProbaInscrieri, Integer> numarPersoaneInscriseColumn;

    ObservableList<DTOProbaInscrieri> modelProbaNrInscrieri = FXCollections.observableArrayList();
    ObservableList<DTOPersoanaProbaId> modelPersoanaProbaId = FXCollections.observableArrayList();
    ObservableList<Proba> modelProba = FXCollections.observableArrayList();
    ObservableList<Proba> modelProbaInscriere = FXCollections.observableArrayList();

    TableView.TableViewSelectionModel<Proba> selectionModel;
    ObservableList<Proba> selectedItems;

    TableView.TableViewSelectionModel<Proba> selectionModelInscriere;
    ObservableList<Proba> selectedItemsInscriere;

    public void setService(IProiectServices service) {
        this.service = service;
    }

    public void setUser(User u) {
        this.user = u;
    }

    public void init() throws ProiectException {
        /// init first screen
        tableCurrentSituation.setItems(modelProbaNrInscrieri);
        List<DTOProbaInscrieri> dtoProbaInscrieriList = service.getAllProbaInscrieri();
        modelProbaNrInscrieri.setAll(dtoProbaInscrieriList);
        this.distantaColumn.setCellValueFactory(new PropertyValueFactory<DTOProbaInscrieri, String>("ProbaDistanta"));
        this.stilColumn.setCellValueFactory(new PropertyValueFactory<DTOProbaInscrieri, String>("ProbaStil"));
        this.numarPersoaneInscriseColumn.setCellValueFactory(new PropertyValueFactory<DTOProbaInscrieri, Integer>("NumberOfInscrieri"));

        //init personProbeId table

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
                List<DTOPersoanaProbaId> dtoPersoanaProbaIds = null;
                try {
                    List<Proba> probe = new ArrayList<>();
                    for(Proba p : selectedItems){
                        probe.add(p);
                    }
                    dtoPersoanaProbaIds = service.getAllPersonProbaId(probe.get(0));
                    modelPersoanaProbaId.setAll(dtoPersoanaProbaIds);
                } catch (ProiectException e) {
                    e.printStackTrace();
                }
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


    @Override
    public void inscriereUpdate() throws ProiectException {
        System.out.println("salutare");
        Platform.runLater(
                () ->{
                    List<DTOProbaInscrieri> dtoProbaInscrieriList = new ArrayList<>();
                    try {
                        dtoProbaInscrieriList = service.getAllProbaInscrieri();
                        System.out.println("Lista actualizata: " + dtoProbaInscrieriList);
                    } catch (ProiectException e) {
                        e.printStackTrace();
                    }
                    modelProbaNrInscrieri.setAll(dtoProbaInscrieriList);
                    try {
                        List<Proba> probe = new ArrayList<>();
                        for(Proba p : selectedItems){
                            probe.add(p);
                        }
                        List<DTOPersoanaProbaId> dtoPersoanaProbaIds = new ArrayList<DTOPersoanaProbaId>();
                        if(probe.size() > 0){
                            dtoPersoanaProbaIds = service.getAllPersonProbaId(probe.get(0));
                            modelPersoanaProbaId.setAll(dtoPersoanaProbaIds);
                        }
                    } catch (ProiectException e) {
                        e.printStackTrace();
                    }
                }
        );

    }

    public void handleInscriere(MouseEvent mouseEvent) {String nume = numeField.getText();
        long varsta = 0L;
        try{
            varsta = Long.parseLong(varstaField.getText());
        }catch (Error e){
            Alert alert=new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error ");
            alert.setContentText("Error while starting app "+e);
            alert.showAndWait();
        }
        List<Proba> probe = new ArrayList<Proba>();
        for (Proba p : selectedItemsInscriere){
            probe.add(p);
        }
        try{

            service.handleInscriere(nume, varsta, probe, user);

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

    public void logOut(){
        try {
            service.logOut(user, this);
        } catch (ProiectException e) {
            System.out.println("Logout error " + e);
        }
    }

    public void logOutHandle(MouseEvent mouseEvent) {
        try {

            service.logOut(user, this);
        }catch (ProiectException e){
            System.out.println(e.getMessage());
        }
        Stage scene = (Stage) logOutButton.getScene().getWindow();
        Alert alert=new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("La revedere");
        alert.setContentText("Ai parasit aplicatia!");
        alert.showAndWait();
        scene.close();
    }

//    public void updateTable(Event event) throws ProiectException {
//        if(service != null)
//            modelProbaNrInscrieri.setAll(service.getAllProbaInscrieri());
//    }
}
