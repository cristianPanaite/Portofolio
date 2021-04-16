#include "Teste.h"
#include "Disciplina.h"
#include "Validator.h"
#include "Repository.h"
#include "Service.h"
#include <cassert>

void teste_entitate() {
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina d1{ "amate", 10, "facultativ", "Andreea" };
	assert(d.get_denumire() == "mate");
	assert(d.get_ore() == 15);
	assert(d.get_tip() == "obligatoriu");
	assert(d.get_cadru() == "Maria Bulbuc");
	d.set_denumire("info");
	d.set_ore(20);
	d.set_tip("optional");
	d.set_cadru("Ion");
	assert(d.get_denumire() == "info");
	assert(d.get_ore() == 20);
	assert(d.get_tip() == "optional");
	assert(d.get_cadru() == "Ion");
	assert(d.get_str().size() > 0);

}

void teste_validare() {
	Disciplina d_ok("mate", 15, "obligatoriu", "Maria Bulbuc");
	Disciplina d_denumire("", 15, "obligatoriu", "Maria Bulbuc");
	Disciplina d_ore("mate", -1, "obligatoriu", "Maria Bulbuc");
	Disciplina d_tip("mate", 15, "", "Maria Bulbuc");
	Disciplina d_cadre("mate", 15, "obligatoriu", "");
	Validator valid;
	valid.valideaza(d_ok);
	try {
		valid.valideaza(d_denumire);
		assert(false);
	}
	catch (ValidException & e) {
		assert(e.getMessage().size() > 0);
	}
	try {
		valid.valideaza(d_ore);
		assert(false);
	}
	catch (ValidException & e) {
		assert(e.getMessage().size() > 0);
	}
	try {
		valid.valideaza(d_tip);
		assert(false);
	}
	catch (ValidException & e) {
		assert(e.getMessage().size() > 0);
	}
	try {
		valid.valideaza(d_cadre);
		assert(false);
	}
	catch (ValidException & e) {
		assert(e.getMessage().size() > 0);
	}


}

