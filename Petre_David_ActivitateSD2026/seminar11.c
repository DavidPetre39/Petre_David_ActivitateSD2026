#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


typedef struct Nod Nod;
typedef struct NodListaSecundara NodListaSecundara;
struct Nod {
	NodListaSecundara* vecini;
	Nod* next;
	Masina info;
};
struct NodListaSecundara {
	struct Nod* info;
	NodListaSecundara* next;
};



void inserareNodInListaPrincipala(Nod** listaPrincipala, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->vecini = NULL;
	nou->info = masina;

	if (*listaPrincipala) {
		Nod* aux = *listaPrincipala;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	*listaPrincipala = nou;
}

void inserareNodInListaSecundara(NodListaSecundara** listaSecundara, Nod* nod) {
	NodListaSecundara* nou = (NodListaSecundara*)malloc(sizeof(NodListaSecundara));
	nou->next = NULL;
	nou->info = nod;
	if (*listaSecundara) {
		NodListaSecundara* aux = *listaSecundara;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
		*listaSecundara = nou;

}


Nod* cautaNodDupaID(Nod* listaPrincipala, int id) {
		Nod* aux = listaPrincipala;
	while (aux) {
		if (aux->info.id == id) {
			return aux;
		}
		aux = aux->next;
	}
	return NULL;
}

void inserareMuchie(Nod* listaPrincipala, int idStart, int idStop) {
	Nod* nodStart=cautaNodDupaID(listaPrincipala, idStart);
	Nod* nodStop=cautaNodDupaID(listaPrincipala, idStop);
	if (nodStart && nodStop) {
		inserareNodInListaSecundara(&nodStart->vecini, nodStop);
		inserareNodInListaSecundara(&nodStop->vecini, nodStart);
	}
	else
		printf("Nu s-au gasit nodurile pentru muchia data\n");

}


void* citireNoduriMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* listaPrincipala = NULL;
	while(!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		inserareNodInListaPrincipala(&listaPrincipala, masina);
	}
	fclose(f);
	return listaPrincipala;
}

void citireMuchiiDinFisier(Nod* graf,const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	while(!feof(f)) {
		int idStart, idStop;
		fscanf(f, "%d %d\n", &idStart, &idStop);
		inserareMuchie(graf, idStart, idStop);
	}
	fclose(f);
}

void dezalocareNoduriGraf(void* listaPrincipala) {

}

void afiseazaListaSecundara(Nod* graf, int id) {
	Nod* nod = cautaNodDupaID(graf, id);
	NodListaSecundara* aux = nod->vecini;
	while (aux) {
		afisareMasina(aux->info->info);
		aux = aux->next;
	}
}

int main() {
	Nod* graf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	afiseazaListaSecundara(graf, 3);
	

	return 0;
}