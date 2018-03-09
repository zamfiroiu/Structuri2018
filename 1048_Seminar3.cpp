#include<iostream>

#pragma warning(disable:4996)
struct Florarie {
	char* denumire;
	int nrFlori;
};

struct nod {
	Florarie info;
	nod* next;
};

Florarie creareFlorarie(char* denumire, int nrFlori) {
	Florarie florarie;
	florarie.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(florarie.denumire, denumire);
	florarie.nrFlori = nrFlori;
	return florarie;
}

nod* inserareInceput(Florarie f, nod* cap) {
	nod* nodNou = (nod*)malloc(sizeof(nod));
	nodNou->info = creareFlorarie(f.denumire,f.nrFlori);
	nodNou->next = cap;
	return nodNou;
}

void afisareLista(nod* cap) {
	nod* p = cap;
	while (p) {
		printf("Floraria %s are %d flori\n",p->info.denumire,p->info.nrFlori);
		p = p->next;
	}
}

nod* stergereLista(nod* cap) {
	while (cap) {
		free(cap->info.denumire);
		nod* temp = cap;
		cap = cap->next;
		free(temp);
	}
	return cap;
}

nod* inserareSfarsit(Florarie f, nod* cap) {
	if (cap) {
		nod*p = cap;
		while (p->next) {
			p = p->next;
		}
		nod*nou = (nod*)malloc(sizeof(nod));
		nou->info = creareFlorarie(f.denumire, f.nrFlori);
		nou->next = p->next;
		p->next = nou;
		//p->next = inserareInceput(f, NULL);
	}
	else {
		cap = inserareInceput(f, cap);
	}
	return cap;
}

nod* inserareSortata(Florarie f, nod* cap) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareFlorarie(f.denumire, f.nrFlori);
	nou->next = NULL;
	if (cap) {
		if (cap->info.nrFlori > f.nrFlori) {
			nou->next = cap;
			cap = nou;
		}
		else {
			nod*p = cap;
			while (p->next && p->next->info.nrFlori < f.nrFlori) {
				p = p->next;
			}
			nou->next = p->next;
			p->next = nou;
		}
	}
	else {
		cap = nou;
	}
	return cap;
}

void main() {
	nod* lista=NULL;
	Florarie florarie = creareFlorarie("Floris", 45);
	lista = inserareInceput(florarie, lista);
	florarie.nrFlori = 35;
	lista = inserareInceput(florarie, lista);

	afisareLista(lista);

	lista=stergereLista(lista);

	lista = inserareSfarsit(florarie, lista);
	florarie.nrFlori = 33;
	lista = inserareSfarsit(florarie, lista);
	florarie.nrFlori = 28;
	lista = inserareSfarsit(florarie, lista);

	printf("ListaNoua: \n");
	afisareLista(lista);
	lista = stergereLista(lista);

	lista = inserareSortata(florarie, lista);
	florarie.nrFlori = 33;
	lista = inserareSortata(florarie, lista);
	florarie.nrFlori = 30;
	lista = inserareSortata(florarie, lista);
	printf("Lista sotrtata: \n");
	afisareLista(lista);
	lista = stergereLista(lista);
	
	free(florarie.denumire);
}