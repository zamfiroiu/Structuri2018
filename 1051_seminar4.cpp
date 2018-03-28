#include<iostream>

struct Train {
	char* type;
	int number;
};

struct simpleNode {
	Train info;
	simpleNode* next;
};

struct doubleNode {
	doubleNode* next;
	doubleNode* prev;
	Train info;
};

struct DLL {
	doubleNode* first;
	doubleNode* last;
};

Train createTrain(char*type, int number) {
	Train train;
	train.type = (char*)malloc(sizeof(char)*(strlen(type) + 1));
	strcpy(train.type, type);
	train.number = number;
	return train;
}

simpleNode* insertAtBegin(simpleNode* head, Train info) {
	simpleNode*newNode = (simpleNode*)malloc(sizeof(simpleNode));
	newNode->next = head;
	newNode->info = createTrain(info.type, info.number);
	return newNode;
}

doubleNode* createDoubleNode(Train info, doubleNode* next, doubleNode* prev) {
	doubleNode* newNode = (doubleNode*)malloc(sizeof(doubleNode));
	newNode->next = next;
	newNode->prev = prev;
	newNode->info = createTrain(info.type,info.number);
	return newNode;
}

DLL insertAtBegin(DLL list, Train info) {
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

void printTrain(Train train) {
	printf("Train %s have the number %d. \n", train.type, train.number);
}

void printInverseList(DLL list) {
	for (doubleNode* p = list.last; p != NULL; p = p->prev) {
		printTrain(p->info);
	}
}

DLL freeList(DLL list) {
	while (list.first) {
		free(list.first->info.type);
		doubleNode* aux = list.first;
		list.first = list.first->next;
		free(aux);
	}
	list.last = NULL;
	return list;
}

DLL insertAtThePosition(DLL list, Train info, int position) {
	doubleNode* p = list.first;
	int counter = 1;
	while (p && counter < position) {
		counter++;
		p = p->next;
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
		else
		{
			list.first = newNode;
		}
		list.last = newNode;
	}
	return list;
}

simpleNode* filterTrains(DLL list, int limit) {
	doubleNode* p = list.first;
	simpleNode* head = NULL;
	while (p) {
		if (p->info.number >= limit) {
			head = insertAtBegin(head, p->info);
		}
		p = p->next;
	}
	return head;
}

Train extractTrain(DLL * list, int number) {
	doubleNode* temp = list->first;
	while (temp && temp->info.number != number) {
		temp = temp->next;
	}
	if (temp) {
		if (temp->prev) {
			temp->prev->next = temp->next;
		}
		else {
			list->first = temp->next;
		}

		if (temp->next) {
			temp->next->prev = temp->prev;
		}
		else {
			list->last = temp->prev;
		}
		Train train = createTrain(temp->info.type, temp->info.number);
		free(temp->info.type);
		free(temp);
		return train;
	}
	else {
		return createTrain("", 0);
	}
}

void main() {
	DLL list;
	list.first = NULL;
	list.last = NULL;

	list = insertAtThePosition(list, createTrain("Regio", 7),1);
	list = insertAtThePosition(list, createTrain("InterRegio", 9),1);
	list = insertAtThePosition(list, createTrain("Regio", 8),2);

	printInverseList(list);

	simpleNode* head = filterTrains(list, 9);

	printf("\n\n");
	while (head) {
		printTrain(head->info);
		simpleNode* aux = head;
		head = head->next;
		free(aux->info.type);
		free(aux);
	}

	list = freeList(list);
}