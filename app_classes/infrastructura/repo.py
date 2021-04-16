from exceptii.exceptii import RepoError


class Repo:

    def __init__(self):
        """
        init repo
        """
        self._items = []

    def size(self):
        """
        return nuber of items in repo
        """

        return len(self._items)

    def adauga(self, item):
        """
        add in repo an object <item>
        """
        if item in self._items:
            raise RepoError("item deja existent!\n")
        self._items.append(item)

    def cauta(self, item):
        """
        search in repo an item
        """
        if item not in self._items:
            raise RepoError("item inexistent")
        for x in self._items:
            if x == item:
                return x

    def exista(self, item):
        """
        check if object <item> exists in repo
        """
        if item not in self._items:
            return False
        for x in self._items:
            if x == item:
                return True

    def modifica(self, item, change):
        """
        modify the name of the object <item> with the string <change>
        """
        item = self.cauta(item)
        self.delete(item)
        item.set_nume(change)
        self.adauga(item)

    def modifica_materie(self, item, change):
        """
        modify the name of a discipline <item> with the string <change>
        """

        item = self.cauta(item)
        self.delete(item)
        item.set_materie(change)
        self.adauga(item)

    def get_all(self):
        """
        return a list with all the objects
        """

        return self._items[:]

    def get_all_by_student(self, stud_id):
        """
        return a list with items with the same student
        """
        l = []
        for item in self._items:
            if item.get_student() == stud_id:
                l.append(item)
        return l[:]

    def get_all_by_discipline(self, disc_id):
        """
        return a list with items with the same discipline
        """
        l = []
        for i in self._items:
            if i.get_id_disciplina() == disc_id:
                l.append(i)
        return l[:]

    def delete(self, item):
        """
        delete an item
        """
        if item not in self._items:
            raise RepoError("item inexistent")
        index = -1
        for i in range(len(self._items)):
            if self._items[i] == item:
                index = i
                break
        del self._items[index]


class FileRepo(Repo):
    def __init__(self, filename, read_entity, write_entity):
        Repo.__init__(self)
        self.__filename = filename
        self.__read_entity = read_entity
        self.__write_entity = write_entity

    def __read_all_from_file(self):
        self._items = []
        with open(self.__filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    elem = self.__read_entity(line)
                    self._items.append(elem)

    def __write_all_to_file(self):
        with open(self.__filename, "w") as f:
            for elem in self._items:
                line = self.__write_entity(elem)
                f.write(line + "\n")

    def adauga(self, item):
        self.__read_all_from_file()
        Repo.adauga(self, item)
        self.__write_all_to_file()

    def cauta(self, item):
        self.__read_all_from_file()
        return Repo.cauta(self, item)

    def exista(self, item):
        self.__read_all_from_file()
        return Repo.exista(self, item)

    def modifica(self, item, change):
        self.__read_all_from_file()
        Repo.modifica(self, item, change)
        self.__write_entity_to_file()

    def modifica_materie(self, item, change):

        self.__read_all_from_file()
        Repo.modifica_materie(self, item, change)
        self.__write_entity_to_file()

    def get_all(self):

        self.__read_all_from_file()
        return Repo.get_all(self)

    def get_all_by_student(self, stud_id):

        self.__read_all_from_file()
        return Repo.get_all_by_student(self, stud_id)

    def get_all_by_discipline(self, disc_id):

        self.__read_all_from_file()
        return Repo.get_all_by_discipline(self, disc_id)

    def delete(self, item):
        self.__read_all_from_file()
        Repo.delete(self, item)
        self.__write_entity_to_file()
