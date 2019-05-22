//#include<stdio.h>
//#include<malloc.h>
//#include<string.h>
//
//struct Drink {
//	int id;
//	char* denumire;
//};
//
//struct nodListaPrincipala;
//
//struct nodListaSimpla {
//	nodListaPrincipala* info;
//	nodListaSimpla* next;
//};
//
//struct nodListaPrincipala {
//	nodListaSimpla* noduriAdiacente;
//	nodListaPrincipala* next;
//	Drink info;
//};
//
//nodListaPrincipala* inserareListaPrincipala(nodListaPrincipala*cap, Drink d) {
//	nodListaPrincipala* nodNou = (nodListaPrincipala*)malloc(sizeof(nodListaPrincipala));
//	nodNou->next = cap;
//	nodNou->noduriAdiacente = NULL;
//	nodNou->info = d;
//	return nodNou;
//}
//
//nodListaSimpla* inserareListaSimpla(nodListaSimpla* cap, nodListaPrincipala* info) {
//	nodListaSimpla* nodNou = (nodListaSimpla*)malloc(sizeof(nodListaSimpla));
//	nodNou->next = cap;
//	nodNou->info = info;
//	return nodNou;
//}
//nodListaPrincipala* cautareNodDupaID(nodListaPrincipala* cap, int id) {
//	while (cap && cap->info.id != id) {
//		cap = cap->next;
//	}
//	return cap;
//}
//
//void inserareArcInGraf(nodListaPrincipala* graf, int nodStart, int nodStop) {
//	nodListaPrincipala* from = cautareNodDupaID(graf, nodStart);
//	nodListaPrincipala* to = cautareNodDupaID(graf, nodStop);
//	if (from && to) {
//		from->noduriAdiacente = inserareListaSimpla(from->noduriAdiacente, to);
//		to->noduriAdiacente = inserareListaSimpla(to->noduriAdiacente, from);
//	}
//}
//
//void afisareListaSimpla(nodListaSimpla* cap) {
//	while (cap) {
//		printf("    %d.%s\n", cap->info->info.id,cap->info->info.denumire);
//		cap = cap->next;
//	}
//}
//
//void afisareListaPrincipala(nodListaPrincipala* cap) {
//	while (cap) {
//		printf("%d.%s are vecini:\n", cap->info.id, cap->info.denumire);
//		afisareListaSimpla(cap->noduriAdiacente);
//		cap = cap->next;
//	}
//}
//
//struct nodStiva {
//	int id;
//	nodStiva*next;
//};
//
//nodStiva* push(nodStiva* cap, int id) {
//	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
//	nou->next = cap;
//	nou->id = id;
//	return nou;
//}
//
//int pop(nodStiva*&cap) {
//	if (cap) {
//		int id = cap->id;
//		cap = cap->next;
//		return id;
//	}
//	else {
//		return -1;
//	}
//}
//
//void parcurgereInAdancime(nodListaPrincipala* graf, int nodStart) {
//	if (graf) {
//		//1. initializam stiva si vectorul de vizitate;
//		//2. inseram nodul de start in stiva si il marcam ca vizitat
//		//3. extragem un nod din stiva
//		//4. afisam nodul extras
//		//5. adaugam in stiva nodurile adiacente nevizitate marcandu-le ca find vizitate
//		//6. ne intoarcem la pasul 3
//	}
//}
//
//
//void main() {
//	nodListaPrincipala* graf = NULL;
//	int nrNoduri = 0;
//	printf("NUmar noduri:");
//	scanf("%d", &nrNoduri);
//	for (int i = nrNoduri-1; i>=0; i--) {
//		Drink d;
//		d.id = i;
//		char buffer[20];
//		printf("Numele bauturii:");
//		scanf("%s", buffer);
//		d.denumire = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
//		strcpy(d.denumire, buffer);
//		graf = inserareListaPrincipala(graf, d);
//	}
//	int nrArce = 0;
//	printf("NUmar arce:");
//	scanf("%d", &nrArce);
//
//	for (int i = 0; i < nrArce; i++) {
//		int from = 0;
//		printf("Nod start:");
//		scanf("%d", &from);
//		int to = 0;
//		printf("Nod stop:");
//		scanf("%d", &to);
//		inserareArcInGraf(graf, from, to);
//	}
//
//	afisareListaPrincipala(graf);
//}