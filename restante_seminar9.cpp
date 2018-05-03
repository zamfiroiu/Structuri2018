//#include<iostream>
//
//struct Gradina {
//	char*nume;
//	int nrPlante;
//};
//
//Gradina creareGradina(char* nume, int nrPlante) {
//	Gradina im;
//	im.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
//	strcpy(im.nume, nume);
//	im.nrPlante = nrPlante;
//	return im;
//}
//
//struct nod {
//	nod* st;
//	nod* dr;
//	Gradina info;
//};
//
//nod* inserare(nod* rad, Gradina g) {
//	if (rad) {
//		if (g.nrPlante < rad->info.nrPlante) {
//			rad->st = inserare(rad->st, g);
//		}
//		else if(g.nrPlante>rad->info.nrPlante) {
//			rad->dr = inserare(rad->dr, g);
//		}
//		return rad;
//	}
//	else {
//		nod* nou = (nod*)malloc(sizeof(nod));
//		nou->info = g;
//		nou->st = NULL;
//		nou->dr = NULL;
//		return nou;
//	}
//}
//
//void afisareGradina(Gradina g) {
//	printf("Gradina %s are %d plante.\n", g.nume, g.nrPlante);
//}
//
//void afisareArbore(nod* rad) {
//	if (rad) {
//		afisareArbore(rad->st);
//		afisareGradina(rad->info);
//		afisareArbore(rad->dr);
//	}
//}
//
//Gradina cautareGradinaDupaNrPlante(nod* rad, int nrPlante) {
//	if(rad){
//		if (rad->info.nrPlante == nrPlante) {
//			return rad->info;
//		}
//		else if(rad->info.nrPlante< nrPlante){
//			return cautareGradinaDupaNrPlante(rad->dr, nrPlante);
//		}
//		else {
//			return cautareGradinaDupaNrPlante(rad->st, nrPlante);
//		}
//	}
//	else {
//		return creareGradina("", -1);
//	}
//}
//
//void stergereArbore(nod** rad) {
//	if (*rad) {
//		nod* stanga = (*rad)->st;
//		stergereArbore(&stanga);
//		stergereArbore(&(*rad)->dr);
//		free((*rad)->info.nume);
//		free(*rad);
//		*rad = NULL;
//	}
//}
//
//int inaltime(nod* rad) {
//	if (rad) {
//		int stanga = inaltime(rad->st);
//		int dreapta = inaltime(rad->dr);
//		int maxim = stanga < dreapta ? dreapta : stanga;
//		maxim++;
//		return maxim;
//	}
//	else {
//		return 0;
//	}
//}
//
//void main() {
//	nod* rad = NULL;
//	rad = inserare(rad, creareGradina("Cismigiu", 8));
//	rad = inserare(rad, creareGradina("Botanica", 10));
//	rad = inserare(rad, creareGradina("Carol", 9));
//	rad = inserare(rad, creareGradina("Zoologica", 3));
//	rad = inserare(rad, creareGradina("Herastrau", 1));
//	rad = inserare(rad, creareGradina("Mihai I", 6));
//	rad = inserare(rad, creareGradina("Moghioros", 5));
//
//	afisareArbore(rad);
//
//	printf("\n");
//
//	afisareGradina(cautareGradinaDupaNrPlante(rad, 9));
//
//	printf("inaltime: %d", inaltime(rad));
//
//	stergereArbore(&rad);
//	printf("arbborele:\n");
//	afisareArbore(rad);
//}