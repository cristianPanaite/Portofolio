#pragma once

#include "Console.h"
#include <stdio.h>
#include <string.h>
#include "service.h"
#include <stdio.h>

/// transformare sir de caractere in numar intreg
/// return numarul, daca sirul de caractere reprezinta un numar intreg valid
/// return -1, altfel

int Number(char* s) {
	int x = 0;
	int semn = 1;
	int i = 0;
	if (s[0] == '-') {
		semn = -1;
		i = 1;
	}
	int len = strlen(s);
	if (len == 0) {
		return -1;
	}
	for (; i < len; i++) {
		if (s[i] >= '0' && s[i] <= '9')
			x = x * 10 + (s[i] - '0');
		else
			return -1;
	}
	return semn * x;
}

void ui_adaugare(Lista* lista) {
	printf("Adaugare tranzactie\n\n");
	int id, day, sum, type;
	char idc[50] = "", dayc[50] = "", sumc[50] = "", typec[50] = "";
	char desc[50] = "";
	printf("Id: "); 
	gets(idc);
	printf("Day: ");
	gets(dayc);
	printf("Sum: ");
	gets(sumc);
	printf("Type: ");
	gets(typec);
	printf("Description: ");
	gets(desc);
	char errors[500] = "";
	id = Number(idc);
	day = Number(dayc);
	sum = Number(sumc);
	type = Number(typec);
	if (id == -1)
		strcat(errors, "Id : Not a number\n");
	if (day == -1)
		strcat(errors, "Day : Not a number\n");
	if (sum == -1)
		strcat(errors, "Sum : Not a number\n");
	if (type == -1)
		strcat(errors, "Type : Not a number\n");
	if (strlen(errors) == 0) {
		char errSrv[100] = "";
		srv_add_tranzactie(id, day, sum, type, desc, errSrv, lista);
		strcat(errors, errSrv);
	}
	if (strlen(errors) != 0)
		printf("Erori:\n\n%s", errors);
	else {
		printf("Adaugare cu succes\n");
	}
	return;
}


void ui_afisare(Lista* l) {
	
	if (dimensiune(l) == 0) {
		printf("Lista nu are elemente\n");
		return;
	}
	printf("Tranzactiile introduse:\n\n");
	for (int i = 0; i < dimensiune(l); i++) {
		printf("%d: Id: %d, Day: %d, Sum: %d, Type: %d, Description: %s\n", i, l->list[i]->id, l->list[i]->day, l->list[i]->sum, l->list[i]->type, l->list[i]->description);
	}
}

void ui_modificare(Lista* l) {
	printf("\nModificare tranzactie\n\n");
	printf("Introduceti id-ul tranzactiei de actualizat si datele corespunzatoare: \n");
	int id, day, sum, type;
	char idc[50] = "", dayc[50] = "", sumc[50] = "", typec[50] = "";
	char desc[50] = "";
	printf("Id: ");
	gets(idc);
	printf("Day: ");
	gets(dayc);
	printf("Sum: ");
	gets(sumc);
	printf("Type: ");
	gets(typec);
	printf("Description: ");
	gets(desc);
	char errors[500] = "";
	id = Number(idc);
	day = Number(dayc);
	sum = Number(sumc);
	type = Number(typec);
	if (id == -1)
		strcat(errors, "Id : Not a number\n");
	if (day == -1)
		strcat(errors, "Day : Not a number\n");
	if (sum == -1)
		strcat(errors, "Sum : Not a number\n");
	if (type == -1)
		strcat(errors, "Type : Not a number\n");
	if (strlen(errors) == 0) {
		char errSrv[100] = "";
		srv_modifica_tranzactie(id, day, sum, type, desc, errSrv, l);
		strcat(errors, errSrv);
	}
	if (strlen(errors) != 0)
		printf("Erori:\n\n%s", errors);
	else {
		printf("Adaugare cu succes\n");
	}
	return;
}

void ui_stergere(Lista* l) {
	printf("\nModificare tranzactie\n\n");
	printf("Introduceti id-ul tranzactiei de sters: ");
	char idc[10];
	int id;
	gets(idc);
	id = Number(idc);

	char errors[500] = "";
	if (id == -1) {
		strcat(errors, "Id : Not a number\n");
	}
	srv_stergere(id, l, errors);
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
	}
	else
		printf("Stergere cu succes\n");
}

void ui_tip(Lista* l) {
	printf("\nVizualizare dupa tip \n");
	printf("Introduceti un tip (1 sau 0): ");
	char typec[10];
	gets(typec);
	int type = Number(typec);
	char errors[500] = "";
	if (type == -1) {
		strcat(errors, "Type : Not a number\n");
	}
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
		return;
	}
	srv_viz_type(type, l, errors);
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
	}
}

void ui_mai_mare(Lista* l) {
	printf("Vizualizare cu o suma mai mare:\n");

	printf("Introduceti o suma (numar intreg): ");
	char sumc[10];
	gets(sumc);
	int sum = Number(sumc);
	char errors[500] = "";
	if (sum == -1) {
		strcat(errors, "Sum : Not a number\n");
	}
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
		return;
	}
	srv_viz_sum_mai_mare(sum, l, errors);
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
	}
}

