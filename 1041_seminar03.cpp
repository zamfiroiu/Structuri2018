#include<iostream>

struct Floare {
	char* denumire;
	float pret;
};

struct nod {
	Floare info;
	nod* next;
};

Floare creareFloare(char* denumire, float pret) {
	Floare floare;
	floare.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(floare.denumire, denumire);
	floare.pret = pret;
	return floare;
}

nod* inserareInceput(nod* cap, Floare floare) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareFloare(floare.denumire, floare.pret);
	nou->next = cap;
	return nou;
}

nod* inserareSfarsit(nod* cap, Floare floare) {
	if (cap) {
		nod* p = cap;
		while (p->next) {
			p = p->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareFloare(floare.denumire, floare.pret);
		nou->next = NULL;
		p->next = nou;
		return cap;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareFloare(floare.denumire, floare.pret);
		nou->next = NULL;
		return nou;
	}
}

void afisareLista(nod* cap) {
	nod*p = cap;
	while (p) {
		printf("%s costa %5.2f lei\n",p->info.denumire,p->info.pret);
		p = p->next;
	}
}

nod* stergereLista(nod* cap) {
	while (cap) {
		free(cap->info.denumire);
		nod*p = cap;
		cap = cap->next;
		free(p);
	}
	return NULL;
}


nod* inserarePePozitie(nod* cap, Floare f, int pozitie) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareFloare(f.denumire, f.pret);
	if (cap) {
		if (pozitie == 1) {
			cap = inserareInceput(cap, f);
		}
		else {
			int contor = 1;
			nod* p = cap;
			while (p->next && contor < pozitie - 1) {
				p = p->next;
				contor++;
			}
			nou->next = p->next;
			p->next = nou;
			return cap;
		}
	}
	else {
		nou->next = NULL;
		return nou;
	}
}


void main() {
	nod* lista = NULL;
	Floare f = creareFloare("Zambila", 3.5);
	lista = inserareInceput(lista, f);
	f.pret = 4;
	lista = inserareInceput(lista, f);
	f.pret = 5;
	lista = inserareInceput(lista, f);

	afisareLista(lista);

	lista=stergereLista(lista);
	
	lista = inserareSfarsit(lista, f);
	f.pret = 4;
	lista = inserareSfarsit(lista, f);

	printf("Lista noua\n");
	afisareLista(lista);
	lista = stergereLista(lista);
	
	lista = inserarePePozitie(lista, f, 4);
	f.pret = 3.5;
	lista = inserarePePozitie(lista, f, 1);
	f.pret = 3;
	lista = inserarePePozitie(lista, f, 2);

	printf("Lista cu pozitii:\n");
	afisareLista(lista);
	lista = stergereLista(lista);

	free(f.denumire);
}