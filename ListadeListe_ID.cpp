//#include<iostream>
//
//struct Carte {
//	char* titlu;
//	int nrPagini;
//};
//
//struct nodDublu {
//	nodDublu* next;
//	nodDublu* prev;
//	Carte info;
//};
//
//struct nodSimplu {
//	nodSimplu* next;
//	nodDublu* first;
//	int nrMaximPagini;
//};
//
//Carte citesteCarte() {
//	Carte carte;
//	char buffer[20];
//	printf("Titlu:");
//	scanf("%s", buffer);
//	carte.titlu = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
//	strcpy(carte.titlu, buffer);
//
//	printf("Nr pagini:");
//	scanf("%d", &carte.nrPagini);
//
//	return carte;
//}
//
//nodDublu* inserareListaDubla(nodDublu* first, Carte info) {
//	if (first) {
//		nodDublu* p = first;
//		while (p->next) {
//			p = p->next;
//		}
//		nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
//		nou->info.nrPagini = info.nrPagini;
//		nou->info.titlu = (char*)malloc(sizeof(char)*(strlen(info.titlu) + 1));
//		strcpy(nou->info.titlu, info.titlu);
//		nou->next = NULL;
//		nou->prev = p;
//		p->next = nou;
//		return first;
//	}
//	else {
//		nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
//		nou->info.nrPagini = info.nrPagini;
//		nou->info.titlu = (char*)malloc(sizeof(char)*(strlen(info.titlu) + 1));
//		strcpy(nou->info.titlu, info.titlu);
//		nou->next = NULL;
//		nou->prev = NULL;
//		return nou;
//	}
//}
//
//nodSimplu* inserareListaPrincipala(nodSimplu* cap, Carte info) {
//	if (cap) {
//		//100 - 0-99
//		//200 - 100-199
//		if (cap->nrMaximPagini - 100 > info.nrPagini) {
//			nodSimplu* nou = (nodSimplu*)malloc(sizeof(nodSimplu));
//			nou->next = cap;
//			nou->nrMaximPagini = (info.nrPagini / 100 + 1) * 100;
//			nou->first = NULL;
//			nou->first = inserareListaDubla(nou->first, info);
//			return nou;
//		}
//		else {
//			if (cap->nrMaximPagini > info.nrPagini) {
//				cap->first = inserareListaDubla(cap->first, info);
//			}
//			else {
//				nodSimplu* p = cap;
//				while (p->next && p->next->nrMaximPagini < info.nrPagini) {
//					p = p->next;
//				}
//				if (p->next) {
//					if (p->next->nrMaximPagini - 100 < info.nrPagini) {
//						p->next->first = inserareListaDubla(p->next->first, info);
//					}
//					else {
//						nodSimplu* nou = (nodSimplu*)malloc(sizeof(nodSimplu));
//						nou->nrMaximPagini = (info.nrPagini / 100 + 1) * 100;
//						nou->next = p->next;
//						p->next = nou;
//						nou->first = NULL;
//						nou->first = inserareListaDubla(nou->first, info);
//					}
//
//				}
//				else {
//					nodSimplu* nou = (nodSimplu*)malloc(sizeof(nodSimplu));
//					nou->nrMaximPagini = (info.nrPagini / 100 + 1) * 100;
//					nou->next = NULL;
//					p->next = nou;
//					nou->first = NULL;
//					nou->first = inserareListaDubla(nou->first, info);
//
//				}
//			}
//				return cap;
//			}
//	}
//	else {
//		nodSimplu* nou = (nodSimplu*)malloc(sizeof(nodSimplu));
//		nou->nrMaximPagini = (info.nrPagini / 100 + 1) * 100;
//		nou->next = NULL;
//		nou->first = NULL;
//		nou->first = inserareListaDubla(nou->first, info);
//		return nou;
//	}
//}
//
//void afisareCarte(Carte carte) {
//	printf("Cartea %s are %d pagini\n", carte.titlu,carte.nrPagini);
//}
//
//void afisareListaDubla(nodDublu* first) {
//	while (first) {
//		afisareCarte(first->info);
//		first = first->next;
//	}
//}
//
//void afisareListaPrincipala(nodSimplu* cap) {
//	while (cap) {
//		afisareListaDubla(cap->first);
//		printf("\n\n");
//		cap = cap->next;
//	}
//}
//
//nodDublu* stergereListaDubla(nodDublu* first) {
//	while (first) {
//		free(first->info.titlu);
//		nodDublu*temp = first;
//		first = first->next;
//		free(temp);
//	}
//	return NULL;
//}
//
//nodSimplu* stergereListaPrincipala(nodSimplu* cap) {
//	while (cap) {
//		cap->first=stergereListaDubla(cap->first);
//		nodSimplu* t = cap;
//		cap = cap->next;
//		free(t);
//	}
//	return cap;
//}
//
//
//void main(){
//
//	nodSimplu* cap = NULL;
//	cap = inserareListaPrincipala(cap, citesteCarte());
//	cap = inserareListaPrincipala(cap, citesteCarte());
//	cap = inserareListaPrincipala(cap, citesteCarte());
//	cap = inserareListaPrincipala(cap, citesteCarte());
//
//	afisareListaPrincipala(cap);
//	cap = stergereListaPrincipala(cap);
//
//}