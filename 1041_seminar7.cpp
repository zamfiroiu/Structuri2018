#include<iostream>

struct Masina {
	char* marca;
	int kilometri;
};

struct nod {
	Masina info;
	nod*next;
};

Masina citireMasinaDinFisier(FILE* f) {
	Masina masina;
	char buffer[20];
	fgets(buffer, 19, f);
	masina.kilometri=atoi(strrchr(buffer, ' '));
	masina.marca = (char*)malloc(sizeof(char)*(strlen(buffer) - strlen(strrchr(buffer, ' ')) + 1));
	strcpy(masina.marca, "");
	strncat(masina.marca, buffer, strlen(buffer) - strlen(strrchr(buffer, ' ')));
	return masina;
}

nod* inserareInListaCirculara(nod* cap, Masina m) {
	nod* nodNou = (nod*)malloc(sizeof(nod));
	nodNou->info = m;
	if (cap) {
		nodNou->next = cap;
		nod*p = cap;
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

void scrieMasinaInFisier(Masina m, FILE* f) {
	fprintf(f, "Masina %s are %d kilometri parcursi.\n", m.marca, m.kilometri);
}

void salvareListaInFisier(nod* cap, char* numeFisier) {
	FILE* file = fopen(numeFisier, "w");
	if (file) {
		if (cap) {
			nod* p = cap;
			do {
				scrieMasinaInFisier(p->info, file);
				p = p->next;
			} while (p != cap);
		}
	}
	fclose(file);
}

void stergereListaCirculara(nod** cap) {
	nod* p = (*cap)->next;
	while (p != *cap) {
		free(p->info.marca);
		nod* aux = p;
		p = p->next;
		free(aux);
	}
	free(p->info.marca);
	free(p);
	*cap = NULL;
}

Masina* filtrare(nod* cap, int prag, int* dim) {
	Masina* vector = NULL;
	*dim = 0;
	if (cap) {
		nod* p = cap;
		do {
			if (p->info.kilometri < prag) {
				(*dim)++;
			}
			p = p->next;
		} while (p != cap);

		vector = (Masina*)malloc(sizeof(Masina)*(*dim));
		*dim = 0;
		do {
			if (p->info.kilometri < prag) {
				vector[*dim].marca = (char*)malloc(sizeof(char)*(strlen(p->info.marca) + 1));
				strcpy(vector[*dim].marca, p->info.marca);
				vector[*dim].kilometri = p->info.kilometri;
				(*dim)++;
			}
			p = p->next;
		} while (p != cap);
		return vector;
	}
}

void main() {

	nod* cap = NULL;
	FILE* file = fopen("masini.txt", "r");
	int nrMasini = 0;
	fscanf(file, "%d", &nrMasini);
	char buffer[3];
	fgets(buffer, 2, file);
	for (int i = 0;i < nrMasini;i++) {
		cap = inserareInListaCirculara(cap, citireMasinaDinFisier(file));
	}
	salvareListaInFisier(cap, "MasiniSalvate.txt");


	int dim = 0;
	Masina* vector = filtrare(cap, 3000, &dim);
	//afisare vector
	//stergere spatiu ocupat de vector


	stergereListaCirculara(&cap);
}