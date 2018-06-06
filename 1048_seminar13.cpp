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
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	nod* stiva = NULL;
	pushStack(&stiva, nodPlecare);
	vizitate[nodPlecare] = 1;
	while (stiva) {
		int nodCurent = popStack(&stiva);
		printf("%d, ", nodCurent);
		for (int i = 0; i < nrNoduri; i++) {
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
	for (int i = 0; i < *nrNoduri; i++) {
		matrice[i] = (int*)malloc(sizeof(int)*(*nrNoduri));
		for (int j = 0; j < *nrNoduri; j++) {
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
	for (int i = 0; i < nrNoduri; i++) {
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

		for (int i = 0; i < nrNoduri; i++) {
			if (matrice[nodCurent][i] == 1 && vizitate[i] == 0) {
				pushQueue(&coada, i);
				vizitate[i] = 1;
			}
		}
	}
	free(vizitate);
	return rezultat;
}

struct nodSimplu {
	int info;
	nodSimplu*next;
};

struct nodPrincipal {
	int info;
	nodPrincipal*next;
	nodSimplu*vecini;
};

void inserareListaSimpla(nodSimplu**cap, int info) {
	nodSimplu*nou = (nodSimplu*)malloc(sizeof(nodSimplu));
	nou->next = NULL;
	nou->info = info;
	if (*cap) {
		nodSimplu*p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

nodPrincipal* creareListaPrincipala(int nrNoduri) {
	nodPrincipal* cap = NULL;
	for (int i = nrNoduri - 1; i >= 0; i--) {
		nodPrincipal*nou = (nodPrincipal*)malloc(sizeof(nodPrincipal));
		nou->info = i;
		nou->vecini = NULL;
		nou->next = cap;
		cap = nou;
	}
	return cap;
}

void inserareMuchie(int nod1, int nod2, nodPrincipal*graf) {
	while (graf && graf->info != nod1) {
		graf = graf->next;
	}
	if (graf) {
		inserareListaSimpla(&graf->vecini, nod2);
	}
}

nodPrincipal*citireGrafListaListe() {
	int nrNoduri;
	printf("nrNoduri:");
	scanf("%d", &nrNoduri);
	nodPrincipal* graf = creareListaPrincipala(nrNoduri);
	int nrMuchii;
	printf("nr muchii:");
	scanf("%d", &nrMuchii);

	for (int i = 0; i < nrMuchii; i++) {
		int nod1;
		int nod2;
		printf("De la:");
		scanf("%d", &nod1);
		printf("Pana la:");
		scanf("%d", &nod2);
		inserareMuchie(nod1, nod2, graf);
		inserareMuchie(nod2, nod1, graf);
	}
	return graf;
}

int numarNoduri(nodPrincipal*graf) {
	int i = 0;
	while (graf) {
		i++;
		graf = graf->next;
	}
	return i;
}

int numarNoduriRecursiv(nodPrincipal*graf) {
	if (graf) {
		return 1 + numarNoduriRecursiv(graf->next);
	}
	else {
		return 0;
	}
}

void parcurgereInAdancime(nodPrincipal* graf, int nodPlecare) {
	int nrNoduri = numarNoduri(graf);
	int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	nod*stiva = NULL;
	
	vizitate[nodPlecare] = 1;
	pushStack(&stiva, nodPlecare);

	while (stiva) {
		nodPlecare = popStack(&stiva);
		printf("%d, ", nodPlecare);
		nodPrincipal*p = graf;
		while (p && p->info != nodPlecare) {
			p = p->next;
		}
		if (p) {
			nodSimplu *s = p->vecini;
			while (s) {
				if (vizitate[s->info] == 0) {
					vizitate[s->info] = 1;
					pushStack(&stiva, s->info);
				}
				s = s->next;
			}
		}
	}
	free(vizitate);
}

void main() {
	nodPrincipal* graf = citireGrafListaListe();
	parcurgereInAdancime(graf, 3);

	//stergere ista de liste
}