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

void afisarePlaja(Plaja plaja) {
	printf("Plaja din %s are %5.2f m2.\n", plaja.locatie, plaja.suprafata);
}

void afisareLista(nod* cap) {
	nod* p = cap;
	while (p) {
		afisarePlaja(p->info);
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
		else if (stricmp(cap->info.locatie, plaja.locatie) == 0) {
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

Plaja extragereDinStiva(nod* *cap) {
	if (*cap) {
		Plaja plaja = crearePlaja((*cap)->info.locatie, (*cap)->info.suprafata);
		nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux->info.locatie);
		free(aux);
		return plaja;
	}
	else {
		Plaja plaja;
		plaja.locatie = NULL;
		plaja.suprafata = -1;
		return plaja;
	}
}

int stivaEsteGoala(nod* stiva) {
	return stiva ? 1 : 0;
}

nod* creareCoadaPlajeMari(nod* *stiva, float limita) {
	nod* coadaRezultat = NULL;
	nod* stivaAuxiliara = NULL;
	while (stivaEsteGoala(*stiva) == 1) {
		Plaja plaja = extragereDinStiva(stiva);
		if (plaja.suprafata >= limita) {
			coadaRezultat = inserareSfarsit(coadaRezultat, plaja);
		}
		stivaAuxiliara = inserareInceput(stivaAuxiliara, plaja);
		free(plaja.locatie);
	}
	while (stivaEsteGoala(stivaAuxiliara) == 1) {
		Plaja plaja = extragereDinStiva(&stivaAuxiliara);
		*stiva = inserareInceput(*stiva, plaja);
		free(plaja.locatie);
	}
	return coadaRezultat;
}

nod* afisarePlajeFiltrate(nod* coada, float limita) {
	nod* rezultat = NULL;
	while (coada) {
		Plaja plaja = extragereDinStiva(&coada);
		if (plaja.suprafata <= limita) {
			afisarePlaja(plaja);
		}
		else {
			rezultat = inserareSfarsit(rezultat, plaja);
		}
		free(plaja.locatie);
	}
	return rezultat;
}

void main() {

	/*nod* stiva = NULL;
	stiva = inserareInceput(stiva, crearePlaja("Mamaia", 20));
	stiva = inserareInceput(stiva, crearePlaja("Costinesti", 17));
	stiva = inserareInceput(stiva, crearePlaja("Eforie", 8));

	Plaja plaja= extragereDinStiva(&stiva);
	
	afisarePlaja(plaja);
	afisarePlaja(extragereDinStiva(&stiva));
	afisarePlaja(extragereDinStiva(&stiva));
	
	if(stivaEsteGoala(stiva)==1)
		afisarePlaja(extragereDinStiva(&stiva));

	stergereLista(&stiva);
	free(plaja.locatie);*/


	//nod* coada = NULL;

	//coada = inserareSfarsit(coada, crearePlaja("Vama veche", 20));
	//coada = inserareSfarsit(coada, crearePlaja("Neptun", 5));
	//coada = inserareSfarsit(coada, crearePlaja("Venus", 8));

	//printf("Plaje mici:\n");

	//coada = afisarePlajeFiltrate(coada, 10);

	//printf("Plaje mari:\n");
	//while (coada) {
	//	Plaja plaja = extragereDinStiva(&coada);
	//	afisarePlaja(plaja);
	//	free(plaja.locatie);
	//}

	nod* stiva = NULL;
	stiva = inserareInceput(stiva, crearePlaja("Mamaia", 20));
	stiva = inserareInceput(stiva, crearePlaja("Costinesti", 17));
	stiva = inserareInceput(stiva, crearePlaja("Eforie", 8));

	nod* coada = NULL;
	coada = creareCoadaPlajeMari(&stiva, 15);
	printf("Coada:\n");
	while (coada) {
		Plaja plaja = extragereDinStiva(&coada);
		afisarePlaja(plaja);
		free(plaja.locatie);
	}
	printf("Stiva\n");
	while (stivaEsteGoala(stiva) == 1) {
		Plaja plaja = extragereDinStiva(&stiva);
		afisarePlaja(plaja);
		free(plaja.locatie);
	}

}