#include<iostream>
struct Clothes {
	int code;
	char* color;
};

struct node {
	Clothes info;
	node*next;
};

struct HashTable {
	node** vector;
	int size;
};

Clothes createClothes(char* color, int code) {
	Clothes c;
	c.code = code;
	c.color = (char*)malloc(sizeof(char)*(strlen(color) + 1));
	strcpy(c.color, color);
	return c;
}

void printClothes(Clothes c) {
	printf("%d.The color is %s\n", c.code, c.color);
}

int getHashCode(int code, int size) {
	return code%size;
}

node* createNode(Clothes info, node* next) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->info = createClothes(info.color, info.code);
	newNode->next = next;
	return newNode;
}

node* insertAtTheEnd(node* head, Clothes info) {
	node* newNode = createNode(info, NULL);
	if (head) {
		node* p = head;
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

HashTable initializeHashTable(int size) {
	HashTable hTable;
	hTable.vector = (node**)malloc(sizeof(node*)*size);
	for (int i = 0; i < size; i++) {
		hTable.vector[i] = NULL;
	}
	hTable.size = size;
	return hTable;
}

int insertInTheHashTable(HashTable hTable, Clothes c) {
	if (hTable.vector) {
		int hashCode = getHashCode(c.code, hTable.size);
		if (hTable.vector[hashCode]) {
			//we have a collision;
			hTable.vector[hashCode] = insertAtTheEnd(hTable.vector[hashCode], c);
			return hashCode;
		}
		else {
			hTable.vector[hashCode] = createNode(c, NULL);
			return hashCode;
		}
	}
	else {
		return -1;
	}
}

void printHashTable(HashTable ht) {
	for (int i = 0; i < ht.size; i++) {
		node*p = ht.vector[i];
		while (p) {
			printClothes(p->info);
			p = p->next;
		}
		printf("\n");
	}
}

Clothes findByCode(HashTable ht, int code) {
	if (ht.vector) {
		int position = getHashCode(code, ht.size);
		node* p = ht.vector[position];
		while (p && p->info.code != code) {
			p = p->next;
		}
		if (p) {
			return p->info;
		}
	}
	Clothes c;
	c.code = -1;
	c.color = NULL;
	return c;
}

void freeHashTable(HashTable * ht) {
	for (int i = 0; i < ht->size; i++)
	{
		if (ht->vector[i]) {
			node*p = ht->vector[i];
			while (p) {
				free(p->info.color);
				node*aux = p;
				p = p->next;
				free(aux);
			}
		}
	}
	free(ht->vector);
	ht->size = 0;
	ht->vector = NULL;
}

void main() {
	HashTable hTable;
	hTable = initializeHashTable(5);
	int position = insertInTheHashTable(hTable, createClothes("Red", 1));
	insertInTheHashTable(hTable, createClothes("Green", 3)); 
	insertInTheHashTable(hTable, createClothes("Blue", 6));

	printHashTable(hTable);

	Clothes c = findByCode(hTable, 3);

	printClothes(c);

	freeHashTable(&hTable);
	//we don't need to delete it 
	//because we have a shallow copy on the return of findByCode()
	//free(c.color);
}