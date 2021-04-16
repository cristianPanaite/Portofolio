#include "Repository.h"


Repo::Repo(double verr_perc)
{
	err_perc = verr_perc;
	discipline = {};
}

void Repo::store(const Disciplina& d)
{

	for (const Disciplina& dc : discipline) {
		if (dc == d) {
			throw RepoException("Disciplina deja introdusa\n");
		}
	}
	discipline.push_back(d);
	/*
	for (auto it = discipline.begin(); it != discipline.end(); it++) {
		auto disc = it->second;
		if(disc == d)
			throw RepoException("Disciplina deja introdusa\n");
	}
	discipline.insert({ index++, d });*/
}

void Repo::stergere(const Disciplina& d)
{

	int i = 0;
	for (const Disciplina& dc : discipline) {
		if (d == dc) {
			discipline.erase(discipline.begin() + i);
			return;
		}
		i++;
	}
	throw RepoException("Disciplina inexistenta\n");
	/*for (auto it = discipline.begin(); it != discipline.end(); it++) {
		auto dc = it->second;
		if (d == dc) {
			discipline.erase(it);
			return;
		}
	}
	throw RepoException("Disciplina inexistenta\n");*/
	
}

int Repo::cauta(const Disciplina& d)
{

	int i = 0;
	for (const Disciplina& dc : discipline) {
		if (d == dc) {
			return i;
		}
		i++;
	}
	throw RepoException("Disciplina inexistenta\n");

	/*int i = 0;
	for (auto it = discipline.begin(); it != discipline.end(); it++) {
		auto dc = it->second;
		if (d == dc) {
			return i;
		}
		i++;
	}
	throw RepoException("Disciplina inexistenta\n");*/
}

Disciplina Repo::cautare(string s)
{
	for (auto& d : discipline) {
		if (d.get_denumire() == s)
			return d;
	}
	throw RepoException("Elementul nu exista cu aceasta cheie");
}

void Repo::modify(const Disciplina& d1, const Disciplina& d)
{
	int idx = this->cauta(d1);
	discipline[idx] = d;
}


const vector<Disciplina> Repo::getAll()
{
	/*vector <std::pair<int, Disciplina>> v;
	transform(discipline.begin(), discipline.end(), std::back_inserter(v), [](const std::pair<int, Disciplina>& p) { return p; });
	vector <Disciplina> out;
	for (auto x : v) {
		out.push_back(x.second);
	}*/

	return discipline;
}

//const unordered_map<int, Disciplina> Repo::getAll_map()
//{
//	return discipline;
//}

int Repo::dimen()
{
	return discipline.size();
}

Disciplina Repo::from_position(int x)
{
	return discipline[x];
}

int Contract::goleste()
{
	contract.clear();
	return 0;
}

int Contract::adauga(string d, REPO& r)
{
	auto& discipline = r.getAll();
	vector<Disciplina> out(discipline.size());
	auto it = copy_if(discipline.begin(), discipline.end(), out.begin(), [&](Disciplina disc) {return (disc.get_denumire() == d); });
	out.resize(distance(out.begin(), it));
	if (out.size() == 0)
		throw ContractException("Disciplina inexistenta!\n");
	contract.push_back(out[0]);
	return contract.size();
}

int Contract::nr_materii()
{
	return contract.size();
}

void Contract::sterge(string d)
{
	int i = 0;
	for (auto& elem : contract) {
		if (elem.get_denumire() == d) {
			contract.erase(contract.begin() + i);
		}
		i++;
	}
}

int Contract::contract_cauta(Disciplina d)
{
	for (auto& dis : contract)
		if (dis.get_denumire() == d.get_denumire())
			return 1;
	return 0;
}

int Contract::generare(int numar, REPO& rep)
{
	goleste();
	if (numar > rep.dimen())
		throw ContractException("Numarul de discipline din contract e mai mare decat numarul de numarul de discipline disponibile!\n");
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, rep.dimen() - 1);
	int i = 0;
	while (numar--) {
		int rndNr = dist(mt);
		Disciplina d = rep.from_position(rndNr);
		while (contract_cauta(d) == 1) {
			rndNr = dist(mt);
			Disciplina d = rep.from_position(rndNr);
			i++;
			if (i > 50)
				break;
		}
		contract.push_back(d);
	}
	return contract.size();
}

int Contract::export_contract(string nume_fisier)
{
	ofstream file (nume_fisier);

	file << this->to_string();

	file.close();
	return contract.size();
}

vector<Disciplina> Contract::getAll()
{
	return contract;
}


string Contract::to_string()
{
	Afisator out;
	for (auto& dis : contract) {
		out.set_str(dis.get_str_CVS());
	}
	return out.get_str();
}

vector<string> parse(string s) {
	vector <string> out;
	string current = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ',') {
			out.push_back(current);
			current = "";
		}
		else {
			current += s[i];
		}
	}
	out.push_back(current);
	return out;
}

void FileRepo::load_from_file()
{

	discipline.clear();
	std::ifstream in(fName);
	if (!in.is_open())
		throw RepoException("Nu am reusit sa deschid fisie	rul:" + fName);
	while (!in.eof()) {
		string s;
		in >> s;
		if (s.size() == 0)
			break;
		vector <string> vect = parse(s);
		if (vect.size() != 4)
			break;
		Disciplina d{ vect[0], stoi(vect[1]), vect[2], vect[3] };
		discipline.push_back(d);
	}
	in.close();
}

void FileRepo::write_to_file()
{

	std::ofstream out(fName);
	if(!out.is_open())
		throw RepoException("Nu am reusit sa deschid fisierul:" + fName);
	for (auto d : discipline) {
		out << d.get_str_CVS();
	}
}

void FileRepo::store(const Disciplina& d)
{
	load_from_file();
	Repo::store(d);
	write_to_file();
}

void FileRepo::stergere(const Disciplina& d)
{
	load_from_file();
	Repo::stergere(d);
	write_to_file();
}

int FileRepo::cauta(const Disciplina& d)
{
	load_from_file();
	return Repo::cauta(d);
}

void FileRepo::modify(const Disciplina& d1, const Disciplina& d)
{
	load_from_file();
	Repo::modify(d1, d);
	write_to_file();
}

const vector<Disciplina> FileRepo::getAll()
{
	load_from_file();
	return Repo::getAll();
}

int FileRepo::dimen()
{
	load_from_file();
	return Repo::dimen();
}

Disciplina FileRepo::from_position(int x)
{
	load_from_file();
	return Repo::from_position(x);
}

void FileRepo::clear_file()
{
	discipline.clear();
	write_to_file();
}

double REPO::getAll_err_perc()
{
	return err_perc;
}
