//#include<iostream>
//
//struct secondNode {
//	int code;
//	secondNode*next;
//};
//
//struct primaryNode {
//	int code;
//	secondNode* kid;
//	primaryNode*next;
//};
//
//void insertSecondList(secondNode** head, int code) {
//	secondNode*newNode = (secondNode*)malloc(sizeof(secondNode));
//	newNode->code = code;
//	newNode->next = NULL;
//	if (*head) {
//		secondNode*p = *head;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = newNode;
//	}
//	else {
//		*head = newNode;
//	}
//}
//
//void pushStack(secondNode**head, int code) {
//	insertSecondList(head, code);
//}
//
//int pullStack(secondNode**head) {
//	if (*head) {
//		secondNode*p = *head;
//		while (p->next && p->next->next)
//			p = p->next;
//		if (p->next) {
//			int result = p->next->code;
//			free(p->next);
//			p->next = NULL;
//			return result;
//		}
//		else {
//			int result = p->code;
//			free(p);
//			*head = NULL;
//			return result;
//		}
//	}
//	else {
//		return -1;
//	}
//}
//
//primaryNode* initializePrimaryList(int noNodes) {
//	primaryNode*head = NULL;
//	for (int i = noNodes - 1; i >= 0; i--) {
//		primaryNode*newNode = (primaryNode*)malloc(sizeof(primaryNode));
//		newNode->code = i;
//		newNode->kid = NULL;
//		newNode->next = head;
//		head = newNode;
//	}
//	return head;
//}
//
//
//
//void insertEdge(primaryNode*head, int code1, int code2) {
//	if (code1 > code2) {
//		int aux = code1;
//		code1 = code2;
//		code2 = aux;
//	}
//	primaryNode* p = head;
//	while (p && p->code < code1) {
//		p = p->next;
//	}
//	if (p) {
//		insertSecondList(&p->kid, code2);
//	}
//	while (p&& p->code != code2) {
//		p = p->next;
//	}
//	if (p) {
//		insertSecondList(&p->kid, code1);
//	}
//}
//
//int* DF(primaryNode*head, int noNodes, int startNode) {
//	int* result = (int*)malloc(sizeof(int)*noNodes);
//	int* flags = (int*)malloc(sizeof(int)*noNodes);
//	for (int i = 0; i < noNodes; i++) {
//		flags[i] = 0;
//	}
//	int k = 0;
//	secondNode* stack = NULL;
//
//	pushStack(&stack, startNode);
//	flags[startNode] = 1;
//
//	while (stack) {
//		int currentNode = pullStack(&stack);
//		result[k++] = currentNode;
//		primaryNode*p = head;
//		while (p && p->code != currentNode) {
//			p = p->next;
//		}
//		if (p) {
//			secondNode* s = p->kid;
//			while (s) {
//				if (flags[s->code] == 0) {
//					pushStack(&stack, s->code);
//					flags[s->code] = 1;
//				}
//				s = s->next;
//			}
//		}
//	}
//
//	free(flags);
//	return result;
//}
//
//
//void main() {
//	int noNodes;
//	printf("Nomber of nodes:");
//	scanf("%d", &noNodes);
//
//	primaryNode*graph = initializePrimaryList(noNodes);
//	int from;
//	int to;
//	printf("From:");
//	scanf("%d", &from);
//	while (from != -1) {
//
//		printf("To:");
//		scanf("%d", &to);
//
//		insertEdge(graph, from, to);
//		printf("From:");
//		scanf("%d", &from);
//	}
//
//	int * result = DF(graph, noNodes, 0);
//	for (int i = 0; i < noNodes; i++) {
//		printf("%d,", result[i]);
//	}
//
//	free(result);
//	//free the lists
//}