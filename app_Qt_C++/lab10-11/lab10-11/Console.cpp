#pragma once
#include "Console.h"
#include <iostream>
#include <string>
using std::getline;
using std::cin;
using std::cout;
using std::string;
const int ERR = 0x3f3f3f3f;

void UI::run()
{
	while (true) {
		string cmds;
		cout << "\nMeniu\n\n\tAdaugare -> 1\n\tStergere-> 2\n\tModificare -> 3\n\tAfisare -> 4\n\tCautare -> 5\n\tFiltrare -> 6\n\tSortare -> 7\n\tStatistica -> 8\n\tContract -> 9\n\tUndo -> 10\n\tExit -> 0\n";
		cout << ">> ";
		getline(cin, cmds);
		int cmd = this->Number(cmds);
		if (cmd == ERR) {
			cout << "Comanda nu e de tip numeric!\n";
			continue;
		}
		try{
			switch (cmd)
			{
			case 0: {
				return;
			}
			case 1: {
				ui_adaugare();
				break;
			}
			case 2: {
				ui_stergere();
				break;
			}
			case 3: {
				ui_modificare();
				break;
			}
			case 4: {
				ui_afisare();
				break;
			}
			case 5: {
				ui_cautare();
				break;
			}
			case 6: {
				ui_filtrare();
				break;
			}
			case 7:{
				ui_sortare();
				break;
			}
			case 8:{
				ui_statistica();
				break;
			}
			case 9:{
				ui_contract();
				break;
			}
			case 10: {
				ui_undo();
					break;
			}
			default: {
				cout << "Comanda invalida!\n";
				continue;
			}
			}
		}
		catch (ValidException & e) {
			cout << "\n Eroare la validare:\n";
			cout << e.getMessage() << "\n";
		}
		catch (RepoException & e) {
			cout << "\n Eroare la repository:\n";
			cout << e.getMessage() << "\n";
		}
	}
}

void UI::ui_adaugare()
{
	cout << "\n\nMeniu Adaugare\n";
	cout << "Format: string (denumire) integer (numar de ore) string (tip: obligatoriu/facultativ/optional) string (cadru didactic)\n";
	string denumire, tip, cadru, ora_s;
	int ora;
	cout << "Denumire: ";
	getline(cin,denumire);
	cout << "Numar de ore: ";
	getline(cin, ora_s);
	cout << "Tip materie: ";
	getline(cin, tip);
	cout << "Cadru didatic: ";
	getline(cin, cadru);

	ora = Number(ora_s);
	if (ora == ERR)
		cout << "Ora -> not numeric type\n";
	srv.adauga(denumire, ora, tip, cadru);
	cout << "\nAdaugare cu succes\n";
}

void UI::ui_stergere()
{
	cout << "\n\nMeniu Stergere\n";
	cout << "Format: string (denumire) integer (numar de ore) string (tip: obligatoriu/facultativ/optional) string (cadru didactic)\n";
	string denumire, tip, cadru, ora_s;
	int ora;
	cout << "Denumire: ";
	getline(cin, denumire);
	cout << "Numar de ore: ";
	getline(cin, ora_s);
	cout << "Tip materie: ";
	getline(cin, tip);
	cout << "Cadru didatic: ";
	getline(cin, cadru);
	ora = Number(ora_s);
	if (ora == ERR)
		cout << "Ora -> not numeric type\n";
	srv.stergere(denumire, ora, tip, cadru);
	cout << "\nStergere cu succes!\n";
}

