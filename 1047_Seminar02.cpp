#include<iostream>

struct Florarie {
	char* denumire;
	int numarFlori;
};

Florarie createFlorarie(char* denumire, int numarFlori) {
	Florarie florarie;
	florarie.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(florarie.denumire, denumire);
	florarie.numarFlori = numarFlori;

	return florarie;
}

void afisareFlorarie(Florarie f) {
	printf("Floraria %s vinde %d flori", f.denumire, f.numarFlori);
}

void afisareMatrice(Florarie ** m, int nrLinii, int*nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareFlorarie(m[i][j]);
			printf("\n");
		}
		printf("\n\n");
	}
}


void citireMatrice(Florarie** *m, int *nrLinii, int* *nrColoane) {
	printf("Numar linii:");
	scanf("%d", nrLinii);
	(*m) = (Florarie**)malloc(sizeof(Florarie*)*(*nrLinii));
	(*nrColoane) = (int*)malloc(sizeof(int)*(*nrLinii));

	for (int i = 0; i < (*nrLinii); i++) {
		printf("Numar coloane pentru linia %d:", (i + 1));
		scanf("%d", &((*nrColoane)[i]));

		(*m)[i] = (Florarie*)malloc(sizeof(Florarie)*(*nrColoane)[i]);
		for (int j = 0; j < (*nrColoane)[i]; j++) {
			(*m)[i][j] = createFlorarie((char*)"Floris", 200 + i*j);
		}
	}

}

int getPozitieMaximDinVector(int*vector, int nrElemente) {
	int maxim = vector[0];
	int pozitie = 0;
	for (int i = 1; i < nrElemente; i++) {
		if (maxim < vector[i]) {
			maxim = vector[i];
			pozitie = i;
		}
	}
	return pozitie;
}

Florarie* obtineCeaMaiLungaLinie(Florarie**m, int nrLinii, int*nrColoane, int*dim) {
	int pozitie = getPozitieMaximDinVector(nrColoane, nrLinii);
	int nrElemente = nrColoane[pozitie];
	Florarie* rezultat = (Florarie*)malloc(sizeof(Florarie)*nrElemente);
	for (int i = 0; i < nrElemente; i++) {
		rezultat[i]=createFlorarie(m[pozitie][i].denumire, m[pozitie][i].numarFlori);
		//rezultat[i] = m[pozitie][i];
		//rezultat[i].denumire=(char*)malloc(sizeof(char)*(strlen(m[pozitie][i].denumire) + 1));
		//strcpy(rezultat[i].denumire, m[pozitie][i].denumire);
	}
	*dim = nrElemente;
	return rezultat;
}

void main() {

	Florarie** matrice;
	int nrLinii;
	int * nrColoane;
	
	citireMatrice(&matrice, &nrLinii, &nrColoane);

	afisareMatrice(matrice, nrLinii, nrColoane);

	int dimensiune = 0;
	Florarie* vector = obtineCeaMaiLungaLinie(matrice, nrLinii, nrColoane, &dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		afisareFlorarie(vector[i]);
	}
	for (int i = 0; i < dimensiune; i++) {
		free(vector[i].denumire);
	}
	free(vector);
	

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			free(matrice[i][j].denumire);
		}
		free(matrice[i]);
	}
	free(matrice);
	free(nrColoane);



}