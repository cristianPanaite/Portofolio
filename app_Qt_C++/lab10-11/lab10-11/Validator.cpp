#pragma once
#include "Validator.h"
#include <string>

string ValidException::getMessage()
{
	return msg;
}

void Validator::valideaza(Disciplina d)
{
	string err = "";
	if (d.get_cadru() == "")
		err += "Nume cadru didactic invalid!\n";
	if (d.get_denumire() == "")
		err += "Denumire invalida!\n";
	if (d.get_ore() < 1)
		err += "Numar de ore invalid\n";
	string type = d.get_tip();
	if (type != "optional" && type != "obligatoriu" && type != "facultativ")
		err += "Tip materie invalid!\n";
	if (err.size() > 0)
		throw(ValidException(err));
	return;
}
