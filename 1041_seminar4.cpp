#include<iostream>

struct Intrerupator {
	char* culoare;
	int numarButoane;
};

struct nodSimplu {
	Intrerupator info;
	nodSimplu* next;
};


struct nodDublu {
	Intrerupator info;
	nodDublu* next;
	nodDublu* prev;
};

struct LDI {
	nodDublu* prim;
	nodDublu* ult;
};



Intrerupator creareObiect(char* culoare, int nrButoane) {
	Intrerupator intrerupator;
	intrerupator.culoare = (char*)malloc(sizeof(char)*(strlen(culoare) + 1));
	strcpy(intrerupator.culoare, culoare);
	intrerupator.numarButoane = nrButoane;
	return intrerupator;
}

nodDublu* creareNod(Intrerupator info, nodDublu* next, nodDublu* prev) {
	nodDublu* nodNou = (nodDublu*)malloc(sizeof(nodDublu));
	nodNou->info = creareObiect(info.culoare, info.numarButoane);
	nodNou->next = next;
	nodNou->prev = prev;
	return nodNou;
}

LDI inserareInceput(LDI lista, Intrerupator info) {
	nodDublu* nodNou = creareNod(info, lista.prim, NULL);
	if (lista.prim) {
		lista.prim->prev = nodNou;
		lista.prim = nodNou;
	}
	else {
		lista.prim = nodNou;
		lista.ult = nodNou;
	}
	return lista;
}

void afisareObiect(Intrerupator info) {
	printf("Intrerupatorul de culoare %s are %d butoane\n", info.culoare, info.numarButoane);
}

nodSimplu*inserareInceput(nodSimplu* cap, Intrerupator info) {
	nodSimplu* nodNou = (nodSimplu*)malloc(sizeof(nodSimplu));
	nodNou->info = creareObiect(info.culoare, info.numarButoane);
	nodNou->next = cap;
	return nodNou;

}
void afisareListaDubla(LDI lista, int flag) {
	if (flag == 0) {
		while (lista.prim) {
			afisareObiect(lista.prim->info);
			lista.prim = lista.prim->next;
		}
	}
	else {
		while (lista.ult) {
			afisareObiect(lista.ult->info);
			lista.ult = lista.ult->prev;
		}
	}
}

LDI stergereLista(LDI lista) {
	while (lista.prim) {
		free(lista.prim->info.culoare);
		nodDublu* pNod = lista.prim;
		lista.prim = lista.prim->next;
		free(pNod);
	}
	lista.ult = NULL;
	return lista;
}

LDI inserareSortata(LDI lista, Intrerupator info) {
	if (lista.prim) {
		nodDublu* p = lista.prim;
		while (p && p->info.numarButoane < info.numarButoane) {
			p = p->next;
		}
		if (p) {
			nodDublu* nodNou = creareNod(info, p, p->prev);
			
			if (p->prev) {
				p->prev->next = nodNou;
			}
			else {
				lista.prim = nodNou;
			}
			p->prev = nodNou;
		}
		else {
			nodDublu* nodNou = creareNod(info, NULL, lista.ult);
			lista.ult->next = nodNou;
			lista.ult = nodNou;
		}
	}
	else {
		nodDublu* nodNou = creareNod(info, NULL, NULL);
		lista.prim = lista.ult = nodNou;
	}
	return lista;
}

///problema la extragerea de pe ultima pozitie
nodSimplu* extragereIntrerupatoare(LDI *lista, int pragButoane) {
	nodDublu* p = lista->prim;
	nodSimplu* cap = NULL;
	while (p) {
		if (p->info.numarButoane < pragButoane) {
			cap = inserareInceput(cap, p->info);
			nodDublu*q = p;
			p = p->next;
			free(q->info.culoare);
			if (q->prev) {
				if (p) {
					p->prev = q->prev;
				}
				else {
					lista->ult = q->prev;
				}
				q->prev->next = p;
			}
			else {
				if (p) {
					p->prev = NULL;
				}
				else {
					lista->ult = NULL;
				}
				lista->prim = p;
			}
			free(q);
		}
		else {
			p = p->next;
		}
	}

	return cap;
}

void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ult = NULL;
	lista = inserareInceput(lista, creareObiect("Alb", 2));
	lista = inserareInceput(lista, creareObiect("Albastru", 4));
	lista = inserareInceput(lista, creareObiect("Galben", 3));
	lista = inserareInceput(lista, creareObiect("Gri", 1));

	afisareListaDubla(lista, 1);

	nodSimplu* cap = extragereIntrerupatoare(&lista, 9);

	printf("\n");
	while (cap) {
		afisareObiect(cap->info);
		free(cap->info.culoare);
		nodSimplu* q = cap;
		cap = cap->next;
		free(q);
	}
	printf("\n");
	afisareListaDubla(lista, 1);
	lista = stergereLista(lista);
}