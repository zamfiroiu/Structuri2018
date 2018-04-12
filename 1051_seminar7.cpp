#include<iostream>


struct Toy{
	char* name;
	int minimumAge;
};

struct node{
	Toy info;
	node* next;
};

Toy readToyFromFile(FILE* f){
	char buffer[20];

	fgets(buffer, 19, f);
	fgets(buffer, 19, f);
	Toy toy;
	toy.name = (char*)malloc(sizeof(char)*(strlen(buffer) ));
	strcpy(toy.name, "");
	strncat(toy.name, buffer, strlen(buffer) - 1);
	
	fscanf(f, "%d", &toy.minimumAge);
	return toy;
}

node* insertInTheList(node* head, Toy toy){
	node* newNode = (node*)malloc(sizeof(node));
	//shallow copy
	newNode->info = toy;
	if (head){
		newNode->next = head;
		node* p = head;
		while (p->next != head){
			p = p->next;
		}
		p->next = newNode;
		return head;
	}
	else{
		newNode->next = newNode;
		return newNode;
	}
}

void printToy(Toy toy, FILE* f){
	fprintf(f, "Toy %s can be used from %d years.\n", toy.name, toy.minimumAge);
}

void printListInFile(const char* fileName, node*head){
	if (head){
		FILE* f = fopen(fileName, "w");
		if (f){
			node* p = head;
			do{
				printToy(p->info,f);
				p = p->next;
			} while (p != head);
			fclose(f);
		}
	}
}

void deleteList(node** head){
	if (*head){
		node* p = (*head)->next;
		while (p != *head){
			free(p->info.name);
			node* temp = p;
			p = p->next;
			free(temp);
		}
		free(p->info.name);
		free(p);
		*head = NULL;
	}
}

void main(){
	node* head=NULL;
	FILE* file = fopen("1051_toys.txt", "r");

	if (file){
		int noElem;
		fscanf(file, "%d", &noElem);
		for (int i = 0; i < noElem; i++){
			head = insertInTheList(head, readToyFromFile(file));
		}

		//print
		printListInFile("printedTOys.txt", head);
		//delete list
		deleteList(&head);


	}
}