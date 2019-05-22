//#include<stdio.h>
//#include<malloc.h>
//#include<string.h>
//
//struct Muzeu {
//	int id;
//	char* nume;
//};
//
//struct nodListaPrincipala;
//
//struct nodListaSecundara {
//	nodListaPrincipala*info;
//	nodListaSecundara* next;
//};
//
//struct nodListaPrincipala {
//	Muzeu info;
//	nodListaSecundara* vecini;
//	nodListaPrincipala*next;
//};
//
//nodListaSecundara* inserareListaSecundara(nodListaSecundara* cap, nodListaPrincipala* info) {
//	nodListaSecundara* nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
//	nou->next = cap;
//	nou->info = info;
//	return nou;
//}
//
//nodListaPrincipala* inseareListaPrincipala(nodListaPrincipala* cap, Muzeu info) {
//	nodListaPrincipala* nou = (nodListaPrincipala*)malloc(sizeof(nodListaPrincipala));
//	nou->info = info;
//	nou->next = NULL;
//	nou->vecini = NULL;
//	if (cap) {
//		nodListaPrincipala*p = cap;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = nou;
//	}
//	else {
//		cap = nou;
//	}
//	return cap;
//}
//
//nodListaPrincipala* cautareNodDupaIDMuzeu(nodListaPrincipala*cap, int id) {
//	while (cap && cap->info.id != id) {
//		cap = cap->next;
//	}
//	return cap;
//}
//
//void adaugareArcInGraf(nodListaPrincipala* graf, int idStart, int idStop) {
//	nodListaPrincipala*nodStart = cautareNodDupaIDMuzeu(graf, idStart);
//	nodListaPrincipala*nodStop = cautareNodDupaIDMuzeu(graf, idStop);
//	if (nodStart && nodStop) {
//		nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
//		nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
//	}
//}
//
//
//void afisareListaSecundara(nodListaSecundara* cap) {
//	while (cap) {
//		printf("      %d.%s\n", cap->info->info.id, cap->info->info.nume);
//		cap = cap->next;
//	}
//}
//
//void afisareListaPrincipala(nodListaPrincipala* cap) {
//	while (cap) {
//		printf("      %d.%s are ca vecini urmatoarele muzee\n", cap->info.id, cap->info.nume);
//		afisareListaSecundara(cap->vecini);
//		cap = cap->next;
//	}
//}
//
//struct nodCoada {
//	int id;
//	nodCoada* next;
//};
//
//nodCoada* inserareCoada(nodCoada* cap, int id) {
//	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
//	nou->id = id;
//	nou->next = NULL;
//	if (cap) {
//		nodCoada*p = cap;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = nou;
//		return cap;
//	}
//	else {
//		return nou;
//	}
//}
//
//int extragereDinCoada(nodCoada* &cap) {
//	if (cap) {
//		int rezultat = cap->id;
//		nodCoada* aux = cap;
//		cap = cap->next;
//		free(aux);
//		return rezultat;
//	}
//	else {
//		return -1;
//	}
//}
//
//int calculareNumarNoduri(nodListaPrincipala* graf) {
//	int nr = 0;
//	while (graf) {
//		nr++;
//		graf = graf->next;
//	}
//	return nr;
//}
//
//void parcurgereInLatime(nodListaPrincipala* graf, int idStart) {
//	if (graf) {
//		nodCoada* coada = NULL;
//		int nrNoduri = calculareNumarNoduri(graf);
//		int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
//		for (int i = 0; i < nrNoduri; i++) {
//			vizitate[i] = 0;
//		}
//
//		coada = inserareCoada(coada, idStart);
//		vizitate[idStart] = 1;
//
//		while (coada) {
//			int idNodCurent = extragereDinCoada(coada);
//			nodListaPrincipala* nodCurent = cautareNodDupaIDMuzeu(graf, idNodCurent);
//			printf("%d.%s\n", nodCurent->info.id, nodCurent->info.nume);
//			nodListaSecundara* p = nodCurent->vecini;
//
//			while (p) {
//				if (vizitate[p->info->info.id] == 0) {
//					vizitate[p->info->info.id] = 1;
//					coada = inserareCoada(coada, p->info->info.id);
//				}
//				p = p->next;
//			}
//
//		}
//	}
//}
//
//void main() {
//	nodListaPrincipala*graf = NULL;
//	int nrNoduri = 0;
//	printf("Numarul de noduri:");
//	scanf("%d", &nrNoduri);
//	for (int i = 0; i < nrNoduri; i++) {
//		char buffer[20];
//
//		printf("Nume muzeu:");
//		scanf("%s", buffer);
//
//		Muzeu m;
//		m.id = i;
//		m.nume = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
//		strcpy(m.nume, buffer);
//		graf = inseareListaPrincipala(graf, m);
//	}
//	int nrArce = 0;
//	printf("Numarul de arce:");
//	scanf("%d", &nrArce);
//
//	for (int i = 0; i < nrArce; i++) {
//		int idNodStart = 0;
//		printf("Id nod start:");
//		scanf("%d", &idNodStart);
//		int idNodStop= 0;
//		printf("Id nod stop:");
//		scanf("%d", &idNodStop);
//		adaugareArcInGraf(graf, idNodStart, idNodStop);
//	}
//
//	afisareListaPrincipala(graf);
//
//	parcurgereInLatime(graf, 0);
//}