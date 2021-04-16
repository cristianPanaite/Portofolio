#pragma once
#include <string>

using std::string;

class Disciplina {

private:

	string denumire, tip, cadru;
	int ore;

public:

	string get_denumire() const;
	int get_ore() const;
	string get_tip() const;
	string get_cadru() const;

	void set_denumire(string s);
	void set_ore(int s);
	void set_tip(string s);
	void set_cadru(string s);

	string get_str();
	string get_str_CVS();
	
	Disciplina() = default;
	Disciplina(string denumire, int ore, string tip, string cadru) : denumire{ denumire }, ore{ ore }, tip{ tip }, cadru{ cadru }{};
	Disciplina(const Disciplina& ot) = default;

	friend bool operator== (const Disciplina& a, const Disciplina& b);
};

class Afisator {
private:
	string output;
public:
	Afisator() = default;
	~Afisator() = default;
	Afisator(const Afisator& ot) = default;
	void set_str(string s);
	string get_str();
};

class DTO {
private:
	string categorie;
	int cnt;
	double procent;
public:
	DTO() = default;
	DTO(string key) : categorie{ key }, cnt{ 1 }, procent{ 0 }{};
	void increment();
	void set_cnt(int x);
	void set_procent(int all);
	string get_str();
};