#include<iostream>

struct Message {
	char* text;
	int priority;
};

Message createMessage(char* text, int priority) {
	Message m;
	m.text = (char*)malloc(sizeof(char)*(strlen(text) + 1));
	strcpy(m.text, text);
	m.priority = priority;

	return m;
}

void printMessage(Message m) {
	printf("Message %s has priority %d\n", m.text, m.priority);
}

struct HEAP {
	Message * vector;
	int size;
};

void filter(HEAP heap, int pos) {
	int leftChild = pos * 2 + 1;
	int rightChild = pos * 2 + 2;
	int maxPos = pos;
	if (leftChild<heap.size && heap.vector[maxPos].priority < heap.vector[leftChild].priority) {
		maxPos = leftChild;
	}
	if (rightChild < heap.size && heap.vector[maxPos].priority < heap.vector[rightChild].priority) {
		maxPos = rightChild;
	}

	if (maxPos != pos) {
		Message aux = heap.vector[pos];
		heap.vector[pos] = heap.vector[maxPos];
		heap.vector[maxPos] = aux;
		if (maxPos <= (heap.size - 1) / 2) {
			filter(heap, maxPos);
		}
	}
}

void printHeap(HEAP heap) {
	for (int i = 0; i < heap.size; i++) {
		printMessage(heap.vector[i]);
	}
}

void insertNewMessage(HEAP * heap, Message m) {
	Message* temp = (Message*)malloc(sizeof(Message)*(heap->size + 1));
	for (int i = 0; i < heap->size; i++) {
		temp[i] = heap->vector[i];
	}
	temp[heap->size] = createMessage(m.text, m.priority);
	heap->size++;
	free(heap->vector);
	heap->vector = temp;
	for (int i = (heap->size - 1) / 2; i >= 0; i--) {
		filter(*heap, i);
	}

}

Message extractMessage(HEAP * heap) {
	Message m = heap->vector[0];
	Message* temp= (Message*)malloc(sizeof(Message)*(heap->size - 1));
	for (int i = 0; i < heap->size-1; i++) {
		temp[i] = heap->vector[i+1];
	}
	heap->size--;
	free(heap->vector);
	heap->vector = temp;

	for (int i = 0; i < heap->size; i++) {
		temp[i] = heap->vector[i];
	}
	return m;
}

void main() {

	HEAP heap;
	heap.size = 6;
	heap.vector = (Message*)malloc(sizeof(Message)*heap.size);
	heap.vector[0] = createMessage("Hello", 5);
	heap.vector[1] = createMessage("how are you?", 4);
	heap.vector[2] = createMessage("Good bye", 7);
	heap.vector[3] = createMessage("see you later", 9);
	heap.vector[4] = createMessage("Alligator", 2);
	heap.vector[5] = createMessage("Crocodile", 6);

	printHeap(heap);
	for (int i = (heap.size - 1) / 2; i >= 0; i--) {
		filter(heap, i);
	}
	printf("\n");
	printHeap(heap);

	Message m = createMessage("Message", 11);
	insertNewMessage(&heap, m);

	printf("\n");
	printHeap(heap);

	for (int i = 0; i < heap.size; i++) {
		free(heap.vector[i].text);
	}
	free(heap.vector);

}