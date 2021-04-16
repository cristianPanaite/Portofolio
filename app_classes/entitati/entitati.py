class Student:

    def __init__(self, stud_id, nume):
        """

        :param stud_id: integer
        :param nume: string
        """
        self.__stud_id = stud_id
        self.__nume = nume

    def get_id(self):
        return self.__stud_id

    def get_nume(self):
        return self.__nume

    def set_nume(self, value):
        """

        :param value: string
        :return:
        """
        self.__nume = value

    def __eq__(self, other):
        return self.__stud_id == other.__stud_id

    def __lt__(self, other):
        return self.get_nume() < other.get_nume()

    def __str__(self):
        return str(self.__stud_id) + " " + self.__nume

    @staticmethod
    def read_student(line):
        parts = line.split(",")
        return Student(int(parts[0].strip()), parts[1].strip())

    @staticmethod
    def write_student(student):
        return str(student.__stud_id) + "," + student.__nume


class Disciplina:

    def __init__(self, param1, param2, param3):
        self.__id = param1
        self.__materie = param2
        self.__nume = param3

    def get_id(self):
        return self.__id

    def get_materie(self):
        return self.__materie

    def get_nume(self):
        return self.__nume

    def set_materie(self, mat):
        self.__materie = mat

    def set_nume(self, nume):
        self.__nume = nume

    def __eq__(self, other):
        return self.__id == other.__id

    def __str__(self):
        return "{} {} {}".format(str(self.__id), self.__materie, self.__nume)

    @staticmethod
    def read_discipline(line):
        parts = line.split(",")
        return Disciplina(int(parts[0].strip()), parts[1].strip(), parts[2].strip())

    @staticmethod
    def write_discipline(disciplina):
        return str(disciplina.__id) + "," + disciplina.__materie + "," + disciplina.__nume


class Nota:

    def __init__(self, param1, param2, param3):
        self.__id_student = param1
        self.__val = param2
        self.__id_disciplina = param3

    def get_student(self):
        return self.__id_student

    def get_val(self):
        return self.__val

    def get_id_disciplina(self):
        return self.__id_disciplina

    def set_student(self, param1):
        self.__id_student = param1

    def set_value(self, param1):
        self.__val = param1

    def set_id_disc(self, param1):
        self.__id_disciplina = param1

    def __eq__(self, other):
        return (self.__id_student == other.__id_student) and (self.__id_disciplina == other.__id_disciplina)

    @staticmethod
    def read_nota(line):
        parts = line.split(",")
        return Nota(int(parts[0].strip()), int(parts[1].strip()), int(parts[2].strip()))

    @staticmethod
    def write_nota(nota):
        return str(nota.__id_student) + "," + str(nota.__val) + "," + str(nota.__id_disciplina)


class Student_medie(Student):
    def __init__(self, stud_id, nume):
        Student.__init__(self, stud_id, nume)
        self.suma = 0
        self.nr_disc = 0;
        self.medie = 0

    def add_nota(self, nota):
        self.suma += nota
        self.nr_disc += 1

    def make_media(self):
        self.medie = (self.suma / self.nr_disc)

    def get_media(self):
        return self.medie



