void teste_repo_store() {
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Repo r;
	assert(r.dimen() == 0);
	r.store(d);
	try {
		r.store(d);
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
	assert(r.dimen() == 1);

}

void teste_repo_modify() {
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina d1{ "info", 12, "facultativ", "Maria" };
	Repo r;
	r.store(d);
	r.modify(d, d1);
	try {
		r.modify(d, d1);
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_repo_delete() {
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina d1{ "info", 20, "obligatoriu", "Mayoyoa Bulbuc" };
	Repo r;
	r.store(d);
	r.store(d1);
	r.stergere(d1);
	assert(r.dimen() == 1);
	try {
		r.stergere(d1);
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_repo_cautare() {
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina d1{ "info", 12, "facultativ", "Maria" };
	Repo r;
	r.store(d);
	assert(r.cauta(d) == 0);
	try {
		int poz = r.cauta(d1);
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_adaugare() {
	Repo r;
	Validator v;
	Contract c;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("info", 12, "facultativ", "Maria");
	try {
		s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_stergere() {
	Repo r;
	Validator v;
	Contract c;
	Service s{ r, v, c};
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("info", 12, "facultativ", "Maria");
	s.stergere("mate", 15, "obligatoriu", "Maria Bulbuc");
	try {
		s.stergere("mate", 15, "obligatoriu", "Maria Bulbuc");
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_modificare() {
	Repo r;
	Validator v;
	Contract c;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.modificare("mate", "info", 12, "facultativ", "Maria");
	try {
		s.modificare("mate", "info", 12, "facultativ", "Maria");
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_afisare() {
	Repo r;
	Validator v;
	Contract c;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("info", 12, "facultativ", "Maria");
	string out = s.afisare();
	assert(out.size() > 0);
}

void teste_srv_cautare() {
	Repo r;
	Validator v;
	Contract c;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.cautare("mate", 15, "obligatoriu", "Maria Bulbuc");
	try {
		s.cautare("mateA", 15, "obligatoriu", "Maria Bulbucita");
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_srv_filtrare_ore() {
	Repo r;
	Validator v;
	Contract c;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("info", 12, "facultativ", "Maria");
	string out = s.filtrare_ore(15);
	assert(out.size() > 0);
}

void teste_srv_filtrare_cadru() {
	Repo r;
	Validator v;
	Contract c;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("info", 12, "facultativ", "Maria");
	string out = s.filtrare_cadru("Maria");
	assert(out.size() > 0);
}

void teste_srv_statistica() {
	Repo r;
	Validator v;
	Contract c;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("infoa", 12, "facultativ", "Maria");
	s.adauga("info", 12, "optional", "John");
	s.adauga("romana", 10, "optional", "Ion");
	
	auto test = s.statistica();
	assert(test.size() == 3);
	for (auto s : test) {
		string x = s.get_str();
		assert(x.size() > 0);
	}
}

void teste_contract() {
	Contract cont;
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina d1{ "info", 12, "facultativ", "Maria" };
	Disciplina d2{ "indsafo", 10, "facultativ", "Maridasda" };
	string D = "mate";
	string D1 = "info";
	string D2 = "indsafo";
	Repo r;
	r.store(d1);
	r.store(d);
	assert(cont.goleste() == 0);
	assert(cont.adauga(D, r) == 1);
	assert(cont.adauga(D1, r) == 2);
	assert(cont.contract_cauta(d) == 1);
	assert(cont.contract_cauta(d2) == 0);
	assert(cont.goleste() == 0);
	r.store(d2);
	try{
		cont.generare(5, r);
		assert (false);
	}
	catch (ContractException & e) {
		assert(e.getMessage().size() > 0);
	}
	cont.goleste();
	assert(cont.generare(2, r) == 2);

	string x = "haha";
	try {
		cont.adauga(x, r);
		assert(false);
	}
	catch (ContractException & e) {
		assert(e.getMessage().size() > 0);
	}

	Disciplina dd{ "mate1", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina dd1{ "info1", 12, "facultativ", "Maria" };
	Disciplina dd2{ "religie", 10, "facultativ", "Maridasda" };
	Disciplina dd3{ "bio", 10, "facultativ", "Maridasda" };
	Disciplina dd4{ "fizique", 10, "facultativ", "Maridasda" };
	r.store(dd);
	r.store(dd1);
	r.store(dd2);
	r.store(dd3);
	r.store(dd4);
	cont.generare(3, r);
	assert(cont.export_contract("teste.txt") == 3);
}

void test_store_f() {
	FileRepo r("fileteste.txt", 0);
	r.clear_file();
	Disciplina dd{ "mate1", 15, "obligatoriu", "Maria Bulbuc" };
	r.store(dd);
	try
	{
		r.store(dd);
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
	assert(r.dimen() == 1);
}
void teste_repo_modify_f() {
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina d1{ "info", 12, "facultativ", "Maria" };

	FileRepo r("fileteste.txt", 0);
	r.clear_file();
	r.store(d);
	r.modify(d, d1);
	try {
		r.modify(d, d1);
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_repo_delete_f() {
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina d1{ "info", 20, "obligatoriu", "Mayoyoa Bulbuc" };

	FileRepo r("fileteste.txt", 0);
	r.clear_file();
	r.store(d);
	r.store(d1);
	r.stergere(d1);
	assert(r.dimen() == 1);
	try {
		r.stergere(d1);
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_repo_cautare_f() {
	Disciplina d{ "mate", 15, "obligatoriu", "Maria Bulbuc" };
	Disciplina d1{ "info", 12, "facultativ", "Maria" };

	FileRepo r("fileteste.txt", 0);
	r.clear_file();
	r.store(d);
	assert(r.cauta(d) == 0);
	try {
		int poz = r.cauta(d1);
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_fisier() {
	test_store_f();
	teste_repo_cautare_f();
	teste_repo_delete_f();
	teste_repo_modify_f();

}

void teste_undo_add() {
	Repo r;
	Contract c;
	Validator v;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("info", 12, "facultativ", "Maria");
	assert(s.dimen_repo() == 2);
	s.undo();
	assert(s.dimen_repo() == 1);
	s.undo();
	assert(s.dimen_repo() == 0);

	try {
		s.undo();
		assert(false);
	}
	catch (RepoException & e) {
		assert (e.getMessage().size() > 0);
	}


}
void teste_undo_stergere() {
	Repo r;
	Contract c;
	Validator v;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("info", 12, "facultativ", "Maria");
	assert(s.dimen_repo() == 2);
	s.stergere("info", 12, "facultativ", "Maria");
	assert(s.dimen_repo() == 1);
	s.undo();
	assert(s.dimen_repo() == 2);
}

void teste_undo_modificare() {
	Repo r;
	Contract c;
	Validator v;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.modificare("mate", "info", 12, "facultativ", "Maria");
	try {
		s.modificare("mate", "info", 12, "facultativ", "Maria");
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
	s.undo();
	try {
		s.modificare("info", "mate", 15, "obligatoriu", "Maria Bulbuc");
		assert(false);
	}
	catch (RepoException & e) {
		assert(e.getMessage().size() > 0);
	}
}

void teste_undo_adaugare_contract() {
	Repo r;
	Contract c;
	Validator v;
	Service s{ r, v, c };
	s.adauga("mate", 15, "obligatoriu", "Maria Bulbuc");
	s.adauga("info", 12, "facultativ", "Maria");
	string ss = "mate";
	s.adauga_contract(ss);
	ss = "info";
	s.adauga_contract(ss);
	assert(c.nr_materii() == 2);
	s.undo();
	assert(c.nr_materii() == 1);


}

void teste_undo() {
	teste_undo_add();
	teste_undo_stergere();
	teste_undo_modificare();
	teste_undo_adaugare_contract();
}
string printstring(int n)
{
	char letters[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
	'r','s','t','u','v','w','x',
	'y','z' };
	string ran = "";
	for (int i = 0; i < n; i++)
		ran = ran + letters[rand() % 26];
	return ran;
}
void teste_monkey() {
	ofstream out("chaos1.txt");
	FileRepo r("chaos.txt", 0.5);
	r.clear_file();
	Contract c;
	Validator v;
	Service s{ r, v, c };

	for (int i = 0; i < 20; i++) {
		try {
			int ore = rand();
			string materie = printstring(150);
			string tip = "facultativ";
			string prof = printstring(20);
			s.adauga(materie, ore, tip, prof);
			out << "Succes\n";
		}
		catch (RepoException & e) {
			assert(e.getMessage().size() > 0);
			out << "FAIL\n";
		}
	}
	out.close();

}

void teste_fromCVS_to_vector() {
	Repo r;
	Contract c;
	Validator v;
	Service s{ r, v, c };
	string str = "mate,5,optional,maria\ninfo,7,facultativ,andrei\n";
	vector<Disciplina> discipline = s.formCVS_to_Disciplina(str);
	assert(discipline[0].get_denumire() == "mate");
	assert(discipline[0].get_ore() == 5);
	assert(discipline[0].get_tip() == "optional");
	assert(discipline[0].get_cadru() == "maria");
	assert(discipline[1].get_denumire() == "info");
	assert(discipline[1].get_ore() == 7);
	assert(discipline[1].get_tip() == "facultativ");
	assert(discipline[1].get_cadru() == "andrei");
}

void Teste::teste_run() {
	teste_entitate();
	teste_validare();
	teste_repo_store();
	teste_repo_modify();
	teste_repo_delete();
	teste_repo_cautare();
	teste_srv_adaugare();
	teste_srv_stergere();
	teste_srv_modificare();
	teste_srv_afisare();
	teste_srv_cautare();
	teste_srv_filtrare_ore();
	teste_srv_filtrare_cadru();
	//teste_srv_statistica();
	teste_contract();
	teste_fisier();
	teste_undo();
	//teste_monkey();
	teste_fromCVS_to_vector();
}