void ui_mai_mic(Lista* l) {
	printf("Vizualizare cu o suma mai mare:\n");

	printf("Introduceti o suma (numar intreg): ");
	char sumc[10];
	gets(sumc);
	int sum = Number(sumc);
	char errors[500] = "";
	if (sum == -1) {
		strcat(errors, "Sum : Not a number\n");
	}
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
		return;
	}
	srv_viz_sum_mai_mic(sum, l, errors);
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
	}
}

void ui_criteriu(Lista* l) {
	printf("Vizualizare dupa un anumit criteriu:\n");
	while (1) {
		printf("\n Tip -> 1\n Mai mare decat -> 2\n Mai mic decat -> 3\n");
		printf("cmd >> ");
		char s[50];
		gets(s);
		int cmd = Number(s);
		if (cmd == -1) {
			printf("Comanda introdusa nu se afla printre cele disponibile\n");
			continue;
		}	
		switch (cmd) {
		case 1:
		{
			ui_tip(l);
			return;
		}
		case 2:
		{
			ui_mai_mare(l);
			return;
		}
		case 3:
		{
			ui_mai_mic(l);
			return;
		}
		default:
			return;
		}
	}
}
void ui_ord_zi(Lista* l) {
	char sensc[50];
	int sens = -1;
	printf("Tranzactii ordonate dupa zi (1 - crescator, 2 - descrescator): ");
	gets(sensc);
	sens = Number(sensc);
	char errors[500] = "";
	if (sens == -1) {
		strcat(errors, "Sens : Not a number\n");
	}
	if (sens != 1 && sens != 2) {
		strcat(errors, "Not an option\n");
	}
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
		return;
	}
	srv_viz_zi(sens, l, errors);
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
	}

}

void ui_ord_suma(Lista* l) {
	char sensc[50];
	int sens = -1;
	printf("Tranzactii ordonate dupa suma (1 - crescator, 2 - descrescator): ");
	gets(sensc);
	sens = Number(sensc);
	char errors[500] = "";
	if (sens == -1) {
		strcat(errors, "Sens : Not a number\n");
	}
	if (sens != 1 && sens != 2) {
		strcat(errors, "Not an option\n");
	}
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
		return;
	}
	srv_viz_suma(sens, l, errors);
	if (strlen(errors) > 0) {
		printf("\nErori :\n%s\n", errors);
	}
}

void ui_ordonat(Lista* l) {
	printf("Meniu Vizualizare Ordonat\n");
	while (1) {
		printf("\n Ordonat dupa zi -> 1\n Ordonat dupa suma -> 2\n");
		printf("cmd >> ");
		char s[50];
		gets(s);
		int cmd = Number(s);
		if (cmd == -1) {
			printf("Comanda introdusa nu se afla printre cele disponibile\n");
			continue;
		}
		switch (cmd)
		{
		case 0:
			return;
		case 1: {
			ui_ord_zi(l);
			return;
		}
		case 2: {
			ui_ord_suma(l);
			return;
		}
		default:
			return;
		}
	}
}

void ui_vizualizare(Lista* l) {
	printf("Meniu Vizualizare\n");

	
	while (1) {
		printf("\n Vizualizare dupa criteriu -> 1\n Vizualizare ordonare -> 2\n");
		printf("cmd >> ");
		char s[50];
		gets(s);
		int cmd = Number(s);
		if (cmd == -1) {
			printf("Comanda introdusa nu se afla printre cele disponibile\n");
			continue;
		}
		switch (cmd)
		{
		case 0:
			return;
		case 1: {
			ui_criteriu(l);
			return;
		}
		case 2: {
			ui_ordonat(l);
			return;
		}
		default:
			return;
		}
	}
}

void ui() {
	Lista* lista;
	lista = init();
	printf("Welcome!\n");
	while (1) {

		printf("Menu:\n Adaugare tranzactie -> 1\n Modificare tranzactie -> 2\n Stergere tranzactie -> 3\n Afiseaza tranzactii -> 4\n Vizualizare Tranzactii -> 5\n Exit -> 0\n");
		printf("cmd >> ");
		char s[50];
		gets(s);
		int cmd = Number(s);
		if (cmd == -1) {
			printf("Comanda introdusa nu se afla printre cele disponibile\n");
			continue;
		}
		switch (cmd)
		{
		case 0:
			return;
		case 1: {
			ui_adaugare(lista);
			continue;
		}
		case 2: {
			ui_modificare(lista);
			continue;
		}
		case 3: {
			ui_stergere(lista);
			continue;
		}
		case 4: {
			ui_afisare(lista);
			continue;
		}
		case 5: {
			ui_vizualizare(lista);
			continue;
		}
		default:
			continue;
		}

	}
	destroy_list(lista);

	return;
}