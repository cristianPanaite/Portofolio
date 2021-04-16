package repository;

import model.Person;
import model.Proba;

import java.util.List;

public interface ProbaRepository extends Repository<Long, Proba> {
    Integer countInscrieri(Proba p);

    List<Person> getAllParticipantsForAProba(Long id);
}
