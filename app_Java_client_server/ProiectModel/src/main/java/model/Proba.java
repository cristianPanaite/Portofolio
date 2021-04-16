package model;

import java.io.Serializable;
import java.util.Objects;

public class Proba extends Entity<Long>implements Serializable {
    private String distanta;
    private String stil;

    public Proba(String distanta, String stil) {
        this.distanta = distanta;
        this.stil = stil;
    }

    public String getDistanta() {
        return distanta;
    }

    public void setDistanta(String distanta) {
        this.distanta = distanta;
    }

    public String getStil() {
        return stil;
    }

    public void setStil(String stil) {
        this.stil = stil;
    }

    public Long getId(){
        return super.getId();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Proba proba = (Proba) o;
        return Objects.equals(distanta, proba.distanta) && Objects.equals(stil, proba.stil);
    }

    @Override
    public int hashCode() {
        return Objects.hash(distanta, stil);
    }

    @Override
    public String toString() {
        return "Proba{" +
                "id=" + super.getId() +
                ", distanta='" + distanta + '\'' +
                ", stil='" + stil + '\'' +
                '}';
    }
}
