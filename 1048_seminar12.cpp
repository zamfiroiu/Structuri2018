#include<iostream>






//de aici


struct nod {
	int cod;
	nod* next;
};

void pushStack(nod ** cap, int cod) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->cod = cod;
	nou->next = *cap;
	*cap = nou;
}

int popStack(nod**cap) {
	if (*cap) {
		int rezultat = (*cap)->cod;
		nod* t = *cap;
		*cap = (*cap)->next;
		free(t);
		return rezultat;
	}
	else {
		return -1;
	}
}

void pushQueue(nod**cap, int cod) {
	nod*nou = (nod*)malloc(sizeof(nod));
	nou->cod = cod;
	nou->next = NULL;
	if (*cap) {
		nod*p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

int popQueue(nod** cap) {
	return popStack(cap);
}

void adancime(int**matrice, int nodPlecare, int nrNoduri) {
	int* vizitate = (int*)malloc(nrNoduri * sizeof(int));
	for (int i = 0;i < nrNoduri;i++) {
		vizitate[i] = 0;
	}
	nod* stiva = NULL;
	pushStack(&stiva, nodPlecare);
	vizitate[nodPlecare] = 1;
	while (stiva) {
		int nodCurent = popStack(&stiva);
		printf("%d, ", nodCurent);
		for (int i = 0;i < nrNoduri;i++) {
			if (matrice[nodCurent][i] == 1 && vizitate[i] == 0) {
				pushStack(&stiva, i);
				vizitate[i] = 1;
			}
		}
	}
	free(vizitate);
}

int** citireMatriceAdiacenta(int * nrNoduri) {
	printf("Numarul de noduri:");
	scanf("%d", nrNoduri);

	int**matrice = (int**)malloc(sizeof(int*)*(*nrNoduri));
	for (int i = 0;i < *nrNoduri;i++) {
		matrice[i] = (int*)malloc(sizeof(int)*(*nrNoduri));
		for (int j = 0;j < *nrNoduri;j++) {
			matrice[i][j] = 0;
		}
	}

	int deLa;
	int panaLa;
	printf("De la:");
	scanf("%d", &deLa);
	while (deLa != -1) {

		printf("Pana la:");
		scanf("%d", &panaLa);

		if (deLa < *nrNoduri && panaLa < *nrNoduri) {
			matrice[deLa][panaLa] = 1;
			matrice[panaLa][deLa] = 1;
		}
		printf("De la:");
		scanf("%d", &deLa);
	}

	return matrice;
}


int* latime(int**matrice, int nodPlecare, int nrNoduri) {
	int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0;i < nrNoduri;i++) {
		vizitate[i] = 0;
	}

	nod* coada = NULL;

	pushQueue(&coada, nodPlecare);
	vizitate[nodPlecare] = 1;

	int*rezultat = (int*)malloc(sizeof(int)*nrNoduri);
	int pozitie = 0;
	while (coada) {
		int nodCurent = popQueue(&coada);
		rezultat[pozitie++] = nodCurent;
	
		for (int i = 0;i < nrNoduri;i++) {
			if (matrice[nodCurent][i] == 1 && vizitate[i] == 0) {
				pushQueue(&coada, i);
				vizitate[i] = 1;
			}
		}
	}
	free(vizitate);
	return rezultat;
}


void main() {

	int nrNoduri;
	int **matrice = citireMatriceAdiacenta(&nrNoduri);
	adancime(matrice, 0, nrNoduri);
	int* parcurgere = latime(matrice, 0, nrNoduri);
	printf("\n");
	for (int i = 0;i < nrNoduri;i++) {
		printf("%d, ", parcurgere[i]);
	}

	free(parcurgere);

	for (int i = 0;i < nrNoduri;i++) {
		free(matrice[i]);
	}
	free(matrice);

}