#include "Teste.h"
#include "Repository.h"
#include "Service.h"
#include "Validator.h"
#include "gui.h"

int main(int argc, char *argv[])
{
	Teste test;
	test.teste_run();
	{
		QApplication a(argc, argv);
		FileRepo repo("fileRepo.txt", 0);
		Validator valid;
		Contract contract;
		Service serv{ repo, valid, contract };

		DisciplineGUI gui{ serv };
		gui.show();
		a.exec();
	}
	return 0;
}
