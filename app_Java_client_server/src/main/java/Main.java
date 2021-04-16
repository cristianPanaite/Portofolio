import model.User;
import repository.*;
import repository.database.UserDBRepository;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Main {
    public static void main(String[] args){
        /// properties for database connection
        Properties props=new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config " + e);
        }
        UserRepository urepo = new UserDBRepository(props);

        User u = new User("andrei", "andrei");
        urepo.add(u);
        Iterable<User> ulist = urepo.findAll();
        User uUpdate = ulist.iterator().next();
        uUpdate.setUsername("manole");
        urepo.update(uUpdate, uUpdate.getId());
        ulist = urepo.findAll();
        User find = urepo.findById(uUpdate.getId());
        System.out.println(find);
        System.out.println(ulist);
        Long dim = urepo.size();
        urepo.delete(uUpdate);
        dim = urepo.size();

//
//        ProbaRepository prepo = new ProbaDBRepository(props);
//        PersonRepository personRepo = new PersonDBRepository(props);
//
//        List<Proba> probe = new ArrayList<>();
//        probe.add(prepo.findById(6L));
//        probe.add(prepo.findById(5L));
//        Inscriere inscriere = new Inscriere(personRepo.findById(1L), probe);
//        inscriere.setId(27L);
//        InscriereRepository irepo = new InscriereDBRepository(props);
//        irepo.add(inscriere);
//        probe.add(prepo.findById(7L));
//        inscriere.setPerson(personRepo.findById(2L));
//        inscriere.setProbe(probe);
//        irepo.update(inscriere, inscriere.getId());
//        Inscriere ifind = irepo.findById(inscriere.getId());
//        Iterable<Inscriere> ilist = irepo.findAll();
//        Long size = irepo.size();
//        irepo.delete(inscriere);
    }

}
