#pragma once

#include "entity.h"
#include "Teste.h"
#include "validare.h"
#include "repo.h"
#include <assert.h>
#include <string.h>

void creeare_entitate() {
	char x[20] = "Abracadabra";
	Tranzactie* t = creeare_tranzactie(0, 5, 20, 0, x);
	assert(get_id(t) == 0);
	assert(get_day(t) == 5);
	assert(get_suma(t) == 20);
	assert(get_type(t) == 0);
	assert(strcmp(get_desc(t), "Abracadabra") == 0);
	strcpy(x, "HAHA");
	set_day(t, 8);
	set_sum(t, 15);
	set_type(t, 1);
	set_desc(t, x);

	assert(get_id(t) == 0);
	assert(get_day(t) == 8);
	assert(get_suma(t) == 15);
	assert(get_type(t) == 1);
	assert(strcmp(get_desc(t), "HAHA") == 0);
}

void validare() {
	char x[20] = "Abracadabra";
	char y[1] = "";
	Tranzactie* tok = creeare_tranzactie(0, 5, 20, 0, x);
	Tranzactie* tid = creeare_tranzactie(-1, 5, 20, 0, x);
	Tranzactie* tday_mare = creeare_tranzactie(0, 0, 20, 0, x);
	Tranzactie* tday_mic = creeare_tranzactie(0, 32, 20, 0, x);
	Tranzactie* ttype = creeare_tranzactie(0, 5, 20, 5, x);
	Tranzactie* tdesc = creeare_tranzactie(0, 5, 20, 0, y);
	char error[50] = "";
	assert(validare_tranzactie(tok, error) == 1);
	assert(strcmp(error, "") == 0);
	assert(validare_tranzactie(tid, error) == 0);
	assert(strcmp(error, "Id invalid\n") == 0);
	strcpy(error, "");
	assert(validare_tranzactie(tday_mare, error) == 0);
	strcpy(error, "");
	assert(validare_tranzactie(tday_mic, error) == 0);
	strcpy(error, "");
	assert(validare_tranzactie(ttype, error) == 0);
	strcpy(error, "");
	assert(validare_tranzactie(tdesc, error) == 0);
	strcpy(error, "");

}

void adaugare() {
	Lista* l = init();
	
	assert(dimensiune(l) == 0);

	char x[20] = "Abracadabra";
	Tranzactie* t = creeare_tranzactie(0, 5, 20, 0, x);
	assert(adauga(t, l) == 0);
	assert(dimensiune(l) != 0);
	assert(adauga(t, l) == -1);

	destroy_list(l);

}

void stergere() {
	Lista* l = init();
	assert(dimensiune(l) == 0);

	char x[20] = "Abracadabra";
	Tranzactie* t1 = creeare_tranzactie(0, 5, 20, 0, x);
	adauga(t1, l);
	Tranzactie* t2 = creeare_tranzactie(1, 6, 25, 0, x);
	adauga(t2, l);
	Tranzactie* t3 = creeare_tranzactie(2, 8, 23, 0, x);
	adauga(t3, l);

	Tranzactie* t4 = creeare_tranzactie(4, 8, 23, 0, x);

	assert(dimensiune(l) == 3);
	assert(sterge(t4, l) == -1);
	assert(sterge(t2, l) != -1);
	assert(dimensiune(l) == 2);

}

void modif() {
	Lista* l = init();
	assert(dimensiune(l) == 0);

	char x[20] = "Abracadabra";
	Tranzactie* t1 = creeare_tranzactie(0, 5, 20, 0, x);	
	adauga(t1, l);
	Tranzactie* t2 = creeare_tranzactie(1, 6, 25, 0, x);
	adauga(t2, l);
	Tranzactie* t3 = creeare_tranzactie(2, 8, 23, 0, x);
	adauga(t3, l);

	char y[20] = "";
	Tranzactie* tOld = creeare_tranzactie(1, 0, 0, 0, y);
	Tranzactie* tOld2 = creeare_tranzactie(5, 0, 0, 0, y);
	Tranzactie* t4 = creeare_tranzactie(1, 8, 23, 0, x);
	assert(modificare(tOld, l, t4) == 0);
	assert(modificare(tOld2, l, t4) == -1);
}

void run_teste() {
	creeare_entitate();
	validare();
	adaugare();
	stergere();
	modif();
}
