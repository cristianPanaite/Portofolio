#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>	
#include <QListWidget>
#include <QTextEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QMessageBox>
#include "Repository.h"
#include "Service.h"
#include "Validator.h"
#include <string>

class ContractGUI : public QWidget {
	Service& srv;
	QHBoxLayout* mainLy = new QHBoxLayout;
	QVBoxLayout* leftLy = new QVBoxLayout;
	QFormLayout* nume = new QFormLayout;
	QLineEdit* numeTxt = new QLineEdit;
	QPushButton* addButton = new QPushButton ("&Adauga");
	QFormLayout* numar = new QFormLayout;
	QLineEdit* numarTxt = new QLineEdit;
	QPushButton* genereaza = new QPushButton ("&Genereaza");
	QFormLayout* nume_fisier = new QFormLayout;
	QLineEdit* nume_fisierTxt = new QLineEdit;
	QPushButton* salveaza_fisier = new QPushButton ("&Salveaza in fisier");
	QVBoxLayout* rightLy = new QVBoxLayout;
	QListWidget* contractList = new QListWidget;
	QHBoxLayout* rightButtons = new QHBoxLayout;
	QPushButton* exit = new QPushButton ("&Exit");
	QPushButton* undo = new QPushButton ("&Undo");

	void initGUIcmps();
	void connctions();
	void loadList(const std::vector<Disciplina> discipline);
public:
	ContractGUI(Service& srv) : srv{ srv } {
		initGUIcmps();
		connctions();
		loadList(srv.get_all_contract());
	};
};

class DisciplineGUI : public QWidget {
	Service& srv;
	QHBoxLayout* lyMain = new QHBoxLayout;
	///left menu
	QVBoxLayout* leftLayout = new QVBoxLayout;
	QListWidget* GUIdiscipline = new QListWidget;
	QHBoxLayout* leftButtons = new QHBoxLayout;
	QPushButton* sort_ore = new QPushButton{ "&Sortare ore" };
	QPushButton* sort_cadru = new QPushButton{ "&Sortare cadru" };
	QPushButton* sort_denumire = new QPushButton{ "&Sortare denumire" };
	QPushButton* fitrare_ore = new QPushButton{ "&Filtrare ore" };
	QPushButton* fitrare_cadru = new QPushButton{ "&Filtrare cadru" };
	QPushButton* afisare = new QPushButton{ "&Afisare" };
	///right menu
	QVBoxLayout* rightLayout = new QVBoxLayout;
	QFormLayout* alpha = new QFormLayout;
	QHBoxLayout* rightButtons = new QHBoxLayout;
	///
	QPushButton* addButton = new QPushButton{ "&Adaugare" };
	///
	QLineEdit* txtMaterie = new QLineEdit;
	QLineEdit* txtOra = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtCadru = new QLineEdit;
	///
	QPushButton* modifyButton = new QPushButton{ "&Modificare" };
	QPushButton* deleteButton = new QPushButton{ "&Stergere" };
	QPushButton* dimensionButton = new QPushButton{ "&Dimensiune" };
	///
	QPushButton* undoButton = new QPushButton{ "&Undo" };
	QPushButton* contractButton = new QPushButton{ "&Contract" }; /// new window
	QPushButton* exitButton = new QPushButton{ "&Exit" }; /// new window

	QVBoxLayout* lyBtnD = new QVBoxLayout;
	QWidget* dynamicButtons = new QWidget;
	vector <QPushButton*> dynButt;


	void initGUIcmps();
	void connctions();
	void loadList(const std::vector<Disciplina> discipline);
	void genereazaButoane(const vector<Disciplina>& d);
public:
	DisciplineGUI(Service& srv) : srv{ srv } {
		initGUIcmps();
		connctions();
		loadList(srv.get_all());
		genereazaButoane(srv.get_all());
	};
};