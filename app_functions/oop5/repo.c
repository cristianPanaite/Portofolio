#pragma once
#include <stdlib.h>
#include "repo.h"

/// alocare memorie Lista

Lista* init()
{
	Lista* lista;
	lista = (Lista*)malloc(sizeof(Lista));
	lista->capacitate = 50;
	lista->lungime = 0;
	lista->list = malloc(sizeof(Tranzactie*) * 50);
	return lista;
}

/// delocare memorie Lista

void destroy_list(Lista* lista)
{
	for (int i = 0; i < lista->lungime; i++) {
		free(lista->list[i]);
	}
	free(lista);
}

/// adaugare in repo
/// t -> Tranzactie
/// lista -> Lista
/// returns -1 if the item doesn't exist
/// returns the position in list if it exists

int adauga(Tranzactie* t, Lista* lista)
{
	int err = exista(t, lista); /// err - verificare daca exista un element cu acelasi id
	if(err != -1){
		return -1;
	}
	lista->list[lista->lungime++] = t;
	return 0;
}

/// verif existenta unui item
/// return indicele pe care se afla
/// return -1 daca nu exista
int exista(Tranzactie* t, Lista* lista)
{
	for (int i = 0; i < lista->lungime; i++) {
		if (t->id == lista->list[i]->id) {
			return i;
		}
	}
	return -1;
}


/// numarul de elemente introduse

int dimensiune(Lista* l)
{
	return l->lungime;
}

/// stergere elemnt din lista

int sterge(Tranzactie* t, Lista* l)
{
	int err = exista(t, l); // verific daca exista elementul t care trebuie sters
	if (err == -1) {
		return err; /// return -1 in cazul in care nu exista
	}
	/// se muta cu o pozitie la stanga elementele de dupa pozitia pe care se afla t
	for (int i = err + 1; i < dimensiune(l); i++) {
		l->list[i - 1] = l->list[i];
	}
	/// numarul de elemente scade cu 1
	l->lungime--;
	return 0;
}

/// modificare tranzactie
/// t -> tranzactia care trebuie modificata
/// l -> lista de tranzactii
/// tnou -> forma tranzactiei dupa update

int modificare(Tranzactie* t, Lista* l, Tranzactie* tnou)
{
	int indx = exista(t, l); /// verific daca exista tranzactia
	if (indx == -1) {
		return -1;
	}

	l->list[indx] = tnou; /// modific tranzactia
	return 0;
}