void UI::ui_modificare()
{
	cout << "\n\nMeniu Modificare\n";
	cout << "Format: string (denumire) integer (numar de ore) string (tip: obligatoriu/facultativ/optional) string (cadru didactic)\n";
	string denumire, tip, cadru, ora_s;
	int ora;
	cout << "Disciplina curenta:\n";
	cout << "Denumire: ";
	cout << "Denumire: ";
	getline(cin, denumire);
	cout << "Numar de ore: ";
	getline(cin, ora_s);
	cout << "Tip materie: ";
	getline(cin, tip);
	cout << "Cadru didatic: ";
	getline(cin, cadru);
	ora = Number(ora_s);
	if (ora == ERR)
		cout << "Ora -> not numeric type\n";
	string denumire2, tip2, cadru2, ora_s2;
	int ora2;
	cout << "Discipina modificata:\n";
	cout << "Denumire: ";
	cout << "Denumire: ";
	getline(cin, denumire);
	cout << "Numar de ore: ";
	getline(cin, ora_s);
	cout << "Tip materie: ";
	getline(cin, tip);
	cout << "Cadru didatic: ";
	getline(cin, cadru);
	ora2 = Number(ora_s2);
	if (ora2 == ERR)
		cout << "Ora -> not numeric type\n";
	srv.modificare(denumire, denumire2, ora2, tip2, cadru2);
	cout << "\nModificare cu succes\n";
}

void UI::ui_afisare()
{
	cout << "\n\nMeniu Afisare\n";
	cout << srv.afisare();

}

void UI::ui_cautare()
{
	cout << "\n\nMeniu Cautare\n";
	cout << "Format: string (denumire) integer (numar de ore) string (tip: obligatoriu/facultativ/optional) string (cadru didactic)\n";
	string denumire, tip, cadru, ora_s;
	int ora;
	cout << "Denumire: ";
	getline(cin, denumire);
	cout << "Numar de ore: ";
	getline(cin, ora_s);
	cout << "Tip materie: ";
	getline(cin, tip);
	cout << "Cadru didatic: ";
	getline(cin, cadru);
	ora = Number(ora_s);
	if (ora == ERR)
		cout << "Ora -> not numeric type\n";
	cout << "Disciplina se afla pe pozitia : " << srv.cautare(denumire, ora, tip, cadru) + 1 << " in lista\n";
}

void UI::ui_filtrare()
{
	cout << "\n\nMeniu Filtrare\n";
	while (true) {
		string cmds;
		cout << "\n\tNumar de ore -> 1\n\tCadru didactic -> 2\n\tBack -> 0\n";
		cout << ">> ";
		getline(cin, cmds);
		int cmd = this->Number(cmds);
		if (cmd == ERR) {
			cout << "Comanda nu e de tip numeric!\n";
			continue;
		}
		try {
			switch (cmd)
			{
			case 0: {
				return;
			}
			case 1: {
				ui_filtrare_ore();
				break;
			}
			case 2: {
				ui_filtrare_cadru();
				break;
			}
			default: {
				cout << "Comanda invalida!\n";
				continue;
			}
			}
		}
		catch (ValidException & e) {
			cout << "\n Eroare la validare:\n";
			cout << e.getMessage() << "\n";
		}
		catch (RepoException & e) {
			cout << "\n Eroare la repository:\n";
			cout << e.getMessage() << "\n";
		}
	}
}

void UI::ui_filtrare_ore()
{
	cout << "\n\nMeniu Filtrare Ore\n";
	cout << "Format: integer (numarul de ore)\n";
	string ora_s;
	int ora;
	cout << "Numar de ore: ";
	getline(cin, ora_s);
	ora = Number(ora_s);
	if (ora == ERR)
		cout << "Ora -> not numeric type\n";
	cout << srv.filtrare_ore(ora);

}

void UI::ui_filtrare_cadru()
{
	cout << "\n\nMeniu Filtrare Cadre\n";
	cout << "Format: string (nume cadru)\n";
	string cadru;
	cout << "Nume de cadru: ";
	getline(cin, cadru);
	cout << srv.filtrare_cadru(cadru);
}

void UI::ui_sortare()
{
	cout << "\n\nMeniu Sortare\n";
	while (true) {
		string cmds;
		cout << "\n\tDenumire -> 1\n\tOre -> 2\n\tCadru + tip -> 3\n\tBack -> 0\n";
		cout << ">> ";
		getline(cin, cmds);
		int cmd = this->Number(cmds);
		if (cmd == ERR) {
			cout << "Comanda nu e de tip numeric!\n";
			continue;
		}
		try {
			switch (cmd)
			{
			case 0: {
				return;
			}
			case 1: {
				ui_sortare_denumire();
				break;
			}
			case 2: {
				ui_sortare_ore();
				break;
			}
			case 3: {
				ui_sortare_cadru_tip();
				break;
			}
			default: {
				cout << "Comanda invalida!\n";
				continue;
			}
			}
		}
		catch (ValidException & e) {
			cout << "\n Eroare la validare:\n";
			cout << e.getMessage() << "\n";
		}
		catch (RepoException & e) {
			cout << "\n Eroare la repository:\n";
			cout << e.getMessage() << "\n";
		}
	}
}

