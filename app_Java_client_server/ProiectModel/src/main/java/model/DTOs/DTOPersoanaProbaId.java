package model.DTOs;

import model.Person;

import java.io.Serializable;

public class DTOPersoanaProbaId implements Serializable {
    private Person person;
    private Long probaId;

    public DTOPersoanaProbaId(Person p, Long id){
        person = p;
        probaId = id;
    }
    public String getName(){
        return person.getNume();
    }
    public Long getVarsta(){
        return  person.getVarsta();
    }
    public Long getProbaId(){
        return probaId;
    }
}
