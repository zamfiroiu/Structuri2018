#include<iostream>

struct Gradina {
	char*nume;
	int nrPlante;
};
struct nodLista {
	Gradina info;
	nodLista*next;
};

Gradina creareGradina(char* nume, int nrPlante) {
	Gradina im;
	im.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(im.nume, nume);
	im.nrPlante = nrPlante;
	return im;
}

nodLista* inserareInceput(nodLista*cap, Gradina info) {
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info = creareGradina(info.nume, info.nrPlante);
	nou->next = cap;
	return nou;
}

struct nod {
	nod* st;
	nod* dr;
	Gradina info;
};

nod* inserare(nod* rad, Gradina g) {
	if (rad) {
		if (g.nrPlante < rad->info.nrPlante) {
			rad->st = inserare(rad->st, g);
		}
		else if(g.nrPlante>rad->info.nrPlante) {
			rad->dr = inserare(rad->dr, g);
		}
		return rad;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = g;
		nou->st = NULL;
		nou->dr = NULL;
		return nou;
	}
}

void afisareGradina(Gradina g) {
	printf("Gradina %s are %d plante.\n", g.nume, g.nrPlante);
}

void afisareArbore(nod* rad) {
	if (rad) {
		afisareArbore(rad->st);
		afisareGradina(rad->info);
		afisareArbore(rad->dr);
	}
}

Gradina cautareGradinaDupaNrPlante(nod* rad, int nrPlante) {
	if(rad){
		if (rad->info.nrPlante == nrPlante) {
			return rad->info;
		}
		else if(rad->info.nrPlante< nrPlante){
			return cautareGradinaDupaNrPlante(rad->dr, nrPlante);
		}
		else {
			return cautareGradinaDupaNrPlante(rad->st, nrPlante);
		}
	}
	else {
		return creareGradina("", -1);
	}
}

void stergereArbore(nod** rad) {
	if (*rad) {
		nod* stanga = (*rad)->st;
		stergereArbore(&stanga);
		stergereArbore(&(*rad)->dr);
		free((*rad)->info.nume);
		free(*rad);
		*rad = NULL;
	}
}

int inaltime(nod* rad) {
	if (rad) {
		int stanga = inaltime(rad->st);
		int dreapta = inaltime(rad->dr);
		int maxim = stanga < dreapta ? dreapta : stanga;
		maxim++;
		return maxim;
	}
	else {
		return 0;
	}
}

void afisareDePeNivel(nod*rad, int nivel) {
	if (rad) {
		if (nivel == 1) {
			afisareGradina(rad->info);
		}
		else {
			afisareDePeNivel(rad->st, nivel - 1);
			afisareDePeNivel(rad->dr, nivel - 1);
		}
	}
}

nod* cautareMaxim(nod* rad) {
	if (rad) {
		while (rad->dr) {
			rad = rad->dr;
		}
		return rad;
	}
}

Gradina extrageGradinaDinArbore(nod**rad, int nrPlante) {
	if (*rad) {
		if ((*rad)->info.nrPlante == nrPlante) {
			if ((*rad)->st == NULL) {
				Gradina rezultat = creareGradina((*rad)->info.nume, (*rad)->info.nrPlante);
				free((*rad)->info.nume);
				nod* temp = (*rad)->dr;
				free(*rad);
				*rad = temp;
				return rezultat;
			}
			if ((*rad)->dr == NULL) {
				Gradina rezultat = creareGradina((*rad)->info.nume, (*rad)->info.nrPlante);
				free((*rad)->info.nume);
				nod* temp = (*rad)->st;
				free(*rad);
				*rad = temp;
				return rezultat;
			}
			nod*temp = cautareMaxim((*rad)->st);
			Gradina aux = temp->info;
			temp->info = (*rad)->info;
			(*rad)->info = aux;
			return extrageGradinaDinArbore(&(*rad)->st, nrPlante);
		}
		else if((*rad)->info.nrPlante<nrPlante) {
			return extrageGradinaDinArbore(&(*rad)->dr, nrPlante);
		}
		else {
			return extrageGradinaDinArbore(&(*rad)->st, nrPlante);
		}
	}
}

void copiereGradiniInLista(nod*rad, nodLista**cap) {
	if (rad) {
		if (rad->info.nrPlante % 2 == 1) {
			*cap = inserareInceput(*cap, rad->info);
		}
		copiereGradiniInLista(rad->st, cap);
		copiereGradiniInLista(rad->dr, cap);
	}
}

nodLista* obtinereListaGradini(nod* rad) {
	nodLista* cap = NULL;
	copiereGradiniInLista(rad, &cap);
	return cap;
}

void main() {
	nod* rad = NULL;
	rad = inserare(rad, creareGradina("Cismigiu", 8));
	rad = inserare(rad, creareGradina("Botanica", 10));
	rad = inserare(rad, creareGradina("Carol", 9));
	rad = inserare(rad, creareGradina("Zoologica", 3));
	rad = inserare(rad, creareGradina("Herastrau", 1));
	rad = inserare(rad, creareGradina("Mihai I", 6));
	rad = inserare(rad, creareGradina("Moghioros", 5));

	//afisareArbore(rad);

	//printf("\n");

	//afisareGradina(cautareGradinaDupaNrPlante(rad, 9));

	//printf("inaltime: %d", inaltime(rad));

	//afisareDePeNivel(rad, 3);
	/*afisareArbore(rad);
	printf("\n");
	afisareGradina(extrageGradinaDinArbore(&rad, 8));
	printf("\n");
	afisareArbore(rad);*/

	nodLista*cap = obtinereListaGradini(rad);
	nodLista*temp = cap;
	while (cap) {
		afisareGradina(cap->info);
		cap = cap->next;
	}
	cap = temp;
	while (cap) {
		free(cap->info.nume);
		temp = cap->next;
		free(cap);
		cap = temp;
	}

	stergereArbore(&rad);
	printf("arbborele:\n");
	afisareArbore(rad);
}