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

void main() {

	int nrNoduri;
	printf("Cate noduri avem:");
	scanf("%d", &nrNoduri);
	nodListaPrincipala* graf = initializareListaPrincipala(nrNoduri);

	int codPlecare;
	int codSosire;
	printf("Codul nodului de plecare:");
	scanf("%d", &codPlecare);
	while (codPlecare != -1) {
		printf("Codul nodului de sosire:");
		scanf("%d", &codSosire);
		adaugareArc(codPlecare, codSosire, graf);

		printf("Codul nodului de plecare:");
		scanf("%d", &codPlecare);
	}

	int * parcurgere = adancime(graf, 0, nrNoduri);

	for (int i = 0; i < nrNoduri; i++) {
		printf("%d,",parcurgere[i]);
	}

	free(parcurgere);
	//stergere lista de liste si secundare si principala

}