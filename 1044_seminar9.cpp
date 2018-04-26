#include<iostream>

struct Vacanta {
	char* destinatie;
	float pret;
};

struct nod {
	Vacanta info;
	nod* st;
	nod*dr;
};

Vacanta creareVacanta(const char* dest, const float pret) {
	Vacanta v;
	v.destinatie = (char*)malloc(sizeof(char)*(strlen(dest) + 1));
	strcpy_s(v.destinatie, strlen(dest) + 1, dest);
	v.pret = pret;

	return v;
}

void afisareVacanta(Vacanta v) {
	printf("Vacanta din %s costa %5.2f lei\n", v.destinatie, v.pret);
}

nod* inserareInArbore(nod* root, Vacanta v) {
	if (root) {
		if (v.pret < root->info.pret) {
			root->st = inserareInArbore(root->st, v);
		}
		else if(v.pret>root->info.pret) {
			root->dr = inserareInArbore(root->dr, v);
		}
		return root;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = v;
		nou->dr = NULL;
		nou->st = NULL;
		return nou;
	}
}

void afisareSRD(nod* root) {
	if (root) {
		afisareSRD(root->st);
		afisareVacanta(root->info);
		afisareSRD(root->dr);
	}
}

Vacanta cautareVacantaDupaPret(nod*root, float pret) {
	if (root) {
		if (root->info.pret > pret) {
			return cautareVacantaDupaPret(root->st, pret);
		}
		else if (root->info.pret < pret) {
			return cautareVacantaDupaPret(root->dr, pret);
		}
		else {
			Vacanta rezultat = creareVacanta(root->info.destinatie, root->info.pret);
			return rezultat;
		}
	}
	else {
		Vacanta rezultat = creareVacanta("", -1);
		return rezultat;
	}
}

void stergereArbore(nod** root) {
	if (*root) {
		stergereArbore(&(*root)->st);
		stergereArbore(&(*root)->dr);
		free((*root)->info.destinatie);
		free(*root);
		*root = NULL;
	}
}


int maxim(int a, int b) {
	return (a < b) ? b : a;
}

int inaltimeArbore(nod*root) {
	if (root) {
		return 1 + maxim(inaltimeArbore(root->st), inaltimeArbore(root->dr));
	}
	else {
		return 0;
	}
}

void afisareNivelDinArbore(nod*root, int nivelCautat, int *nivelCurent) {
	if (root) {
		if (*nivelCurent == nivelCautat) {
			afisareVacanta(root->info);
		}
		else {
			(*nivelCurent)++;
			afisareNivelDinArbore(root->st, nivelCautat, nivelCurent);

			(*nivelCurent)--;
			afisareNivelDinArbore(root->dr, nivelCautat, nivelCurent);
		}
	}
}

void main() {
	nod* root=NULL;
	root = inserareInArbore(root, creareVacanta("Dubai", 7));
	root = inserareInArbore(root, creareVacanta("Ibiza", 3));
	root = inserareInArbore(root, creareVacanta("Monaco", 1));
	root = inserareInArbore(root, creareVacanta("Barcelona", 12));
	root = inserareInArbore(root, creareVacanta("Tenerife", 10));
	root = inserareInArbore(root, creareVacanta("Coasta de azur", 11));
	root = inserareInArbore(root, creareVacanta("Coasta de azur", 8));

	afisareSRD(root);
	printf("Inaltime:%d\n", inaltimeArbore(root));
	root = inserareInArbore(root, creareVacanta("Moscova", 9));
	printf("Inaltime:%d\n", inaltimeArbore(root));

	afisareSRD(root);

	Vacanta v = cautareVacantaDupaPret(root, 10);

	printf("\n");
	afisareVacanta(v);

	printf("%d\n", inaltimeArbore(root));

	int nivel = 1;
	afisareNivelDinArbore(root, 2, &nivel);
	stergereArbore(&root);
}