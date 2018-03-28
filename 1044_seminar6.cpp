#include<iostream>

struct Curs {
	int id;
	char* denumire;
	int prezenti;
};

struct nod {
	Curs info;
	nod* next;
};

struct HashTable {
	nod** vector;
	int dim;
};

Curs creareCurs(char* denumire, int prezenti, int id) {
	Curs c;
	c.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy_s(c.denumire, strlen(denumire) + 1, denumire);
	c.prezenti = prezenti;
	c.id = id;
	return c;
}

nod* inserareInceput(nod* cap, Curs curs) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareCurs(curs.denumire, curs.prezenti,curs.id);
	nou->next = cap;
	return nou;
}

int hashCode(int id, HashTable tabela) {
	return id% tabela.dim;
}

int inserareTabelaDispersie(HashTable tabela, Curs curs) {
	if (tabela.vector) {
		int pozitie = hashCode(curs.id, tabela);
		if (tabela.vector[pozitie]) {
			//avem coliziune
			tabela.vector[pozitie] = inserareInceput(tabela.vector[pozitie], curs);
		}
		else {
			tabela.vector[pozitie] = inserareInceput(tabela.vector[pozitie], curs);
		}
		return pozitie;
	}
	else {
		return -1;
	}
}

HashTable initializareTabelaDispersie(int dim) {
	HashTable tabela;
	tabela.dim = dim;
	tabela.vector = (nod**)malloc(sizeof(nod*)*dim);
	for (int i = 0; i < dim; i++) {
		tabela.vector[i] = NULL;
	}
	return tabela;
}

void afisareCurs(Curs c) {
	printf("%d.Cursul %s are %d prezenti.\n", c.id, c.denumire, c.prezenti);
}

void afisareTabela(HashTable tabela) {
	for (int i = 0; i < tabela.dim; i++) {
		nod* p = tabela.vector[i];
		while (p) {
			afisareCurs(p->info);
			p = p->next;
		}
		printf("\n");
	}

}

Curs cautareCursInLista(nod* cap, int id) {
	while (cap && cap->info.id!= id) {
		cap = cap->next;
	}
	if (cap)
		return cap->info;
	else {
		Curs c;
		c.id = -1;
		c.denumire = NULL;
		return c;
	}
}

Curs cautareCursDupaID(HashTable tabela, int id) {
	if (tabela.vector) {
		int pozitie = hashCode(id, tabela);
		return cautareCursInLista(tabela.vector[pozitie], id);
	}
	else {
		Curs c;
		c.id = -1;
		c.denumire = NULL;
		return c;
	}
}

void stergere(HashTable *tabela) {
	for (int i = 0; i < tabela->dim; i++) {
		nod* p = tabela->vector[i];
		while (p) {
			free(p->info.denumire);
			nod*temp = p;
			p = p->next;
			free(temp);
		}
	}
	free(tabela->vector);
	tabela->vector = NULL;
	tabela->dim = 0;
}

void main() {
	HashTable tabela = initializareTabelaDispersie(5);

	inserareTabelaDispersie(tabela, creareCurs("SDD", 35, 1));
	inserareTabelaDispersie(tabela, creareCurs("PAG", 15, 3));
	inserareTabelaDispersie(tabela, creareCurs("Java", 20, 6));

	afisareTabela(tabela);
	printf("Curs:");
	afisareCurs(cautareCursDupaID(tabela,3));
	stergere(&tabela);
}