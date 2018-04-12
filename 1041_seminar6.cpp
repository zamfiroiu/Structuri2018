#include<iostream>

struct Telefon {
	char* serie;
	float pret;
	int memorie;
};

struct nod {
	Telefon info;
	nod* next;
};

struct HashTable {
	nod**vector;
	int dim;
};

Telefon creareTelefon(char* serie, float pret, int memorie) {
	Telefon t;
	t.serie = (char*)malloc(sizeof(char)*(strlen(serie) + 1));
	strcpy(t.serie, serie);
	t.pret = pret;
	t.memorie = memorie;
	return t;
}

void afisareTelefon(Telefon t) {
	printf("Telefonul cu seria %s costa %5.2f si are %d Gb memorie.\n",t.serie,t.pret,t.memorie);
}

int hashFunction(char* serie, int dim) {
	int s = 0;
	for (int i = 0;i < strlen(serie);i++) {
		s += serie[i];
	}

	return s%dim;
}

nod* creareNod(Telefon info, nod* next) {
	nod* nodNou = (nod*)malloc(sizeof(nod));
	nodNou->info = creareTelefon(info.serie, info.pret, info.memorie);
	nodNou->next = next;

	return nodNou;
}

nod* inserareSfarsit(nod* cap, Telefon info) {
	nod* nodNou = creareNod(info, NULL);
	if (cap) {
		nod*p = cap;
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

HashTable initializareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (nod**)malloc(sizeof(nod*)*dim);
	for (int i = 0;i < dim;i++) {
		ht.vector[i] = NULL;
	}

	return ht;
}

int inserareInTabela(Telefon t, HashTable ht) {
	if (ht.vector) {
		int hashCode = hashFunction(t.serie, ht.dim);
		if (ht.vector[hashCode]) {
			//avem coliziune
			ht.vector[hashCode] = inserareSfarsit(ht.vector[hashCode], t);
			return hashCode;
		}
		else {
			//nu avem coliziune
			ht.vector[hashCode] = creareNod(t, NULL);
			return hashCode;
		}
	}
	else {
		return -1;
	}
}


void afisareTabela(HashTable ht) {
	for (int i = 0;i < ht.dim;i++) {
		if (ht.vector[i]) {
			nod* p = ht.vector[i];
			while (p) {
				afisareTelefon(p->info);
				p = p->next;
			}
			printf("\n");
		}
	}
}

Telefon cautareDupaSerie(char* serie, HashTable ht) {
	if (ht.vector) {
		int pozitie = hashFunction(serie, ht.dim);
		
		nod*p = ht.vector[pozitie];
		while (p && strcmp(serie, p->info.serie) != 0) {
			p = p->next;
		}
		if (p) {
			return p->info;
		}
	}
	Telefon t;
	t.serie = NULL;
	t.pret = -1;
	t.memorie = -1;
	return t;
}

void stergereSpatiu(HashTable *ht) {
	for (int i = 0;i < ht->dim;i++) {
		nod* p = ht->vector[i];
		while (p) {
			free(p->info.serie);
			nod* aux = p;
			p = p->next;
			free(aux);
		}
		ht->vector[i] = NULL;
	}
	free(ht->vector);
	ht->dim = 0;
	ht->vector = NULL;
}

void main() {
	HashTable hTable;
	hTable = initializareHashTable(6);

	int pozitie = inserareInTabela(creareTelefon("C45D3", 1000, 4), hTable);
	inserareInTabela(creareTelefon("D34C5", 1200, 6), hTable);
	inserareInTabela(creareTelefon("F36D5", 1700, 12), hTable);

	afisareTabela(hTable);

	Telefon t = cautareDupaSerie("F36D5", hTable);
	if (t.serie) {
		afisareTelefon(t);
	}

	stergereSpatiu(&hTable);
	
	//nu stergem deoarece avem shallow copy la return din findByserie
	//free(t.serie);
}