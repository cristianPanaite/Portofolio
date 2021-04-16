package model.DTOs;

import model.Proba;

import java.io.Serializable;

public class DTOProbaInscrieri implements Serializable {
    private Proba proba;
    private Integer numberOfInscrieri;

    public DTOProbaInscrieri(Proba p, Integer i){
        proba = p;
        numberOfInscrieri = i;
    }

    public String getProbaDistanta(){
        return proba.getDistanta();
    }
    public String getProbaStil(){
        return proba.getStil();
    }
    public Integer getNumberOfInscrieri(){
        return numberOfInscrieri;
    }
}
