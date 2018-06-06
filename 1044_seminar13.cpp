#include<iostream>

struct nod {
	int info;
	nod* next;
};

struct nodPrincipal {
	nod* vecini;
	int cod;
	nodPrincipal*next;
};


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

void inserareListaSecundara(nod**cap, int cod) {
	pushQueue(cap, cod);
}

nodPrincipal*creareListaPrincipala(int nrNoduri){
	nodPrincipal* cap = NULL;
	for (int i = nrNoduri-1; i >=0; i--) {
		nodPrincipal*p = (nodPrincipal*)malloc(sizeof(nodPrincipal));
		p->cod = i;
		p->vecini = NULL;
		p->next = cap;
		cap = p;
	}
	return cap;
}


void inserareArc(int deLa, int panaLa, nodPrincipal* cap) {
	nodPrincipal*p = cap;
	while (p && p->cod != deLa) {
		p = p->next;
	}
	if (p) {
		inserareListaSecundara(&p->vecini, panaLa);
	}
}

nodPrincipal*citireGraf() {
	int nrNoduri;
	printf("numarul de noduri:");
	scanf("%d", &nrNoduri);
	nodPrincipal*graf = creareListaPrincipala(nrNoduri);
	int nrArce;

	printf("numarul de arce:");
	scanf("%d", &nrArce);

	for (int i = 0; i < nrArce; i++) {
		int cod1;
		int cod2;
		printf("De la:");
		scanf("%d", &cod1);
		printf("Pana la:");
		scanf("%d", &cod2);
		inserareArc(cod1, cod2, graf);
		inserareArc(cod2, cod1, graf);
	}
	return graf;
}


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
				pushQueue(&coada, i);
				vizitate[i] = 1;
			}
		}
	}
	free(vizitate);
}

int nrNoduri(nodPrincipal*lista) {
	int nr = 0;
	while (lista) {
		lista = lista->next;
		nr++;
	}
	return nr;
}
//1. ne luam un vector de vizitate;
//2. ne luam o stiva';
//3. adaugam nodul de plecare in stiva si il vizitam;
//4. incepem procesul;
//5. Extragem nodul din stiva;
//6 afisam nodul extras;
//7. cautam vecinii nevizitati ai nodului extras si ii adaugam in stiva, sii le vizitam;
//8. GOTO 5, cat timp avem stiva.


void ParcurgereListaInAdncime(nodPrincipal* graf, int nodPlecare) {
	nod* stiva = NULL;
	int nrnoduri = nrNoduri(graf);

	int* vizitate = (int*)malloc(sizeof(int)*nrnoduri);
	for (int i = 0; i < nrnoduri; i++) {
		vizitate[i] = 0;
	}

	pushStack(&stiva, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (stiva) {
		int nodCurent = popStack(&stiva);
		printf("%d, ", nodCurent);
		nodPrincipal*p = graf;
		while (p && p->cod != nodCurent) {
			p = p->next;
		}
		if (p) {
			nod* s = p->vecini;
			while (s) {
				if (vizitate[s->info] == 0) {
					pushStack(&stiva, s->info);
					vizitate[s->info] = 1;
				}
				s = s->next;
			}
		}
	}
	free(vizitate);
}



void main() {
	nodPrincipal* graf = citireGraf();
	ParcurgereListaInAdncime(graf, 3);
	
	//dezalocare memorie lista de liste
	while (graf) {
		while (graf->vecini) {
			nod*p = graf->vecini;
			graf->vecini = p->next;
			free(p);
		}
		nodPrincipal*p = graf;
		graf = graf->next;
		free(p);
	}
}