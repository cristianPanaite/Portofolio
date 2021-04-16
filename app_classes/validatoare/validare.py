from exceptii.exceptii import ValidError


class ValidatorDisciplina:
    def valideaza_disciplina(self, disc):
        errors = ""

        if disc.get_id() < 0:
            errors += "id invalid!\n"
        if disc.get_nume() == "":
            errors += "nume invalid!\n"
        if disc.get_materie() == "":
            errors += "materie invalida!\n"

        if len(errors) > 0:
            raise ValidError(errors)


class ValidatorNote:
    def valideaza_note(self, nota, exist_stud, exist_disc):
        errors = ""

        if (nota.get_val() <= 0):
            errors += "nota nu poate fi negativa\n"
        if (nota.get_val() > 10):
            errors += "nota nu poate fi mai mare decat 10\n"
        if exist_stud == False:
            errors += "nota nu poate fi data la un student inexistent\n"
        if exist_disc == False:
            errors += "nota nu poate fi data la o materie inexistenta\n"

        if len(errors) > 0:
            raise ValidError(errors)


class ValidatorStudent:

    def valideaza_student(self, stud):
        errors = ""

        if stud.get_id() < 0:
            errors += "id invalid!\n"
        if stud.get_nume() == "":
            errors += "nume invalid!\n"

        if len(errors) > 0:
            raise ValidError(errors)



