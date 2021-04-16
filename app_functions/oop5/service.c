#pragma once
#include "service.h"
#include "entity.h"
#include "validare.h"
#include "repo.h"
#include "Console.h"

/// functie service de adaugare a unei tranzactii

void srv_add_tranzactie(int id, int day, int sum, int type, char* desc, char* error, Lista* lista)
{
	Tranzactie* t = creeare_tranzactie(id, day, sum, type, desc); /// creearea tranzactiei
	if (validare_tranzactie(t, error) != 1) { /// validare date
		return;
	}
	int ok = 0; /// variabila care memoreaza succesul/esecul adaugarii
	ok = adauga(t, lista); 
	if (ok == -1) {
		strcat(error, "Item-ul exista deja in lista\n");
	}
	return;
}

/// functie service de modificare a unei tranzactii

void srv_modifica_tranzactie(int id, int day, int sum, int type, char* desc, char* error, Lista* lista)
{
	Tranzactie* tOld = creeare_tranzactie(id, 0, 0, 0, desc); /// creeare tranzactie cheie
	Tranzactie* tNew = creeare_tranzactie(id, day, sum, type, desc); /// tranzactia cu noile date
	if (validare_tranzactie(tNew, error) != 1) { /// verificarea validitatii noii tranzactii
		return;
	}
	int ok = modificare(tOld, lista, tNew); // variabila care memoreaza succesul / esecul modificarii
	if (ok == -1) {
		strcat(error, "Item-ul nu exista in lista\n");
	}
	return;
}

/// functie service de stergere a unei tranzactii

void srv_stergere(int id, Lista* lista, char* errors)
{
	char y[2] = "";
	Tranzactie* t = creeare_tranzactie(id, 0, 0, 0, y); /// creeare tranzactie cheie
	int ok = sterge(t, lista); /// variabila care memoreaza succesul / esecul stergerii
	if (ok == -1)
		strcat(errors, "Itemul nu exista.\n");
	return;

}

void srv_viz_type(int type, Lista* l, char* errors)
{
	int ok = 0;
	for (int i = 0; i < l->lungime; i++) {
		if (l->list[i]->type == type) {
			ok = 1;
			printf("%d: Id: %d, Day: %d, Sum: %d, Type: %d, Description: %s\n", i, l->list[i]->id, l->list[i]->day, l->list[i]->sum, l->list[i]->type, l->list[i]->description);
		}
	}
	if (ok == 0) {
		strcat(errors, "Nu exista tranzactii de acest tip\n");
	}
	return;
}

void srv_viz_sum_mai_mare(int sum, Lista* l, char* errors)
{
	int ok = 0;
	for (int i = 0; i < l->lungime; i++) {
		if (l->list[i]->sum > sum) {
			ok = 1;
			printf("%d: Id: %d, Day: %d, Sum: %d, Type: %d, Description: %s\n", i, l->list[i]->id, l->list[i]->day, l->list[i]->sum, l->list[i]->type, l->list[i]->description);
		}
	}
	if (ok == 0) {
		strcat(errors, "\nNu exista tranzactii cu suma mai mare decat cea introdusa\n");
	}
	return;
}

void srv_viz_sum_mai_mic(int sum, Lista* l, char* errors)
{
	int ok = 0;
	for (int i = 0; i < l->lungime; i++) {
		if (l->list[i]->sum < sum) {
			ok = 1;
			printf("%d: Id: %d, Day: %d, Sum: %d, Type: %d, Description: %s\n", i, l->list[i]->id, l->list[i]->day, l->list[i]->sum, l->list[i]->type, l->list[i]->description);
		}
	}
	if (ok == 0) {
		strcat(errors, "\nNu exista tranzactii cu suma mai mica decat cea introdusa\n");
	}
	return;
}

void srv_viz_zi(int sens, Lista* l, char* errors)
{
	Tranzactie** copie_lista;
	copie_lista = malloc(sizeof(Tranzactie*) * l->lungime);
	for (int i = 0; i < l->lungime; i++)
	{
		copie_lista[i] = l->list[i];
	}
	if (sens == 1) {
		for (int i = 0; i < l->lungime - 1; i++) {
			for (int j = i + 1; j < l->lungime; j++) {
				if (copie_lista[i]->day > copie_lista[j]->day) {
					Tranzactie* aux = copie_lista[i];
					copie_lista[i] = copie_lista[j];
					copie_lista[j] = aux;
				}
			}
		}
	}
	else {
		for (int i = 0; i < l->lungime - 1; i++) {
			for (int j = i + 1; j < l->lungime; j++) {
				if (copie_lista[i]->day < copie_lista[j]->day) {
					Tranzactie* aux = copie_lista[i];
					copie_lista[i] = copie_lista[j];
					copie_lista[j] = aux;
				}
			}
		}
	}
	for (int i = 0; i < l->lungime; i++) {
		printf("%d: Id: %d, Day: %d, Sum: %d, Type: %d, Description: %s\n", i, copie_lista[i]->id, copie_lista[i]->day, copie_lista[i]->sum, copie_lista[i]->type, copie_lista[i]->description);
	}
	for (int i = 0; i < l->lungime; i++) {
		free(copie_lista[i]);
	}
	free(copie_lista);
	return;
}

void srv_viz_suma(int sens, Lista* l, char* errors)
{
	Tranzactie** copie_lista;
	copie_lista = malloc(sizeof(Tranzactie) * l->lungime);
	for (int i = 0; i < l->lungime; i++)
	{
		copie_lista[i] = l->list[i];
	}
	if (sens == 1) {
		for (int i = 0; i < l->lungime - 1; i++) {
			for (int j = i + 1; j < l->lungime; j++) {
				if (copie_lista[i]->sum > copie_lista[j]->sum) {
					Tranzactie* aux = copie_lista[i];
					copie_lista[i] = copie_lista[j];
					copie_lista[j] = aux;
				}
			}
		}
	}
	else {
		for (int i = 0; i < l->lungime - 1; i++) {
			for (int j = i + 1; j < l->lungime; j++) {
				if (copie_lista[i]->sum < copie_lista[j]->sum) {
					Tranzactie* aux = copie_lista[i];
					copie_lista[i] = copie_lista[j];
					copie_lista[j] = aux;
				}
			}
		}
	}
	for (int i = 0; i < l->lungime; i++) {
		printf("%d: Id: %d, Day: %d, Sum: %d, Type: %d, Description: %s\n", i, copie_lista[i]->id, copie_lista[i]->day, copie_lista[i]->sum, copie_lista[i]->type, copie_lista[i]->description);
	}

	for (int i = 0; i < l->lungime; i++) {
		free(copie_lista[i]);
	}
	free(copie_lista);
	return;
}


