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

struct nodLista {
	Vacanta info;
	nodLista* next;
};

Vacanta creareVacanta(const char* dest, const float pret) {
	Vacanta v;
	v.destinatie = (char*)malloc(sizeof(char)*(strlen(dest) + 1));
	strcpy_s(v.destinatie, strlen(dest) + 1, dest);
	v.pret = pret;

	return v;
}
nodLista* inserareInceput(nodLista* cap, Vacanta v) {
	nodLista*nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info = creareVacanta(v.destinatie, v.pret);
	nou->next = cap;
	return nou;
}

void copiereInLista(nod*root, nodLista** cap, char litera) {
	if (root) {
		copiereInLista(root->st, cap, litera);
		if (root->info.destinatie[0] == litera) {
			*cap = inserareInceput(*cap, root->info);
		}
		copiereInLista(root->dr, cap, litera);
	}
}


void afisareVacanta(Vacanta v) {
	printf("Vacanta din %s costa %5.2f lei\n", v.destinatie, v.pret);
}

nod* inserareInArbore(nod* root, Vacanta v) {
	if (root) {
		if (v.pret < root->info.pret) {
			root->st = inserareInArbore(root->st, v);
		}
		else if (v.pret>root->info.pret) {
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


void afisareRSD(nod* root) {
	if (root) {
		afisareVacanta(root->info);
		afisareRSD(root->st);
		afisareRSD(root->dr);
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

int gradEchilibru(nod* root) {
	return inaltimeArbore(root->dr) - inaltimeArbore(root->st);
}

nod* rotireStanga(nod* root) {
	nod* aux = root->dr;
	root->dr = aux->st;
	aux->st = root;
	return aux;
}

nod* rotireDreapta(nod* root) {
	nod* temp = root->st;
	root->st = temp->dr;
	temp->dr = root;
	return temp;
}

nod* inserareAVL(nod* root, Vacanta v) {
	if (root) {
		if (v.pret < root->info.pret) {
			root->st = inserareAVL(root->st, v);
		}
		else {
			root->dr = inserareAVL(root->dr, v);
		}
		int GE = gradEchilibru(root);
		if (GE == 2) {
			if (gradEchilibru(root->dr) == -1) {
				root->dr = rotireDreapta(root->dr);
			}
			root = rotireStanga(root);			
		}
		if (GE == -2) {
			if (gradEchilibru(root->st) == -1) {
				root = rotireDreapta(root);
			}
			else {
				root->st = rotireStanga(root->st);
				root = rotireDreapta(root);
			}
		}

		return root;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = v;
		nou->st = NULL;
		nou->dr = NULL;
		return nou;
	}
}



void main() {
	nod* root = NULL;
	root = inserareAVL(root, creareVacanta("Dubai", 1));
	root = inserareAVL(root, creareVacanta("Ibiza", 2));
	root = inserareAVL(root, creareVacanta("Monaco", 3));
	root = inserareAVL(root, creareVacanta("Barcelona", 4));
	root = inserareAVL(root, creareVacanta("Tenerife", 5));
	root = inserareAVL(root, creareVacanta("Coasta de azur", 6));
	root = inserareAVL(root, creareVacanta("Coasta de azur", 7));

	afisareRSD(root);

	nodLista* cap = NULL;
	copiereInLista(root, &cap, 'c');
	printf("\n\n");
	while (cap) {
		afisareVacanta(cap->info);
		nodLista* temp = cap;
		cap = cap->next;
		free(temp->info.destinatie);
		free(temp);
	}

	stergereArbore(&root);
}