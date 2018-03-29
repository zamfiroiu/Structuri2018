#include<iostream>

struct wagon {
	char* code;
	int capacity;
};

struct nod {
	wagon info;
	nod* next;
};

struct HashTable {
	int size;
	nod**vector;
};

wagon createWagon(char* code, int capacity) {
	wagon w;
	w.code = (char*)malloc(sizeof(char)*(strlen(code) + 1));
	strcpy(w.code, code);
	w.capacity = capacity;
	return w;
}

void printWagon(wagon w) {
	printf("The wagon with code %s has %d places.\n", w.code, w.capacity);
}

unsigned int getHashCode(char* code, HashTable hTable) {
	int s = 0;
	for (int i = 0; i < strlen(code); i++) {
		s += code[i];
	}
	return s%hTable.size;
}

HashTable initialize(int size) {
	HashTable hTable;
	hTable.vector = (nod**)malloc(sizeof(nod*)*size);
	for (int i = 0; i < size; i++) {
		hTable.vector[i] = NULL;
	}
	hTable.size = size;

	return hTable;
}

nod* createNode(wagon info, nod* next) {
	nod* newNode = (nod*)malloc(sizeof(nod));
	newNode->info = createWagon(info.code, info.capacity);
	newNode->next = next;
	return newNode;
}


nod* insertAtTheEnd(nod* head, wagon info) {
	nod*newNode = createNode(info, NULL);
	if (head) {
		nod*p = head;
		while (p->next) {
			p = p->next;
		}
		p->next = newNode;
		return head;
	}
	else {
		return newNode;
	}
}

int insertInHashTable(HashTable hTable, wagon w) {
	if (hTable.size > 0) {
		int hashCode = getHashCode(w.code, hTable);
		if (hTable.vector[hashCode]) {
			//we have a colition
			hTable.vector[hashCode] = 
				insertAtTheEnd(hTable.vector[hashCode], w);
			return hashCode;
		}
		else {
			hTable.vector[hashCode] = createNode(w, NULL);
			return hashCode;
		}
	}
	else {
		return -1;
	}
}

void printHashTable(HashTable hTable) {
	for (int i = 0; i < hTable.size; i++) {
		if (hTable.vector[i]) {
			nod* p = hTable.vector[i];
			while (p) {
				printWagon(p->info);
				p = p->next;
			}
			printf("\n");
		}
	}
}

wagon findByCode(char* code, HashTable hTable) {
	if (hTable.vector) {
		int hashCode = getHashCode(code, hTable);
		if (hTable.vector[hashCode]) {
			nod* p = hTable.vector[hashCode];
			while (p && strcmp(p->info.code, code) != 0) {
				p = p->next;
			}
			if (p) {
				return p->info;
			}
			else {
				wagon w;
				w.code = NULL;
				w.capacity = 0;
				return w;
			}
		}
		else {
			wagon w;
			w.code = NULL;
			w.capacity = 0;
			return w;
		}
	}
	else {

		wagon w;
		w.code = NULL;
		w.capacity = 0;
		return w;
	}
}

void deleteMemory(HashTable *hTable) {
	for (int i = 0; i < hTable->size; i++) {
		while (hTable->vector[i]) {
			free(hTable->vector[i]->info.code);
			nod* p = hTable->vector[i];
			hTable->vector[i] = hTable->vector[i]->next;
			free(p);
		}
	}
	free(hTable->vector);
	hTable->size = 0;
	hTable->vector = NULL;
}

void main() {
	HashTable hTable = initialize(8);
	int position = insertInHashTable(hTable, createWagon("432", 100));
	insertInHashTable(hTable, createWagon("234", 120));
	insertInHashTable(hTable, createWagon("667", 80));

	printHashTable(hTable);

	wagon wagon = findByCode("456", hTable);

	deleteMemory(&hTable);
	//we don't delete it becuase 
	//we have a shallow copy in findByCode
	//free(wagon.code);
}