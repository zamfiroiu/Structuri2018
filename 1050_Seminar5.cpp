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

void displayBook(Book book) {
	printf("Book %s has %d pages\n", 
		book.title, book.numberOfPages);
}

void displayList(node* head) {
	node* p = head;
	while (p) {
		displayBook(p->info);
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

node* pushStack(node* stack, Book book) {
	stack = insertAtBegin(stack, book);
	return stack;
}

Book popStack(node* *stack) {
	if (*stack) {
		Book result = createBook((*stack)->info.title, (*stack)->info.numberOfPages);
		node* temp = *stack;
		*stack = (*stack)->next;
		temp->next = NULL;
		deleteList(temp);
		//free(temp->info.title);
		//free(temp);
		return result;
	}
	else {
		Book book;
		book.title = NULL;
		book.numberOfPages = -1;
		return book;
	}
}

int existsStack(node* stack) {
	return stack ? 1 : 0;
}

node* pushQueue(node* head, Book info) {
	head = insertAtEnd(head, info);
	return head;
}

Book popQueue(node* * head) {
	return popStack(head);
}

node* filterBooksbyPages(node* stack, int limit) {
	node* tempStack = NULL;
	while (existsStack(stack)) {
		Book tempBook = popStack(&stack);
		if (tempBook.numberOfPages >= limit) {
			displayBook(tempBook);
		}
		else {
			tempStack = pushStack(tempStack, tempBook);
		}
		free(tempBook.title);
	}
	while (tempStack) {
		Book temp = popStack(&tempStack);
		stack = pushStack(stack,temp);
		free(temp.title);
	}

	return stack;
}

node* filterBooksbyPagesInAQueue(node* *stack, int limit) {
	node* tempStack = NULL;
	node* resultQueue = NULL;

	while (existsStack(*stack)) {
		Book tempBook = popStack(stack);
		if (tempBook.numberOfPages >= limit) {
			resultQueue = pushQueue(resultQueue, tempBook);
		}
		else {
			tempStack = pushStack(tempStack, tempBook);
		}
		free(tempBook.title);
	}
	while (tempStack) {
		Book temp = popStack(&tempStack);
		*stack = pushStack(*stack, temp);
		free(temp.title);
	}

	return resultQueue;
}

void main() {

	node* stack = NULL;
	stack = pushStack(stack, createBook("Baltagul", 165));
	stack = pushStack(stack, createBook("Morometii", 520));
	stack = pushStack(stack, createBook("Ion", 994));

	//while (existsStack(stack)) {
	//	Book book = popStack(&stack);
	//	displayBook(book);
	//	free(book.title);
	//}


	//node* queue = NULL;
	//queue = pushQueue(queue, createBook("Moara cu noroc", 150));
	//queue = pushQueue(queue, createBook("Structuri de date", 600));
	//queue = pushQueue(queue, createBook("JUnit testing", 240));


	//if (queue) {
	//	Book book = popQueue(&queue);
	//	displayBook(book);
	//	free(book.title);
	//}

	////memory leaks
	//while (queue) {
	//	displayBook(popQueue(&queue));
	//}

	//filterBooksbyPages - print and return
	/*stack = filterBooksbyPages(stack, 500);

	printf("The result stack:\n");
	while (existsStack(stack)) {
		Book book = popStack(&stack);
		displayBook(book);
		free(book.title);
	}*/


	//filterBooksbyPagesinAQueue - return a queue and a stack
	node* resultQueue = filterBooksbyPagesInAQueue(&stack, 500);
	printf("The result stack:\n");
	while (existsStack(stack)) {
		Book book = popStack(&stack);
		displayBook(book);
		free(book.title);
	}

	printf("The queue:\n");
	while (resultQueue) {
		Book book = popQueue(&resultQueue);
		displayBook(book);
		free(book.title);
	}

}