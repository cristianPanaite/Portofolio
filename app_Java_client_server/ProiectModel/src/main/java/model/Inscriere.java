package model;

import java.io.Serializable;
import java.util.List;
import java.util.Objects;

public class Inscriere extends Entity<Long> implements Serializable {
    /// schimb cu person
    private Person person;
    private List<Proba> probe;

    public Inscriere(Person personId, List<Proba> probe) {
        this.person = personId;
        this.probe = probe;
    }

    public Person getPerson() {
        return person;
    }

    public void setPerson(Person personId) {
        this.person = personId;
    }

    public List<Proba> getProbe() {
        return probe;
    }

    public void setProbe(List<Proba> probe) {
        this.probe = probe;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Inscriere inscriere = (Inscriere) o;
        return Objects.equals(person, inscriere.person) && Objects.equals(probe, inscriere.probe) && Objects.equals(super.getId(), inscriere.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hash(person, probe);
    }

    @Override
    public String toString() {
        return "Inscriere{" +
                "id=" + super.getId() +
                ", personId=" + person +
                ", probe=" + probe +
                '}';
    }
}
