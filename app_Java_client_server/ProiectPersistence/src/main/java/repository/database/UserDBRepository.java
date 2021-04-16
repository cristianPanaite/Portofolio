package repository.database;

import model.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import repository.UserRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class UserDBRepository implements UserRepository {
    private JdbcUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public UserDBRepository(Properties prop){
        logger.info("Initializing UserDBRepository with properties");
        dbUtils = new JdbcUtils(prop);
    }

    @Override
    public void add(User elem) {
        logger.traceEntry("saving user {}", elem);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Insert into Users (username, password) values (?, ?)")){
            preStmt.setString(1, elem.getUsername());
            preStmt.setString(2, elem.getPassword());
            int result = preStmt.executeUpdate();
            logger.trace("saved {} instances", result);
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void delete(User elem) {
        logger.traceEntry("deleting user {}", elem);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Delete from Users WHERE id = ?")){
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
    public void update(User elem, Long id) {
        logger.traceEntry("update {} person with id", id);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("Update Users set username = ?, password = ? where id = ?")){
            preStmt.setString(1, elem.getUsername());
            preStmt.setString(2, elem.getPassword());
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
        try(PreparedStatement preStmt=con.prepareStatement("select count(*) as [SIZE] from Users")) {
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
    public User findById(Long id) {
        logger.traceEntry("find element by id: {}", id);
        Connection con = dbUtils.getConnection();
        User u = null;
        try(PreparedStatement preStmt = con.prepareStatement("Select * from Users where id = ?")){
            preStmt.setInt(1, id.intValue());
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    String username = result.getString("username");
                    String password = result.getString("password");
                    u = new User(username, password);
                    u.setId(id);
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return u;
    }

    @Override
    public Iterable<User> findAll() {
        logger.traceEntry("find element by id: {}");
        Connection con = dbUtils.getConnection();
        List<User> u = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("Select * from Users")){
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    int id = result.getInt("id");
                    String username = result.getString("username");
                    String password = result.getString("password");
                    User user = new User(username, password);
                    user.setId((long)id);
                    u.add(user);
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return u;
    }

    @Override
    public User findByUsernameAndPassword(String username, String password) {
        logger.traceEntry("Returning user with username: {} password: {}", username, password);
        Connection con = dbUtils.getConnection();
        User u = null;
        try(PreparedStatement preStmt = con.prepareStatement("Select * from Users where username = ? and password = ?")){
            preStmt.setString(1, username);
            preStmt.setString(2, password);
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    int id = result.getInt("id");
                    u = new User(username, password);
                    u.setId((long)id);
                }
            }
        }catch (Exception ex){
            logger.error(ex);
            System.err.println("Error db : " + ex);
        }
        logger.traceExit();
        return u;
    }
}
