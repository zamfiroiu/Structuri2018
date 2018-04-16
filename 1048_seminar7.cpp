#include<iostream>

struct Examen {
	char* materie;
	int numarCredite;
};

struct nod {
	Examen info;
	nod* next;
};


Examen citireExamenDinFisier(FILE*f) {
	char buffer[50];
	fgets(buffer, 49, f);
	Examen examen;
	examen.numarCredite=atoi(strchr(buffer, ',')+1);
	*strchr(buffer, ',') = '\0';
	examen.materie = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(examen.materie, buffer);
	return examen;
}

nod* inserareInListaCirculara(Examen examen, nod* cap) {
	nod* nodNou = (nod*)malloc(sizeof(nod));
	//shallow copy
	nodNou->info = examen;
	if (cap) {
		nodNou->next = cap;
		nod* p = cap;
		while (p->next != cap) {
			p = p->next;
		}
		p->next = nodNou;
		return cap;
	}
	else {
		nodNou->next = nodNou;
		return nodNou;
	}
}

void salvareExamenInFisier(FILE* f, Examen examen) {
	fprintf(f, "Examenul de la %s are %d credite.\n", examen.materie, examen.numarCredite);
}

void salvareListaInFisier(char* numeFisier, nod* cap) {
	if (cap) {
		FILE* f = fopen(numeFisier, "w");
		if (f) {
			nod* p = cap;
			do {
				salvareExamenInFisier(f, p->info);
				p = p->next;
			} while (p != cap);
		}
		fclose(f);
	}
}

void stergereListaCirculara(nod ** cap) {
	if (*cap) {
		nod*p = (*cap)->next;
		while (p != *cap) {
			free(p->info.materie);
			nod* aux = p;
			p = p->next;
			free(aux);
		}
		free(p->info.materie);
		free(p);
		*cap = NULL;
	}
}

void main() {

	nod* cap = NULL;
	FILE* file = fopen("examene.txt", "r");
	if (file) {
		int nrMaterii = 0;
		fscanf(file, "%d", &nrMaterii);
		char buffer[3];
		fgets(buffer, 2, file);
		for (int i = 0; i < nrMaterii; i++) {
			cap = inserareInListaCirculara(citireExamenDinFisier(file), cap);
		}
	}
	fclose(file);
	salvareListaInFisier("ExameneSalvate.txt", cap);

	stergereListaCirculara(&cap);
}