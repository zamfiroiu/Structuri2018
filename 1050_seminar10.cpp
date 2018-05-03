#include<iostream>

struct Casino {
	int noSlotMachines;
	char* name;
};

Casino createCasino(char* name, int number) {
	Casino c;
	c.name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	strcpy(c.name, name);
	c.noSlotMachines = number;

	return c;
}


void printCasino(Casino c) {
	printf("Casino %s has %d slots machines.\n", c.name, c.noSlotMachines);
}

struct node {
	Casino info;
	node*left;
	node*right;
};

node* insertCasinoInTree(Casino c, node* root) {
	if (root) {
		if (c.noSlotMachines < root->info.noSlotMachines) {
			root->left = insertCasinoInTree(c, root->left);
		}
		else if (c.noSlotMachines > root->info.noSlotMachines) {
			root->right = insertCasinoInTree(c, root->right);

		}
		return root;
	}
	else {
		node* newNode = (node*)malloc(sizeof(node));
		newNode->info = c;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
}

void printTree(node* root) {
	if (root) {
		printTree(root->left);
		printCasino(root->info);
		printTree(root->right);
	}
}

int height(node* root) {
	if (root) {
		int left = height(root->left);
		int right = height(root->right);
		return (left > right) ? left + 1 : right + 1;
	}
	else {
		return 0;
	}
}


Casino searchCasinoByNo(node* root, int numberSlotMachines) {
	if (root) {
		if (numberSlotMachines < root->info.noSlotMachines) {
			return searchCasinoByNo(root->left, numberSlotMachines);
		}
		else if (numberSlotMachines > root->info.noSlotMachines) {
			return searchCasinoByNo(root->right, numberSlotMachines);
		}
		else {
			return root->info;
		}
	}
	else {
		return createCasino("", -1);
	}
}
void freeTree(node**root) {
	if (*root) {
		freeTree(&(*root)->left);
		freeTree(&(*root)->right);
		free((*root)->info.name);
		free(*root);
		*root = NULL;
	}
}

void printNodesFromALevel(node* root, int desiredLevel, int currentLevel) {
	if (root) {
		if (desiredLevel == currentLevel) {
			printCasino(root->info);
		}
		else {
			currentLevel++;
			printNodesFromALevel(root->left, desiredLevel, currentLevel);
			printNodesFromALevel(root->right, desiredLevel, currentLevel);
		}
	}
}

node* getNodeWithMaxim(node* root) {
	if (root) {
		while (root->right)
			root = root->right;
		return root;
	}
}

Casino extractCasinoFromTree(node**root, int number) {
	if (*root) {
		if ((*root)->info.noSlotMachines == number) {
			
			Casino result = createCasino((*root)->info.name, (*root)->info.noSlotMachines);
			if ((*root)->left == NULL) {
				node*temp = (*root)->right;
				free((*root)->info.name);
				free(*root);
				*root = temp;
			}
			else if ((*root)->right == NULL) {
				node*temp = (*root)->left;
				free((*root)->info.name);
				free(*root);
				*root = temp;
			}
			else {
				node* temp = getNodeWithMaxim((*root)->left);
				Casino aux = (*root)->info;
				(*root)->info = temp->info;
				temp->info = aux;
				free(result.name);
				result = extractCasinoFromTree(&((*root)->left), number);
			}
			return result;
		}
		else if ((*root)->info.noSlotMachines > number) {
			return extractCasinoFromTree(&((*root)->left),number);
		}
		else {
			return extractCasinoFromTree(&((*root)->right), number);
		}
	}
}



















node* deleteNode(node* root, int slots) {
	if (root) {
		if (slots > root->info.noSlotMachines) {
			root->right = deleteNode(root->right, slots);
		}
		else if (slots < root->info.noSlotMachines) {
			root->left = deleteNode(root->left, slots);
		}
		else {
			if (root->left == NULL) {
				free(root->info.name);
				node* temp = root->right;
				free(root);
				return temp;
			}
			if (root->right == NULL) {
				free(root->info.name);
				node* temp = root->left;
				free(root);
				return temp;
			}
			node* temp = getNodeWithMaxim(root->left);
			Casino aux = temp->info;
			temp->info = root->info;
			root->info = aux;
			root->left = deleteNode(root->left, slots);
			return root;
		}
	}
	return root;
}

void main() {
	node* root = NULL;

	root = insertCasinoInTree(createCasino("MaxBet", 6), root);
	root = insertCasinoInTree(createCasino("Admiral", 3), root);
	root = insertCasinoInTree(createCasino("MaxBet 1", 4), root);
	root = insertCasinoInTree(createCasino("BlingBet", 8), root);
	root = insertCasinoInTree(createCasino("Maximus", 7), root);
	root = insertCasinoInTree(createCasino("Fortuna", 11), root);
	root = insertCasinoInTree(createCasino("Bonus", 9), root);

	/*printTree(root);

	Casino c = searchCasinoByNo(root, 7);
	printf("\n");
	printCasino(c);

	printf("Height: %d\n\n", height(root));

	printNodesFromALevel(root, 3, 1);*/

	//printCasino(getNodeWithMaxim(root)->info);
	//
	//printTree(root);

	//root = deleteNode(root, 6);

	//printf("\n");
	//printTree(root);

	printTree(root);
	printf("\n");
	printCasino(extractCasinoFromTree(&root, 6));

	printf("\n");
	printTree(root);


	freeTree(&root);
}