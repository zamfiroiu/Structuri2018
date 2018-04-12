#include<iostream>

struct Carte {
	char* titlu;
	int nrPagini;
};

struct nodDublu {
	nodDublu* next;
	nodDublu* prev;
	Carte info;
};

struct HashTable {
	int dim;
	nodDublu** vector;
};


Carte citesteCarte() {
	Carte carte;
	char buffer[20];
	printf("Titlu:");
	scanf("%s", buffer);
	carte.titlu = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(carte.titlu, buffer);

	printf("Nr pagini:");
	scanf("%d", &carte.nrPagini);

	return carte;
}

nodDublu* inserareListaDubla(nodDublu* first, Carte info) {
	if (first) {
		nodDublu* p = first;
		while (p->next) {
			p = p->next;
		}
		nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
		nou->info.nrPagini = info.nrPagini;
		nou->info.titlu = (char*)malloc(sizeof(char)*(strlen(info.titlu) + 1));
		strcpy(nou->info.titlu, info.titlu);
		nou->next = NULL;
		nou->prev = p;
		p->next = nou;
		return first;
	}
	else {
		nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
		nou->info.nrPagini = info.nrPagini;
		nou->info.titlu = (char*)malloc(sizeof(char)*(strlen(info.titlu) + 1));
		strcpy(nou->info.titlu, info.titlu);
		nou->next = NULL;
		nou->prev = NULL;
		return nou;
	}
}

HashTable initializare(int dim) {
	HashTable tabela;
	tabela.dim = dim;
	tabela.vector = (nodDublu**)malloc(sizeof(nodDublu*)*dim);
	for (int i = 0;i < dim;i++) {
		tabela.vector[i] = NULL;
	}
	return tabela;
}

int hashCode(int nrPagini, HashTable tabela) {
	return nrPagini%tabela.dim;
}

int inserareInTabela(HashTable tabela, Carte carte) {
	int pozitie = -1;
	if (tabela.vector) {
		pozitie = hashCode(carte.nrPagini, tabela);
		if (tabela.vector[pozitie]) {
			//coliziune
			tabela.vector[pozitie] = inserareListaDubla(tabela.vector[pozitie], carte);
		}
		else
		{
			//nu avem coliziune
			tabela.vector[pozitie] = inserareListaDubla(tabela.vector[pozitie], carte);
		}
	}
	return pozitie;
}

void afisareCarte(Carte carte) {
	printf("Cartea %s are %d pagini\n", carte.titlu,carte.nrPagini);
}

void afisareListaDubla(nodDublu* first) {
	while (first) {
		afisareCarte(first->info);
		first = first->next;
	}
}

void afisareTabela(HashTable tabela) {
	for (int i = 0;i < tabela.dim;i++) {
		afisareListaDubla(tabela.vector[i]);
		printf("\n");
	}
}

nodDublu* stergereListaDubla(nodDublu* first) {
	while (first) {
		free(first->info.titlu);
		nodDublu*temp = first;
		first = first->next;
		free(temp);
	}
	return NULL;
}

HashTable stergereTabela(HashTable tabela) {
	for (int i = 0;i < tabela.dim;i++) {
		tabela.vector[i]=stergereListaDubla(tabela.vector[i]);
	}
	free(tabela.vector);
	tabela.vector = NULL;
	return tabela;
}

Carte cautareInLista(int nrPagini, nodDublu* first) {
	while (first) {
		if (first->info.nrPagini == nrPagini) {
			Carte result;
			result.titlu = (char*)malloc(sizeof(char)*(strlen(first->info.titlu) + 1));
			strcpy(result.titlu, first->info.titlu);
			result.nrPagini = first->info.nrPagini;
			return result;
		}
		else
		{
			first = first->next;
		}
	}
	Carte c;
	c.titlu = NULL;
	c.nrPagini = -1;
	return c;
}

Carte cautareCarte(int nrPagini, HashTable tabela) {
	if (tabela.vector) {
		int pozitie = hashCode(nrPagini, tabela);
		return cautareInLista(nrPagini,tabela.vector[pozitie]);
	}
	else {
		Carte c;
		c.titlu = NULL;
		c.nrPagini = -1;
		return c;
	}

}

void main() {

	HashTable tabela = initializare(5);
	inserareInTabela(tabela, citesteCarte());
	inserareInTabela(tabela, citesteCarte());
	inserareInTabela(tabela, citesteCarte());
	inserareInTabela(tabela, citesteCarte());

	afisareTabela(tabela);

	Carte c= cautareCarte(300, tabela);
	printf("Carte gasita: ");
	if(c.nrPagini!=-1)
		afisareCarte(c);
	else {
		printf("cartea nu a fost gasita");
	}
	tabela=stergereTabela(tabela);
	if(c.titlu)
		free(c.titlu);
}