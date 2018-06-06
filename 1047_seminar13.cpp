#include<iostream>

struct nodListaSecundara {
	int cod;
	nodListaSecundara*next;
};

struct nodListaPrincipala {
	int cod;
	nodListaPrincipala* next;
	nodListaSecundara* noduriAdiacente;
};

void inserareListaSecundara(nodListaSecundara* *cap, int codNod) {
	nodListaSecundara * nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
	nou->cod = codNod;
	nou->next = NULL;
	if (*cap) {
		nodListaSecundara* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

void adaugareArc(int deLa, int panaLa, nodListaPrincipala*cap) {
	//se recomanda utilizarea de functii
	nodListaPrincipala*p = cap;
	while (p && p->cod != deLa) {
		p = p->next;
	}
	if (p) {
		inserareListaSecundara(&p->noduriAdiacente, panaLa);
	}

	p = cap;
	while (p && p->cod != panaLa) {
		p = p->next;
	}
	if (p) {
		inserareListaSecundara(&p->noduriAdiacente, deLa);
	}
}

nodListaPrincipala* initializareListaPrincipala(int nrNoduri) {
	nodListaPrincipala*cap = NULL;
	for (int i = nrNoduri - 1; i >= 0; i--) {
		nodListaPrincipala* nou = (nodListaPrincipala*)malloc(sizeof(nodListaPrincipala));
		nou->cod = i;
		nou->noduriAdiacente = NULL;
		nou->next = cap;
		cap = nou;
	}

	return cap;
}

void pushStack(nodListaSecundara**cap, int valoare) {
	nodListaSecundara* nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
	nou->cod = valoare;
	nou->next = *cap;
	*cap = nou;
}

int popStack(nodListaSecundara**cap) {
	if (*cap) {
		int rezultat = (*cap)->cod;
		nodListaSecundara*temp = *cap;
		*cap = (*cap)->next;
		free(temp);
		return rezultat;
	}
	else {
		return -1;
	}
}

void pushQueue(nodListaSecundara**cap, int cod) {
	inserareListaSecundara(cap, cod);
}

int popQueue(nodListaSecundara**cap) {
	return popStack(cap);
}

int numarNoduri(nodListaPrincipala*cap) {
	int nr = 0;
	while (cap) {
		nr++;
		cap = cap->next;
	}

	return nr;
}

void latime(nodListaPrincipala*graf, int nodPlecare) {
	nodListaSecundara*coada = NULL;
	int nrNoduri = numarNoduri(graf);

	int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}

	vizitate[nodPlecare] = 1;
	pushQueue(&coada, nodPlecare);

	while (coada) {
		int nodCurent = popQueue(&coada);
		printf("%d, ", nodCurent);
		nodListaPrincipala*p = graf;
		while (p && p->cod != nodCurent) {
			p = p->next;
		}
		if (p) {
			nodListaSecundara*s = p->noduriAdiacente;
			while (s) {
				if (vizitate[s->cod] == 0) {
					pushQueue(&coada, s->cod);
					vizitate[s->cod] = 1;
				}
				s = s->next;
			}
		}
	}
	free(vizitate);
}



int * adancime(nodListaPrincipala*graf, int nodPlecare, int nrNoduri) {
	nodListaSecundara*stiva = NULL;

	int*vizitate = (int*)malloc(nrNoduri * sizeof(int));
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	int* rezultat = (int*)malloc(nrNoduri * sizeof(int));
	int k = 0;

	pushStack(&stiva, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (stiva) {
		int nodCurent = popStack(&stiva);
		rezultat[k++] = nodCurent;
		nodListaPrincipala*p = graf;
		while (p && p->cod != nodCurent) {
			p = p->next;
		}
		if (p) {
			nodListaSecundara* s = p->noduriAdiacente;
			while (s) {
				if (vizitate[s->cod] == 0) {
					pushStack(&stiva, s->cod);
					vizitate[s->cod] = 1;
				}
				s = s->next;
			}
		}
	}
	free(vizitate);
	return rezultat;
}

int ** citireMatriceAdiacenta(int *nrNoduri) {
	printf("Numar noduri:");
	scanf("%d", nrNoduri);

	int**matrice = (int**)malloc(sizeof(int*)*(*nrNoduri));
	for (int i = 0; i < *nrNoduri; i++) {
		matrice[i] = (int*)malloc(sizeof(int)*(*nrNoduri));
		for (int j = 0; j < *nrNoduri; j++) {
			matrice[i][j] = 0;
		}
	}
	int nrArce;
	printf("Numar arce:");
	scanf("%d", &nrArce);

	for (int i = 0; i < nrArce; i++) {
		int cod1;
		int cod2;

		printf("De la:");
		scanf("%d", &cod1);
		printf("Pana la:");
		scanf("%d", &cod2);

		matrice[cod1][cod2] = 1;
		matrice[cod2][cod1] = 1;
	}

	return matrice;
}


int* latimePeMatrice(int**matrice, int nodPlecare, int nrNoduri) {
	nodListaSecundara*coada = NULL;

	int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}

	vizitate[nodPlecare] = 1;
	pushQueue(&coada, nodPlecare);

	int*rezultat = (int*)malloc(sizeof(int)*nrNoduri);
	int k = 0;
	while (coada) {
		int nodCurent = popQueue(&coada);
		rezultat[k++] = nodCurent;
		for (int i = 0; i < nrNoduri; i++) {
			if (matrice[nodCurent][i] == 1 && vizitate[i] == 0) {
				vizitate[i] = 1;
				pushQueue(&coada, i);
			}
		}
	}
	free(vizitate);
	return rezultat;

}

void main() {

	//int nrNoduri;
	//printf("Cate noduri avem:");
	//scanf("%d", &nrNoduri);
	//nodListaPrincipala* graf = initializareListaPrincipala(nrNoduri);

	//int codPlecare;
	//int codSosire;
	//printf("Codul nodului de plecare:");
	//scanf("%d", &codPlecare);
	//while (codPlecare != -1) {
	//	printf("Codul nodului de sosire:");
	//	scanf("%d", &codSosire);
	//	adaugareArc(codPlecare, codSosire, graf);

	//	printf("Codul nodului de plecare:");
	//	scanf("%d", &codPlecare);
	//}

	//int * parcurgere = adancime(graf, 0, nrNoduri);

	//for (int i = 0; i < nrNoduri; i++) {
	//	printf("%d,", parcurgere[i]);
	//}
	//printf("\nLatime:");
	//latime(graf, 0);

	//free(parcurgere);
	////stergere lista de liste si secundare si principala

	int nrNoduri;
	int**matrice = citireMatriceAdiacenta(&nrNoduri);
	int* rezultat = latimePeMatrice(matrice, 0, nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		printf("%d,", rezultat[i]);
	}


}