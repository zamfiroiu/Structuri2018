#include<iostream>

struct Bottle {
	float volume;
	char* brand;
};

Bottle createBottle(char* brand, float volume) {
	Bottle b;
	b.brand = (char*)malloc(sizeof(char)*(strlen(brand) + 1));
	strcpy(b.brand, brand);
	b.volume = volume;

	return b;
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

void main() {
	node* root = NULL;

	root = insertInATree(root, createBottle("Zagori", 6));
	root = insertInATree(root, createBottle("Aqua", 2));
	root = insertInATree(root, createBottle("Dorna", 4));
	root = insertInATree(root, createBottle("Sprite", 11));
	root = insertInATree(root, createBottle("Fanta", 8));
	root = insertInATree(root, createBottle("Mirinda", 7));
	root = insertInATree(root, createBottle("Cola", 9));

	printTree(root);

	printBottle(searchBottleByVolume(root, 8));

	printf("Height of tree is: %d\n\n", calculateHeight(root));

	freeTree(&root);
}