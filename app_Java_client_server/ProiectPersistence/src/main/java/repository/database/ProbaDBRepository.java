package repository.database;

import model.Person;
import model.Proba;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import repository.ProbaRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class ProbaDBRepository implements ProbaRepository {
    private JdbcUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public ProbaDBRepository(Properties prop){
        logger.info("Initializing ProbaDBRepository with properties");
        dbUtils = new JdbcUtils(prop);
    }
    @Override
    public void add(Proba elem) {
        logger.traceEntry("saving proba {}", elem);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Insert into Probe (distanta, stil) values (?, ?)")){
            preStmt.setString(1, elem.getDistanta());
            preStmt.setString(2, elem.getStil());
            int result = preStmt.executeUpdate();
            logger.traceEntry("Saved {} instances", result);
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void delete(Proba elem) {
        logger.traceEntry("delete proba {}", elem);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Delete from Probe where id = ?")){
            preStmt.setInt(1, elem.getId().intValue());
            int result = preStmt.executeUpdate();
            logger.trace("deleted {} instances", result);
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void update(Proba elem, Long id) {
        logger.traceEntry("update {} proba ");
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Update Probe set distanta = ?, stil = ? where id = ?")){
            preStmt.setString(1, elem.getDistanta());
            preStmt.setString(2, elem.getStil());
            preStmt.setInt(3, id.intValue());
            int result = preStmt.executeUpdate();
            logger.trace("Updated {} instances", result);
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
    }

    @Override
    public Long size() {
        logger.traceEntry();
        Connection con=dbUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement("select count(*) as [SIZE] from Probe")) {
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
    public Proba findById(Long id) {
        logger.traceEntry("find element by id: {}", id);
        Connection con = dbUtils.getConnection();
        Proba p = null;
        try(PreparedStatement preStmt = con.prepareStatement("Select * from Probe where id = ?")){
            preStmt.setInt(1, id.intValue());
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    String distanta = result.getString("distanta");
                    String stil = result.getString("stil");
                    p = new Proba(distanta, stil);
                    p.setId(id);
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return p;
    }

    @Override
    public Iterable<Proba> findAll() {
        logger.traceEntry("find element by id: {}");
        Connection con = dbUtils.getConnection();
        List<Proba> probe = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("Select * from Probe")){
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    int id = result.getInt("id");
                    String distanta = result.getString("distanta");
                    String stil = result.getString("stil");
                    Proba p = new Proba(distanta, stil);
                    p.setId((long)id);
                    probe.add(p);
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return probe;
    }

    @Override
    public Integer countInscrieri(Proba p) {
        logger.traceEntry("return how many inscrieri for a proba");
        Connection con=dbUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement("select count(*) as [SIZE] from InscrieriProba where idProba = ?")) {
            preStmt.setInt(1, p.getId().intValue());
            try(ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    return (Integer) result.getInt("SIZE");
                }
            }
        }catch(SQLException ex){
            logger.error(ex);
            System.out.println("Error DB "+ex);
        }
        return 0;
    }

    @Override
    public List<Person> getAllParticipantsForAProba(Long id) {
        logger.traceEntry("Returning all participants for a specific proba");
        List<Person> personForAProba = new ArrayList<>();

        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Select Persoane.id as id, nume, varsta from Persoane\n" +
                "inner join Inscrieri I on Persoane.id = I.personId\n" +
                "inner join InscrieriProba IP on I.id = IP.idInscriere\n" +
                "inner join Probe P on P.id = IP.idProba where P.id = ?"))
        {
            preStmt.setInt(1, id.intValue());
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    int idPerson = result.getInt("id");
                    String nume = result.getString("nume");
                    int varsta = result.getInt("varsta");
                    Person p = new Person(nume, (long)varsta);
                    p.setId((long) idPerson);
                    personForAProba.add(p);
                }
            }

        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return personForAProba;
    }
}
