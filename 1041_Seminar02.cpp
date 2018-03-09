#include<iostream>


struct Martisor {
	char* culoare;
	float pret;
};

Martisor createMartisor(char* culoare, float pret) {
	Martisor martisor;
	martisor.culoare = (char*)malloc(sizeof(char)*(strlen(culoare) + 1));
	strcpy(martisor.culoare, culoare);
	martisor.pret = pret;

	return martisor;
}

void afisareMartisor(Martisor martisor) {
	printf("Martisorul de culoare %s costa %5.2f lei.", 
		martisor.culoare, martisor.pret);
}

void citireMatrice(int *nLinii, int* *nColoane, Martisor** *matrice) {
	printf("Numarul de linii:");
	scanf("%d", nLinii);

	*nColoane = (int*)malloc(sizeof(int)*(*nLinii));
	*matrice = (Martisor**)malloc(sizeof(Martisor*)*(*nLinii));

	for (int i = 0; i < (*nLinii); i++) {
		printf("Numarul de coloane pentru linia %d:", (i + 1));
		scanf("%d", &(*nColoane)[i]);
		(*matrice)[i] = (Martisor*)malloc(sizeof(Martisor)*(*nColoane)[i]);
		for (int j = 0; j < (*nColoane)[i]; j++) {
			(*matrice)[i][j] = createMartisor("Rosu", 20 + ((i + 1)*(j + 1)));
		}
	}
}

int getPozitieMinim(int *vector, int dimensiune) {
	int minim = vector[0];
	int pozitie = 0;
	for (int i = 0; i < dimensiune; i++) {
		if (vector[i] < minim) {
			minim = vector[i];
			pozitie = i;
		}
	}
	return pozitie;
}

Martisor* getLinieScurta(Martisor** matrice, int nLinii, int* nColoane, int *dimensiune) {
	Martisor* rezultat;
	int pozitie = getPozitieMinim(nColoane, nLinii);
	int nrElemente = nColoane[pozitie];
	rezultat = (Martisor*)malloc(sizeof(Martisor)*nrElemente);

	for (int i = 0; i < nrElemente; i++) {
		rezultat[i] = createMartisor(matrice[pozitie][i].culoare, matrice[pozitie][i].pret);
	}
	*dimensiune = nrElemente;
	return rezultat;
}

void main() {

	int nLinii;
	int* nColoane;
	Martisor** matrice;
	
	citireMatrice(&nLinii, &nColoane, &matrice);

	for (int i = 0; i < nLinii; i++) {
		for (int j = 0; j < nColoane[i]; j++) {
			afisareMartisor(matrice[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	int nrElemente = 0;
	Martisor* shortestLine = getLinieScurta(matrice, nLinii, nColoane, &nrElemente);

	for (int i = 0; i < nrElemente; i++) {
		afisareMartisor(shortestLine[i]);
		printf("\n");
	}
	for (int i = 0; i < nrElemente; i++) {
		free(shortestLine[i].culoare);
	}
	free(shortestLine);


	for (int i = 0; i < nLinii; i++) {
		for (int j = 0; j < nColoane[i]; j++) {
			free(matrice[i][j].culoare);
		}
		free(matrice[i]);
	}
	free(matrice);
	free(nColoane);
}