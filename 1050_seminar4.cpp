#include<iostream>

struct CreditCard {
	char* owner;
	int cardNumber;
};

struct simpleNode {
	CreditCard info;
	simpleNode*next;
};

struct doubleNode {
	CreditCard info;
	doubleNode* next;
	doubleNode* prev;
};

struct DLL {
	doubleNode* first;
	doubleNode* last;
};

CreditCard createCard(char* owner, int number) {
	CreditCard card;
	card.owner=(char*)malloc(sizeof(char)*(strlen(owner) + 1));
	strcpy(card.owner, owner);
	card.cardNumber = number;

	return card;
}

doubleNode* createDoubleNode(CreditCard card, doubleNode* next, doubleNode *prev) {
	doubleNode*newNode = (doubleNode*)malloc(sizeof(doubleNode));
	newNode->info = createCard(card.owner,card.cardNumber);
	newNode->next = next;
	newNode->prev = prev;
	return newNode;
}

DLL insertAtBegining(DLL list, CreditCard info) {
	doubleNode* newNode = createDoubleNode(info, list.first, NULL);

	if (list.first) {
		list.first->prev = newNode;
	}
	else {
		list.last = newNode;
	}
	list.first = newNode;
	return list;
}

simpleNode* insertAtBegining(simpleNode* head, CreditCard info) {
	simpleNode*newNode = (simpleNode*)malloc(sizeof(simpleNode));
	newNode->info = createCard(info.owner, info.cardNumber);
	newNode->next = head;
	return newNode;
}

void printCreditCard(CreditCard card) {
	printf("%s has a card with the number %d.\n", card.owner, card.cardNumber);
}

void printNormalList(DLL list) {
	doubleNode* p = list.first;
	while (p) {
		printCreditCard(p->info);
		p = p->next;
	}
}

void printInverseList(DLL list) {
	for (doubleNode* p = list.last; p != NULL; p = p->prev) {
		printCreditCard(p->info);
	}
}

void freeList(DLL *list) {
	while (list->first) {
		doubleNode* aux = list->first;
		list->first = list->first->next;
		free(aux->info.owner);
		free(aux);
	}
	list->last = NULL;
}

DLL insertOnThePosition(DLL list, CreditCard info, int position) {
	if (list.first) {
		doubleNode* p = list.first;
		while (p && position > 1) {
			p = p->next;
			position--;
		}
		if (p) {
			doubleNode* newNode = createDoubleNode(info, p, p->prev);
			p->prev = newNode;
			if (newNode->prev) {
				newNode->prev->next = newNode;
			}
			else {
				list.first = newNode;
			}
		}
		else {
			doubleNode* newNode = createDoubleNode(info, NULL, list.last);
			if (list.last) {
				list.last->next = newNode;

			}
			else {
				list.first = newNode;
			}
			list.last = newNode;
		}
	}
	else {
		list = insertAtBegining(list, info);
	}
	return list;
}

simpleNode* filterCreditCards(DLL list, int value) {
	simpleNode* head = NULL;
	while (list.first) {
		if (list.first->info.cardNumber >= value) {
			head = insertAtBegining(head, list.first->info);
		}
		list.first = list.first->next;
	}

	return head;
}
void main() {
	DLL list;
	list.first = NULL;
	list.last = NULL;

	list = insertOnThePosition(list, createCard("Popescu", 3002),1);
	list = insertOnThePosition(list, createCard("John", 3006),1);
	list = insertOnThePosition(list, createCard("Ionescu", 3111),2);

	printNormalList(list);

	simpleNode*head = filterCreditCards(list, 3015);

	printf("\n");
	while (head) {
		printCreditCard(head->info);
		free(head->info.owner);
		simpleNode* aux = head;
		head = head->next;
		free(aux);
	}

	freeList(&list);
}