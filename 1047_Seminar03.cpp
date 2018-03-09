#include<iostream>

struct Plaja {
	char* locatie;
	float suprafata;
};

struct nod {
	Plaja info;
	nod* next;
};

nod* inserareInceput(nod* cap, Plaja plaja) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info.locatie = (char*)malloc(sizeof(char)*(strlen(plaja.locatie) + 1));
	strcpy(nou->info.locatie, plaja.locatie);
	nou->info.suprafata = plaja.suprafata;
	nou->next = cap;
	return nou;
}

Plaja crearePlaja(char*locatie, float suprafata) {
	Plaja plaja;
	plaja.locatie = (char*)malloc(sizeof(char)*(strlen(locatie) + 1));
	strcpy(plaja.locatie, locatie);
	plaja.suprafata = suprafata;

	return plaja;
}

nod* inserareSfarsit(nod* cap, Plaja plaja) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearePlaja(plaja.locatie, plaja.suprafata);
	nou->next = NULL;
	if (cap) {
		nod* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		cap = nou;
	}
	return cap;
}



void afisareLista(nod* cap) {
	nod* p = cap;
	while (p) {
		printf("Plaja din %s are %5.2f m2.\n", p->info.locatie, p->info.suprafata);
		p = p->next;
	}
}

void stergereLista(nod* *cap) {
	while (*cap) {
		free((*cap)->info.locatie);
		nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
	}
}

nod* inserareSortata(nod* cap, Plaja plaja) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearePlaja(plaja.locatie, plaja.suprafata);
	
	if (cap) {
		if (stricmp(cap->info.locatie, plaja.locatie)>0) {
			nou->next = cap;
			cap = nou;
		}
		else if(stricmp(cap->info.locatie, plaja.locatie)==0){
			if (cap->info.suprafata >= plaja.suprafata) {
				nou->next = cap;
				cap = nou;
			}
			else {
				nou->next = cap->next;
				cap->next = nou;
			}
		}
		else {
			nod* p = cap;
			while (p->next && stricmp(p->next->info.locatie, plaja.locatie) < 0 && p->next->info.suprafata<plaja.suprafata)
			{
				p = p->next;
			}

			if (p->next) {
				nou->next = p->next;
				p->next = nou;
			}
			else {
				p->next = nou;
				nou->next = NULL;
			}
		}
	}
	else
	{
		cap = nou;
		nou->next = NULL;
	}

	return cap;
}

void main() {

	nod* lista=NULL;
	Plaja plaja = crearePlaja("Mamaia", 300);
	lista = inserareInceput(lista, plaja);
	plaja.suprafata = 400;
	lista = inserareInceput(lista, plaja);
	plaja.suprafata = 500;
	lista = inserareInceput(lista, plaja);

	afisareLista(lista);

	stergereLista(&lista);
	lista = inserareSfarsit(lista, plaja);
	plaja.suprafata = 600;
	lista = inserareSfarsit(lista, plaja);
	plaja.suprafata = 700;
	lista = inserareSfarsit(lista, plaja);
	printf("\n");
	afisareLista(lista);

	stergereLista(&lista);
	lista = inserareSortata(lista, plaja);
	plaja.suprafata = 800;
	lista = inserareSortata(lista, plaja);
	plaja.suprafata = 900;
	lista = inserareSortata(lista, plaja);
	printf("\n");
	afisareLista(lista);

	free(plaja.locatie);
}