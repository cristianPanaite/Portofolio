package repository;

import model.Person;

import java.util.List;

public interface PersonRepository extends Repository<Long, Person> {
    List<Long> getAllProbeIdInscrieri(Person p);

    Person getByNumeAndVarsta(String nume, Long varsta);
}
