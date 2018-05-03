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
//Imparat creareImparat(char* nume, int anDomnie) {
//	Imparat im;
//	im.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
//	strcpy(im.nume, nume);
//	im.anDomnie = anDomnie;
//	return im;
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
//		else if(im.anDomnie>rad->info.anDomnie){
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
//		else if(rad->info.anDomnie<anCautat){
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
//void main() {
//
//	nod* rad = NULL;
//	rad = inserareInArbore(rad, creareImparat("Carol I", 8));
//	rad = inserareInArbore(rad, creareImparat("Carol II", 6));
//	rad = inserareInArbore(rad, creareImparat("Ferdinand", 4));
//	rad = inserareInArbore(rad, creareImparat("Traian", 12));
//	rad = inserareInArbore(rad, creareImparat("Cezar", 14));
//	rad = inserareInArbore(rad, creareImparat("Romulus", 10));
//	rad = inserareInArbore(rad, creareImparat("Napoleon", 11));
//
//	afisareArbore(rad);
//
//	printf("\n");
//	afisareImparat(cautareImparatDupaAn(rad, 12));
//
//	printf("\nInaltime: %d\n\n", inaltimeArbore(rad));
//
//	stergereArbore(&rad);
//};