//#include<iostream>
//
//struct Imparat {
//	char * nume;
//	int anDomnie;
//};
//
//struct nod {
//	Imparat info;
//	nod* st;
//	nod* dr;
//};
//
//struct nodLista {
//	Imparat info;
//	nodLista*next;
//};
//
//Imparat creareImparat(char* nume, int anDomnie) {
//	Imparat im;
//	im.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
//	strcpy(im.nume, nume);
//	im.anDomnie = anDomnie;
//	return im;
//}
//
//nodLista* inserareInceput(nodLista* cap, Imparat info) {
//	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
//	nou->info = creareImparat(info.nume, info.anDomnie);
//	nou->next = cap;
//	return nou;
//}
//
//void afisareImparat(Imparat im) {
//	printf("Imparatul %s si-a inceput domnia in anul %d.\n", im.nume, im.anDomnie);
//}
//
//nod* inserareInArbore(nod* rad, Imparat im) {
//	if (rad) {
//		if (im.anDomnie < rad->info.anDomnie) {
//			rad->st = inserareInArbore(rad->st, im);
//		}
//		else if (im.anDomnie>rad->info.anDomnie) {
//			rad->dr = inserareInArbore(rad->dr, im);
//		}
//		return rad;
//	}
//	else {
//		nod* nou = (nod*)malloc(sizeof(nod));
//		nou->info = im;
//		nou->st = NULL;
//		nou->dr = NULL;
//		return nou;
//	}
//}
//
//void afisareArbore(nod*rad) {
//	if (rad) {
//		afisareArbore(rad->st);
//		afisareImparat(rad->info);
//		afisareArbore(rad->dr);
//	}
//}
//
//Imparat cautareImparatDupaAn(nod* rad, int anCautat) {
//	if (rad) {
//		if (rad->info.anDomnie == anCautat) {
//			return rad->info;
//		}
//		else if (rad->info.anDomnie<anCautat) {
//			return cautareImparatDupaAn(rad->dr, anCautat);
//		}
//		else {
//			return cautareImparatDupaAn(rad->st, anCautat);
//		}
//	}
//	else {
//		return creareImparat("", -1);
//	}
//}
//
//int inaltimeArbore(nod* rad) {
//	if (rad) {
//		int stanga = inaltimeArbore(rad->st);
//		int dreapta = inaltimeArbore(rad->dr);
//		return stanga > dreapta ? stanga + 1 : dreapta + 1;
//	}
//	else {
//		return 0;
//	}
//}
//
//void stergereArbore(nod** rad) {
//	if (*rad) {
//		stergereArbore(&(*rad)->st);
//		stergereArbore(&(*rad)->dr);
//		free((*rad)->info.nume);
//		free(*rad);
//		*rad = NULL;
//	}
//}
//
//void afisareDePeNivel(nod* rad, int nivelCautat, int nivelCurent) {
//	if (rad) {
//		if (nivelCautat == nivelCurent) {
//			afisareImparat(rad->info);
//		}
//		else {
//			afisareDePeNivel(rad->st, nivelCautat, nivelCurent + 1); 
//			afisareDePeNivel(rad->dr, nivelCautat, nivelCurent + 1);
//		}
//	}
//}
//
//nod* cautareMaxim(nod* rad) {
//	if (rad) {
//		while (rad->dr) {
//			rad = rad->dr;
//		}
//		return rad;
//	}
//}
//
//nod* stergereNod(nod* rad, int an) {
//	if (rad) {
//		if (an < rad->info.anDomnie) {
//			rad->st = stergereNod(rad->st, an);
//		}
//		else if (an>rad->info.anDomnie) {
//			rad->dr = stergereNod(rad->dr, an);
//		}
//		else {
//			//stergere nod
//			if (rad->st == NULL) {
//				nod* temp = rad->dr;
//				free(rad->info.nume);
//				free(rad);
//				return temp;
//			}
//			if (rad->dr == NULL) {
//				nod* temp = rad->st;
//				free(rad->info.nume);
//				free(rad);
//				return temp;
//			}
//			nod* temp = cautareMaxim(rad->st);
//			Imparat aux = temp->info;
//			temp->info = rad->info;
//			rad->info = aux;
//			rad->st = stergereNod(rad->st, an);
//			return rad;
//		}
//	}
//}
//
//
//Imparat extrageImparatDinArbore(nod**rad, int an) {
//	if (*rad) {
//		if (an > (*rad)->info.anDomnie) {
//			return extrageImparatDinArbore(&(*rad)->dr, an);
//		}
//		else if (an < (*rad)->info.anDomnie) {
//			return extrageImparatDinArbore(&(*rad)->st, an);
//		}
//		else {
//			if ((*rad) -> st == NULL) {
//				nod* temp = (*rad)->dr;
//				Imparat rezultat = (*rad)->info;
//				free(*rad);
//				*rad = temp;
//				return rezultat;
//			}
//			if ((*rad)->dr == NULL) {
//				nod* temp = (*rad)->st;
//				Imparat rezultat = (*rad)->info;
//				free(*rad);
//				*rad = temp;
//				return rezultat;
//			}
//			nod*temp = cautareMaxim((*rad)->st);
//			Imparat aux = (*rad)->info;
//			(*rad)->info = temp->info;
//			temp->info = aux;
//
//			return extrageImparatDinArbore(&(*rad)->st, an);
//		}
//	}
//}
//
//void copiereImparatiInLista(nodLista** cap, nod* rad) {
//	if(rad){
//		if (rad->info.anDomnie % 2 == 1) {
//			*cap = inserareInceput(*cap, rad->info);
//		}
//		copiereImparatiInLista(cap, rad->st);
//		copiereImparatiInLista(cap, rad->dr);
//	}
//}
//
//nodLista * ListaCuImparati(nod* rad) {
//	nodLista*cap = NULL;
//	if (rad) {
//		copiereImparatiInLista(&cap, rad);
//		
//	}
//	return cap;
//}
//
//void main() {
//
//	nod* rad = NULL;
//	rad = inserareInArbore(rad, creareImparat("Carol I", 8));
//	rad = inserareInArbore(rad, creareImparat("Carol II", 7));
//	rad = inserareInArbore(rad, creareImparat("Ferdinand", 3));
//	rad = inserareInArbore(rad, creareImparat("Traian", 12));
//	rad = inserareInArbore(rad, creareImparat("Cezar", 14));
//	rad = inserareInArbore(rad, creareImparat("Romulus", 10));
//	rad = inserareInArbore(rad, creareImparat("Napoleon", 11));
///*
//	afisareArbore(rad);
//
//	printf("\n");
//	afisareImparat(cautareImparatDupaAn(rad, 12));
//
//	printf("\nInaltime: %d\n\n", inaltimeArbore(rad));*/
//
//
//	//afisareDePeNivel(rad, 2, 1);
//
//	afisareArbore(rad);
//	printf("\n");
//	stergereNod(rad, 12);
//	//afisareImparat(extrageImparatDinArbore(&rad, 8));
//	printf("\n");
//	afisareArbore(rad);
//	//printf("\n");
//
//	//nodLista* cap = ListaCuImparati(rad);
//
//	//nodLista*copie = cap;
//	//while (cap) {
//	//	afisareImparat(cap->info);
//	//	cap = cap->next;
//	//}
//	//cap = copie;
//	//while (cap) {
//	//	free(cap->info.nume);
//	//	copie = cap;
//	//	cap = cap->next;
//	//	free(copie);
//	//}
//
//	stergereArbore(&rad);
//};