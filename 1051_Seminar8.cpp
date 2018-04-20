//#include<iostream>
//
//struct Message {
//	char* text;
//	int priority;
//};
//
//Message createMessage(char* text, int priority) {
//	Message m;
//	m.text = (char*)malloc(sizeof(char)*(strlen(text) + 1));
//	strcpy(m.text, text);
//	m.priority = priority;
//	return m;
//}
//
//void printMessage(Message m) {
//	printf("Message %s has priority %d.\n", m.text, m.priority);
//}
//
//struct HEAP {
//	Message*vector;
//	int size;
//};
//
//void printHeap(HEAP heap) {
//	for (int i = 0; i < heap.size; i++) {
//		printMessage(heap.vector[i]);
//	}
//}
//
//void filter(HEAP heap, int position) {
//	if (position <= (heap.size - 1) / 2) {
//		int leftChild = 2 * position + 1;
//		int rightChild = 2 * position + 2;
//		int max = position;
//		if (leftChild<heap.size && heap.vector[max].priority < heap.vector[leftChild].priority) {
//			max = leftChild;
//		}
//		if (rightChild<heap.size && heap.vector[max].priority < heap.vector[rightChild].priority) {
//			max = rightChild;
//		}
//		if (position != max) {
//			Message aux = heap.vector[position];
//			heap.vector[position] = heap.vector[max];
//			heap.vector[max] = aux;
//			if (max < (heap.size - 1) / 2) {
//				filter(heap, max);
//			}
//		}
//
//	}
//}
//
//void insertNewMessage(HEAP* heap, Message m) {
//	Message * temp = (Message*)malloc(sizeof(Message)*(heap->size + 1));
//	for (int i = 0; i < heap->size; i++) {
//		temp[i] = heap->vector[i];
//	}
//	temp[heap->size] = m;
//	heap->size++;
//	free(heap->vector);
//	heap->vector = temp;
//	for (int i = (heap->size - 1) / 2; i >= 0; i--) {
//		filter(*heap, i);
//	}
//}
//
//Message extractMessage(HEAP *heap) {
//	if (heap->vector) {
//		Message result = heap->vector[0];
//		Message* temp = (Message*)malloc(sizeof(Message)*(heap->size - 1));
//		for (int i = 0; i < heap->size - 1; i++) {
//			temp[i] = heap->vector[i + 1];
//		}
//		heap->size--;
//		free(heap->vector);
//		heap->vector = temp;
//		for (int i = (heap->size - 1) / 2; i >= 0; i--) {
//			filter(*heap, i);
//		}
//		return result;
//	}
//}
//
//void main() {
//	HEAP heap;
//	heap.size = 6;
//	heap.vector = (Message*)malloc(sizeof(Message)*heap.size);
//	heap.vector[0] = createMessage("Hello", 5);
//	heap.vector[1] = createMessage("Hello again", 3);
//	heap.vector[2] = createMessage("How are you", 4);
//	heap.vector[3] = createMessage("bye", 9);
//	heap.vector[4] = createMessage("Something", 8);
//	heap.vector[5] = createMessage("Something else", 6);
//
//	printHeap(heap);
//
//	for (int i = (heap.size - 1) / 2; i >= 0; i--) {
//		filter(heap, i);
//	}
//
//	printf("\n");
//	printHeap(heap);
//
//	insertNewMessage(&heap, createMessage("Last message", 11));
//
//	printf("\n");
//	printHeap(heap);
//
//	Message m = extractMessage(&heap);
//	printf("\n");
//	printMessage(m);
//
//	printf("\n");
//
//	printHeap(heap);
//
//}