#pragma once
#include <vector>
#include <string>
#include "Disciplina.h"
#include "Lista.h"
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <cstdlib>

using std::to_string;
using std::string;
using std::vector;
using std::string;
using std::unordered_map;
using std::transform;

class RepoException {
	string msg;
public:
	RepoException(string s) : msg{ s } {};
	string getMessage() {
		return msg;
	}
};
class ContractException {
	string msg;
public:
	ContractException(string s) : msg{ s } {};
	string getMessage() {
		return msg;
	}
};

class REPO {
protected:
	double err_perc;
public:
	virtual void store(const Disciplina& d) = 0;
	virtual void stergere(const Disciplina& d) = 0;
	virtual void modify(const Disciplina& d1, const Disciplina& d) = 0;
	virtual const vector<Disciplina> getAll() = 0;
	virtual int cauta(const Disciplina& d) = 0;
	virtual Disciplina cautare(string s) = 0;
	virtual int dimen() = 0;
	virtual Disciplina from_position(int x) = 0;

	virtual double getAll_err_perc();
};

class Repo: public REPO {
protected:
	//unordered_map<int, Disciplina> discipline;
	//int index;

	vector<Disciplina> discipline;
public:
	Repo() = default;
	Repo(double verr_perc);
	virtual void store(const Disciplina& d);
	virtual void stergere(const Disciplina& d);
	virtual int cauta(const Disciplina& d);
	virtual Disciplina cautare(string s);
	virtual void modify(const Disciplina& d1, const Disciplina& d);
	virtual const vector<Disciplina> getAll();
	//const unordered_map<int, Disciplina> getAll_map();
	virtual int dimen();
	virtual Disciplina from_position(int x);
};

class FileRepo :public Repo {
private:
	string fName;
	void load_from_file();
	void write_to_file();
public:
	FileRepo(string fname, double err_perc) : Repo(err_perc), fName{ fname } {}
	~FileRepo() = default;
	void store(const Disciplina& d) override;
	void stergere(const Disciplina& d) override;
	int cauta(const Disciplina& d) override;
	void modify(const Disciplina& d1, const Disciplina& d) override;
	const vector<Disciplina> getAll() override;
	int dimen() override;
	Disciplina from_position(int x) override;
	void clear_file();

};

class Contract {
private:
	vector<Disciplina> contract;
public:
	Contract() = default;
	Contract(const Contract& ot) = default;
	~Contract() = default;
	int goleste();
	int adauga(string d, REPO& r);
	int nr_materii();
	void sterge(string d);
	int contract_cauta(Disciplina d);
	int generare(int numar, REPO& rep);
	int export_contract(string nume_fisier);
	vector<Disciplina> getAll();
	string to_string();

};

