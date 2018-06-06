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
		if (to > -1 && from < *noNodes && to < *noNodes && to != from) {
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

int popStack(node**head) {
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
	return popStack(head);
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
		int currentNode = popStack(&stack);
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
	int* result = (int*)malloc(sizeof(int)*noNodes);
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

struct nodSimplu {
	int cod;
	nodSimplu*next;
};

struct nodPrincipal {
	nodSimplu*vecini;
	nodPrincipal*next;
	int cod;
};

nodPrincipal* initializareLista(int nrNoduri) {
	nodPrincipal*cap = NULL;
	for (int i = nrNoduri - 1;i >= 0;i--) {
		nodPrincipal*nou = (nodPrincipal*)malloc(sizeof(nodPrincipal));
		nou->cod = i;
		nou->vecini = NULL;
		nou->next = cap;
		cap = nou;
	}
	return cap;
}

void inserareNodSimplu(nodSimplu**cap, int cod) {
	nodSimplu* nou = (nodSimplu*)malloc(sizeof(nodSimplu));
	nou->cod = cod;
	nou->next = NULL;
	if (*cap) {
		nodSimplu*p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareArc(int deLa, int panaLa, nodPrincipal*graf) {
	nodPrincipal*p = graf;
	while (p && p->cod != deLa) {
		p = p->next;
	}
	if (p) {
		inserareNodSimplu(&p->vecini, panaLa);
	}
}

nodPrincipal* citireGrafListaDeListe() {
	int nrNoduri;
	printf("Numarul de noduri:");
	scanf("%d", &nrNoduri);

	nodPrincipal* graf = initializareLista(nrNoduri);
	int nrArce;
	printf("Numarul de Arce:");
	scanf("%d", &nrArce);

	for (int i = 0;i < nrArce;i++) {
		int deLa;
		int panaLa;
		printf("De la:");
		scanf("%d", &deLa);
		printf("Pana la:");
		scanf("%d", &panaLa);
		if (deLa >= 0 && deLa < nrNoduri &&panaLa >= 0 && panaLa < nrNoduri && deLa!=panaLa) {
			inserareArc(deLa, panaLa, graf);
			inserareArc(panaLa, deLa, graf);
		}

	}
	return graf;
}

int numarNoduri(nodPrincipal* cap) {
	int contor = 0;
	while(cap){
		contor++;
		cap = cap->next;
	}
	return contor;
}

void latimeListaDeListe(nodPrincipal*graf, int nodPlecare) {
	int nrNoduri = numarNoduri(graf);
	int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0;i < nrNoduri;i++) {
		vizitate[i] = 0;
	}

	node*coada = NULL;
	pushQueue(&coada, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (coada) {
		int nodCurent = pullQueue(&coada);
		printf("%d, ", nodCurent);
		nodPrincipal* p;
		for (p = graf;p && p->cod != nodCurent;p = p->next);
		if (p) {
			nodSimplu*s = p->vecini;
			while (s) {
				if (vizitate[s->cod] == 0) {
					vizitate[s->cod] = 1;
					pushQueue(&coada, s->cod);					
				}
				s = s->next;
			}
		}
	}
	free(vizitate);
}

void stergereListaSimpla(nodSimplu**cap) {
	while (*cap) {
		nodSimplu*aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

void stergereListaDeListe(nodPrincipal**cap) {
	while (*cap) {
		stergereListaSimpla(&(*cap)->vecini);
		nodPrincipal*aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

void main() {
	nodPrincipal* graf = citireGrafListaDeListe();
	latimeListaDeListe(graf, 0);
	stergereListaDeListe(&graf);
}