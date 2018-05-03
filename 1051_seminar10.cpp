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
		printTree(root->left);
		printBottle(root->info);
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



void main() {
	node* root = NULL;

	root = insertInATree(root, createBottle("Zagori", 6));
	root = insertInATree(root, createBottle("Aqua", 2));
	root = insertInATree(root, createBottle("Dorna", 4));
	root = insertInATree(root, createBottle("Sprite", 11));
	root = insertInATree(root, createBottle("Fanta", 8));
	root = insertInATree(root, createBottle("Mirinda", 7));
	root = insertInATree(root, createBottle("Cola", 9));

	//printTree(root);

	//printBottle(searchBottleByVolume(root, 8));

	//printf("Height of tree is: %d\n\n", calculateHeight(root));

	//printByLevel(root, 3);
	//printf("\n");
	//printBottle(getNodeWithMaximum(root)->info);

	//printTree(root);
	//printf("\n");
	//root = deleteNode(root, 6);

	//printf("\n");
	//printTree(root);

	/*printTree(root);
	printf("\n");
	printBottle(extractBottleFromTree(&root, 6));

	printf("\n");
	printTree(root);*/

	listNode* head = copyBottlesInList(root, 9);
	while (head) {
		printBottle(head->info);
		head = head->next;
	}
	//free that list
	freeTree(&root);
}