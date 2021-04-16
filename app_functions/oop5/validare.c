#pragma once
#include "validare.h"

int validare_tranzactie(Tranzactie* t, char* errors) {
	int valid = 1;
	// id > 0
	if (t->id < 0) {
		strcat(errors, "Id invalid\n");
		valid = 0;
	}
	// day cuprinsa in [1, 31]
	if (t->day < 1 || t->day > 31) {
		strcat(errors, "Zi invalida\n");
		valid = 0;
	}
	// tip conform cerintei
	if (t->type != 1 && t->type != 0) {
		strcat(errors, "Tip invalid\n");
		valid = 0;
	}
	// descriere diferita de stringul vid
	if (strlen(t->description) == 0) {
		strcat(errors, "Descriere invalida\n");
		valid = 0;
	}
	return valid;
}