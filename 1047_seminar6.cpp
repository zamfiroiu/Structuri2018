#include<iostream>

struct Prajitura {
	int cod;
	char* ingredientPrincipal;
	float numarCalorii;
};

struct nod {
	Prajitura info;
	nod* next;
};

struct HashTable {
	nod** vector;
	int dim;
};

Prajitura crearePrajitura(int cod, char* ingredient, float calorii) {
	Prajitura prajitura;
	prajitura.cod = cod;
	prajitura.ingredientPrincipal = (char*)malloc(sizeof(char)*(strlen(ingredient) + 1));
	strcpy(prajitura.ingredientPrincipal, ingredient);
	prajitura.numarCalorii = calorii;
	return prajitura;
}

void afisarePrajitura(Prajitura prajitura) {
	printf("%d. Prajitura cu %s are %5.2f calorii.\n", prajitura.cod, prajitura.ingredientPrincipal, prajitura.numarCalorii);
}

nod* creareNod(Prajitura prajitura, nod* next) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearePrajitura(prajitura.cod, prajitura.ingredientPrincipal, prajitura.numarCalorii);
	nou->next = next;
	return nou;
}

nod* inserareInceput(nod* cap, Prajitura info) {
	return creareNod(info, cap);
}

int getHashCode(int cod, int dim) {
	return cod%dim;
}

HashTable initializareHashTable(int dim) {
	HashTable tabela;
	tabela.vector = (nod**)malloc(sizeof(nod*)*dim);
	tabela.dim = dim;
	for (int i = 0; i < dim; i++) {
		tabela.vector[i] = NULL;
	}
	return tabela;
}

int inserareInHashTable(HashTable tabela, Prajitura prajitura) {
	if (tabela.vector) {
		int hashCode = getHashCode(prajitura.cod, tabela.dim);
		if (tabela.vector[hashCode]) {
			//avem coliziune
			tabela.vector[hashCode] = inserareInceput(tabela.vector[hashCode], prajitura);
		}
		else {
			tabela.vector[hashCode] = creareNod(prajitura, NULL);
		}
		return hashCode;
	}
	else {
		return -1;
	}
}

void afisareTabela(HashTable tabela) {
	for (int i = 0; i<tabela.dim; i++) {
		nod* p = tabela.vector[i];
		while (p) {
			afisarePrajitura(p->info);
			p = p->next;
		}
		printf("\n");
	}
}

Prajitura cautareDupaID(HashTable tabela, int cod) {
	if (tabela.vector) {
		int hashCode = getHashCode(cod, tabela.dim);
		nod* p = tabela.vector[hashCode];
		while (p && cod != p->info.cod) {
			p = p->next;
		}
		if (p) {
			return p->info;
		}
		else {
			Prajitura prajitura;
			prajitura.cod = -1;
			prajitura.ingredientPrincipal = NULL;
			return prajitura;
		}
	}
	else {
		Prajitura prajitura;
		prajitura.cod = -1;
		prajitura.ingredientPrincipal = NULL;
		return prajitura;
	}
}

void stergereTabela(HashTable*tabela) {
	for (int i = 0; i < tabela->dim; i++) {
		nod* p = tabela->vector[i];
		while (p) {
			free(p->info.ingredientPrincipal);
			nod* aux = p;
			p = p->next;
			free(aux);
		}
	}
	free(tabela->vector);
	tabela->vector = NULL;
	tabela->dim = 0;
}


void main() {
	HashTable tabela = initializareHashTable(5);
	int pozitie = inserareInHashTable(tabela, crearePrajitura(1, "Lapte", 30));
	inserareInHashTable(tabela, crearePrajitura(4, "Faina", 100));
	inserareInHashTable(tabela, crearePrajitura(6, "Ciocolata", 200));

	afisareTabela(tabela);

	Prajitura prajitura = cautareDupaID(tabela, 4);
	printf("Prajitura:");
	afisarePrajitura(prajitura);
	//ingredientul prajiturii nu il stergem deoarece la return am facut shallow copy
	
	stergereTabela(&tabela);
}