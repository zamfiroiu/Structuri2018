//#include<stdio.h>
//#include<malloc.h>
//#include<string.h>
//
//struct Comanda {
//	int id;
//	char* denumire;
//};
//
//struct nodStiva {
//	int id;
//	nodStiva*next;
//};
//
//nodStiva * push(nodStiva* cap, int id) {
//	nodStiva* nodNou = (nodStiva*)malloc(sizeof(nodStiva));
//	nodNou->id = id;
//	nodNou->next = NULL;
//	if (cap) {
//		nodStiva* p = cap;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = nodNou;
//	}
//	else {
//		cap = nodNou;
//	}
//	return cap;
//}
//int pop(nodStiva* &cap) {
//	if (cap) {
//		nodStiva*p = cap;
//		while (p->next && p->next->next) {
//			p = p->next;
//		}
//		if (p->next) {
//			int rezultat = p->next->id;
//			free(p->next);
//			p->next = NULL;
//			return rezultat;
//		}
//		else {
//			int rezultat = p->id;
//			free(p);
//			cap = NULL;
//			return rezultat;
//		}
//	}
//	else {
//		return -1;//nu exista id-ul
//	}
//}
//
//struct nodListaPrincipala;
//
//struct nodListaSimpla {
//	nodListaPrincipala* info;
//	nodListaSimpla*next;
//};
//
//struct nodListaPrincipala {
//	Comanda info;
//	nodListaPrincipala* next;
//	nodListaSimpla* adiacente;
//};
//
//nodListaSimpla* inserareListaSimpla(nodListaSimpla* cap, nodListaPrincipala* nod) {
//	nodListaSimpla* nodNou = (nodListaSimpla*)malloc(sizeof(nodListaSimpla));
//	nodNou->next = NULL;
//	nodNou->info = nod;
//	if (cap) {
//		nodListaSimpla*temp = cap;
//		while (temp->next) {
//			temp = temp->next;
//		}
//		temp->next = nodNou;
//	}
//	else {
//		cap = nodNou;
//	}
//	return cap;
//}
//
//nodListaPrincipala* inserareListaPrincipala(nodListaPrincipala* cap, Comanda c) {
//	nodListaPrincipala* nodNou = (nodListaPrincipala*)malloc(sizeof(nodListaPrincipala));
//	nodNou->adiacente = NULL;
//	nodNou->info = c;
//	nodNou->next = NULL;
//	if (cap) {
//		nodListaPrincipala* p = cap;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = nodNou;
//	}
//	else {
//		cap = nodNou;
//	}
//
//	return cap;
//}
//
//nodListaPrincipala* cautareDupaID(nodListaPrincipala*cap, int id) {
//	while (cap && cap->info.id != id) {
//		cap = cap->next;
//	}
//	return cap;
//}
//
//void adaugareArcInGrafNeorientat(int de_la, int pana_la, nodListaPrincipala* graf) {
//	nodListaPrincipala* DE = cautareDupaID(graf, de_la);
//	nodListaPrincipala* PANA = cautareDupaID(graf, pana_la);
//	if (DE && PANA) {
//		DE->adiacente = inserareListaSimpla(DE->adiacente, PANA);
//		PANA->adiacente = inserareListaSimpla(PANA->adiacente, DE);
//	}
//
//}
//
//void afisareListaSimpla(nodListaSimpla* cap) {
//	while (cap) {
//		printf("     %d. %s\n", cap->info->info.id, cap->info->info.denumire);
//		cap = cap->next;
//	}
//}
//
//void afisareGraf(nodListaPrincipala* graf) {
//	while (graf) {
//		printf("%d.%s are nodurile adiacente:\n", graf->info.id, graf->info.denumire);
//		afisareListaSimpla(graf->adiacente);
//		graf = graf->next;
//	}
//}
//
//int calculareNrNoduri(nodListaPrincipala* cap) {
//	int nr = 0;
//	while (cap) {
//		nr++;
//		cap = cap->next;
//	}
//
//	return nr;
//}
//
//void parcurgereInAdancime(nodListaPrincipala*graf, int nodStart) {
//	//1. ne luam o stiva
//	//2. adaugam nodul de start in stiva;
//	//3. luam un vector de vizitate initializat cu 0 pe toate pozitiile
//	//4. vizitam nodul de start;
//	//5. extragem element din stiva
//	//6. il afisam/ procesam
//	//7. adaugam in stiva nodurile adiacente nevizitate
//	//8. ne intarcem la pasul 5
//	nodStiva* stiva = NULL;
//	stiva = push(stiva, nodStart);
//	int nrNoduri = calculareNrNoduri(graf);
//	int*vizitate = (int*)malloc(sizeof(int)*nrNoduri);
//	for (int i = 0; i < nrNoduri; i++) {
//		vizitate[i] = 0;
//	}
//	vizitate[nodStart] = 1;
//	while (stiva) {
//		int nodCurent = pop(stiva);
//		nodListaPrincipala* nodC = cautareDupaID(graf, nodCurent);
//		printf("%d.%s", nodC->info.id,nodC->info.denumire);
//		nodListaSimpla* temp = nodC->adiacente;
//		while (temp) {
//			if (vizitate[temp->info->info.id] == 0) {
//				stiva = push(stiva, temp->info->info.id);
//				vizitate[temp->info->info.id] = 1;
//			}
//			temp = temp->next;
//		}
//
//	}
//}
//
//void main() {
//	nodListaPrincipala* graf = NULL;
//	printf("Cate noduri avem:");
//	int nrNoduri = 0;
//	scanf("%d", &nrNoduri);
//	for (int i = 0; i < nrNoduri; i++) {
//		Comanda c;
//		c.id = i;
//		char buffer[20];
//		printf("Denumirea comenzii:");
//		scanf("%s", buffer);
//		c.denumire = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
//		strcpy(c.denumire, buffer);
//		graf = inserareListaPrincipala(graf, c);
//	}
//	printf("Cate Arce avem:");
//	int nrArce = 0;
//	scanf("%d", &nrArce);
//	for (int i = 0; i < nrArce; i++) {
//		printf("De la:");
//		int de_la = 0;
//		scanf("%d", &de_la);
//		printf("Pana la:");
//		int pana_la = 0;
//		scanf("%d", &pana_la);
//		adaugareArcInGrafNeorientat(de_la, pana_la, graf);
//	}
//	afisareGraf(graf);
//
//	parcurgereInAdancime(graf, 0);
//
//}