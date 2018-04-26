#include<iostream>

struct folder {
	char* nume;
	int dimensiune;
};

folder creareFolder(char* nume, int dimen) {
	folder f;
	f.dimensiune = dimen;
	f.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(f.nume, nume);
	return f;
}

void afisareFolder(folder f) {
	printf("Folderul %s ocupa %d B\n", f.nume, f.dimensiune);
}

struct nod {
	folder info;
	nod* st;
	nod* dr;
};

nod* inserareNod(nod* root, folder f) {
	if (root) {
		if (f.dimensiune < root->info.dimensiune) {
			root->st = inserareNod(root->st, f);
		}
		else {
			root->dr = inserareNod(root->dr, f);
		}
		return root;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = f;
		nou->st = NULL;
		nou->dr = NULL;
		return nou;
	}
}

void afisareSRD(nod* root) {
	if (root) {
		afisareSRD(root->st);
		afisareFolder(root->info);
		afisareSRD(root->dr);
	}
}

void main() {
	nod* arbore = NULL;

	arbore = inserareNod(arbore, creareFolder("Settings", 6));
	arbore = inserareNod(arbore, creareFolder("System32", 5));
	arbore = inserareNod(arbore, creareFolder("Windows", 2));
	arbore = inserareNod(arbore, creareFolder("Poze", 4));
	arbore = inserareNod(arbore, creareFolder("RecycleBin", 8));

	afisareSRD(arbore);


}