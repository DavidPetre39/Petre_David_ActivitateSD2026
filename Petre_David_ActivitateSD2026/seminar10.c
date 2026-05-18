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
typedef struct NodArbore NodArbore;

struct NodArbore {
	Masina masina;
	NodArbore *left;
	NodArbore* right;
};

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

int calculeazaInaltimeArbore(NodArbore *root) {
	if (root)
		return max(calculeazaInaltimeArbore(root->left), calculeazaInaltimeArbore(root->right))+1;
	else return 0;
}

//ALTE FUNCTII NECESARE:
// - aici veti adauga noile functii de care aveti nevoie.

char calculGE(NodArbore* root) {
	if (root)
		return calculeazaInaltimeArbore(root->left) - calculeazaInaltimeArbore(root->right);
	else return 0;
}

void rotireStanga(NodArbore** root) {
	NodArbore* aux = (*root)->right;
	(*root)->right = aux->left;
	aux->left = (*root);
	(*root) = aux;
}

void rotireDreapta(NodArbore** root) {
	NodArbore* aux = (*root)->left;
	(*root)->left = aux->right;
	aux->right = (*root);
	(*root) = aux;
}

void adaugaMasinaInArboreEchilibrat(NodArbore **root, Masina masinaNoua) {
	if (*root) {
		if ((*root)->masina.id > masinaNoua.id) {
			adaugaMasinaInArboreEchilibrat(&(*root)->left, masinaNoua);
		}
		else {
			adaugaMasinaInArboreEchilibrat(&(*root)->right, masinaNoua);
		}
		int grad = calculGE(*root);
		if (grad == 2) { //dezechilibru in stanga
			if(calculGE((*root)->left) == -1){
				rotireStanga(&(*root)->left);
			}
			rotireDreapta(root);
			}
		else if (grad == -2) {
			if (calculGE((*root)->right == 1)) {
				rotireDreapta(&(*root)->right);
			}
			rotireStanga(root);
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
		nou->masina = masinaNoua;
		nou->left = NULL;
		nou->right = NULL;
		(*root) = nou;
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	NodArbore* root = NULL;
	while (!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		adaugaMasinaInArboreEchilibrat(&root, masina);
	}
	fclose(f);
	return root;
}

void afisareMasiniDinArbore(NodArbore *root) {
	if (root) {
		afisareMasina(root->masina);
		afisareMasiniDinArbore(root->left);
		afisareMasiniDinArbore(root->right);
	}
}

void dezalocareArboreDeMasini(NodArbore **root) {
	if (*root) {
		dezalocareArboreDeMasini(&(*root)->left);
		dezalocareArboreDeMasini(&(*root)->right);
		free((*root)->masina.numeSofer);
		free((*root)->masina.model);
		free(*root);
		*root = NULL;
	}
}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(NodArbore* root, const char* numeSofer) {
	float sum = 0;
	if (root) {
		sum += calculeazaPretulMasinilorUnuiSofer(root->left, numeSofer);
		sum += calculeazaPretulMasinilorUnuiSofer(root->right, numeSofer);
		if (strcmp(root->masina.numeSofer, numeSofer) == 0) {
			sum += root->masina.pret;
		}
	}
	return sum;
};

int main() {
	NodArbore* root = citireArboreDeMasiniDinFisier("masini.txt");
	afisareMasiniDinArbore(root);
	printf("%.2f", calculeazaPretulMasinilorUnuiSofer(root, "Ionescu"));
	dezalocareArboreDeMasini(&root);
	return 0;
}