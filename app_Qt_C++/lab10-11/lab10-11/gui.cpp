#include "gui.h"

void DisciplineGUI::initGUIcmps()
{
	setLayout(lyMain);
	/// left menu
	leftLayout->addWidget(GUIdiscipline);
	leftButtons->addWidget(sort_ore);
	leftButtons->addWidget(sort_cadru);
	leftButtons->addWidget(sort_denumire);
	leftButtons->addWidget(fitrare_ore);
	leftButtons->addWidget(fitrare_cadru);
	leftButtons->addWidget(afisare);
	leftLayout->addLayout(leftButtons);
	lyMain->addLayout(leftLayout);

	///right menu
	alpha->addRow("Nume Materie:", txtMaterie);
	alpha->addRow("Numar Ore:", txtOra);
	alpha->addRow("Tip Materie:", txtTip);
	alpha->addRow("Nume Cadru:", txtCadru);
	rightLayout->addLayout(alpha);
	rightButtons->addWidget(addButton);
	rightButtons->addWidget(modifyButton);
	rightButtons->addWidget(deleteButton);
	rightButtons->addWidget(dimensionButton);
	rightLayout->addLayout(rightButtons);
	rightLayout->addWidget(undoButton);
	rightLayout->addWidget(contractButton);
	rightLayout->addWidget(exitButton);
	lyMain->addLayout(rightLayout);
	dynamicButtons->setLayout(lyBtnD);
	lyMain->addWidget(dynamicButtons);

}

void DisciplineGUI::connctions()
{
	QObject::connect(sort_ore, &QPushButton::clicked, [&]() {
			string sorted = srv.sortare_ore();
			vector<Disciplina> output = srv.formCVS_to_Disciplina(sorted);

			genereazaButoane(output);
			loadList(output);
		});
	QObject::connect(exitButton, &QPushButton::clicked, [&]() {
			close();
		});
	QObject::connect(sort_cadru, &QPushButton::clicked, [&]() {
			string sorted = srv.sortare_cadru_tip();
			vector<Disciplina> output = srv.formCVS_to_Disciplina(sorted);
			genereazaButoane(output);
			loadList(output);
		});
	QObject::connect(sort_denumire, &QPushButton::clicked, [&]() {
			string sorted = srv.sortare_denumire();
			vector<Disciplina> output = srv.formCVS_to_Disciplina(sorted);
			genereazaButoane(output);
			loadList(output);
		});
	QObject::connect(afisare, &QPushButton::clicked, [&]() {
			auto output = srv.get_all();
			loadList(output);
		});
	QObject::connect(dimensionButton, &QPushButton::clicked, [&]() {
		int dimen = srv.dimen_repo();
		QString s = QString::number(dimen);
		QMessageBox::information(nullptr, "Numar de discipline", s);
		});
	QObject::connect(undoButton, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
		}
		catch (...){
			QMessageBox::warning(nullptr, "Eroare", "Nu mai sunt actiuni pt undo");
		}
		genereazaButoane(srv.get_all());
		loadList(srv.get_all());
		});
	QObject::connect(modifyButton, &QPushButton::clicked, [&]() {
			auto materie = txtMaterie->text();
			auto ora_qs = txtOra->text();
			auto tip = txtTip->text();
			auto cadru = txtCadru->text();
			int ora;
			try{
				string ora_s = ora_qs.toStdString();
				ora = stoi(ora_s);
			}
			catch (...){
				QMessageBox::warning(nullptr, "Eroare", "Nu ai introdus valoare numerica!");
			}
			try {
				srv.modificare(materie.toStdString(), materie.toStdString(), ora, tip.toStdString(), cadru.toStdString());
			}
			catch (RepoException & e) {
				QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(e.getMessage()));
			}
			catch (ValidException & e) {
				QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(e.getMessage()));
			}
			catch (...) {
				QMessageBox::warning(nullptr, "Eroare", "Eroare");
			}

			genereazaButoane(srv.get_all());
			loadList(srv.get_all());
		});
	QObject::connect(deleteButton, &QPushButton::clicked, [&]() {
			auto materie = txtMaterie->text();
			auto ora_qs = txtOra->text();
			auto tip = txtTip->text();
			auto cadru = txtCadru->text();
			int ora;
			try{
				string ora_s = ora_qs.toStdString();
				ora = stoi(ora_s);
			}
			catch (...){
				QMessageBox::warning(nullptr, "Eroare", "Nu ai introdus valoare numerica!");
			}
			try {
				srv.stergere(materie.toStdString(), ora, tip.toStdString(), cadru.toStdString());
			}
			catch (RepoException & e) {
				QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(e.getMessage()));
			}
			catch (ValidException & e) {
				QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(e.getMessage()));
			}
			catch (...) {
				QMessageBox::warning(nullptr, "Eroare", "Eroare");
			}
			genereazaButoane(srv.get_all());
			loadList(srv.get_all());

		});
	QObject::connect(addButton, &QPushButton::clicked, [&]() {
			auto materie = txtMaterie->text();
			auto ora_qs = txtOra->text();
			auto tip = txtTip->text();
			auto cadru = txtCadru->text();
			int ora;
			try{
				string ora_s = ora_qs.toStdString();
				ora = stoi(ora_s);
			}
			catch (...){
				QMessageBox::warning(nullptr, "Eroare", "Nu ai introdus valoare numerica!");
			}
			try {
				srv.adauga(materie.toStdString(), ora, tip.toStdString(), cadru.toStdString());
			}
			catch (RepoException & e) {
				QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(e.getMessage()));
			}
			catch (ValidException & e) {
				QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(e.getMessage()));
			}
			catch (...) {
				QMessageBox::warning(nullptr, "Eroare", "Eroare");
			}
			genereazaButoane(srv.get_all());
			loadList(srv.get_all());
		});
	QObject::connect(GUIdiscipline, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = GUIdiscipline->selectedItems();
		if (sel.isEmpty()) {
			txtMaterie->setText("");
			txtOra->setText("");
			txtTip->setText("");
			txtCadru->setText("");
		}
		else {
			auto selItem = sel.at(0);
			txtMaterie->setText(selItem->text());
			auto d = srv.find(selItem->text().toStdString());
			txtOra->setText(QString::number(d.get_ore()));
			txtTip->setText(QString::fromStdString(d.get_tip()));
			txtCadru->setText(QString::fromStdString(d.get_cadru()));
		}
		});
	QObject::connect(contractButton, &QPushButton::clicked, [&]() {
		auto contractGUI = new ContractGUI { srv };
		contractGUI->show();
		});
}

