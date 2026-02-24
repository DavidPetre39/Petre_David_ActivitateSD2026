#include <stdio.h>
#include <stdlib.h>
struct Student {
	int id;
	char* nume;
	int varsta;
	int nrNote;
	int* note;
};
struct Student creareStudent(int _id, char* _nume, int _varsta, int _nrNote, int* _note) {
	struct Student s;
	s.id = _id;
	s.nume = malloc(sizeof(char) * (strlen(_nume) + 1));
	strcpy(s.nume, _nume);
	s.varsta = _varsta;
	if (_nrNote > 0) {
		s.nrNote = _nrNote;
		s.note = malloc(sizeof(int) * _nrNote);
		for (int i = 0; i < s.nrNote; i++)
			s.note[i] = _note[i];
	}
	return s;
}
void afisare(struct Student s) {
	printf("\nID student : %d", s.id);
	printf("\nNume student : %s", s.nume);
	printf("\nVarsta student : %d", s.varsta);
	printf("\nNumar note : %d", s.nrNote);
	if (s.nrNote > 0) {
		printf("\nNote student : ");
		for (int i = 0; i < s.nrNote; i++)
			printf("%d ", s.note[i]);
	}
}
void dezalocare(struct Student* s) {
	free(s->nume);
	if (s->nrNote > 0)
		free(s->note);
}
int main() {
	struct Student s1 = creareStudent(1, "Gigel", 21, 5, (int[]) { 10, 9, 8, 7, 6 });
	afisare(s1);
	dezalocare(&s1);
}