#include<iostream>

#pragma warning(disable:4996)
struct Florarie {
	char* denumire;
	int nrFlori;
};

struct nod {
	Florarie info;
	nod* next;
};

Florarie creareFlorarie(char* denumire, int nrFlori) {
	Florarie florarie;
	florarie.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(florarie.denumire, denumire);
	florarie.nrFlori = nrFlori;
	return florarie;
}

nod* inserareInceput(Florarie f, nod* cap) {
	nod* nodNou = (nod*)malloc(sizeof(nod));
	nodNou->info = creareFlorarie(f.denumire, f.nrFlori);
	nodNou->next = cap;
	return nodNou;
}

void afisareFlorarie(Florarie f) {
	printf("Floraria %s are %d flori\n", f.denumire, f.nrFlori);
}

void afisareLista(nod* cap) {
	nod* p = cap;
	while (p) {
		afisareFlorarie(p->info);
		p = p->next;
	}
}

nod* stergereLista(nod* cap) {
	while (cap) {
		free(cap->info.denumire);
		nod* temp = cap;
		cap = cap->next;
		free(temp);
	}
	return cap;
}

nod* inserareSfarsit(Florarie f, nod* cap) {
	if (cap) {
		nod*p = cap;
		while (p->next) {
			p = p->next;
		}
		nod*nou = (nod*)malloc(sizeof(nod));
		nou->info = creareFlorarie(f.denumire, f.nrFlori);
		nou->next = p->next;
		p->next = nou;
		//p->next = inserareInceput(f, NULL);
	}
	else {
		cap = inserareInceput(f, cap);
	}
	return cap;
}

nod* inserareSortata(Florarie f, nod* cap) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareFlorarie(f.denumire, f.nrFlori);
	nou->next = NULL;
	if (cap) {
		if (cap->info.nrFlori > f.nrFlori) {
			nou->next = cap;
			cap = nou;
		}
		else {
			nod*p = cap;
			while (p->next && p->next->info.nrFlori < f.nrFlori) {
				p = p->next;
			}
			nou->next = p->next;
			p->next = nou;
		}
	}
	else {
		cap = nou;
	}
	return cap;
}

nod* pushStack(nod*stiva, Florarie info) {
	stiva = inserareInceput(info, stiva);
	return stiva;
}

Florarie popStack(nod* *stiva) {
	if (*stiva) {
		Florarie f = creareFlorarie((*stiva)->info.denumire, (*stiva)->info.nrFlori);
		nod* temp = *stiva;
		*stiva=(*stiva)->next;
		free(temp->info.denumire);
		free(temp);
		return f;
	}
	else {
		Florarie f;
		f.denumire = NULL;
		f.nrFlori = -1;
		return f;
	}
}

nod* pushQueue(nod*coada, Florarie f) {
	return inserareSfarsit(f, coada);
}

Florarie popQueue(nod** coada) {
	return popStack(coada);
}

nod* filtrareFlorariiCuAfisare(nod* stiva, int prag) {
	nod* stivaTemp = NULL;
	while (stiva) {
		Florarie f = popStack(&stiva);
		if (f.nrFlori < prag) {
			stivaTemp = pushStack(stivaTemp, f);			
		}
		else {
			afisareFlorarie(f);
		}
		free(f.denumire);
	}
	while (stivaTemp) {
		Florarie f = popStack(&stivaTemp);
		stiva = pushStack(stiva, f);
		free(f.denumire);
	}
	return stiva;
}

nod* filtrareFlorariiCuSalvareInCoada(nod* *stiva, int prag) {
	nod* stivaTemp = NULL;
	nod* coadaRezultat = NULL;
	while (*stiva) {
		Florarie f = popStack(stiva);
		if (f.nrFlori < prag) {
			stivaTemp = pushStack(stivaTemp, f);
		}
		else {
			coadaRezultat = pushQueue(coadaRezultat, f);
		}
		free(f.denumire);
	}
	while (stivaTemp) {
		Florarie f = popStack(&stivaTemp);
		*stiva = pushStack(*stiva, f);
		free(f.denumire);
	}
	return coadaRezultat;
}

Florarie extragareDinCoada(nod**coada, int nrFlori) {
	nod*coadaTemp = NULL;
	Florarie rezultat;
	while (*coada) {
		Florarie f = popQueue(coada);
		if (f.nrFlori == nrFlori) {
			rezultat = f;
		}
		else {
			coadaTemp = pushQueue(coadaTemp, f);
			free(f.denumire);
		}
	}
	*coada = coadaTemp;
	return rezultat;
}

void main() {

	nod* stiva = NULL;
	stiva = pushStack(stiva, creareFlorarie("Floris", 4));
	stiva = pushStack(stiva, creareFlorarie("Flores", 16));
	stiva = pushStack(stiva, creareFlorarie("FloriPrintate", 8));
	stiva = pushStack(stiva, creareFlorarie("Floraria de la colt", 28));

	/*stiva = filtrareFlorariiCuAfisare(stiva, 10);
	
	printf("stiva ramasa:\n");
	while (stiva) {
		Florarie f = popStack(&stiva);
		afisareFlorarie(f);
		free(f.denumire);
	}*/

	nod*coada = filtrareFlorariiCuSalvareInCoada(&stiva, 10);
	Florarie rezultat = extragareDinCoada(&coada, 16);
	afisareFlorarie(rezultat);
	printf("\nCoada:\n");
	while (coada) {
		Florarie f = popQueue(&coada);
		afisareFlorarie(f);
		free(f.denumire);
	}
	
	printf("stiva ramasa:\n");
	while (stiva) {
		Florarie f = popStack(&stiva);
		afisareFlorarie(f);
		free(f.denumire);
	}


	/*memory leak
	if (stiva) {
		afisareFlorarie(popStack(&stiva));
	}

	while (stiva) {
		Florarie f = popStack(&stiva);
		afisareFlorarie(f);
		free(f.denumire);
	}
	
	nod* coada = NULL;
	coada = pushQueue(coada, creareFlorarie("FloriAlbe", 5));
	coada = pushQueue(coada, creareFlorarie("FloriAlbastre", 8));
	coada = pushQueue(coada, creareFlorarie("Floricica", 17));
	coada = pushQueue(coada, creareFlorarie("FloriRosii", 7));

	printf("coada:\n");
	while (coada) {
		Florarie f = popQueue(&coada);
		afisareFlorarie(f);
		free(f.denumire);
	}*/

}