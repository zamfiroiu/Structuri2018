#include<iostream>

struct Portocala{
	int nrFelii;
	float* greutateFelii;
};

Portocala crearePortocala(int nrFelii, float* greutateFelii){
	Portocala portocala;
	portocala.nrFelii = nrFelii;
	portocala.greutateFelii = (float*)malloc(sizeof(float)*nrFelii);
	for (int i = 0; i < nrFelii; i++){
		portocala.greutateFelii[i] = greutateFelii[i];
	}
	return portocala;
}

struct nod{
	Portocala info;
	nod* next;
};

nod* inserareInceput(Portocala portocala, nod* cap){
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->next = cap;
	nou->info = crearePortocala(portocala.nrFelii, portocala.greutateFelii);
	return nou;
}

void afisarePortocala(Portocala p){
	printf("Portocala are %d felii:", p.nrFelii);
	for (int i = 0; i < p.nrFelii; i++){
		printf("%5.2f, ", p.greutateFelii[i]);
	}
	printf("\n");
}

void afisareLista(nod* cap){
	nod* p = cap;
	while (p){
		afisarePortocala(p->info);
		p = p->next;
	}
}

nod* stergereLista(nod*cap){
	while (cap){
		free(cap->info.greutateFelii);
		nod*temp = cap;
		cap = cap->next;
		free(temp);
	}
	return NULL;
}

nod* inserareSfarsit(Portocala portocala, nod* cap){
	if (cap){
		nod*p = cap;
		while (p->next){
			p = p->next;
		}
		p->next = inserareInceput(portocala, NULL);
	}
	else{
		cap = inserareInceput(portocala, cap);
	}
	return cap;
}

float greutateTotala(Portocala portocala){
	float total = 0;
	for (int i = 0; i < portocala.nrFelii; i++){
		total += portocala.greutateFelii[i];
	}

	return total;
}

nod* inserareInainteDeNod(Portocala portocala, nod* cap, float greutate){
	if (cap){
		if (greutate == greutateTotala(cap->info)){
			cap = inserareInceput(portocala, cap);
		}
		else{
			nod* p = cap;
			while (p->next && greutate != greutateTotala(p->next->info)){
				p = p->next;
			}
			p->next = inserareInceput(portocala, p->next);
		}
	}
	else{
		cap = inserareInceput(portocala, cap);
	}

	return cap;
}

nod* pushStack(nod* stiva, Portocala info){
	stiva = inserareSfarsit(info, stiva);
	return stiva;
}

Portocala popStack(nod* *stiva){
	if (*stiva){
		nod* p = *stiva;
		while (p->next && p->next->next){
			p = p->next;
		}
		if (p->next){
			Portocala portocala = crearePortocala(p->next->info.nrFelii,p->next->info.greutateFelii);
			free(p->next->info.greutateFelii);
			free(p->next);
			p->next = NULL;
			return portocala;
		}
		else{
			Portocala portocala = crearePortocala(p->info.nrFelii, p->info.greutateFelii);
			free(p->info.greutateFelii);
			free(p);
			*stiva = NULL;
			return portocala;
		}
	}
	else{
		Portocala portocala;
		portocala.greutateFelii = NULL;
		portocala.nrFelii = 0;
		return portocala;
	}
}

nod* pushQueue(nod* coada, Portocala p){
	return inserareSfarsit(p, coada);
}

Portocala popQueue(nod* *coada){
	if (*coada){
		Portocala portocala = crearePortocala((*coada)->info.nrFelii, (*coada)->info.greutateFelii);
		nod* temp = *coada;
		*coada = (*coada)->next;
		free(temp->info.greutateFelii);
		free(temp);
		return portocala;
	}
	else{
		Portocala portocala;
		portocala.greutateFelii = NULL;
		portocala.nrFelii = 0;
		return portocala;
	}
}

nod* filtrarePortocaleCuSalvareInCoada(nod* *stiva, float prag){
	nod* stivaTemp = NULL;
	nod*coada = NULL;
	while (*stiva){
		Portocala portocala = popStack(stiva);
		if (greutateTotala(portocala) < prag){
			coada = pushQueue(coada, portocala);
		}
		else{
			stivaTemp = pushStack(stivaTemp, portocala);
		}
		free(portocala.greutateFelii);
	}
	while (stivaTemp){
		Portocala p = popStack(&stivaTemp);
		*stiva = pushStack(*stiva, p);
		free(p.greutateFelii);
	}
	return coada;
}



nod* filtrarePortocaleCuAfisare(nod* stiva, float prag){
	nod* stivaTemp = NULL;
	while (stiva){
		Portocala portocala=popStack(&stiva);
		if (greutateTotala(portocala) < prag){
			afisarePortocala(portocala);
		}
		else{
			stivaTemp = pushStack(stivaTemp, portocala);
		}
		free(portocala.greutateFelii);
	}
	while (stivaTemp){
		Portocala p = popStack(&stivaTemp);
		stiva = pushStack(stiva, p);
		free(p.greutateFelii);
	}
	return stiva;
}

void main(){
	nod* stiva = NULL;
	int dim = 3;
	float *gr = (float*)malloc(sizeof(float)*dim);
	gr[0] = 30;
	gr[1] = 100;
	gr[2] = 130;


	stiva = pushStack(stiva, crearePortocala(dim, gr));
	gr[0] = 40;
	stiva = pushStack(stiva, crearePortocala(dim, gr));
	gr[0] = 50;
	stiva = pushStack(stiva, crearePortocala(dim, gr));
	gr[0] = 60;
	stiva = pushStack(stiva, crearePortocala(dim, gr));

	nod*coada = filtrarePortocaleCuSalvareInCoada(&stiva, 280);

	printf("Coada:\n");
	while (coada){
			Portocala portocala = popQueue(&coada);
			afisarePortocala(portocala);
			free(portocala.greutateFelii);
	}

	printf("Stiva:\n");
	while (stiva){
		Portocala portocala = popStack(&stiva);
		afisarePortocala(portocala);
		free(portocala.greutateFelii);
	}


	////memoryLeak
	//if (stiva){
	//	afisarePortocala(popStack(&stiva));
	//}

	//while (stiva){
	//	Portocala portocala = popStack(&stiva);
	//	afisarePortocala(portocala);
	//	free(portocala.greutateFelii);
	//}

	//nod* coada = NULL;
	//coada = pushQueue(coada, crearePortocala(dim, gr));
	//gr[0] = 70;
	//coada = pushQueue(coada, crearePortocala(dim, gr));
	//gr[0] = 80;
	//coada = pushQueue(coada, crearePortocala(dim, gr));
	//gr[0] = 90;
	//coada = pushQueue(coada, crearePortocala(dim, gr));

	//printf("Coada\n");
	//while (coada){
	//	Portocala portocala = popQueue(&coada);
	//	afisarePortocala(portocala);
	//	free(portocala.greutateFelii);
	//}
}