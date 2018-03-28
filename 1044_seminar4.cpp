#include<iostream>

struct Aeroport {
	char* nume;
	int numarZboruri;
};

struct nod {
	nod* next;
	nod* prev;
	Aeroport info;
};

struct LDI {
	nod* prim;
	nod* ult;
};

Aeroport creareAeroport(char* nume, int nrZboruri) {
	Aeroport a;
	a.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy_s(a.nume, strlen(nume) + 1, nume);
	a.numarZboruri = nrZboruri;

	return a;
}

nod* creareNod(Aeroport a, nod* next, nod* prev) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->next = next;
	nou->prev = prev;
	nou->info = creareAeroport(a.nume, a.numarZboruri);
	return nou;
}


LDI inserareInceput(Aeroport info, LDI lista) {
	nod* nodNou = creareNod(info, lista.prim, NULL);
	if (lista.prim) {
		lista.prim->prev=nodNou;
		lista.prim = nodNou;
	}
	else {
		lista.prim = nodNou;
		lista.ult = nodNou;
	}
	return lista;
}

LDI inserareSfarsit(Aeroport info, LDI lista) {
	nod* nodNou = creareNod(info, NULL, lista.ult);
	if (lista.ult) {
		lista.ult->next = nodNou;
		lista.ult = nodNou;
	}
	else {
		lista.prim = nodNou;
		lista.ult = nodNou;
	}
	return lista;
}

void afisareAeroport(Aeroport a) {
	printf("Aeroportul %s are %d zboruri\n", a.nume, a.numarZboruri);
}

void afisareListaSfarsitInceput(LDI lista) {
	for (nod* p = lista.ult; p != NULL; p = p->prev) {
		afisareAeroport(p->info);
	}
}

LDI stergereLista(LDI lista) {
	while (lista.prim) {
		free(lista.prim->info.nume);
		nod* aux = lista.prim;
		lista.prim = lista.prim->next;
		free(aux);
	}
	lista.ult = NULL;
	return lista;
}

LDI inserarePePozitie(Aeroport info, LDI lista, int pozitie) {
	if (pozitie <= 1 || lista.prim==NULL) {
		lista = inserareInceput(info, lista);
		return lista;
	}
	else {
		int contor = 1;
		nod* p = lista.prim;
		while (p && contor < pozitie) {
			p = p->next;
			contor++;
		}
		if (p) {
			nod* nodNou = creareNod(info, p, p->prev);
			p->prev->next = nodNou;
			p->prev = nodNou;
			return lista;
		}
		else {
			lista = inserareSfarsit(info, lista);
			return lista;
		}
	}
}

Aeroport extragereAeroport(LDI * lista, int nrZboruriCautat) {
	nod*p = lista->prim;
	while (p && p->info.numarZboruri != nrZboruriCautat) {
		p = p->next;
	}
	if (p) {
		Aeroport rezultat = creareAeroport(p->info.nume, p->info.numarZboruri);
		if (p->prev) {
			p->prev->next = p->next;
			if (p->next) {				
				p->next->prev = p->prev;
			}
			else {
				//suntem pe ultimul nod
				lista->ult = p->prev;
				if (lista->ult == NULL) {
					lista->prim = NULL;
				}
			}
		}
		else
		{
			//suntem pe primul nod
			if (p->next) {
				p->next->prev = NULL;
				lista->prim = p->next;
			}
			else{
				lista->prim = NULL;
				lista->ult = NULL;
			}
		}
		free(p->info.nume);
		free(p);
		return rezultat;
	}
	else {
		Aeroport a;
		a.nume = NULL;
		a.numarZboruri = -1;
		return a;
	}
}

void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ult = NULL;

	lista = inserarePePozitie(creareAeroport("Otopeni", 300), lista,1);
	//lista = inserarePePozitie(creareAeroport("Baneasa", 30), lista,1);
	//lista = inserarePePozitie(creareAeroport("Kogalniceanu", 150), lista,2);

	afisareListaSfarsitInceput(lista);

	Aeroport a = extragereAeroport(&lista, 300);
	printf("Aeroportul:\n");
	afisareAeroport(a);

	printf("Lista dupa extragere\n");
	afisareListaSfarsitInceput(lista);

	lista = stergereLista(lista);

}