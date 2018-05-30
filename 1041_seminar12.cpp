//#include<iostream>
//
//struct nodSecundar {
//	int cod;
//	nodSecundar*next;
//};
//
//struct nodPrincipal {
//	int cod;
//	nodSecundar*adiacente;
//	nodPrincipal*next;
//};
//
//nodSecundar* inserareListaSecundara(nodSecundar*cap, int cod) {
//	nodSecundar* nou = (nodSecundar*)malloc(sizeof(nodSecundar));
//	nou->next = NULL;
//	nou->cod = cod;
//	if (cap) {
//		nodSecundar*aux = cap;
//		while (aux->next) {
//			aux = aux->next;
//		}
//		aux->next = nou;
//		return cap;
//	}
//	else {
//		return nou;
//	}
//}
//
//void pushStack(nodSecundar**cap, int cod) {
//	nodSecundar*nou = (nodSecundar*)malloc(sizeof(nodSecundar));
//	nou->cod = cod;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//int popStack(nodSecundar**cap) {
//	if (*cap) {
//		nodSecundar*aux = (*cap)->next;
//		int rezultat =(*cap)->cod;
//		free(*cap);
//		*cap = aux;
//		return rezultat;
//	}
//	else {
//		return -1;
//	}
//}
//
//void pushQueue(nodSecundar**cap, int cod) {
//	*cap = inserareListaSecundara(*cap, cod);
//}
//
//int popQueue(nodSecundar**cap) {
//	return popStack(cap);
//}
//
//nodPrincipal*creareListaPrincipala(int nrNoduri) {
//	nodPrincipal*cap = NULL;
//	for (int i = nrNoduri - 1; i >= 0; i--) {
//		nodPrincipal*nou = (nodPrincipal*)malloc(sizeof(nodPrincipal));
//		nou->cod = i;
//		nou->adiacente = NULL;
//		nou->next = cap;
//		cap = nou;
//	}
//	return cap;
//}
//
//void inserareMuchie(int cod1, int cod2, nodPrincipal*cap) {
//	nodPrincipal*p = cap;
//	while (p && p->cod != cod1) {
//		p = p->next;
//	}
//	if (p) {
//		p->adiacente = inserareListaSecundara(p->adiacente, cod2);
//	}
//}
//
//nodPrincipal* citireGrafListaDeListe() {
//	int nrNoduri;
//	printf("Numarul de noduri:");
//	scanf("%d", &nrNoduri);
//
//	nodPrincipal*graf = creareListaPrincipala(nrNoduri);
//	int cod1;
//	int cod2;
//
//	printf("De la:");
//	scanf("%d", &cod1);
//	while (cod1 != -1) {
//		printf("Pana la:");
//		scanf("%d", &cod2);
//		inserareMuchie(cod1, cod2, graf);
//		inserareMuchie(cod2, cod1, graf);
//		printf("De la:");
//		scanf("%d", &cod1);
//	}
//
//	return graf;
//}
//
//int nrNoduri(nodPrincipal*cap) {
//	int nr = 0;
//	while (cap) {
//		nr++;
//		cap = cap->next;
//	}
//	return nr;
//}
//
//void adancime(nodPrincipal* graf, int nodPlecare) {
//	nodSecundar*stiva = NULL;
//	pushStack(&stiva, nodPlecare);
//	int nr = nrNoduri(graf);
//	int* vizitate = (int*)malloc(sizeof(int)*nr);
//	for (int i = 0; i < nr; i++) {
//		vizitate[i] = 0;
//	}
//
//	vizitate[nodPlecare] = 1;
//
//	while (stiva) {
//		int nodCurent = popStack(&stiva);
//		printf("%d, ", nodCurent);
//		nodPrincipal*p = graf;
//		while (p && p->cod != nodCurent) {
//			p = p->next;
//		}
//		if (p) {
//			nodSecundar*s = p->adiacente;
//			while (s) {
//				if (vizitate[s->cod] == 0) {
//					vizitate[s->cod] = 1;
//					pushStack(&stiva, s->cod);
//				}
//				s = s->next;
//			}
//		}
//	}
//	free(vizitate);
//}
//
//
//void latime(nodPrincipal* graf, int nodPlecare) {
//	nodSecundar*coada = NULL;
//	pushQueue(&coada, nodPlecare);
//	int nr = nrNoduri(graf);
//	int* vizitate = (int*)malloc(sizeof(int)*nr);
//	for (int i = 0; i < nr; i++) {
//		vizitate[i] = 0;
//	}
//
//	vizitate[nodPlecare] = 1;
//
//	while (coada) {
//		int nodCurent = popQueue(&coada);
//		printf("%d, ", nodCurent);
//		nodPrincipal*p = graf;
//		while (p && p->cod != nodCurent) {
//			p = p->next;
//		}
//		if (p) {
//			nodSecundar*s = p->adiacente;
//			while (s) {
//				if (vizitate[s->cod] == 0) {
//					vizitate[s->cod] = 1;
//					pushQueue(&coada, s->cod);
//				}
//				s = s->next;
//			}
//		}
//	}
//	free(vizitate);
//}
//
//void main() {
//	nodPrincipal*graf = citireGrafListaDeListe();
//	adancime(graf, 0);
//	printf("\n");
//	latime(graf, 0);
//
//
//}