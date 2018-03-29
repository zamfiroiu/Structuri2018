//#include<iostream>
//struct Book {
//	char* title;
//	int numberOfPages;
//};
//
//struct node {
//	Book info;
//	node* next;
//};
//
//node* insertAtBegin(node* head, Book book) {
//	node* newNode = (node*)malloc(sizeof(node));
//	newNode->info.title = (char*)malloc(sizeof(char)*(strlen(book.title) + 1));
//	strcpy(newNode->info.title, book.title);
//	newNode->info.numberOfPages = book.numberOfPages;
//	newNode->next = head;
//	return newNode;
//}
//
//Book createBook(const char* title, int numberOfPages) {
//	Book book;
//	book.title = (char*)malloc(sizeof(char)*(strlen(title) + 1));
//	strcpy(book.title, title);
//	book.numberOfPages = numberOfPages;
//
//	return book;
//}
//
//node* insertAtEnd(node* head, Book book) {
//	node* newNode = (node*)malloc(sizeof(node));
//	newNode->info.title = (char*)malloc(sizeof(char)*(strlen(book.title) + 1));
//	strcpy(newNode->info.title, book.title);
//	newNode->info.numberOfPages = book.numberOfPages;
//	newNode->next = NULL;
//	if (head) {
//		node*p = head;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = newNode;
//	}
//	else {
//		head = newNode;
//	}
//	return head;
//}
//
//void displayBook(Book book) {
//	printf("Book %s has %d pages\n", book.title, book.numberOfPages);
//}
//
//void displayList(node* head) {
//	node* p = head;
//	while (p) {
//		displayBook(p->info);
//		p = p->next;
//	}
//}
//
//node* deleteList(node* head) {
//	while (head) {
//		free(head->info.title);
//		node* temp = head;
//		head = head->next;
//		free(temp);
//	}
//	return head;
//}
//
//node* insertSorted(node* head, Book book) {
//	if (head) {
//		if (book.numberOfPages < head->info.numberOfPages) {
//			head = insertAtBegin(head, book);
//		}
//		else {
//			node*p = head;
//			while (p->next && p->next->info.numberOfPages < book.numberOfPages) {
//				p = p->next;
//			}
//			p->next = insertAtBegin(p->next, book);
//		}
//	}
//	else {
//		head = insertAtBegin(NULL, book);
//	}
//	return head;
//}
//
//void pushStack(node* *stack, Book info) {
//	*stack = insertAtEnd(*stack, info);
//}
//
//Book popStack(node* *stack) {
//	node* p = *stack;
//	while (p && p->next && p->next->next) {
//		p = p->next;
//	}
//	if (p && p->next) {
//		Book book = createBook(p->next->info.title, p->next->info.numberOfPages);
//		free(p->next->info.title);
//		free(p->next);
//		p->next = NULL;
//		return book;
//	}
//	else {
//		if (p) {
//			Book book = createBook(p->info.title, p->info.numberOfPages);
//			free(p->info.title);
//			free(p);
//			*stack = NULL;
//			return book;
//		}
//		else {
//			Book book;
//			book.title = NULL;
//			book.numberOfPages = -1;
//			return book;
//		}
//	}
//}
//
//int isEmpty(node* stack) {
//	return stack ? 0 : 1;
//}
//
//void pushQueue(node* * queue, Book info) {
//	*queue = insertAtBegin(*queue, info);
//}
//
//Book popQueue(node** queue) {
//	return popStack(queue);
//}
//
//node* filterBooksInAQueue(node* *stack, int limit) {
//	node* resultQueue = NULL;
//	node* tempStack = NULL;
//	while (*stack) {
//		Book book = popStack(stack);
//		if (book.numberOfPages > limit) {
//			pushStack(&tempStack,book);
//		}
//		else {
//			pushQueue(&resultQueue, book);
//		}
//		free(book.title);
//	}
//
//	while (tempStack) {
//		Book book = popStack(&tempStack);
//		pushStack(stack, book);
//		free(book.title);
//	}
//	return resultQueue;
//}
//
//node* filterBooks(node* stack, int limit) {
//	node*tempStack = NULL;
//	while (stack) {
//		Book book = popStack(&stack);
//		if (book.numberOfPages > limit) {
//			pushStack(&tempStack, book);			
//		}
//		else {
//			displayBook(book);
//		}
//		free(book.title);
//	}
//	while (tempStack) {
//		Book book = popStack(&tempStack);
//		pushStack(&stack, book);
//		free(book.title);
//	}
//	return stack;
//}
//
//
//
//void main() {
//	node* stack = NULL;
//
//	pushStack(&stack, createBook("Morometii", 400));
//	pushStack(&stack, createBook("Ion", 200));
//	pushStack(&stack, createBook("Moara cu noroc", 160));
//	pushStack(&stack, createBook("Baltagul", 170));
//	//
//	////memory leak
//	//if (!isEmpty(stack)) {
//	//	displayBook(popStack(&stack));
//	//}
//
//	//while (stack) {
//	//	Book book = popStack(&stack);
//	//	displayBook(book);
//	//	free(book.title);
//	//}
//
//	//node* queue = NULL;
//	//pushQueue(&queue, createBook("Morometii", 400));
//	//pushQueue(&queue, createBook("Ion", 200));
//	//pushQueue(&queue, createBook("Moara cu noroc", 160));
//	//pushQueue(&queue, createBook("Baltagul", 170));
//
//	//printf("Queue:\n");
//	//while (queue) {
//	//	Book book = popQueue(&queue);
//	//	displayBook(book);
//	//	free(book.title);
//	//}
//
//	/*stack = filterBooks(stack, 200);
//	printf("The result stack:\n");
//	while (stack) {
//		Book book = popStack(&stack);
//		displayBook(book);
//		free(book.title);
//	}*/
//
//	node* resultQueue = filterBooksInAQueue(&stack, 200);
//	printf("Queue:\n");
//	while (resultQueue) {
//		Book book = popQueue(&resultQueue);
//		displayBook(book);
//		free(book.title);
//	}
//
//	printf("The result stack:\n");
//	while (stack) {
//		Book book = popStack(&stack);
//		displayBook(book);
//		free(book.title);
//	}
//
//	//node*p = (node*)malloc(sizeof(node));
//	//free(p);
//	//p = NULL;
//
//	node** p;
//	p = (node**)malloc(sizeof(node*));
//	(*p) = NULL;
//
//}