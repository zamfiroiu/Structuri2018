#include<iostream>

struct Teatru{
	int id;
	char* denumire;
	int nrSpectacole;
};

struct nod{
	Teatru info;
	nod* next;
};

struct HashTable{
	int dimensiune;
	nod **vector;
};

Teatru creareTeatru(int id, char* denumire, int nrSpectacole){
	Teatru t;
	t.id = id;
	t.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(t.denumire, denumire);
	t.nrSpectacole = nrSpectacole;
	return t;
}

void afisareTeatru(Teatru t){
	printf("%d.Teatrul %s are %d spectacole.\n", t.id, t.denumire, t.nrSpectacole);
}

int getHashCode(int id, int dim){
	return id%dim;
}

nod* creareNod(Teatru info, nod* next){
	nod* nodNou = (nod*)malloc(sizeof(nod));
	nodNou->info = creareTeatru(info.id, info.denumire, info.nrSpectacole);
	nodNou->next = next;
	return nodNou;
}

nod* inserareSfarsit(nod* cap, Teatru info){
	nod* nodNou = creareNod(info, NULL);
	if (cap){
		nod* p = cap;
		while (p->next){
			p = p->next;
		}
		p->next = nodNou;
		return cap;
	}
	else{
		return nodNou;
	}
}

HashTable initializare(int dim){
	HashTable ht;
	ht.dimensiune = dim;
	ht.vector = (nod**)malloc(sizeof(nod*)*dim);
	for (int i = 0; i < dim; i++){
		ht.vector[i] = NULL;
	}
	return ht;
}

int inserareInTabela(HashTable ht, Teatru t){
	if (ht.vector){
		int hashCode = getHashCode(t.id, ht.dimensiune);
		if (ht.vector[hashCode]){
			//avem coliziune
			ht.vector[hashCode] = inserareSfarsit(ht.vector[hashCode], t);
		}
		else{
			//nu avem coliziune
			ht.vector[hashCode] = creareNod(t, NULL);
		}
		return hashCode;
	}
	else{
		return -1;
	}
}

void afisareTabela(HashTable ht){
	for (int i = 0; i < ht.dimensiune; i++){
		nod* p = ht.vector[i];
		while (p){
			afisareTeatru(p->info);
			p = p->next;
		}
		printf("\n");
	}
}

Teatru findById(int id, HashTable ht){
	if (ht.vector){
		int code = getHashCode(id, ht.dimensiune);
		nod* p = ht.vector[code];
		while (p && p->info.id != id){
			p = p->next;
		}
		if (p){
			return p->info;
		}
	}
	Teatru t;
	t.id = -1;
	t.denumire = NULL;
	return t;
}

void stergereTabela(HashTable *ht){
	for (int i = 0; i < ht->dimensiune; i++){
		nod* p = ht->vector[i];
		while (p){
			free(p->info.denumire);
			nod*aux = p;
			p = p->next;
			free(aux);
		}
	}
	free(ht->vector);
	ht->dimensiune = 0;
	ht->vector = NULL;
}

void main(){
	HashTable hTable;
	hTable = initializare(6);

	inserareInTabela(hTable, creareTeatru(1, "TNB", 10));
	inserareInTabela(hTable, creareTeatru(3, "Comedie", 8));
	inserareInTabela(hTable, creareTeatru(7, "CCSB", 11));

	afisareTabela(hTable);

	Teatru t = findById(3, hTable);
	afisareTeatru(t);


	stergereTabela(&hTable);

	//nu terbuie sa stergem
	//deoarece avem shallow copy la return in findbyid()
	//free(t.denumire);
}