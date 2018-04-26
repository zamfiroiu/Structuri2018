#include<iostream>

struct Drona {
	float greutate;
	char* model;
};

struct nod {
	Drona info;
	nod* st;
	nod*dr;
};

Drona creareDrona(float greutate, char* model) {
	Drona d;
	d.greutate = greutate;
	d.model = (char*)malloc(sizeof(char)*(strlen(model) + 1));
	strcpy(d.model, model);
	return d;
}

void afisareDrona(Drona d) {
	printf("Drona %s cantareste %5.2f Kg.\n", d.model, d.greutate);
}

nod* inserareInArbore(Drona d, nod* root) {
	if (root) {
		if (d.greutate < root->info.greutate) {
			root->st = inserareInArbore(d, root->st);
		}else if(d.greutate>root->info.greutate){
			root->dr = inserareInArbore(d, root->dr);
		}
		return root;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = d;
		nou->st = NULL;
		nou->dr = NULL;
		return nou;
	}
}

void afisareRSD(nod* root) {
	if (root) {
		afisareDrona(root->info);
		afisareRSD(root->st);
		afisareRSD(root->dr);
	}
}

Drona cautareDronaDupaGreutate(nod* root, float greutateaCautata) {
	if (root) {
		if (greutateaCautata == root->info.greutate) {
			return root->info;
		}
		else if (greutateaCautata < root->info.greutate) {
			return cautareDronaDupaGreutate(root->st, greutateaCautata);
		}
		else {
			return cautareDronaDupaGreutate(root->dr, greutateaCautata);
		}
	}
	else {
		Drona d = creareDrona(-1, "");
		return d;
	}
}

int inaltimeArbore(nod * root) {
	if (root) {
		int hS = inaltimeArbore(root->st);
		int hD = inaltimeArbore(root->dr);
		int h = (hS < hD) ? hD : hS;
		h++;
		return h;
	}
	else {
		return 0;
	}
}

void stergereArbore(nod** root) {
	if (*root) {
		stergereArbore(&(*root)->st); 
		stergereArbore(&(*root)->dr);
		free((*root)->info.model);
		free(*root);
		*root = NULL;
	}
}

void afisareDePeNivel(nod*root, int nivelCautat) {
	if (root) {
		if (nivelCautat == 1) {
			afisareDrona(root->info);
		}
		else
		{
			nivelCautat--;
			afisareDePeNivel(root->st, nivelCautat);
			afisareDePeNivel(root->dr, nivelCautat);
		}
	}
}

void main() {

	nod* root = NULL;

	root = inserareInArbore(creareDrona(7, "Phantom"), root);
	root = inserareInArbore(creareDrona(5, "Vampir"), root);
	root = inserareInArbore(creareDrona(3, "SkyDrive"), root);
	root = inserareInArbore(creareDrona(10, "SkyWalk"), root);
	root = inserareInArbore(creareDrona(8, "Phantom II"), root);
	root = inserareInArbore(creareDrona(9, "Drone Sky"), root);
	root = inserareInArbore(creareDrona(12, "OnTheSky"), root);

	afisareRSD(root);

	printf("\n");
	afisareDrona(cautareDronaDupaGreutate(root, 8));

	printf("Inaltime arbore:%d\n", inaltimeArbore(root));

	afisareDePeNivel(root, 3);

	stergereArbore(&root);

}