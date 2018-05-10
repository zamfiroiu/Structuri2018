#include<iostream>

struct Bottle {
	float volume;
	char* brand;
};

struct listNode {
	Bottle info;
	listNode*next;
};



Bottle createBottle(char* brand, float volume) {
	Bottle b;
	b.brand = (char*)malloc(sizeof(char)*(strlen(brand) + 1));
	strcpy(b.brand, brand);
	b.volume = volume;

	return b;
}

listNode*insertAtBegin(listNode*head, Bottle inf) {
	listNode*newNode = (listNode*)malloc(sizeof(listNode));
	newNode->info = createBottle(inf.brand, inf.volume);
	newNode->next = head;
	return newNode;
}

void printBottle(Bottle b) {
	printf("%s bottle has %5.2f volume.\n", b.brand, b.volume);
}

struct node {
	Bottle info;
	node*left;
	node* right;
};

node* insertInATree(node* root, Bottle b) {
	if (root) {
		if (b.volume < root->info.volume) {
			root->left = insertInATree(root->left, b);
		}
		else if(b.volume>root->info.volume){
			root->right = insertInATree(root->right, b);
		}
		return root;
	}
	else {
		node* newNode = (node*)malloc(sizeof(node));
		newNode->info = b;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
}

void printTree(node* root) {
	if (root) {
		printBottle(root->info);
		printTree(root->left);
		printTree(root->right);
	}
}

Bottle searchBottleByVolume(node* root, float volume) {
	if (root) {
		if (volume < root->info.volume) {
			return searchBottleByVolume(root->left, volume);
		}
		else if (volume> root->info.volume) {
			return searchBottleByVolume(root->right, volume);
		}
		else {
			return root->info;
		}
	}
	else {
		return createBottle("", -1);
	}
}

int calculateHeight(node* root) {
	if (root) {
		int left = calculateHeight(root->left);
		int right = calculateHeight(root->right);
		return left > right ? left + 1 : right + 1;
	}
	else {
		return 0;
	}
}

void freeTree(node**root) {
	if (*root) {
		freeTree(&(*root)->left);
		freeTree(&(*root)->right);
		free((*root)->info.brand);
		free(*root);
		*root = NULL;
	}
}

void printByLevel(node*root, int level) {
	if (root) {
		if (level == 1) {
			printBottle(root->info);
		}
		else {
			printByLevel(root->left, level - 1);
			printByLevel(root->right, level - 1);
		}
	}
}

node* getNodeWithMaximum(node* root) {
	if (root) {
		if (root->right) {
			return getNodeWithMaximum(root->right);
		}
		else {
			return root;
		}
	}
}

node* deleteNode(node* root, float volume) {
	if (root) {
		if (root->info.volume == volume) {
			if (root->left == NULL) {
				node* temp = root->right;
				free(root->info.brand);
				free(root);
				return temp;
			}
			if (root->right == NULL) {
				node* temp = root->left;
				free(root->info.brand);
				free(root);
				return temp;
			}
			node* temp = getNodeWithMaximum(root->left);
			Bottle aux = root->info;
			root->info = temp->info;
			temp->info = aux;
			root->left = deleteNode(root->left, volume);
			return root;

		}
		else if(root->info.volume>volume) {
			root->left=deleteNode(root->left, volume);
			return root;
		}
		else {
			root->right = deleteNode(root->right, volume);
			return root;
		}
	}
}


Bottle extractBottleFromTree(node** root, float volume) {
	if (*root) {
		if ((*root)->info.volume == volume) {
			if ((*root)->left == NULL) {
				node* temp = (*root)->right;
				Bottle result = createBottle((*root)->info.brand, (*root)->info.volume);
				free((*root)->info.brand);
				free(*root);
				*root = temp;
				return result;
			}
			if ((*root)->right == NULL) {
				node* temp = (*root)->left;
				Bottle result = createBottle((*root)->info.brand, (*root)->info.volume);
				free((*root)->info.brand);
				free(*root);
				*root = temp;
				return result;
			}
			node* temp = getNodeWithMaximum((*root)->left);
			Bottle aux = temp->info;
			temp->info = (*root)->info;
			(*root)->info = aux;
			return extractBottleFromTree(&(*root)->left, volume);
		}
		else if ((*root)->info.volume > volume){
			return extractBottleFromTree(&(*root)->left, volume);
		}
		else {
			return extractBottleFromTree(&(*root)->right, volume);
		}
	}
}

void copyBottlesRecursiv(node* root, listNode**head, float maxVolume) {
	if (root) {
		if (root->info.volume < maxVolume) {
			*head = insertAtBegin(*head, root->info);
		}
		copyBottlesRecursiv(root->left, head, maxVolume);
		copyBottlesRecursiv(root->right, head, maxVolume);
	}
}

listNode* copyBottlesInList(node*root, float maxVolume) {
	if (root) {
		listNode* head = NULL;
		copyBottlesRecursiv(root, &head, maxVolume);
		return head;
	}
	else {
		return NULL;
	}
}

int balanceFactor(node* root) {
	return calculateHeight(root->right) - calculateHeight(root->left);
}

node* rotateToLeft(node* root) {
	node* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	return temp;
}

node* rotateToRight(node*root) {
	node* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	return temp;
}

node*insertAVL(node*root, Bottle info) {
	if (root) {
		if (info.volume < root->info.volume) {
			root->left = insertAVL(root->left, info);
		}
		else {
			root->right = insertAVL(root->right, info);
		}
		//check the balance factor
		int BF = balanceFactor(root);
		if (BF == 2) {
			if (balanceFactor(root->right) == 1) {
				root = rotateToLeft(root);
			}
			else {
				//here he a complicated method
				root->right = rotateToRight(root->right);
				root = rotateToLeft(root);
			}
		}
		if (BF == -2) {
			if (balanceFactor(root->left) == -1) {
				root = rotateToRight(root);
			}
			else {
				root->left = rotateToLeft(root->left);
				root = rotateToRight(root);
			}
		}
		return root;
	}
	else {
		node* newNode = (node*)malloc(sizeof(node));
		newNode->info = info;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
}

void main() {
	node* root = NULL;

	root = insertAVL(root, createBottle("Zagori", 1));
	root = insertAVL(root, createBottle("Aqua", 2));
	root = insertAVL(root, createBottle("Dorna", 3));
	root = insertAVL(root, createBottle("Sprite", 4));
	root = insertAVL(root, createBottle("Fanta", 5));
	root = insertAVL(root, createBottle("Mirinda", 6));
	root = insertAVL(root, createBottle("Cola", 7));

	printTree(root);
	
	freeTree(&root);
}