#pragma once
#include "validare.h"
#include "repo.h"
#include "entity.h"


void srv_add_tranzactie(int id, int day, int sum, int type, char* desc, char* error, Lista* lista);
void srv_modifica_tranzactie(int id, int day, int sum, int type, char* desc, char* error, Lista* lista);
void srv_stergere(int id, Lista* lista, char* errors);
void srv_viz_type(int type, Lista* l, char* errors);
void srv_viz_sum_mai_mare(int sum, Lista* l, char* errors);
void srv_viz_sum_mai_mic(int sum, Lista* l, char* errors);
void srv_viz_zi(int sens, Lista* l, char* errors);
void srv_viz_suma(int sens, Lista* l, char* errors);