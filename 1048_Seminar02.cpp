#include<iostream>

#pragma warning(disable:4996)

struct Cadou {
	char* destinatar;
	float greutate;
};

int numarCadouri(float prag, Cadou ** matrice, int nLinii, int* nColoane) {
	int nr = 0;
	for (int i = 0; i < nLinii; i++) {
		for (int j = 0; j < nColoane[i]; j++) {
			if (matrice[i][j].greutate <= prag) {
				nr++;
			}
		}
	}
	return nr;
}

Cadou impachetareCadou(const char* destinatar, float greutate) {
	Cadou cadou;
	cadou.destinatar = (char*)malloc(sizeof(char)*(strlen(destinatar) + 1));
	strcpy(cadou.destinatar, destinatar);
	cadou.greutate = greutate;
	return cadou;
}

void afisareCadou(Cadou cadou) {
	printf("cadoul primit de %s cantareste %5.2f kg\n", cadou.destinatar, cadou.greutate);
}

void citireMatrice(int *nLinii, int* *nColoane, Cadou** *matrice) {
	printf("numar linii:");
	scanf("%d", nLinii);

	*matrice = (Cadou**)malloc(sizeof(Cadou*)*(*nLinii));
	*nColoane = (int*)malloc(sizeof(int)*(*nLinii));
	
	for (int i = 0; i < *nLinii; i++) {
		printf("NUmarul de coloane pentur linia %d:", (i + 1));
		scanf("%d", &(*nColoane)[i]);

		(*matrice)[i] = (Cadou*)malloc(sizeof(Cadou)*(*nColoane)[i]);
		for (int j = 0; j < (*nColoane)[i]; j++) {
			(*matrice)[i][j] = impachetareCadou("Popescu", (i + 100)*(j + 20));
		}
	}
}

void main() {
	int nLinii;
	int* nColoane;
	Cadou** matrice;

	citireMatrice(&nLinii, &nColoane, &matrice);
	
	for (int i = 0; i < nLinii; i++) {
		for (int j = 0; j < nColoane[i]; j++) {
			afisareCadou(matrice[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < nLinii; i++) {
		for (int j = 0; j < nColoane[i]; j++) {
			free(matrice[i][j].destinatar);
		}
		free(matrice[i]);
	}
	free(matrice);
	free(nColoane);
}