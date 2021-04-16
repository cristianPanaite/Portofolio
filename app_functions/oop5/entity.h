#pragma once

typedef struct {
	int id;
	int day, sum;
	int type;
	char* description;
}Tranzactie;


Tranzactie* creeare_tranzactie(int id, int day, int sum, int type, char* desc);
int get_id(Tranzactie* t);
int get_day(Tranzactie* t);
int get_suma(Tranzactie* t);
int get_type(Tranzactie* t);
char* get_desc(Tranzactie* t);

void set_day(Tranzactie* t, int x);
void set_sum(Tranzactie* t, int x);
void set_type(Tranzactie* t, int x);
void set_desc(Tranzactie* t, char* x);
