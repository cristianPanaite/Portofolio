from entitati.entitati import Student, Disciplina, Nota, Student_medie
import string
import random
from exceptii.exceptii import RepoError


class ServiceDisciplina:

    def __init__(self, repoDisciplina, validDisciplina):
        """

        :param repoDisciplina: repo object
        :param validDisciplina: ValidatorDisciplina object
        """
        self.__repoDisciplina = repoDisciplina
        self.__validDisciplina = validDisciplina

    def adauga_disciplina(self, id_disc, materie, nume):
        """
        :param id_disc: integer
        :param materie: string
        :param nume: string
        create discipline, validate it and then add to repo
        """
        disciplina = Disciplina(id_disc, materie, nume)
        self.__validDisciplina.valideaza_disciplina(disciplina)
        self.__repoDisciplina.adauga(disciplina)

    def modify_materie(self, d_id, materie_change):
        """

        :param d_id: integer
        :param materie_change: string
        search a discipline with d_id id and then change the name of discipline with the string materie_change
        """
        cheie = Disciplina(d_id, "NONE", "NONE")
        self.__validDisciplina.valideaza_disciplina(cheie)
        self.__repoDisciplina.modifica_materie(cheie, materie_change)

    def modify_nume(self, d_id, name_change):
        """

        :param d_id: integer
        :param name_change: string
        search a discipline with d_id id and then change the name of teacher with the string name_change
        """
        cheie = Disciplina(d_id, "NONE", "NONE")
        self.__validDisciplina.valideaza_disciplina(cheie)
        self.__repoDisciplina.modifica(cheie, name_change)

    def delete_disciplina(self, d_id):
        """
        :param s_id: integer
        search a discipline with d_id id and then delete it
        """
        cheie = Disciplina(d_id, "NONE", "NONE")
        self.__validDisciplina.valideaza_disciplina(cheie)
        self.__repoDisciplina.delete(cheie)

    def caut_disciplina(self, d_id):
        """
        :param d_id: integer
        :return: the discipline found by id
        """
        cheie = Disciplina(d_id, None, None)
        self.__validDisciplina.valideaza_disciplina(cheie)
        return self.__repoDisciplina.cauta(cheie)

    def get_disciplines(self):
        """
        get all disciplines
        :return: list
        """
        return self.__repoDisciplina.get_all()

    def get_string_disc(self, disc):
        return str(disc)

    def create_random_discipline(self):
        """
        create a random discipline with the length of string equals to 10
        :return: a discipline object
        """
        string_len = 10
        letters = string.ascii_letters
        disc_name = ''.join(random.choice(letters) for i in range(string_len))
        disc_materie = ''.join(random.choice(letters) for i in range(string_len))
        disc_id = random.randint(1, 100)
        return Disciplina(disc_id, disc_materie, disc_name)

    def create_random_disciplines(self, number_of_disciplines):
        """
        create a number of diciplines
        :param number_of_disciplines: integer
        """
        for n in range(number_of_disciplines):
            discipline = self.create_random_discipline()
            try:
                self.__repoDisciplina.adauga(discipline)
            except RepoError:
                n -= 1


class ServiceStudent:

    def __init__(self, repoStudent, validStudent):
        """
        init function
        :param repoStudent: repo object
        :param validStudent: ValidatorStudent object
        """
        self.__repoStudent = repoStudent
        self.__validStudent = validStudent

    def adauga_stud(self, stud_id, nume):
        """

        :param stud_id: integer
        :param nume: string
        :return:
        """
        student = Student(stud_id, nume)
        self.__validStudent.valideaza_student(student)
        self.__repoStudent.adauga(student)

    def delete_student(self, stud_id):
        """

        :param stud_id: integer
        :return:
        """
        cheie = Student(stud_id, "None")
        self.__validStudent.valideaza_student(cheie)
        self.__repoStudent.delete(cheie)

    def modify_student(self, s_id, nume_change):
        """

        :param s_id: integer
        :param nume_change: string
        :return:
        """
        cheie = Student(s_id, "NONE")
        self.__validStudent.valideaza_student(cheie)
        self.__repoStudent.modifica(cheie, nume_change)

    def cauta_student(self, s_id):
        """

        :param s_id: integer
        :return:
        """
        cheie = Student(s_id, None)
        self.__validStudent.valideaza_student(cheie)
        return self.__repoStudent.cauta(cheie)

    def get_students(self):
        """
        get all students
        :return: list
        """
        return self.__repoStudent.get_all()

    def create_random_student(self):
        """

        :return: Student
        """
        string_len = 10
        letters = string.ascii_letters
        st_name = ''.join(random.choice(letters) for i in range(string_len))
        st_id = random.randint(1, 100)
        return Student(st_id, st_name)

    def create_random_students(self, number_of_students):
        """

        :param number_of_students: integer
        """
        for n in range(number_of_students):
            student = self.create_random_student()
            try:
                self.__repoStudent.adauga(student)
            except RepoError:
                n -= 1


