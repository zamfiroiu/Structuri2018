#include<iostream>

struct Tanc {
	char* name;
	float weight;
};

struct node{
	Tanc info;
	node*next;
};

Tanc readTanc(FILE* f) {
	char buffer[20];
	fgets(buffer, 19, f);
	Tanc tanc;
	tanc.name = (char*)malloc(sizeof(char)*(strlen(buffer)));
	
	strcpy(tanc.name, "");
	strncat(tanc.name, buffer, strlen(buffer) - 1);
	
	fgets(buffer, 19, f);
	tanc.weight = atof(buffer);

	return tanc;
}

node* insertInCircularList(Tanc tanc, node*head) {
	node* newNode = (node*)malloc(sizeof(node));
	//shallow copy
	newNode->info = tanc;
	if (head) {
		node*p = head;
		while (p->next != head) {
			p = p->next;
		}
		p->next = newNode;
		newNode->next = head;
		return head;
	}
	else {
		newNode->next = newNode;
		return newNode;
	}
}

void printTanc(Tanc tanc, FILE* f) {
	fprintf(f, "The tank %s has %5.2f kiolgrams.\n", tanc.name, tanc.weight);
}


void printListInFile(node* head, char* fileName) {
	FILE* file = fopen(fileName, "w");
	if (file) {
		node* p = head;
		do {
			printTanc(p->info, file);
			p = p->next;
		} while (p != head);
		fclose(file);
	}
}

void deleteList(node**head) {
	if (*head) {
		node* p = (*head)->next;
		while (p != *head) {
			node* aux = p;
			p = p->next;
			free(aux->info.name);
			free(aux);
		}
		free(p->info.name);
		free(p);
		*head = NULL;
	}
}

Tanc* filterList(node* head, float limit, int *noElements) {
	node* p= head;
	*noElements = 0;
	do {
		if (p->info.weight >= limit) {
			(*noElements)++;
		}
	} while (p != head);
	Tanc* vector = (Tanc*)malloc(sizeof(Tanc)*(*noElements));
	p = head;
	*noElements = 0;
	do {
		if (p->info.weight >= limit) {
			vector[*noElements].name = (char*)malloc(sizeof(char)*(strlen(p->info.name) + 1));
			strcpy(vector[*noElements].name, p->info.name);
			vector[*noElements].weight = p->info.weight;
			(*noElements)++;
		}
	} while (p != head);
	return vector;
}

void main() {

	node*head = NULL;

	FILE* file = fopen("1050_tanks.txt", "r");
	int noElements;
	fscanf(file, "%d", &noElements);
	char buffer[3];
	//fflush(file);
	fgets(buffer, 3, file);
	for (int i = 0; i < noElements; i++) {
		head = insertInCircularList(readTanc(file), head);
	}

	printListInFile(head, "PrintedTanks.txt");
	fclose(file);
	//call filterList for an array and print that array
	//after you have to delete that array.
	deleteList(&head);
}