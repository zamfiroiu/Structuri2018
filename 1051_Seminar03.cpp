#include<iostream>
struct Book {
	char* title;
	int numberOfPages;
};

struct node {
	Book info;
	node* next;
};

node* insertAtBegin(node* head, Book book) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->info.title = (char*)malloc(sizeof(char)*(strlen(book.title) + 1));
	strcpy(newNode->info.title, book.title);
	newNode->info.numberOfPages = book.numberOfPages;
	newNode->next = head;
	return newNode;
}

Book createBook(const char* title, int numberOfPages) {
	Book book;
	book.title = (char*)malloc(sizeof(char)*(strlen(title) + 1));
	strcpy(book.title, title);
	book.numberOfPages = numberOfPages;

	return book;
}

node* insertAtEnd(node* head, Book book) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->info.title = (char*)malloc(sizeof(char)*(strlen(book.title) + 1));
	strcpy(newNode->info.title, book.title);
	newNode->info.numberOfPages = book.numberOfPages;
	newNode->next = NULL;
	if (head) {
		node*p = head;
		while (p->next) {
			p = p->next;
		}
		p->next = newNode;
	}
	else {
		head = newNode;
	}
	return head;	
}

void displayList(node* head) {
	node* p = head;
	while (p) {
		printf("Book %s has %d pages\n",p->info.title,p->info.numberOfPages);
		p = p->next;
	}
}

node* deleteList(node* head) {
	while (head) {
		free(head->info.title);
		node* temp = head;
		head = head->next;
		free(temp);
	}
	return head;
}

node* insertSorted(node* head, Book book) {
	if (head) {
		if (book.numberOfPages < head->info.numberOfPages) {
			head = insertAtBegin(head, book);
		}
		else {
			node*p = head;
			while (p->next && p->next->info.numberOfPages < book.numberOfPages) {
				p = p->next;
			}
			p->next = insertAtBegin(p->next, book);
		}
	}
	else {
		head = insertAtBegin(NULL, book);
	}
	return head;
}

void main() {
	node* head = NULL;
	Book book = createBook("Ion", 200);
	head = insertAtBegin(head, book);
	book.numberOfPages = 300;
	head = insertAtBegin(head, book);
	displayList(head);
	head=deleteList(head);
	head = insertAtEnd(head, book);
	book.numberOfPages = 500;
	head = insertAtEnd(head, book);
	printf("INsert at end:\n");
	displayList(head);
	head=deleteList(head);

	head = insertSorted(head, book);
	book.numberOfPages = 200;
	head = insertSorted(head, book);
	book.numberOfPages = 400;
	head = insertSorted(head, book);

	printf("Sorted list:\n");
	displayList(head);
	head = deleteList(head);


	free(book.title);
}