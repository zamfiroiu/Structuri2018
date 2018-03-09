#include<iostream>

struct Magazin {
	char* nume;
	float cifra_afaceri;
};

Magazin creareMagazin(char* nume, float ca) {
	Magazin m;
	m.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy_s(m.nume, strlen(nume) + 1, nume);
	m.cifra_afaceri = ca;

	return m;
}

struct nod {
	Magazin info;
	nod* next;
};

nod* inserareInceput(nod* cap, Magazin m) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareMagazin(m.nume,m.cifra_afaceri);
	nou->next = cap;
	return nou;
}


//de simplificat
//de modificat, astfel incat sa folositi inserareInceput

nod* inserareSfarsit(nod* cap, Magazin m) {
	if (cap) {
		nod*p = cap;
		while (p->next) {
			p = p->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareMagazin(m.nume, m.cifra_afaceri);
		nou->next = NULL;
		p->next = nou;

		return cap;
	}
	else
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareMagazin(m.nume, m.cifra_afaceri);
		nou->next = NULL;
		return nou;
	}
}

///ce se intampla daca inseram o valoare mai
//mica decat toate elementele din lista
nod* inserareSortata(nod* cap, Magazin m) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareMagazin(m.nume, m.cifra_afaceri);
	if (cap) {
		nod*p = cap;
		while (p->next != NULL && p->next->info.cifra_afaceri < m.cifra_afaceri ) {
			p = p->next;
		}

		if (p->next) {
			nou->next = p->next;
			p->next = nou;
		}
		else
		{
			p->next = nou;
			nou->next = NULL;
		}
	}
	else {
		nou->next = NULL;
		return nou;
	}
	return cap;
}

void afisareLista(nod* lista) {
	nod*temp = lista;
	while (temp) {
		printf("Magazinul %s are o CA de %5.2f\n", temp->info.nume, temp->info.cifra_afaceri);
		temp = temp->next;
	}
}



nod* stergere(nod*lista) {
	while (lista) {
		free(lista->info.nume);
		nod*p = lista;
		lista = lista->next;
		free(p);
	}
	return NULL;
}




void main() {
	nod* cap;
	cap = NULL;
	Magazin m1 = creareMagazin("ABC",3000);
	cap = inserareInceput(cap, m1);
	m1.cifra_afaceri = 4000;
	cap = inserareInceput(cap, m1);
	m1.cifra_afaceri = 5000;
	cap = inserareInceput(cap, m1);

	afisareLista(cap);

	cap = stergere(cap);

	printf("\n\n");
	cap = inserareSfarsit(cap, m1);
	m1.cifra_afaceri = 6000;
	cap = inserareSfarsit(cap, m1);
	m1.cifra_afaceri = 7000;
	cap = inserareSfarsit(cap, m1);

	afisareLista(cap);
	cap = stergere(cap);
	free(m1.nume);




}