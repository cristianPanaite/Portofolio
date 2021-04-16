#pragma once
#include "Service.h"
#include <map>
#include <algorithm>

using std::copy_if;
using std::distance;
using std::map;
using std::unordered_map;
using std::find;
using std::count_if;

void Service::adauga(string denumire, int ore, string tip, string cadru)
{
	double probabilitate = (rand() % 100) * 1.0 / 100;
	/*if (probabilitate < repo.getAll_err_perc())
		throw RepoException("Chaos");*/
	Disciplina d{ denumire, ore, tip, cadru };
	validator.valideaza(d);
	repo.store(d);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, d));
}

void Service::stergere(string denumire, int ore, string tip, string cadru)
{
	double probabilitate = (rand() % 100) * 1.0 / 100;
	/*if (probabilitate < repo.getAll_err_perc())
		throw RepoException("Chaos");*/
	Disciplina d{ denumire, ore, tip, cadru };
	validator.valideaza(d);
	repo.stergere(d);

	undoActions.push_back(std::make_unique<UndoStergere>(repo, d));
}

void Service::modificare(string denumire, string denumire2, int ore2, string tip2, string cadru2)
{
	double probabilitate = (rand() % 100) * 1.0 / 100;
	/*if (probabilitate < repo.getAll_err_perc())
		throw RepoException("Chaos");*/
	Disciplina d1;
	d1 = repo.cautare(denumire);
	//validator.valideaza(d1);
	Disciplina d2{ denumire2, ore2, tip2, cadru2 };
	validator.valideaza(d2);
	repo.modify(d1, d2);


	undoActions.push_back(std::make_unique<UndoMod>(repo, d2, d1));
}

int Service::cautare(string denumire, int ore, string tip, string cadru)
{
	Disciplina d{ denumire, ore, tip, cadru };
	validator.valideaza(d);
	return repo.cauta(d);
}

int Service::dimen_repo()
{
	return repo.dimen();
}

Disciplina Service::find(string materie)
{
	auto discipline = repo.getAll();
	for (auto d : discipline) {
		if (d.get_denumire() == materie)
			return d;
	}
	throw RepoException("Nu exista aceasta disciplina");
}

