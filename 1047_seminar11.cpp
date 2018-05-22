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

struct nodLista {
	Drona info;
	nodLista*next;
};



Drona creareDrona(float greutate, char* model) {
	Drona d;
	d.greutate = greutate;
	d.model = (char*)malloc(sizeof(char)*(strlen(model) + 1));
	strcpy(d.model, model);
	return d;
}
nodLista* inserareInceputLista(nodLista* cap, Drona d) {
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info = creareDrona(d.greutate, d.model);
	nou->next = cap;
	return nou;
}

void afisareDrona(Drona d) {
	printf("Drona %s cantareste %5.2f Kg.\n", d.model, d.greutate);
}

nod* inserareInArbore(Drona d, nod* root) {
	if (root) {
		if (d.greutate < root->info.greutate) {
			root->st = inserareInArbore(d, root->st);
		}
		else if (d.greutate>root->info.greutate) {
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

nod* cautareMaxim(nod*root) {
	if (root) {
		while (root->dr) {
			root = root->dr;
		}
		return root;
	}
	else {
		return NULL;
	}
}

Drona extrageDrona(nod** root, float greutate) {
	if (*root) {
		if ((*root)->info.greutate == greutate) {
			Drona rezultat = (*root)->info;
			if ((*root)->dr == NULL) {
				nod* temp = (*root)->st;
				free(*root);
				*root = temp;
			}
			else if ((*root)->st == NULL) {
				nod* temp = (*root)->dr;
				free(*root);
				*root = temp;
			}
			else {
				nod* temp = cautareMaxim((*root)->st);
				Drona aux = temp->info;
				temp->info = (*root)->info;
				(*root)->info = aux;
				extrageDrona(&(*root)->st, greutate);
			}

			return rezultat;
		}
		else if ((*root)->info.greutate > greutate) {
			return extrageDrona(&(*root)->st, greutate);
		}
		else {
			return extrageDrona(&(*root)->dr, greutate);
		}
	}
	else {
		return creareDrona(-1, "");
	}

}

nod* stergeNod(nod* root, float greutate) {
	if (root) {
		if (root->info.greutate == greutate) {
			if (root->st == NULL) {
				nod* temp = root->dr;
				free(root->info.model);
				free(root);
				return temp;
			}
			if (root->dr == NULL) {
				nod* temp = root->st;
				free(root->info.model);
				free(root);
				return temp;
			}

			nod* temp = cautareMaxim(root->st);
			Drona aux = root->info;
			root->info = temp->info;
			temp->info = aux;
			root->st = stergeNod(root->st, greutate);
			return root;

		}
		else if (root->info.greutate > greutate) {
			root->st = stergeNod(root->st, greutate);
		}
		else {
			root->dr = stergeNod(root->dr, greutate);
		}
	}
	return root;
}

nodLista* copiereDroneImpareRecursiv(nod* root, nodLista* cap) {
	if (root) {
		if (((int)root->info.greutate) % 2 == 0) {
			cap = inserareInceputLista(cap, root->info);
		}
		cap = copiereDroneImpareRecursiv(root->st, cap);
		cap = copiereDroneImpareRecursiv(root->dr, cap);
		return cap;
	}
	else {
		return cap;
	}
}

nodLista* copiereDroneImpare(nod* root) {
	if (root) {
		nodLista* cap = NULL;
		cap = copiereDroneImpareRecursiv(root, cap);
		return cap;
	}
	else return NULL;
}

int gradEchilibru(nod*root) {
	return inaltimeArbore(root->st) - inaltimeArbore(root->dr);
}

nod* rotireStanga(nod* root) {
	nod* temp = root->dr;
	root->dr = temp->st;
	temp->st = root;
	return temp;
}

nod* rotireDreapta(nod* root) {
	nod* temp = root->st;
	root->st = temp->dr;
	temp->dr = root;
	return temp;
}

nod* inserareAVL( Drona d, nod* root) {
	if (root) {
		if (d.greutate > root->info.greutate) {
			root->dr = inserareAVL(d, root->dr);
		}
		else {
			root->st = inserareAVL(d, root->st);
		}
		//echilibram
		int ge = gradEchilibru(root);
		if (ge == -2) {
			//dezechilibru in partea dreapta
			if (gradEchilibru(root->dr) == -1) {
				//rotire la stanga
				root = rotireStanga(root);
			}
			else {
				root->dr=rotireDreapta(root->dr);
				root = rotireStanga(root);
			}
		}
		if (ge == 2) {
			if (gradEchilibru(root->st) == 1) {
				root = rotireDreapta(root);
			}
			else {
				//dezechilibru complicat
				root->st = rotireStanga(root->st);
				root = rotireDreapta(root);
			}
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

void main() {

	nod* root = NULL;

	root = inserareAVL(creareDrona(1, "Phantom"), root);
	root = inserareAVL(creareDrona(2, "Vampir"), root);
	root = inserareAVL(creareDrona(3, "SkyDrive"), root);
	root = inserareAVL(creareDrona(4, "SkyWalk"), root);
	root = inserareAVL(creareDrona(5, "Phantom II"), root);
	root = inserareAVL(creareDrona(6, "Drone Sky"), root);
	root = inserareAVL(creareDrona(7, "OnTheSky"), root);

	afisareRSD(root);

	stergereArbore(&root);

}