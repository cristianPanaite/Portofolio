package model;

import java.io.Serializable;
import java.util.Objects;

public class Person extends Entity<Long> implements Serializable {

    private String nume;
    private Long varsta;

    public Person(String nume, Long varsta) {
        this.nume = nume;
        this.varsta = varsta;
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


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        return Objects.equals(nume, person.nume) && Objects.equals(varsta, person.varsta);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nume, varsta);
    }

    @Override
    public String toString() {
        return "Person{" +
                "id=" + super.getId() +
                ", nume='" + nume + '\'' +
                ", varsta=" + varsta +
                '}';
    }
}
