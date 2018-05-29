#include<iostream>


int** readGraph(int* noNodes) {

	printf("Number of nodes:");
	scanf("%d", noNodes);

	int**matrix = (int**)malloc(sizeof(int*)*(*noNodes));
	for (int i = 0; i < *noNodes; i++) {
		matrix[i] = (int*)malloc(sizeof(int)*(*noNodes));
		for (int j = 0; j < *noNodes; j++) {
			matrix[i][j] = 0;
		}
	}
	int from;
	int to;

	printf("From node: ");
	scanf("%d", &from);
	while (from > -1) {
		printf("To node: ");
		scanf("%d", &to);
		if (to > -1 && from < *noNodes && to < *noNodes && to!=from) {
			matrix[from][to] = 1;
			matrix[to][from] = 1;
		}
		printf("From node: ");
		scanf("%d", &from);
	}

	return matrix;
}

struct node {
	int info;
	node* next;
};

void pushStack(node* *head, int info) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->info = info;
	newNode->next = *head;
	*head = newNode;
}

int pulStack(node**head) {
	if (*head) {
		int result = (*head)->info;
		node* aux = *head;
		*head = (*head)->next;
		free(aux);
		return result;
	}
	else {
		return -1;
	}
}

void pushQueue(node**head, int info) {
	node*newNode = (node*)malloc(sizeof(node));
	newNode->info = info;
	newNode->next = NULL;
	if (*head) {
		node*p = *head;
		while (p->next) {
			p = p->next;
		}
		p->next = newNode;
	}
	else {
		*head = newNode;
	}
}

int pullQueue(node**head) {
	return pulStack(head);
}


void DF(int** matrix, int noNodes, int startNode) {
	int* flags = (int*)malloc(noNodes * sizeof(int));
	for (int i = 0; i < noNodes; i++) {
		flags[i] = 0;
	}
	node*stack = NULL;

	pushStack(&stack, startNode);
	flags[startNode] = 1;

	while (stack) {
		int currentNode = pulStack(&stack);
		printf("%d ", currentNode);
		for (int i = 0; i < noNodes; i++) {
			if (matrix[currentNode][i] == 1 && flags[i] == 0) {
				pushStack(&stack, i);
				flags[i] = 1;
			}
		}
	}

	free(flags);
}

int * BF(int**matrix, int noNodes, int startNode) {
	int*flags = (int*)malloc(sizeof(int)*noNodes);
	for (int i = 0; i < noNodes; i++) {
		flags[i] = 0;
	}
	int* result= (int*)malloc(sizeof(int)*noNodes);
	node* queue = NULL;

	pushQueue(&queue, startNode);
	flags[startNode] = 1;

	int k = 0;
	while (queue) {
		int currentNode = pullQueue(&queue);
		result[k++] = currentNode;
		for (int i = 0; i < noNodes; i++) {
			if (matrix[currentNode][i] == 1 && flags[i] == 0) {
				pushQueue(&queue, i);
				flags[i] = 1;
			}
		}
	}
	free(flags);
	return result;
}

void main() {
	int noNodes;
	int**matrix = readGraph(&noNodes);
	DF(matrix, noNodes, 0);

	int* result = BF(matrix, noNodes, 0);

	for (int i = 0; i < noNodes; i++) {
		printf("%d, ", result[i]);
	}

	free(result);
	for (int i = 0; i < noNodes; i++) {
		free(matrix[i]);
	}
	free(matrix);
}