class ServiceNote:

    def __init__(self, repoNote, validNote, repoStudent, repoDisciplina):
        """

        :param repoNote: repo object
        :param validNote: ValidatorNota object
        :param repoStudent: repo object
        :param repoDisciplina: repo object
        """
        self.__repoNote = repoNote
        self.__validNote = validNote
        self.__repoStudent = repoStudent
        self.__repoDisciplina = repoDisciplina

    def adauga_nota(self, stud_id, disc_id, val):
        """

        :param stud_id: integer
        :param disc_id: integer
        :param val: integer
        :return:
        """
        nota = Nota(stud_id, val, disc_id)
        stud = Student(stud_id, None)
        disc = Disciplina(disc_id, None, None)
        self.__validNote.valideaza_note(nota, self.__repoStudent.exista(stud), self.__repoDisciplina.exista(disc))
        self.__repoNote.adauga(nota)

    def print_note_student(self, stud_id):
        """

        :param stud_id: integer
        :return: string to output in controller
        """
        output = ""
        cheie = Student(stud_id, None)
        # Omega(1), O(n)

        student = self.__repoStudent.cauta(cheie)
        output += str(student)
        output += "\n"

        note_student = self.__repoNote.get_all_by_student(student.get_id())
        # O(len(note_student))
        for nota in note_student:
            output += "Nota {} la disciplina ".format(nota.get_val())
            cheie_disc = Disciplina(nota.get_id_disciplina(), None, None)
            disc = self.__repoDisciplina.cauta(cheie_disc)
            output += str(disc)
            output += "\n"

        return output

    def print_note_materie_ord_nume(self, disc_id):

        """
            disc_id : integer
            return: string for output
        """
        cheie_disc = Disciplina(disc_id, None, None)
        note = self.__repoNote.get_all()
        list_with_disciplines = []
        for nota in note:
            if nota.get_id_disciplina() == cheie_disc.get_id():
                list_with_disciplines.append(nota)
        # sortare
        for i in range(len(list_with_disciplines) - 1):
            for j in range(i + 1, len(list_with_disciplines)):
                cstud1 = Student(list_with_disciplines[i].get_student(), None)
                stud1 = self.__repoStudent.cauta(cstud1)
                cstud2 = Student(list_with_disciplines[j].get_student(), None)
                stud2 = self.__repoStudent.cauta(cstud2)
                if (stud1.get_nume() >= stud2.get_nume()):
                    list_with_disciplines[i], list_with_disciplines[j] = list_with_disciplines[j], list_with_disciplines[i]

        output = ""

        for nota in list_with_disciplines:
            cstud = Student(nota.get_student(), None)
            stud = self.__repoStudent.cauta(cstud)
            output += stud.get_nume() + " " + str(nota.get_val()) + "\n"

        return output

    def print_note_materie_ord_nota(self, disc_id):
        """
            disc_id : integer
            return: string for output
        """

        cheie_disc = Disciplina(disc_id, None, None)
        note = self.__repoNote.get_all()
        list_with_disciplines = []
        for nota in note:
            if nota.get_id_disciplina() == cheie_disc.get_id():
                list_with_disciplines.append(nota)
        # sortare

        #for i in range(len(list_with_disciplines) - 1):
        #   for j in range(i + 1, len(list_with_disciplines)):
        #       nota1 = list_with_disciplines[i].get_val()
        #       nota2 = list_with_disciplines[j].get_val()
        #       if (nota1 >= nota2):
        #           list_with_disciplines[i], list_with_disciplines[j] = list_with_disciplines[j], list_with_disciplines[i]

        any_sort(list_with_disciplines, key=lambda x:x.get_val(), cmp = cmp)
        output = ""

        for nota in list_with_disciplines:
            cstud = Student(nota.get_student(), None)
            stud = self.__repoStudent.cauta(cstud)
            output += stud.get_nume() + " " + str(nota.get_val()) + "\n"

        return output
    # O(len(l))
    def make_media_f(self, l, i):
        if i == len(l):
            return
        l[i].make_media()
        self.make_media_f(l, i + 1)

    def media(self):
        list_stud = []
        for nota in self.__repoNote.get_all():
            cstud1 = Student(nota.get_student(), None)
            stud = self.__repoStudent.cauta(cstud1)
            if stud not in list_stud:
                stud_med = Student_medie(stud.get_id(), stud.get_nume())
                stud_med.add_nota(nota.get_val())
                list_stud.append(stud_med)
            else:
                i = list_stud.index(stud)
                list_stud[i].add_nota(nota.get_val())

        self.make_media_f(list_stud, 0)

        for i in range(len(list_stud) - 1):
           for j in range(len(list_stud)):
               if (list_stud[i].get_media() > list_stud[j].get_media()):
                   list_stud[i], list_stud[j] = list_stud[j], list_stud[i]


        procent = int((20 * self.__repoStudent.size()) / 100)

        output = ""

        for i in range(procent):
            cstud = Student(list_stud[i].get_id(), None)
            stud = self.__repoStudent.cauta(cstud)
            output += stud.get_nume() + " media: " + str(list_stud[i].get_media())

        return output

    def promovati(self):
        promovare = {}
        discipline = self.__repoDisciplina.get_all()

        for disc in discipline:
            studenti_cu_nota_la_disc = []
            studenti_cu_nota_la_disc = self.__repoNote.get_all_by_discipline(disc.get_id())
            promovare[str(disc.get_id())] = [0, len(studenti_cu_nota_la_disc)]
            for nota in studenti_cu_nota_la_disc:
                if nota.get_val() >= 5:
                    promovare[str(disc.get_id())][0] += 1

        output = ""

        for key in promovare.keys():
            if promovare[key][1] != 0:
                disc = self.__repoDisciplina.cauta(Disciplina(int(key), None, None))
                procent = (promovare[key][0] / promovare[key][1]) * 100
                output += "Promovabilitatea la disciplina " + str(disc) + "are promovabilitate de: " + str(
                    procent) + "%\n"

        return output


