#pragma once
#include "Repository.h"
#include "Validator.h"
#include "Disciplina.h"
#include "undo.h"
#include <string>
#include <vector>
#include <algorithm>
using std::sort;
using std::vector;
using std::unique_ptr;
using std::string;

class Service {
private:
	REPO& repo;
	Validator& validator;
	Contract& contract;
	vector<unique_ptr<ActiuneUndo>> undoActions;
public:
	Service(REPO& r, Validator& v, Contract& c) : repo{ r }, validator{ v }, contract{ c }{};
	~Service() = default;
	void adauga(string denumire, int ore, string tip, string cadru);
	void stergere(string denumire, int ore, string tip, string cadru);
	void modificare(string denumire, string denumire2, int ore2, string tip2, string cadru2);
	int cautare(string denumire, int ore, string tip, string cadru);
	int dimen_repo();
	Disciplina find(string materie);
	string filtrare_ore(const int ore);
	string filtrare_cadru(string cadru);
	string sortare_denumire();
	string sortare_ore();
	string sortare_cadru_tip();
	string afisare();
	string adauga_contract(string nume);
	void golire_contract();
	void generare_contract(int nr);
	void export_contract(string nf);
	vector<Disciplina> get_all();
	vector<Disciplina> get_all_contract();
	vector<DTO> statistica();
	void undo();
	vector<Disciplina> formCVS_to_Disciplina(string CVS);
};