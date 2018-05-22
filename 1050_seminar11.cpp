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
		printCasino(root->info);
		printTree(root->left);
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
			return extractCasinoFromTree(&((*root)->left), number);
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

int balanceFactor(node* root) {
	return height(root->right) - height(root->left);
}

node* rotateToRight(node* root) {
	node* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	return temp;
}

node* rotateToLeft(node* root) {
	node* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	return temp;
}

node* insertInAVL(Casino info,node* root) {
	if (root) {
		if (info.noSlotMachines < root->info.noSlotMachines) {
			root->left = insertInAVL(info,root->left);
		}
		else {
			root->right = insertInAVL(info, root->right);
		}
		//we have to balance this tree
		int BF = balanceFactor(root);
		if (BF == -2) {
			if (balanceFactor(root->left) == -1) {
				root = rotateToRight(root);
			}
			else {
				root->left = rotateToLeft(root->left);
				root = rotateToRight(root);
			}
		}
		if (BF == 2) {
			if (balanceFactor(root->right) == 1) {
				root = rotateToLeft(root);
			}
			else {
				root->right = rotateToRight(root->right);
				root = rotateToLeft(root);
			}
		}
		return root;

	}
	else {
		node* newNode = (node*)malloc(sizeof(node));
		newNode->info = info;
		newNode->right = NULL;
		newNode->left = NULL;
		return newNode;
	}
}

void main() {
	node* root = NULL;

	root = insertInAVL(createCasino("MaxBet", 1), root);
	root = insertInAVL(createCasino("Admiral", 2), root);
	root = insertInAVL(createCasino("MaxBet 1", 3), root);
	root = insertInAVL(createCasino("BlingBet", 4), root);
	root = insertInAVL(createCasino("Maximus", 5), root);
	root = insertInAVL(createCasino("Fortuna", 6), root);
	root = insertInAVL(createCasino("Bonus", 7), root);

	printTree(root);

	freeTree(&root);
}