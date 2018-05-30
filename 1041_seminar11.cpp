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
//		afisareImparat(rad->info);
//		afisareArbore(rad->st);
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
//int gradEchilibru(nod* rad) {
//	return inaltimeArbore(rad->dr) - inaltimeArbore(rad->st);
//}
//
//nod* rotireStanga(nod* rad) {
//	nod* temp = rad->dr;
//	rad->dr = temp->st;
//	temp->st = rad;
//	return temp;
//}
//
//nod* rotireDreapta(nod* rad) {
//	nod* temp = rad->st;
//	rad->st = temp->dr;
//	temp->dr = rad;
//	return temp;
//}
//
//nod* inserareAVL(nod* rad, Imparat info) {
//	if (rad) {
//		if (info.anDomnie < rad->info.anDomnie) {
//			rad->st = inserareAVL(rad->st,info);
//		}
//		else {
//			rad->dr = inserareAVL(rad->dr, info);
//		}
//		//trebuie sa echilibram
//		int GE = gradEchilibru(rad);
//		if (GE == 2) {
//			if (gradEchilibru(rad->dr) == 1) {
//				rad = rotireStanga(rad);
//			}
//			else {
//				rad->dr = rotireDreapta(rad->dr);
//				rad = rotireStanga(rad);
//			}
//		}
//		if (GE == -2) {
//			if (gradEchilibru(rad->st) == -1) {
//				rad = rotireDreapta(rad);
//			}
//			else {
//				rad->st = rotireStanga(rad->st);
//				rad = rotireDreapta(rad);
//			}
//		}
//		return rad;
//	}
//	else {
//		nod* nou = (nod*)malloc(sizeof(nod));
//		nou->info = info;
//		nou->dr = NULL;
//		nou->st = NULL;
//		return nou;
//	}
//}
//
//void main() {
//
//	nod* rad = NULL;
//	rad = inserareAVL(rad, creareImparat("Carol I", 1));
//	rad = inserareAVL(rad, creareImparat("Carol II", 2));
//	rad = inserareAVL(rad, creareImparat("Ferdinand", 3));
//	rad = inserareAVL(rad, creareImparat("Traian", 4));
//	rad = inserareAVL(rad, creareImparat("Cezar", 5));
//	rad = inserareAVL(rad, creareImparat("Romulus", 6));
//	rad = inserareAVL(rad, creareImparat("Napoleon", 7));
//	afisareArbore(rad);
//
//	stergereArbore(&rad);
//};