#include<iostream>

struct Vacanta {
	char* destinatie;
	int durata;
};

Vacanta creareVacanta(char* dest, int durata) {
	Vacanta v;
	v.destinatie = (char*)malloc(sizeof(char)*(strlen(dest) + 1));
	strcpy_s(v.destinatie, strlen(dest) + 1, dest);
	v.durata = durata;
	return v;
}

void afisareVacanta(Vacanta v) {
	printf("Vacanta din %s dureaza %d zile\n", v.destinatie, v.durata);
}

struct nod {
	Vacanta info;
	nod* st;
	nod*dr;
};

nod* inserare(nod*rad, Vacanta v) {
	if (rad) {
		if (rad->info.durata < v.durata) {
			rad->dr = inserare(rad->dr, v);
		}
		else if(rad->info.durata>v.durata) {
			rad->st = inserare(rad->st, v);
		}
		return rad;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = v;
		nou->st = NULL;
		nou->dr = NULL;
		return nou;
	}
}

void afisare(nod* rad) {
	if (rad) {
		afisare(rad->st);
		afisareVacanta(rad->info);
		afisare(rad->dr);
	}
}

Vacanta cautareVacantaDupaDurata(nod* rad, int durata) {
	if (rad) {
		if (rad->info.durata < durata) {
			return cautareVacantaDupaDurata(rad->dr, durata);
		}
		else {
			if (rad->info.durata > durata) {
				return cautareVacantaDupaDurata(rad->st, durata);
			}
			else {
				return rad->info;
			}
		}
	}
	else {
		return creareVacanta("", -1);
	}
}

void stergere(nod** rad) {
	if (*rad) {
		stergere(&(*rad)->st);
		stergere(&(*rad)->dr);
		free((*rad)->info.destinatie);
		free(*rad);
		*rad = NULL;
	}
}

void main() {
	nod* rad = NULL;
	rad = inserare(rad, creareVacanta("Mamaia", 6));
	rad = inserare(rad, creareVacanta("Busteni", 3));
	rad = inserare(rad, creareVacanta("Vama", 5));
	rad = inserare(rad, creareVacanta("Bahamas", 8));
	rad = inserare(rad, creareVacanta("Dubai", 11));
	rad = inserare(rad, creareVacanta("Paris", 13));
	rad = inserare(rad, creareVacanta("Madrid", 9));
	rad = inserare(rad, creareVacanta("Focsani", 7));

	afisare(rad);

	printf("\n");
	afisareVacanta(cautareVacantaDupaDurata(rad, 9));

	stergere(&rad);
	printf("arbore:\n");
	afisare(rad);

}