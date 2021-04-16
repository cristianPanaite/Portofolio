package repository.database;

import model.Inscriere;
import model.Person;
import model.Proba;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import repository.InscriereRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class InscriereDBRepository implements InscriereRepository {

    private JdbcUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public InscriereDBRepository(Properties prop){
        logger.info("Initializing InscriereDbRepository with properties");
        dbUtils = new JdbcUtils(prop);
    }

    @Override
    public void add(Inscriere elem) {
        logger.traceEntry("saving inscriere {}", elem);
        Connection con = dbUtils.getConnection();
        /// daca fac insert in doua tabele diferite cum fac sa se execute doar daca se poate insera in ambele?
        try(PreparedStatement preStmt = con.prepareStatement("INSERT into Inscrieri (personID) VALUES (?)")){
            preStmt.setInt(1, elem.getPerson().getId().intValue());
            int result = preStmt.executeUpdate();
            logger.trace("Saved {} instances", result);
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        Inscriere inscriere = findByPersonId(elem.getPerson().getId());
        List<Proba> probe = elem.getProbe();
        for(Proba p : probe){
            try(PreparedStatement preStmt = con.prepareStatement("INSERT into InscrieriProba (idInscriere, idProba) VALUES (?, ?)")){
                preStmt.setInt(1, inscriere.getId().intValue());
                preStmt.setInt(2, p.getId().intValue());
                int result = preStmt.executeUpdate();
                logger.trace("Saved {} instances", result);
            }catch (Exception ex){
                logger.error(ex);
                System.err.println("Error db : " + ex);
            }
        }
        logger.traceExit();
    }

    @Override
    public void delete(Inscriere elem) {
        logger.traceEntry("deleting inscriere {}", elem);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("DELETE from Inscrieri where id = ?")){
            preStmt.setInt(1, elem.getId().intValue());
            /// de modificat setarile din database cand se sterge o inscriere din tabel sa se stearga si din tabelul m-n
            int result = preStmt.executeUpdate();
            logger.trace("Deleted {} instances", result);
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void update(Inscriere elem, Long id) {
        logger.traceEntry("update item {} with id: {}", elem, id);
        Connection con = dbUtils.getConnection();
        Inscriere existing = this.findById(id);
        if(!existing.getPerson().getId().equals(elem.getPerson().getId())){
            try(PreparedStatement preStmt = con.prepareStatement("Update Inscrieri set personId = ? where id = ?")){
                preStmt.setInt(1, elem.getPerson().getId().intValue());
                preStmt.setInt(2, id.intValue());
                int result = preStmt.executeUpdate();
                logger.trace("Updated {} instances", result);
            }catch (Exception ex){
                logger.error(ex);
                System.err.println("Error db : " + ex);
            }
        }
        Set<Proba> probeUpdate = new HashSet<>(elem.getProbe());
        Set<Proba> probeCurrent = new HashSet<>(existing.getProbe());
        if(!probeUpdate.equals(probeCurrent)){
            for(Proba p : probeCurrent){
                try(PreparedStatement preStmt = con.prepareStatement("Delete from InscrieriProba where idInscriere = ?")){
                    preStmt.setInt(1, id.intValue());
                    int result = preStmt.executeUpdate();
                    logger.trace("Deleted {} instances from m-n table", result);
                }catch (Exception ex){
                    logger.error(ex);
                    System.err.println("Error db : " + ex);
                }
            }
            for(Proba p : probeUpdate){
                try(PreparedStatement preStmt = con.prepareStatement("INSERT into InscrieriProba (idInscriere, idProba) VALUES (?, ?)")){
                    preStmt.setInt(1, id.intValue());
                    preStmt.setInt(2, p.getId().intValue());
                    int result = preStmt.executeUpdate();
                    logger.trace("Saved {} instances in m-n table", result);
                }catch (Exception ex){
                    logger.error(ex);
                    System.err.println("Error db : " + ex);
                }
            }
        }
    }

    @Override
    public Long size() {
        logger.traceEntry();
        Connection con=dbUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement("select count(*) as [SIZE] from Inscrieri")) {
            try(ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    logger.traceExit(result.getInt("SIZE"));
                    return (long)result.getInt("SIZE");
                }
            }
        }catch(SQLException ex){
            logger.error(ex);
            System.out.println("Error DB "+ex);
        }
        return 0L;
    }

    @Override
    public Inscriere findById(Long id) {
        logger.traceEntry("Finding items with id: ", id);
        Connection con = dbUtils.getConnection();
        Inscriere inscriere = null;
        try(PreparedStatement preStmt = con.prepareStatement("Select * FROM Inscrieri where id = ?")){
            preStmt.setInt(1, id.intValue());
            try(ResultSet result = preStmt.executeQuery()) {
                while (result.next()){
                    int idInscriere = result.getInt("id");
                    int personId = result.getInt("personId");

                    /// get Person form his Id
                    Person p = null;
                    try(PreparedStatement preStmt2 = con.prepareStatement("Select * FROM Persoane where id = ?")){
                        preStmt2.setInt(1, personId);
                        try(ResultSet resultSet = preStmt2.executeQuery()){
                            while(resultSet.next()){
                                int idP = resultSet.getInt("id");
                                String nume = resultSet.getString("nume");
                                int varsta = resultSet.getInt("varsta");
                                p = new Person(nume, (long) varsta);
                                p.setId((long) idP);
                            }
                        }
                    }catch (Exception ex){
                        logger.error(ex);
                        System.err.println("Error db : " + ex);
                    }

                    /// get ids of Probe
                    List<Integer> probeId = new ArrayList<>();
                    try(PreparedStatement preStmt2 = con.prepareStatement("Select * FROM InscrieriProba where idInscriere = ?")){
                        preStmt2.setInt(1, idInscriere);
                        try(ResultSet resultSet = preStmt2.executeQuery()){
                            while(resultSet.next()){
                                int idProba = resultSet.getInt("idProba");
                                probeId.add(idProba);
                            }
                        }
                    }catch (Exception ex){
                        logger.error(ex);
                        System.err.println("Error db : " + ex);
                    }

                    /// Get Probe from their ids
                    List<Proba> probe = new ArrayList<>();
                    for(Integer idProba : probeId){
                        try(PreparedStatement preStmt2 = con.prepareStatement("Select * FROM Probe where id = ?")){
                            preStmt2.setInt(1, idProba);
                            try(ResultSet resultSet = preStmt2.executeQuery()){
                                while(resultSet.next()){
                                    int idP = resultSet.getInt("id");
                                    String distanta = resultSet.getString("distanta");
                                    String stil = resultSet.getString("stil");
                                    Proba proba = new Proba(distanta, stil);
                                    proba.setId((long) idP);
                                    probe.add(proba);
                                }
                            }
                        }catch (Exception ex){
                            logger.error(ex);
                            System.err.println("Error db : " + ex);
                        }
                    }
                    ////
                    inscriere = new Inscriere(p, probe);
                    inscriere.setId(id);
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return inscriere;
    }

    @Override
    public Iterable<Inscriere> findAll() {
        logger.traceEntry("Returning all inscrieri");
        Connection con = dbUtils.getConnection();
        List<Inscriere> inscrieri = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("Select * FROM Inscrieri")){
            try(ResultSet result = preStmt.executeQuery()) {
                while (result.next()){
                    int idInscriere = result.getInt("id");
                    int personId = result.getInt("personId");

                    /// get Person form his Id
                    Person p = null;
                    try(PreparedStatement preStmt2 = con.prepareStatement("Select * FROM Persoane where id = ?")){
                        preStmt2.setInt(1, personId);
                        try(ResultSet resultSet = preStmt2.executeQuery()){
                            while(resultSet.next()){
                                int idP = resultSet.getInt("id");
                                String nume = resultSet.getString("nume");
                                int varsta = resultSet.getInt("varsta");
                                p = new Person(nume, (long) varsta);
                                p.setId((long) idP);
                            }
                        }
                    }catch (Exception ex){
                        logger.error(ex);
                        System.err.println("Error db : " + ex);
                    }

                    /// get ids of Probe
                    List<Integer> probeId = new ArrayList<>();
                    try(PreparedStatement preStmt2 = con.prepareStatement("Select * FROM InscrieriProba where idInscriere = ?")){
                        preStmt2.setInt(1, idInscriere);
                        try(ResultSet resultSet = preStmt2.executeQuery()){
                            while(resultSet.next()){
                                int idProba = resultSet.getInt("idProba");
                                probeId.add(idProba);
                            }
                        }
                    }catch (Exception ex){
                        logger.error(ex);
                        System.err.println("Error db : " + ex);
                    }

                    /// Get Probe from their ids
                    List<Proba> probe = new ArrayList<>();
                    for(Integer idProba : probeId){
                        try(PreparedStatement preStmt2 = con.prepareStatement("Select * FROM Probe where id = ?")){
                            preStmt2.setInt(1, idProba);
                            try(ResultSet resultSet = preStmt2.executeQuery()){
                                while(resultSet.next()){
                                    int idP = resultSet.getInt("id");
                                    String distanta = resultSet.getString("distanta");
                                    String stil = resultSet.getString("stil");
                                    Proba proba = new Proba(distanta, stil);
                                    proba.setId((long) idP);
                                    probe.add(proba);
                                }
                            }
                        }catch (Exception ex){
                            logger.error(ex);
                            System.err.println("Error db : " + ex);
                        }
                    }
                    ////
                    Inscriere inscriere = new Inscriere(p, probe);
                    inscriere.setId((long)idInscriere);
                    inscrieri.add(inscriere);
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        return inscrieri;
    }

    @Override
    public Inscriere findByPersonId(Long id) {
        logger.traceEntry("find inscriere with person id: {}", id);
        Inscriere inscriere = null;
        int inscriereId;
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Select * from Inscrieri where personId = ?")){
            preStmt.setInt(1, id.intValue());
            try(ResultSet result = preStmt.executeQuery()){
                if(result.next()){
                    inscriereId = result.getInt("id");
                    inscriere = findById((long) inscriereId);
                    return inscriere;
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        return null;
    }
}
