package dto;

import model.Person;
import model.Proba;
import model.User;

import java.io.Serializable;
import java.util.List;

public class InscrieriDTO implements Serializable {
    private String nume;
    private Long varsta;
    private List<Proba> probeList;
    private User username;

    public InscrieriDTO(String nume, Long varsta, List<Proba> probeList, User username) {
        this.nume = nume;
        this.varsta = varsta;
        this.probeList = probeList;
        this.username = username;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public Long getVarsta() {
        return varsta;
    }

    public void setVarsta(Long varsta) {
        this.varsta = varsta;
    }

    public List<Proba> getProbeList() {
        return probeList;
    }

    public void setProbeList(List<Proba> probeList) {
        this.probeList = probeList;
    }

    public User getUsername() {
        return username;
    }

    public void setUsername(User username) {
        this.username = username;
    }
}
