#include<iostream>

struct Vacanta {
	char* destinatie;
	int durata;
};

struct nodLista {
	Vacanta info;
	nodLista*next;
};

Vacanta creareVacanta(char* dest, int durata) {
	Vacanta v;
	v.destinatie = (char*)malloc(sizeof(char)*(strlen(dest) + 1));
	strcpy_s(v.destinatie, strlen(dest) + 1, dest);
	v.durata = durata;
	return v;
}

void afisareVacanta(Vacanta v) {
	printf("Vacanta din %s dureaza %d zile\n", v.destinatie, v.durata);
}

struct nod {
	Vacanta info;
	nod* st;
	nod*dr;
};

nod* inserare(nod*rad, Vacanta v) {
	if (rad) {
		if (rad->info.durata < v.durata) {
			rad->dr = inserare(rad->dr, v);
		}
		else if (rad->info.durata>v.durata) {
			rad->st = inserare(rad->st, v);
		}
		return rad;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = v;
		nou->st = NULL;
		nou->dr = NULL;
		return nou;
	}
}

void afisare(nod* rad) {
	if (rad) {
		afisare(rad->st);
		afisareVacanta(rad->info);
		afisare(rad->dr);
	}
}

Vacanta cautareVacantaDupaDurata(nod* rad, int durata) {
	if (rad) {
		if (rad->info.durata < durata) {
			return cautareVacantaDupaDurata(rad->dr, durata);
		}
		else {
			if (rad->info.durata > durata) {
				return cautareVacantaDupaDurata(rad->st, durata);
			}
			else {
				return rad->info;
			}
		}
	}
	else {
		return creareVacanta("", -1);
	}
}

void stergere(nod** rad) {
	if (*rad) {
		stergere(&(*rad)->st);
		stergere(&(*rad)->dr);
		free((*rad)->info.destinatie);
		free(*rad);
		*rad = NULL;
	}
}

int calculeazaInaltime(nod* rad) {
	if (rad) {
		int Hst = calculeazaInaltime(rad->st);
		int Hdr = calculeazaInaltime(rad->dr);
		return Hst > Hdr ? Hst + 1 : Hdr + 1;
	}
	else {
		return 0;
	}
}

nod* cautareNodCuValoareMinima(nod* rad) {
	if (rad) {
		if (rad->st) {
			return cautareNodCuValoareMinima(rad->st);
		}
		else {
			return rad;
		}
	}
	else {
		return rad;
	}
}

Vacanta extrageVacanta(nod**rad, int durata) {
	if (*rad) {
		if (durata < (*rad)->info.durata) {
			return extrageVacanta(&(*rad)->st, durata);
		}else if(durata>(*rad)->info.durata){
			return extrageVacanta(&(*rad)->dr, durata);
		}
		else {
			if ((*rad)->st == NULL) {
				Vacanta rezultat = (*rad)->info;
				nod* temp = (*rad)->dr;
				free((*rad)->info.destinatie);
				free(*rad);
				*rad = temp;
				return rezultat;
			}
			if ((*rad)->dr == NULL) {
				Vacanta rezultat = (*rad)->info;
				nod* temp = (*rad)->st;
				free(*rad);
				*rad = temp;
				return rezultat;
			}
			nod* temp = cautareNodCuValoareMinima((*rad)->dr);
			Vacanta aux = (*rad)->info;
			(*rad)->info = temp->info;
			temp->info = aux;
			return extrageVacanta(&(*rad)->dr, durata);
		}
	}
	else {
		return creareVacanta("", -1);
	}
}

nodLista* inserareInceput(nodLista* cap, Vacanta v) {
	nodLista*nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info = creareVacanta(v.destinatie, v.durata);
	nou->next = cap;
	return nou;
}

void copiereVacantePare(nod* rad, nodLista**cap) {
	if (rad) {
		copiereVacantePare(rad->st, cap);
		if(rad->info.durata%2==1){
			*cap = inserareInceput(*cap, rad->info);
		}
		copiereVacantePare(rad->dr, cap);
	}
}

nodLista* vacantePare(nod* rad) {
	nodLista* cap = NULL;
	copiereVacantePare(rad, &cap);
	return cap;
}


void main() {
	nod* rad = NULL;
	rad = inserare(rad, creareVacanta("Mamaia", 6));
	rad = inserare(rad, creareVacanta("Busteni", 3));
	rad = inserare(rad, creareVacanta("Vama", 5));
	rad = inserare(rad, creareVacanta("Bahamas", 8));
	rad = inserare(rad, creareVacanta("Dubai", 11));
	rad = inserare(rad, creareVacanta("Paris", 13));
	rad = inserare(rad, creareVacanta("Madrid", 9));
	rad = inserare(rad, creareVacanta("Focsani", 7));

	//afisare(rad);

	//printf("\n");
	////printf("inaltime:%d\n", calculeazaInaltime(rad));
	////afisareVacanta(cautareNodCuValoareMinima(rad)->info);
	//afisareVacanta(extrageVacanta(&rad, 8));

	//printf("\n");
	//afisare(rad);

	nodLista*cap = NULL;// vacantePare(rad);
	copiereVacantePare(rad, &cap);
	while (cap) {
		afisareVacanta(cap->info);
		nodLista*aux = cap;
		cap = cap->next;
		free(aux->info.destinatie);
		free(aux);
	}

	stergere(&rad);
	printf("arbore:\n");
	afisare(rad);

}