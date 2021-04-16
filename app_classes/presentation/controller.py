from exceptii.exceptii import ValidError, RepoError


class Console:

    def __ui_adauga_stud(self, params):
        if len(params) != 2:
            raise ValueError("Nr parametrii invalid. Trebuie sa fie 2")
        s_id = int(params[0])
        nume = params[1]
        self.__srvStudent.adauga_stud(s_id, nume)

    def __ui_print_students(self, params):
        students = self.__srvStudent.get_students()
        if students == None:
            students = []
        if len(students) == 0:
            raise RepoError("lista goala")
        for student in students:
            print(str(student))

    def __ui_delete_student(self, params):
        if len(params) != 1:
            raise ValueError("nr parametrii invalid. trebuie sa fie unul")
        s_id = int(params[0])
        self.__srvStudent.delete_student(s_id)

    def __ui_mofify_student(self, params):
        if len(params) != 2:
            raise ValueError("Nr parametrii invalid. Trebuie sa fie 2")
        s_id = int(params[0])
        nume_change = params[1]
        self.__srvStudent.modify_student(s_id, nume_change)

    def __ui_adauga_disciplina(self, params):
        if len(params) != 3:
            raise ValueError("nr parametri invalid. Trebuie sa fie 3")
        id_disc = int(params[0])
        materie = params[1]
        nume = params[2]

        self.__srvDisciplina.adauga_disciplina(id_disc, materie, nume)

    def __ui_print_disciplines(self, params):
        disciplines = self.__srvDisciplina.get_disciplines()
        if len(disciplines) == 0:
            raise RepoError("Lista este goala")
        for disc in disciplines:
            print(str(disc))

    def __ui_modify_materie(self, params):
        if len(params) != 2:
            raise ValueError("Nr parametrii invalid. Trebuie sa fie 2")
        d_id = int(params[0])
        materie_change = params[1]
        self.__srvDisciplina.modify_materie(d_id, materie_change)

    def __ui_modify_name(self, params):
        if len(params) != 2:
            raise ValueError("Nr parametrii invalid. Trebuie sa fie 2")
        d_id = int(params[0])
        name_change = params[1]
        self.__srvDisciplina.modify_nume(d_id, name_change)

    def __ui_delete_discipline(self, params):
        if len(params) != 1:
            raise ValueError("nr parametrii invalid. trebuie sa fie unul")
        d_id = int(params[0])
        self.__srvDisciplina.delete_disciplina(d_id)

    def __ui_caut_stud(self, params):
        if len(params) != 1:
            raise ValueError("nr parametrii invalid. trebuie sa fie unul")
        s_id = int(params[0])

        student = self.__srvStudent.cauta_student(s_id)
        print(student)

    def __ui_caut_disc(self, params):
        if len(params) != 1:
            raise ValueError("nr parametrii invalid. trebuie sa fie unul")
        d_id = int(params[0])

        disciplina = self.__srvDisciplina.caut_disciplina(d_id)
        print(disciplina)

    def __ui_adauga_nota(self, params):
        if len(params) != 3:
            raise ValueError("nr parametrii invalid. trebuie sa fie 3")

        stud_id = int(params[0])
        disc_id = int(params[1])
        nota = int(params[2])

        nota = self.__srvNote.adauga_nota(stud_id, disc_id, nota)

    def __ui_print_note_student(self, param):
        if len(param) != 1:
            raise ValidError("nr parametrii invalid. trebuie sa fie unul care sa repreezinte id-ul studentului")
        stud_id = int(param[0])

        print(self.__srvNote.print_note_student(stud_id))

    def __ui_random_students(self, param):
        if len(param) != 1:
            raise ValidError("nr parametrii invalid. trebuie sa fie unul care sa repreezinte numarul de studenti")
        nr_studs = int(param[0])
        self.__srvStudent.create_random_students(nr_studs)

    def __ui_random_disciplines(self, param):
        if len(param) != 1:
            raise ValidError("nr parametrii invalid. trebuie sa fie unul care sa repreezinte numarul de discipline")
        nr_disc = int(param[0])
        self.__srvDisciplina.create_random_disciplines(nr_disc)

    def __ui_sort_nume_disc(self, param):
        if len(param) != 1:
            raise ValueError("Numar de parametrii invalid. Trebuie sa fie unul")

        id_disc = int(param[0])
        disc = self.__srvDisciplina.caut_disciplina(id_disc)
        print(self.__srvDisciplina.get_string_disc(disc))
        print(self.__srvNote.print_note_materie_ord_nume(id_disc))

    def __ui_sort_nota_disc(self, param):
        if len(param) != 1:
            raise ValueError("Numar de parametrii invalid. Trebuie sa fie unul")

        id_disc = int(param[0])
        disc = self.__srvDisciplina.caut_disciplina(id_disc)
        print(self.__srvDisciplina.get_string_disc(disc))
        print(self.__srvNote.print_note_materie_ord_nota(id_disc))

    def __ui_primii(self, param):
        if len(param) != 0:
            raise ValueError("nu trebuie parametrii")

        print(self.__srvNote.media())

    def __ui_promovare(self, param):
        if len(param) != 0:
            raise ValueError("nu trebuie parametrii")

        print(self.__srvNote.promovati())

    def __init__(self, srvStudent, srvDisciplina, srvNote):
        self.__srvStudent = srvStudent
        self.__srvDisciplina = srvDisciplina
        self.__srvNote = srvNote
        self.__commands = {
            "add_stud": self.__ui_adauga_stud,
            "print_stud": self.__ui_print_students,
            "delete_stud": self.__ui_delete_student,
            "modify_stud": self.__ui_mofify_student,
            "add_disc": self.__ui_adauga_disciplina,
            "print_disc": self.__ui_print_disciplines,
            "modify_disc_materie": self.__ui_modify_materie,
            "modify_disc_name": self.__ui_modify_name,
            "delete_disc": self.__ui_delete_discipline,
            "caut_stud": self.__ui_caut_stud,
            "caut_disc": self.__ui_caut_disc,
            "add_nota": self.__ui_adauga_nota,
            "print_nota_stud": self.__ui_print_note_student,
            "random_stud": self.__ui_random_students,
            "random_disc": self.__ui_random_disciplines,
            "sort_nume_disc": self.__ui_sort_nume_disc,
            "sort_nota_disc": self.__ui_sort_nota_disc,
            "primii": self.__ui_primii,
            "promovare": self.__ui_promovare
        }

    def run(self):
        while True:
            cmd = input(">>>")
            if cmd == "exit":
                return
            cmd = cmd.strip()
            params = cmd.split()
            if len(params) == 0:
                continue
            nume_cmd = params[0]
            params = params[1:]
            if nume_cmd in self.__commands:
                try:
                    self.__commands[nume_cmd](params)
                except ValueError as ve:
                    print("Eroare valori numerice:\n" + str(ve))
                except ValidError as vale:
                    print("Eroare de validare:\n" + str(vale))
                except RepoError as re:
                    print("Eroare de repo:\n" + str(re))
            else:
                print("comanda invalida!")







