package repository;

import model.Inscriere;

public interface InscriereRepository extends Repository<Long, Inscriere> {
    Inscriere findByPersonId(Long id);
}
