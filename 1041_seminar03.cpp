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

void main() {
	nod* lista=NULL;
	Floare f = creareFloare("Zambila", 3.5);
	lista = inserareInceput(lista, f);
	f.pret = 4;
	lista = inserareInceput(lista, f);
	f.pret = 5;
	lista = inserareInceput(lista, f);

}