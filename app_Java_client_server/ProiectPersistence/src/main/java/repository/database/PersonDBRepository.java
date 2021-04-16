package repository.database;

import model.Person;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import repository.PersonRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class PersonDBRepository implements PersonRepository {
    private JdbcUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public PersonDBRepository(Properties prop){
        logger.info("Initializing PersonDbRepository with properties");
        dbUtils = new JdbcUtils(prop);
    }
    @Override
    public void add(Person elem) {
        logger.traceEntry("saving person {}", elem);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Insert into Persoane (nume, varsta) values (?, ?)")){
            preStmt.setString(1, elem.getNume());
            preStmt.setInt(2, elem.getVarsta().intValue());
            int result = preStmt.executeUpdate();
            logger.traceEntry("Saved {} instances", result);
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void delete(Person elem) {
        logger.traceEntry("deleting person {}", elem);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Delete from Persoane where id = ?")){
            preStmt.setInt(1, elem.getId().intValue());
            int result = preStmt.executeUpdate();
            logger.trace("deleted {} intances", result);
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void update(Person elem, Long id) {
        logger.traceEntry("update {} person with id", id);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Update Persoane set nume = ?, varsta = ? where id = ?")){
            preStmt.setString(1, elem.getNume());
            preStmt.setInt(2, elem.getVarsta().intValue());
            preStmt.setInt(3, id.intValue());
            int result = preStmt.executeUpdate();
            logger.trace("updated {} instances", result);
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
        try(PreparedStatement preStmt=con.prepareStatement("select count(*) as [SIZE] from Persoane")) {
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
    public Person findById(Long id) {
        logger.traceEntry("find element by id: {}", id);
        Connection con = dbUtils.getConnection();
        Person p = null;
        try(PreparedStatement preStmt = con.prepareStatement("Select * from Persoane where id = ?")){
            preStmt.setInt(1, id.intValue());
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    String nume = result.getString("nume");
                    int varsta = result.getInt("varsta");
                    p = new Person(nume, (long) varsta);
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
    public Iterable<Person> findAll() {
        logger.traceEntry("return all elements");
        Connection con = dbUtils.getConnection();
        List<Person> personList = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("Select * from Persoane")){
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    int id = result.getInt("id");
                    String nume = result.getString("nume");
                    int varsta = result.getInt("varsta");
                    Person p = new Person(nume, (long) varsta);
                    p.setId((long)id);
                    personList.add(p);
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return personList;
    }

    @Override
    public List<Long> getAllProbeIdInscrieri(Person P) {
        logger.traceEntry("return all prebe ids for a person {}", P);
        List<Long> ids = new ArrayList<>();

        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("SELECT * from Inscrieri inner join InscrieriProba on Inscrieri.id = InscrieriProba.idInscriere inner join Persoane P on Inscrieri.personId = P.id where P.id = ?"))
        {
            preStmt.setInt(1, P.getId().intValue());
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    int id = result.getInt("idProba");
                    ids.add((long) id);
                }
            }

        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return ids;
    }

    @Override
    public Person getByNumeAndVarsta(String nume, Long varsta) {
        logger.traceEntry("Finding Person by nume = {} and varsta = {}", nume, varsta);
        Connection con = dbUtils.getConnection();
        Person p = null;
        try(PreparedStatement preStmt = con.prepareStatement("Select id from Persoane where nume = ? and varsta = ?")){
            preStmt.setString(1, nume);
            preStmt.setInt(2, varsta.intValue());
            try(ResultSet result = preStmt.executeQuery()){
                if(result.next()){
                    int id = result.getInt("id");
                    p = new Person(nume, varsta);
                    p.setId((long) id);
                    return p;
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();

        return p;
    }
}