void DisciplineGUI::loadList(const std::vector<Disciplina> discipline)
{
	GUIdiscipline->clear();
	for (const auto d : discipline) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.get_denumire()));
		GUIdiscipline->addItem(item);
	}
}

void DisciplineGUI::genereazaButoane(const vector<Disciplina>& d)
{
	for (auto p : dynButt) {
		delete p;
	}
	dynButt.clear();
	for (const auto& disc : d) {
		auto btn = new QPushButton{ QString::fromStdString(disc.get_denumire()) };
		dynButt.push_back(btn);
		lyBtnD->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [this, disc, btn]() {
			srv.stergere(disc.get_denumire(), disc.get_ore(), disc.get_tip(), disc.get_cadru());
			int i = 0;
			for (auto p : dynButt) {
				if (p == btn) {
					dynButt.erase(dynButt.begin() + i);
				}
				i++;
			}
			delete btn;
			loadList(srv.get_all());
		});
	}
}


void ContractGUI::initGUIcmps()
{
	setLayout(mainLy);
	nume->addRow("Nume Materie:", numeTxt);
	leftLy->addLayout(nume);
	leftLy->addWidget(addButton);
	numar->addRow("Numar de materii:", numarTxt);
	leftLy->addLayout(numar);
	leftLy->addWidget(genereaza);
	nume_fisier->addRow("Numele fisierului:", nume_fisierTxt);
	leftLy->addLayout(nume_fisier);
	leftLy->addWidget(salveaza_fisier);
	mainLy->addLayout(leftLy);
	rightLy->addWidget(contractList);
	rightButtons->addWidget(undo);
	rightButtons->addWidget(exit);
	rightLy->addLayout(rightButtons);
	mainLy->addLayout(rightLy);
}

void ContractGUI::connctions()
{
	QObject::connect(addButton, &QPushButton::clicked, [&]() {
		auto nume_materie = numeTxt->text();
		try {
			srv.adauga_contract(nume_materie.toStdString());
		}
		catch (ContractException & e) {
			QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(e.getMessage()));
		}
		loadList(srv.get_all_contract());
		});
	QObject::connect(genereaza, &QPushButton::clicked, [&]() {
		auto numar = numarTxt->text();
		try {
			string nr = numar.toStdString();
			if(nr.length() > 0)
				srv.generare_contract(stoi(nr));
			else
				QMessageBox::warning(nullptr, "Eroare", "Nu ati introdus un numar");
		}
		catch (ContractException & e) {
			QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(e.getMessage()));
		}
		loadList(srv.get_all_contract());
		});
	QObject::connect(salveaza_fisier, &QPushButton::clicked, [&]() {
		auto nume_fis = nume_fisierTxt->text();
		string name = nume_fis.toStdString();
		if (name.length() > 0) {
			srv.export_contract(name);
			QMessageBox::information(nullptr, "Succes", "Contract salvat");
		}
		else
			QMessageBox::warning(nullptr, "Eroare", "Nu ati introdus un nume de fisier");

		loadList(srv.get_all_contract());
		});
	QObject::connect(exit, &QPushButton::clicked, [&]() {
		close();
		});
	QObject::connect(undo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
		}
		catch (...) {
			QMessageBox::warning(nullptr, "Eroare", "Nu mai sunt actiuni pt undo");
		}
		loadList(srv.get_all_contract());
		});
}

void ContractGUI::loadList(const std::vector<Disciplina> discipline)
{
	contractList->clear();
	for (const auto d : discipline) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.get_denumire()));
		contractList->addItem(item);
	}
}
