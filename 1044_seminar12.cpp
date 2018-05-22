#include<iostream>

struct nod {
	int info;
	nod* next;
};

void pushStack(nod**cap, int info) {
	nod*nou = (nod*)malloc(sizeof(nod));
	nou->info = info;
	nou->next = *cap;
	*cap = nou;
}

int popStack(nod** cap) {
	if (*cap) {
		int rezultat = (*cap)->info;
		nod* temp = *cap;
		(*cap) = (*cap)->next;
		free(temp);
		return rezultat;
	}
	else {
		return -1;
	}
}

void pushQueue(nod**cap, int info) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = info;
	nou->next = NULL;
	if (*cap) {
		nod* p = *cap;
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

int** citireMatriceAdiacenta(int * nrNoduri) {
	printf("Numar noduri:");
	scanf("%d", nrNoduri);

	int** matrice = (int**)malloc(*nrNoduri * sizeof(int*));
	for (int i = 0; i < *nrNoduri; i++) {
		matrice[i] = (int *)malloc(*nrNoduri * sizeof(int));
		for (int j = 0; j < *nrNoduri; j++) {
			matrice[i][j] = 0;
		}
	}

	int nod1;
	int nod2;
	printf("de la: ");
	scanf("%d", &nod1);
	while (nod1 != -1) {
		printf("pana la: ");
		scanf("%d", &nod2);
		if (nod1 < *nrNoduri && nod2 < *nrNoduri) {
			matrice[nod1][nod2] = 1;
			matrice[nod2][nod1] = 1;
		}

		printf("de la: ");
		scanf("%d", &nod1);
	}

	return matrice;
}

int*adancime(int** matrice, int nrNoduri, int nodPlecare) {
	int* rezultat = (int*)malloc(sizeof(int)*nrNoduri);
	int k = 0;

	nod* stiva = NULL;
	int*vizitate = (int*)malloc(nrNoduri * sizeof(int));
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	pushStack(&stiva, nodPlecare);
	vizitate[nodPlecare] = 1;
	while (stiva) {
		int nodCurent = popStack(&stiva);
		rezultat[k++] = nodCurent;
		for (int i = 0; i < nrNoduri; i++) {
			if (matrice[nodCurent][i] == 1 && vizitate[i] == 0) {
				//daca nodul i are legatura cu nodul curent
				//si nodul nu a fost vizitat;
				pushStack(&stiva, i);
				vizitate[i] = 1;
			}
		}
	}
	free(vizitate);
	return rezultat;

}

void latime(int**matrice, int nrNoduri, int nodPlecare) {
	nod* coada = NULL;
	int*vizitate = (int*)malloc(nrNoduri * sizeof(int));
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}

	pushQueue(&coada, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (coada) {
		int nodCurent = popQueue(&coada);
		printf("%d", nodCurent);

		for (int i = 0; i < nrNoduri; i++) {
			if (matrice[nodCurent][i] == 1 && vizitate[i] == 0) {
				pushQueue(&coada,i);
				vizitate[i] = 1;
			}
		}
	}
	free(vizitate);
}

void main() {
	int nrNoduri;
	int**matriceAdiacenta = citireMatriceAdiacenta(&nrNoduri);
	int* parcurgereAdancime = adancime(matriceAdiacenta, nrNoduri, 0);

	for (int i = 0; i < nrNoduri; i++) {
		printf("%d,", parcurgereAdancime[i]);
	}

	latime(matriceAdiacenta, nrNoduri, 0);


	//dezalocari
	for (int i = 0; i < nrNoduri; i++) {
		free(matriceAdiacenta[i]);
	}
	free(matriceAdiacenta);
	free(parcurgereAdancime);

}