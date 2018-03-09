#include<iostream>

struct Hotel {
	char* name;
	int numberRooms;
};

struct node {
	Hotel info;
	node* next;
};

node* insertAtBegin(node* head, Hotel hotel) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->info.name = (char*)malloc(sizeof(char)*(strlen(hotel.name) + 1));
	strcpy(newNode->info.name, hotel.name);
	newNode->info.numberRooms = hotel.numberRooms;
	newNode->next = head;
	return newNode;
}

Hotel createHotel(char* name, int numberofRooms) {
	Hotel hotel;
	hotel.name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	strcpy(hotel.name, name);
	hotel.numberRooms = numberofRooms;
	return hotel;
}

void printList(node* head) {
	node* p = head;
	while (p) {
		printf("Hotel %s has %d rooms\n", p->info.name,p->info.numberRooms);
		p = p->next;
	}
}

node* deleteList(node* head) {
	while (head) {
		free(head->info.name);
		node* temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}

node* insertAtEnd(node*head, Hotel hotel) {
	if (head) {
		node* p = head;
		while (p->next) {
			p = p->next;
		}
		p->next = insertAtBegin(NULL, hotel);
		return head;
	}
	else {
		return insertAtBegin(NULL, hotel);
	}
}

node* insertSorted(node*head, Hotel hotel) {
	if (head) {
		if (hotel.numberRooms < head->info.numberRooms) {
			head = insertAtBegin(head, hotel);
		}
		else {
			node* p = head;
			while (p->next && hotel.numberRooms > p->next->info.numberRooms) {
				p = p->next;
			}
			p->next = insertAtBegin(p->next, hotel);
		}
	}
	else {
		head = insertAtBegin(NULL, hotel);
	}
	return head;
}

node* filterHotels(node* head, int value) {
	node* result = NULL;
	node*p = head;
	while (p){
		if (p->info.numberRooms < value) {
			result = insertAtEnd(result, p->info);
		}
		p = p->next;
	}
	return result;
}

void main() {
	node* head = NULL;
	Hotel hotel = createHotel("Sheraton", 85);
	head = insertAtBegin(head, hotel);
	hotel.numberRooms = 62;
	head = insertAtBegin(head, hotel);

	printList(head);	
	head = deleteList(head);

	head = insertAtEnd(head, hotel);
	hotel.numberRooms = 39;
	head = insertAtEnd(head, hotel);
	
	printf("\n");
	printList(head);
	head = deleteList(head);

	head = insertSorted(head, hotel);
	hotel.numberRooms = 25;
	head = insertSorted(head, hotel);
	hotel.numberRooms = 29;
	head = insertSorted(head, hotel);

	printf("\n");
	printList(head);

	node* list = filterHotels(head, 26);
	printf("List:\n");
	printList(list);

	list = deleteList(list);

	head = deleteList(head);

	free(hotel.name);



}