string Service::filtrare_ore(const int ore)
{
	auto& discipline = repo.getAll();
	int ind = 1;
	Afisator output;
	vector<Disciplina> out(discipline.size());
	auto it = copy_if(discipline.begin(), discipline.end(), out.begin(), [&](Disciplina d) {return (d.get_ore() == ore); });
	out.resize(distance(out.begin(), it));
	for (auto& disciplina : out) {
		output.set_str(disciplina.get_str_CVS() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::filtrare_cadru(string cadru)
{
	auto& discipline = repo.getAll();
	int ind = 1;
	Afisator output;
	vector<Disciplina> out(discipline.size());
	auto it = copy_if(discipline.begin(), discipline.end(), out.begin(), [&](Disciplina d) {return (d.get_cadru() == cadru); });
	out.resize(distance(out.begin(), it));
	for (auto& disciplina : out) {
		output.set_str(disciplina.get_str_CVS() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::sortare_denumire()
{
	auto discipline = repo.getAll();
	sort(discipline.begin(), discipline.end(), [](const Disciplina& a, const Disciplina& b) {
		return a.get_denumire() < b.get_denumire();
		});
	int ind = 1;
	Afisator output;
	for (auto disciplina : discipline) {
		output.set_str(disciplina.get_str_CVS() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::sortare_ore()
{
	auto discipline = repo.getAll();
	sort(discipline.begin(), discipline.end(), [](const Disciplina& a, const Disciplina& b) {
		return a.get_ore() < b.get_ore();
		});
	int ind = 1;
	Afisator output;
	for (auto disciplina : discipline) {
		output.set_str(disciplina.get_str_CVS() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::sortare_cadru_tip()
{
	auto discipline = repo.getAll();
	sort(discipline.begin(), discipline.end(), [](const Disciplina& a, const Disciplina& b) {
		if (a.get_cadru() == b.get_cadru())
			return a.get_tip() < b.get_tip();
		return a.get_cadru() < b.get_cadru();
		});
	int ind = 1;
	Afisator output;
	for (auto disciplina : discipline) {
		output.set_str(disciplina.get_str_CVS() + "\n");
		ind++;
	}
	return output.get_str();
}


string Service::afisare()
{
	auto discipline = repo.getAll();
	int ind = 1;
	Afisator output;
	for (auto disciplina : discipline) {
		output.set_str(disciplina.get_str_CVS() + "\n");
		ind++;
	}
	return output.get_str();
}

string Service::adauga_contract(string nume)
{
	contract.adauga(nume, repo);
	undoActions.push_back(std::make_unique<UndoAddContract>(contract, nume));
	return "Adaugare cu succes";
}

void Service::golire_contract()
{
	contract.goleste();
}

void Service::generare_contract(int nr)
{
	contract.generare(nr, repo);
}

void Service::export_contract(string nf)
{
	nf += ".txt";
	contract.export_contract(nf);
}

vector<Disciplina> Service::get_all()
{
	return repo.getAll();
}

vector<Disciplina> Service::get_all_contract()
{
	return contract.getAll();
}

vector<DTO> Service::statistica()
{
	//auto discipline = repo.getAll();
	////auto m_discipline = repo.getAll_map();
	//vector<string> tipuri;
	//int numar_discipline = repo.dimen();
	////map<string, DTO> statistica;
	//unordered_map<string, int> statistica;

	//for (auto element : discipline) {
	//	auto disciplina = element;
	//	/*int ok = 0;
	//	for (auto& x : tipuri) {
	//		if (x == disciplina.get_tip()) {
	//			ok = 1;
	//			break;
	//		}
	//	}
	//	if (ok == 0)
	//		tipuri.push_back(disciplina.get_tip());*/


	//	if (find(tipuri.begin(), tipuri.end(), disciplina.get_tip()) != tipuri.end()) {
	//		tipuri.push_back(disciplina.get_tip());
	//	}
	//	if (statistica.find(disciplina.get_tip()) == statistica.end()) {
	//		DTO nou{ disciplina.get_tip() };
	//		statistica.insert({ disciplina.get_tip(), nou });
	//	}
	//	else {
	//		DTO aux = statistica[disciplina.get_tip()];
	//		aux.increment();
	//		statistica[disciplina.get_tip()] = aux;
	//	}
	//}

	//for (auto x : tipuri) {
	//	int cnt = count_if(discipline.begin(), discipline.end(), [&](Disciplina& d) { return (d.get_tip() == x); });
	//	statistica.insert({ x, cnt });
	//}

	//vector <DTO> output;
	////while (it != statistica.end()) {
	////	it->second.set_procent(numar_discipline);
	////	output.push_back(it->second);
	////	it++;
	////}
	//for (auto it = statistica.begin(); it != statistica.end(); it++) {
	//	DTO obj{ it->first };
	//	obj.set_cnt(it->second);
	//	obj.set_procent(numar_discipline);
	//	output.push_back(obj);
	//}

	//return output;
	vector<DTO> v;
	return v;
}

void Service::undo()
{
	if (undoActions.empty()) {
		throw RepoException("Nu mai exista operatii");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

vector<Disciplina> Service::formCVS_to_Disciplina(string CVS)
{
	vector<Disciplina> output;
	int len = CVS.length();
	string materie = "", ores = "", tip = "", cadru = "";
	int ora = -1;
	int i = 0;
	while (i < len && CVS[i]) {
		while (CVS[i] != ',') {
			materie.push_back(CVS[i]);
			i++;
		}
		i++;
		while (CVS[i] != ',') {
			ores.push_back(CVS[i]);
			i++;
		}
		i++;
		while (CVS[i] != ',') {
			tip.push_back(CVS[i]);
			i++;
		}
		i++;
		while (CVS[i] != '\n') {
			cadru.push_back(CVS[i]);
			i++;
		}
		while (CVS[i] == '\n')
			i++;
		ora = stoi(ores);
		Disciplina d{ materie, ora, tip, cadru };
		output.push_back(d);
		ora = -1;
		materie = "";
		ores = "";
		tip = "";
		cadru = "";
	}
	return output;
}
