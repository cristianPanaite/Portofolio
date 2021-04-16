#include "Disciplina.h"
#include <string>

using std::to_string;

string Disciplina::get_denumire() const
{
	return denumire;
}

int Disciplina::get_ore() const
{
	return ore;
}

string Disciplina::get_tip() const
{
	return tip;
}

string Disciplina::get_cadru() const
{
	return cadru;
}

void Disciplina::set_denumire(string s) 
{
	denumire = s;
}

void Disciplina::set_ore(int s)
{
	ore = s;
}

void Disciplina::set_tip(string s)
{
	tip = s;
}

void Disciplina::set_cadru(string s)
{
	cadru = s;
}

string Disciplina::get_str()
{
	string s = "";
	s += "Denumire : " + denumire + "; ";
	string ora_s = std::to_string(ore);
	s += "Numar de ore: " + ora_s + "; ";
	s += "Tip: " + tip + "; ";
	s += "Cadru didactic: " + cadru + " ";

	return s;
}

string Disciplina::get_str_CVS()
{
	return denumire + "," + std::to_string(ore) + "," + tip + "," + cadru + "\n";
}

bool operator==(const Disciplina& a, const Disciplina& b)
{
	return(a.denumire == b.denumire);
}

void Afisator::set_str(string s)
{
	output += s;
}

string Afisator::get_str()
{
	return output;
}

void DTO::increment()
{
	cnt++;
}

void DTO::set_cnt(int x)
{
	cnt = x;
}

void DTO::set_procent(int all)
{
	procent = (cnt * 1.0 / all) * 100;
}

string DTO::get_str()
{
	string output = categorie + " " + to_string(procent) + "%\n";
	return output;
}
