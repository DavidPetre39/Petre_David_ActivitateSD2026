//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//typedef struct Nod Nod;
//typedef struct ListaDubla ListaDubla;
//struct Nod{
//	Masina info;
//	Nod* next;
//	Nod* prev;
//};
//
//struct ListaDubla {
//	Nod* prim;
//	Nod* ultim;
//};
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(ListaDubla lista) {
//	Nod* p = lista.prim;
//	while(p){
//		afisareMasina(p->info);
//		p = p->next;
//	}
//}
//
//void afisareInversaListaMasini(ListaDubla lista) {
//	Nod* p = lista.ultim;
//	while (p) {
//		afisareMasina(p->info);
//		p = p->prev;
//	}
//}
//
//void adaugaMasinaInLista(ListaDubla *ld, Masina masinaNoua) {
//	Nod* nou = malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	nou->prev = ld->ultim;
//	if (ld->ultim) {
//		ld->ultim->next = nou;
//	}
//	else {
//		ld->prim = nou;
//	}
//	ld->ultim = nou;
//}
//
//void adaugaLaInceputInLista(ListaDubla *ld, Masina masinaNoua) {
//	Nod* nou = malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = ld->prim;
//	nou->prev = NULL;
//	if (ld->prim) {
//		ld->prim->prev = nou;
//	}
//	else {
//		ld->ultim = nou;
//	}
//	ld->prim = nou;
//}
//
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	if (f) {
//		ListaDubla ld;
//		ld.prim = NULL;
//		ld.ultim = NULL;
//		while (!feof(f)) {
//			Masina m = citireMasinaDinFisier(f);
//			adaugaMasinaInLista(&ld, m);
//		}
//		fclose(f);
//		return ld;
//	}
//}
//
//void dezalocareLDMasini(ListaDubla *ld) {
//	while(ld->prim && ld->prim->next){
//		free(ld->prim->info.model);
//		free(ld->prim->info.numeSofer);
//		ld->prim = ld->prim->next;
//		free(ld->prim->prev);
//	}
//	if (ld->prim) {
//		free(ld->prim->info.model);
//		free(ld->prim->info.numeSofer);
//		free(ld->prim);
//	}
//}
//
//float calculeazaPretMediu(ListaDubla *ld){
//	if (ld == NULL || ld->prim == NULL) {
//		return 0;
//	}
//	float suma = 0;
//	int nr = 0;
//	Nod* p = ld->prim;
//	while (p) {
//		suma += p->info.pret;
//		nr++;
//		p = p->next;
//	}
//	if (nr == 0) {
//		return 0;
//	}
//
//	return suma / nr;
//}
//
//char* getNumeSoferMasinaScumpa(ListaDubla* ld) {
//	if (ld == NULL || ld->prim == NULL) {
//		return NULL;
//	}
//	Nod* p = ld->prim;
//	float pretMax = p->info.pret;
//	char* nume = p->info.numeSofer;
//	p = p->next;
//	while (p) {
//		if (p->info.pret > pretMax) {
//			pretMax = p->info.pret;
//			nume = p->info.numeSofer;
//		}
//		p = p->next;
//	}
//	char* copie = malloc(strlen(nume) + 1);
//	strcpy(copie, nume);
//	return copie;
//}
//
//void stergeMasinaDupaID(ListaDubla* ld, int id) {
//	if (ld->prim && ld->prim->info.id == id) {
//		free(ld->prim->info.model);
//		free(ld->prim->info.numeSofer);
//		ld->prim = ld->prim->next;
//		if (ld->prim) {
//			free(ld->prim->prev);
//		}
//		else {
//			free(ld->ultim);
//			ld->ultim = NULL;
//		}
//		return;
//	}
//	Nod* p = ld->prim;
//	while(p && p->info.id!=id){
//		p = p->next;
//	}
//	if (p) {
//		if(p->prev){
//			p->prev->next = p->next;
//		}
//		if(p->next){
//			p->next->prev = p->prev;
//		}
//		else {
//			p->prev->next = NULL;
//			ld->ultim = p->prev;
//		}
//		free(p->info.model);
//		free(p->info.numeSofer);
//		free(p);
//	}
//}
//int main() {
//	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	stergeMasinaDupaID(&lista, 10);
//	printf("Masini dupa stergere: \n");
//	afisareListaMasini(lista);
//
//	return 0;
//}