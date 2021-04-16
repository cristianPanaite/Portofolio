#pragma once
#include "entity.h"
#include <stdlib.h>
#define NULL 0

/// Trazacitie
/*
	// int : id > 0
	// int : day cuprinsa in [1, 31]
	// int : tip conform cerintei
	// int : suma
	// char*: descriere diferita de stringul vid
*/

Tranzactie* creeare_tranzactie(int id, int day, int sum, int type, char* desc)
{
	Tranzactie* tr;
	tr = (Tranzactie*)malloc(sizeof(Tranzactie));
	tr->id = id;
	tr->day = day;
	tr->sum = sum;
	tr->type = type;
	tr->description = (char*)malloc(strlen(desc) + 1);
	strcpy(tr->description, desc);
	return tr;
}


// dealoca memoria alocata la init
void distrugere_tranzactie(Tranzactie* t) {
	free(t->description);
	free(t);
}

int get_id(Tranzactie* t)
{
	return t->id;
}

int get_day(Tranzactie* t)
{
	return t->day;
}

int get_suma(Tranzactie* t)
{
	return t->sum;
}

int get_type(Tranzactie* t)
{
	return t->type;
}

char* get_desc(Tranzactie* t)
{
	return t->description;
}

void set_day(Tranzactie* t, int x)
{
	t->day = x;
}

void set_sum(Tranzactie* t, int x)
{
	t->sum = x;
}

void set_type(Tranzactie* t, int x)
{
	t->type = x;
}

void set_desc(Tranzactie* t, char* x)
{
	free(t->description);
	t->description = (char*)malloc(strlen(x) + 1);
	strcpy(t->description, x);
}