def partition(arr, low, high):
    i = (low - 1)  # index of smaller element
    pivot = arr[high]  # pivot

    for j in range(low, high):

        # If current element is smaller than the pivot
        if arr[j] < pivot:
            # increment index of smaller element
            i = i + 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return (i + 1)


def quickSort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quickSort(arr, low, pi - 1)
        quickSort(arr, pi + 1, high)


def gnomeSort(arr, n):
    index = 0
    while index < n:
        if index == 0:
            index = index + 1
        if arr[index] >= arr[index - 1]:
            index = index + 1
        else:
            arr[index], arr[index - 1] = arr[index - 1], arr[index]
            index = index - 1

    return arr


def any_sort(iterable, *, key=lambda x:x, reverse=False, cmp):
    index = 0
    n = len(iterable)
    while index < n:
        if index == 0:
            index = index + 1
        if reverse == False:
            if cmp(key(iterable[index]), key(iterable[index - 1])):
                index = index + 1
            else:
                iterable[index], iterable[index - 1] = iterable[index - 1], iterable[index]
                index = index - 1
        else:
            if key(iterable[index]) < key(iterable[index - 1]):
                index = index + 1
            else:
                iterable[index], iterable[index - 1] = iterable[index - 1], iterable[index]
                index = index - 1


    return iterable

def cmp(x, y):
    if x > y:
        return 1
    if x < y:
        return -1
    if x == y:
        return 0