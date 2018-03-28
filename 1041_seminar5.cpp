#include<iostream>

struct Floare {
	char* denumire;
	float pret;
};

struct nod {
	Floare info;
	nod* next;
};

void afisareFloare(Floare f) {
	printf("Floarea %s costa %5.2f lei\n",f.denumire,f.pret);
}

Floare creareFloare(char* denumire, float pret) {
	Floare floare;
	floare.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(floare.denumire, denumire);
	floare.pret = pret;
	return floare;
}

nod* inserareInceput(nod* cap, Floare floare) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareFloare(floare.denumire, floare.pret);
	nou->next = cap;
	return nou;
}

nod* pushStack(nod* stiva, Floare info) {
	stiva = inserareInceput(stiva, info);
	return stiva;
}

Floare popStack(nod* *stiva) {
	Floare floare;
	if (*stiva) {
		floare = creareFloare((*stiva)->info.denumire,(*stiva)->info.pret);
		nod* aux = *stiva;
		*stiva = (*stiva)->next;
		free(aux->info.denumire);
		free(aux);
		return floare;
	}
	else {
		floare.denumire = NULL;
		floare.pret = -1;
		return floare;
	}
}

int emptyStack(nod* stiva) {
	return (stiva == NULL) ? 1 : 0;
}

nod* pushQueue(nod* coada, Floare info) {
	return inserareInceput(coada, info);
}

Floare popQueue(nod* *coada) {
	if (*coada) {
		nod*p = *coada;
		while (p->next && p->next->next) {
			p = p->next;
		}
		if (p->next) {
			Floare f = creareFloare(p->next->info.denumire, p->next->info.pret);
			free(p->next->info.denumire);
			free(p->next);
			p->next = NULL;
			return f;
		}
		else {
			Floare f = creareFloare(p->info.denumire, p->info.pret);
			free(p->info.denumire);
			free(p);
			*coada = NULL;
			return f;
		}
	}
	else {
		Floare floare;
		floare.denumire = NULL;
		floare.pret = -1;
		return floare;
	}
}

nod* filtrareFloriCuAfisare(nod* stiva, float limita) {
	nod*stivaTemp = NULL;
	while (stiva) {
		Floare f = popStack(&stiva);
		if (f.pret < limita) {
			afisareFloare(f);
		}
		else {
			stivaTemp = pushStack(stivaTemp, f);
		}
		free(f.denumire);
	}
	while (stivaTemp) {
		Floare f = popStack(&stivaTemp);
		stiva = pushStack(stiva, f);
		free(f.denumire);
	}
	return stiva;
}

nod* filtrareFloriCuSalvareInCoada(nod* *stiva, float limita) {
	nod*stivaTemp = NULL;
	nod*coadaRezultat = NULL;
	while (*stiva) {
		Floare f = popStack(stiva);
		if (f.pret < limita) {
			coadaRezultat = pushQueue(coadaRezultat, f);
		}
		else {
			stivaTemp = pushStack(stivaTemp, f);
		}
		free(f.denumire);
	}
	while (stivaTemp) {
		Floare f = popStack(&stivaTemp);
		*stiva = pushStack(*stiva, f);
		free(f.denumire);
	}
	return coadaRezultat;
}

void main() {
	nod * stiva = NULL;
	stiva = pushStack(stiva, creareFloare("Lalea", 5));
	stiva = pushStack(stiva, creareFloare("Trandafir", 9));
	stiva = pushStack(stiva, creareFloare("Orhidee", 17));

	////memory Leak
	//if (!emptyStack(stiva)) {
	//	afisareFloare(popStack(&stiva));
	//}

	//while (stiva) {
	//	Floare f = popStack(&stiva);
	//	afisareFloare(f);
	//	free(f.denumire);
	//}


	//nod* coada = NULL;

	//coada = pushQueue(coada, creareFloare("Trandafir", 10));
	//coada = pushQueue(coada, creareFloare("Orhidee", 27));
	//coada = pushQueue(coada, creareFloare("Lalea", 6));
	//coada = pushQueue(coada, creareFloare("Zambila", 4));

	//while (coada) {
	//	Floare f = popQueue(&coada);
	//	afisareFloare(f);
	//	free(f.denumire);
	//}

	nod* coada = filtrareFloriCuSalvareInCoada(&stiva, 8);

	printf("coada:\n");
	while (coada) {
		Floare f = popQueue(&coada);
		afisareFloare(f);
		free(f.denumire);
	}

	printf("Stiva:\n");
	while (stiva) {
		Floare f = popStack(&stiva);
		afisareFloare(f);
		free(f.denumire);
	}

}