void UI::ui_sortare_denumire()
{
	cout << "\n\nMeniu Sortare Denumire\n";
	cout << srv.sortare_denumire();
}

void UI::ui_sortare_ore()
{
	cout << "\n\nMeniu Sortare ore\n";
	cout << srv.sortare_ore();
}

void UI::ui_sortare_cadru_tip()
{
	cout << "\n\nMeniu Sortare Cadru + Tip\n";
	cout << srv.sortare_cadru_tip();
}

void UI::ui_statistica()
{
	cout << "Statistica:\n";
	vector<DTO> stas = srv.statistica();
	for (auto s : stas) {
		cout << s.get_str();
	}
}

void UI::ui_contract()
{
	while (true) {
	cout << "\n\nMeniu Contract\n";
		string cmds;
		cout << "\n\tAdaugare disciplina in contract -> 1\n\tGoleste -> 2\n\tGenereaza -> 3\n\tExporta -> 4\n\tBack -> 0\n";
		cout << ">> ";
		getline(cin, cmds);
		int cmd = this->Number(cmds);
		if (cmd == ERR) {
			cout << "Comanda nu e de tip numeric!\n";
			continue;
		}
		try {
			switch (cmd)
			{
			case 0: {
				return;
			}
			case 1: {
				ui_adauga_contract();
				break;
			}
			case 2: {
				ui_goleste_contract();
				break;
			}
			case 3: {
				ui_genereaza_contract();
				break;
			}
			case 4: {
				ui_export();
				break;
			}
			default: {
				cout << "Comanda invalida!\n";
				continue;
			}
			}
		}
		catch (ValidException & e) {
			cout << "\n Eroare la validare:\n";
			cout << e.getMessage() << "\n";
		}
		catch (RepoException & e) {
			cout << "\n Eroare la repository:\n";
			cout << e.getMessage() << "\n";
		}
		catch (ContractException & e) {
			cout << "\n Eroare la contract:\n";
			cout << e.getMessage() << "\n";
		}
	}
}

void UI::ui_adauga_contract()
{
	cout << "\n\nMeniu Adaugare Disciplina in Contract\n";
	string disc;
	cout << "Nume disciplina: ";
	getline(cin, disc);
	cout << srv.adauga_contract(disc);
}

void UI::ui_goleste_contract()
{
	srv.golire_contract();
	cout << "Golire cu succes\n";
}

void UI::ui_genereaza_contract()
{
	cout << "\n\nMeniu Generare Contract\n";
	string number;

	cout << "Numar de discipline: ";
	getline(cin, number);
	int nr = Number(number);
	if (nr == ERR) {
		cout << "Ora -> not numeric type\n";
		return;
	}
	srv.generare_contract(nr);
}

void UI::ui_export()
{
	cout << "\n\nMeniu export\n";
	cout << "Introdu numele fisierului:";
	string nume_fisier;
	getline(cin, nume_fisier);
	srv.export_contract(nume_fisier);
	cout << "Export cu succes!\n";

}

void UI::ui_undo()
{
	srv.undo();
}

int UI::Number(string s)
{
	if (s.size() == 0) {
		return ERR;
	}
	int x = 0;
	int semn = 1;
	int i = 0;
	if (s[0] == '-') {
		semn = -1;
		i = 1;
	}
	int len = s.size();
	if (len == 0) {
		return -1;
	}
	for (; i < len; i++) {
		if (s[i] >= '0' && s[i] <= '9')
			x = x * 10 + (s[i] - '0');
		else
			return ERR;
	}
	return semn * x;
}
