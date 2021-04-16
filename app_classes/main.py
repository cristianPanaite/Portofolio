from testing.teste import Teste
from entitati.entitati import Student, Disciplina, Nota
from infrastructura.repo import Repo, FileRepo
from validatoare.validare import ValidatorStudent, ValidatorDisciplina, ValidatorNote
from business.services import ServiceStudent, ServiceDisciplina, ServiceNote
from presentation.controller import Console

teste = Teste()
teste.run()
validStudent = ValidatorStudent()
validDisciplina = ValidatorDisciplina()
validNote = ValidatorNote()
repoStudent = FileRepo("studenti.txt", Student.read_student, Student.write_student)
repoDisciplina = FileRepo("discipline.txt", Disciplina.read_discipline, Disciplina.write_discipline)
repoNote = FileRepo("note.txt", Nota.read_nota, Nota.write_nota)
srvStudent = ServiceStudent(repoStudent, validStudent)
srvDisciplina = ServiceDisciplina(repoDisciplina, validDisciplina)
srvNote = ServiceNote(repoNote, validNote, repoStudent, repoDisciplina)
ui = Console(srvStudent, srvDisciplina, srvNote)
ui.run()

