#include<iostream>

struct Cont {
	char* username;
	int nrFollowers;
};

struct nod {
	Cont info;
	nod* next;
};

struct HashTable {
	nod** vector;
	int dim;
};

Cont creareCont(char* username, int number) {
	Cont c;
	c.username = (char*)malloc(sizeof(char)*(strlen(username) + 1));
	strcpy_s(c.username, strlen(username) + 1, username);
	c.nrFollowers = number;
	return c;
}

void afisareCont(Cont c) {
	printf("%s are %d urmaritori.\n", c.username, c.nrFollowers);
}

nod* creareNod(Cont info, nod* next) {
	nod* nodNou = (nod*)malloc(sizeof(nod));
	nodNou->info = creareCont(info.username, info.nrFollowers);
	nodNou->next = next;
	return nodNou;
}

nod* inserareSfarsit(nod* cap, Cont info) {
	nod* nodNou = creareNod(info, NULL);
	if (cap) {
		nod* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nodNou;
		return cap;
	}
	else {
		return nodNou;
	}
}

HashTable initializareTabela(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (nod**)malloc(sizeof(nod*)*dim);
	for (int i = 0; i < dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

int getHashCode(char*username, int dim) {
	return username[0] % dim;
}

int inserareInTabela(HashTable ht, Cont c) {
	if (ht.vector) {
		int code = getHashCode(c.username, ht.dim);
		if (ht.vector[code]) {
			//avem coliziune
			ht.vector[code] = inserareSfarsit(ht.vector[code], c);
		}
		else {
			//nu am coliziune
			ht.vector[code] = creareNod(c, NULL);
		}
		return code;
	}
	else {
		return -1;
	}
}

void afisareTabela(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		nod* p = ht.vector[i];
		while (p) {
			afisareCont(p->info);
			p = p->next;
		}
		printf("\n");
	}
}

Cont findByUsername(HashTable ht, char* username) {
	if (ht.vector) {
		int pozitie = getHashCode(username, ht.dim);
		nod* p = ht.vector[pozitie];
		while (p && strcmp(username, p->info.username) != 0) {
			p = p->next;
		}
		if (p) {
			return p->info;
		}
	}
	Cont c;
	c.username = NULL;
	c.nrFollowers = 0;
	return c;
}

void stergereSpatiu(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		nod* p = ht->vector[i];
		while (p) {
			free(p->info.username);
			nod* aux = p;
			p = p->next;
			free(aux);
		}
	}
	free(ht->vector);
	ht->dim = 0;
	ht->vector = NULL;
}

void main() {
	HashTable  hTable;
	hTable = initializareTabela(5);
	int pozitie = inserareInTabela(hTable, creareCont("user", 1000));
	inserareInTabela(hTable, creareCont("instagram", 70000));
	inserareInTabela(hTable, creareCont("username", 5000));

	afisareTabela(hTable);

	Cont c = findByUsername(hTable, "instagram");
	afisareCont(c);

	stergereSpatiu(&hTable);

	//nu terbuie sa il stergem
	//deoarece avem shallow copy la return in findByUsername
	//free(c.username);

}