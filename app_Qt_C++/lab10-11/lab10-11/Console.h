#pragma once
#include "Service.h"

class UI {
private:
	Service& srv;
	void ui_adaugare();
	void ui_stergere();
	void ui_modificare();
	void ui_afisare();
	void ui_cautare();
	void ui_filtrare();
	void ui_filtrare_ore();
	void ui_filtrare_cadru();
	void ui_sortare();
	void ui_sortare_denumire();
	void ui_sortare_ore();
	void ui_sortare_cadru_tip();
	void ui_statistica();
	void ui_contract();
	void ui_adauga_contract();
	void ui_goleste_contract();
	void ui_genereaza_contract();
	void ui_export();
	void ui_undo();
	int Number(string s);
public:
	UI(Service& s) : srv{ s } {};
	void run();
	
};