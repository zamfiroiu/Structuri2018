#include<iostream>

struct Film {
	char* nume;
	float durata;
};


Film createFilm(char* nume, float durata) {
	Film film;
	film.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy_s(film.nume, strlen(nume) + 1, nume);
	film.durata = durata;

	return film;
}

void printFilm(Film f) {
	printf("Filmul %s dureaza %5.2f minute.\t", f.nume, f.durata);
}

int maxim(int* vector, int lungime) {
	int rezultat = vector[0];
	for (int i = 1; i < lungime; i++) {
		if (rezultat < vector[i]) {
			rezultat = vector[i];
		}
	}
	return rezultat;
}

Film*CautaLinieDeFilme(Film**m, int nrLinii, int*nrColoane, int*dim) {
	*dim = maxim(nrColoane, nrLinii);
	Film* rezultat = (Film*)malloc(sizeof(Film)*(*dim));
	for (int i = 0; i < nrLinii; i++) {
		if ((*dim) == nrColoane[i]) {
			for (int j = 0; j < (*dim); j++) {
				rezultat[j] = m[i][j];
				rezultat[j].nume = (char*)malloc(
					sizeof(char)*(strlen(m[i][j].nume) + 1));
				strcpy_s(rezultat[j].nume, strlen(m[i][j].nume) + 1, m[i][j].nume);
			}
			i = nrLinii + 1;
		}
	}
	return rezultat;
}

void citireMatrice(Film** *matrice, int *nrLinii, int* *nrColoane) {

	printf("Numar linii:");
	scanf_s("%d", nrLinii);
	(*nrColoane) = (int*)malloc(sizeof(int)*(*nrLinii));

	(*matrice) = (Film**)malloc(sizeof(Film*)*(*nrLinii));
	for (int i = 0; i < *nrLinii; i++) {
		printf("Numar Coloane pentru linia %d:", (i + 1));
		scanf_s("%d", &(*nrColoane)[i]);
		(*matrice)[i] = (Film*)malloc(sizeof(Film)*(*nrColoane)[i]);
		for (int j = 0; j < (*nrColoane)[i]; j++) {
			(*matrice)[i][j] = createFilm("BlackPanter", 136 + i*j);
		}
	}
}

void main() {

	char buffer[20];
	strcpy_s(buffer,5, "taxi");
	Film f = createFilm(buffer, 120);
	printFilm(f);

	Film **matrice;
	int nrLinii;
	int *nrColoane;
	
	citireMatrice(&matrice, &nrLinii, &nrColoane);	

	for (int i = 0; i < nrLinii; i++) {
		for (int k = 0; k < nrColoane[i]; k++) {
			printFilm(matrice[i][k]);
		}
		printf("\n");
	}

	Film * vector;
	int lungime = 0;
	vector = CautaLinieDeFilme(matrice, nrLinii, nrColoane, &lungime);
	printf("Vectorul de filme:\n");
	for (int i = 0; i < lungime; i++) {
		printFilm(vector[i]);
	}

	//dezalocare vector
	for (int i = 0; i < lungime; i++) {
		free(vector[i].nume);
	}
	free(vector);

	//dezalocare matrice
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			free(matrice[i][j].nume);
		}
		free(matrice[i]);
	}
	free(matrice);
	
	free(nrColoane);


}