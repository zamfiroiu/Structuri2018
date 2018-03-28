#include<iostream>

struct Magazin {
	char* nume;
	float cifra_afaceri;
};

Magazin creareMagazin(char* nume, float ca) {
	Magazin m;
	m.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy_s(m.nume, strlen(nume) + 1, nume);
	m.cifra_afaceri = ca;

	return m;
}

struct nod {
	Magazin info;
	nod* next;
};

nod* inserareInceput(nod* cap, Magazin m) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareMagazin(m.nume, m.cifra_afaceri);
	nou->next = cap;
	return nou;
}


//de simplificat
//de modificat, astfel incat sa folositi inserareInceput

nod* inserareSfarsit(nod* cap, Magazin m) {
	if (cap) {
		nod*p = cap;
		while (p->next) {
			p = p->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareMagazin(m.nume, m.cifra_afaceri);
		nou->next = NULL;
		p->next = nou;

		return cap;
	}
	else
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareMagazin(m.nume, m.cifra_afaceri);
		nou->next = NULL;
		return nou;
	}
}

///ce se intampla daca inseram o valoare mai
//mica decat toate elementele din lista
nod* inserareSortata(nod* cap, Magazin m) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareMagazin(m.nume, m.cifra_afaceri);
	if (cap) {
		nod*p = cap;
		while (p->next != NULL && p->next->info.cifra_afaceri < m.cifra_afaceri) {
			p = p->next;
		}

		if (p->next) {
			nou->next = p->next;
			p->next = nou;
		}
		else
		{
			p->next = nou;
			nou->next = NULL;
		}
	}
	else {
		nou->next = NULL;
		return nou;
	}
	return cap;
}

void afisareMagazin(Magazin m) {
	printf("Magazinul %s are o CA de %5.2f\n", m.nume, m.cifra_afaceri);

}

void afisareLista(nod* lista) {
	nod*temp = lista;
	while (temp) {
		afisareMagazin(temp->info);
		temp = temp->next;
	}
}



nod* stergere(nod*lista) {
	while (lista) {
		free(lista->info.nume);
		nod*p = lista;
		lista = lista->next;
		free(p);
	}
	return NULL;
}

nod* pushStack(nod* stiva, Magazin m) {
	stiva = inserareSfarsit(stiva, m);
	return stiva;
}

Magazin popStack(nod* *stiva) {
	if (*stiva) {
		if ((*stiva)->next) {
			nod*p = *stiva;
			while (p->next->next) {
				p = p->next;
			}
			Magazin rezultat = creareMagazin(p->next->info.nume,p->next->info.cifra_afaceri);
			free(p->next->info.nume);
			free(p->next);
			p->next = NULL;
			return rezultat;
		}
		else {
			Magazin rezultat = creareMagazin((*stiva)->info.nume, (*stiva)->info.cifra_afaceri);
			free((*stiva)->info.nume);
			free(*stiva);
			*stiva = NULL;
			return rezultat;
		}
	}
	else {
		Magazin rezultat;
		rezultat.cifra_afaceri = -1;
		rezultat.nume = NULL;
		return rezultat;
	}
}


nod* pushQueue(nod* coada, Magazin m) {
	return inserareInceput(coada, m);
}

Magazin popQueue(nod* *coada) {
	return popStack(coada);
}


nod* filtrareMagazineCuAfisare(nod* stiva, int limita) {
	nod* stivaTemp = NULL;
	while (stiva) {
		Magazin m = popStack(&stiva);
		if (m.cifra_afaceri > limita) {
			stivaTemp = pushStack(stivaTemp, m);
		}
		else {
			afisareMagazin(m);
		}
		free(m.nume);
	}
	while (stivaTemp) {
		Magazin m = popStack(&stivaTemp);
		stiva = pushStack(stiva, m);
		free(m.nume);
	}
	return stiva;
}

nod* filtrareMagazineCuSalvareInCoada(nod* *stiva, int limita) {
	nod* stivaTemp = NULL;
	nod* coadaRezultat = NULL;
	while (*stiva) {
		Magazin m = popStack(stiva);
		if (m.cifra_afaceri > limita) {
			stivaTemp = pushStack(stivaTemp, m);
		}
		else {
			coadaRezultat = pushQueue(coadaRezultat, m);
		}
		free(m.nume);
	}
	*stiva = stivaTemp;
	return coadaRezultat;
}



void main() {

	nod* stiva = NULL;
	stiva = pushStack(stiva, creareMagazin("Emag", 1000));
	stiva = pushStack(stiva, creareMagazin("Mega Image", 800));
	stiva = pushStack(stiva, creareMagazin("ABC", 1400));
	stiva = pushStack(stiva, creareMagazin("Plus", 700));


	/*stiva = filtrareMagazineCuAfisare(stiva, 900);
	printf("stiva ramasa:\n");
	while (stiva) {
		Magazin m = popStack(&stiva);
		afisareMagazin(m);
		free(m.nume);
	}*/

	nod* coadaRezultat = filtrareMagazineCuSalvareInCoada(&stiva, 1100);

	printf("Coada:\n");
	while (coadaRezultat)
	{
		Magazin m = popQueue(&coadaRezultat);
		afisareMagazin(m);
		free(m.nume);
	}

	printf("stiva ramasa:\n");
	while (stiva) {
		Magazin m = popStack(&stiva);
		afisareMagazin(m);
		free(m.nume);
	}

	////memory Leak
	//if (stiva) {
	//	afisareMagazin(popStack(&stiva));
	//}

	//while (stiva) {
	//	Magazin m = popStack(&stiva);
	//	afisareMagazin(m);
	//	free(m.nume);
	//}

	//nod* coada = NULL;
	//coada = pushQueue(coada, creareMagazin("Carrefour", 2000));
	//coada = pushQueue(coada, creareMagazin("Metro", 1800));
	//coada = pushQueue(coada, creareMagazin("Billa", 1500));
	//coada = pushQueue(coada, creareMagazin("Cora", 1000));

	//printf("Coada:\n");
	//while (coada)
	//{
	//	Magazin m = popQueue(&coada);
	//	afisareMagazin(m);
	//	free(m.nume);
	//}



}