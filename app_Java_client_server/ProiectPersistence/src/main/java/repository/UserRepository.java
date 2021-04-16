package repository;

import model.User;

public interface UserRepository extends Repository<Long, User> {
    public User findByUsernameAndPassword(String username, String password);
}
