#pragma once
#include "entity.h"

typedef struct {
	int capacitate;
	int lungime;
	Tranzactie** list;
}Lista;

Lista* init();
void destroy_list(Lista* lista);
int adauga(Tranzactie* t, Lista* lista);
int exista(Tranzactie* t, Lista* lista);
int dimensiune(Lista* l);
int sterge(Tranzactie* t, Lista* l);
int modificare(Tranzactie* t, Lista* l, Tranzactie* tnou);