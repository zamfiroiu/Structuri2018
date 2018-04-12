#include<iostream>

struct Porc {
	char* rasa;
	float greutate;
};


struct nod {
	nod* next;
	Porc info;
};

Porc crearePorc(char* rasa, float greutate) {
	Porc porc;
	porc.rasa = (char*)malloc(sizeof(char)*(strlen(rasa) + 1));
	strcpy(porc.rasa, rasa);
	porc.greutate = greutate;

	return porc;
}

nod* inserareInListaCirculara(nod*cap, Porc porc) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearePorc(porc.rasa, porc.greutate);
	if (cap) {
		nou->next = cap;
		nod* p = cap;
		while (p->next != cap) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		nou->next = nou;
		return nou;
	}
}

void afisarePorc(Porc porc) {
	printf("Porcul de rasa %s are o greutate de %5.2f.\n", porc.rasa, porc.greutate);
}

void afisareListaCirculara(nod* cap) {
	if (cap) {
		nod* p = cap;
		do {
			afisarePorc(p->info);
			p = p->next;
		} while (p != cap);
	}
}

void stergereListaCircualara(nod** cap) {
	if (cap) {
		nod*p = (*cap)->next;
		while (p != *cap) {
			free(p->info.rasa);
			nod* aux = p;
			p = p->next;
			free(aux);
		}
		free(p->info.rasa);
		free(p);
		*cap = NULL;
	}
}

Porc* filtrareInVector(nod*cap, float greutateMinima, int* dimensiune) {
	if (cap) {
		int nr = 0;
		nod* p = cap;
		while (p->next != cap) {
			if (p->info.greutate >= greutateMinima) {
				nr++;
			}
			p = p->next;
		}
		if (p->info.greutate >= greutateMinima) {
			nr++;
		}

		Porc * vector = (Porc*)malloc(sizeof(Porc)*nr);
		p = cap;
		nr = 0;
		do {
			if (p->info.greutate >= greutateMinima) {
				vector[nr] = crearePorc(p->info.rasa, p->info.greutate);
				nr++;
			}
			p = p->next;
		} while (p != cap);
		*dimensiune = nr;
		return vector;
	}
	else {
		return NULL;
	}
}

Porc citirePorc(FILE* f) {
	char buffer[20];
	//fread(buffer, sizeof(buffer), 19, f);
	fgets(buffer, 19, f);
	//fscanf(f, "%[^\n]s", buffer);
	//fscanf(f, "%[^\n]s", buffer);
	//fscanf(f, "%[^\n]s", buffer);
	float greutate=atof(strrchr(buffer, ' '));
	strrchr(buffer, ' ')[0] = '\0';
	Porc porc;
	porc.rasa = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(porc.rasa, buffer);
	porc.greutate = greutate;

	return porc;
}

void main() {

	nod * cap = NULL;

	//cap = inserareInListaCirculara(cap, crearePorc("Mangalita", 300));
	//cap = inserareInListaCirculara(cap, crearePorc("Marele alb", 200));
	//cap = inserareInListaCirculara(cap, crearePorc("Vietnamez", 30));

	//afisareListaCirculara(cap);

	//int dimensiune = 0;
	//Porc * vector = filtrareInVector(cap, 100, &dimensiune);

	//printf("Vector:\n");
	//for (int i = 0; i < dimensiune; i++) {
	//	afisarePorc(vector[i]);
	//}

	//stergereListaCircualara(&cap);


	FILE* fisier = fopen("1047_obiecte.txt", "r");
	if (fisier) {
		int nrElemente = 0;
		fscanf(fisier, "%d", &nrElemente);
		char bufer[20];
		fgets(bufer, 19, fisier);
		for (int i = 0; i < nrElemente; i++) {
			cap = inserareInListaCirculara(cap, citirePorc(fisier));
		}
	}
	afisareListaCirculara(cap);
	stergereListaCircualara(&cap);
}