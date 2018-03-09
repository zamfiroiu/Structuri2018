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

void afisareLista(nod* cap){
	nod* p = cap;
	while (p){
		printf("Portocala are %d felii:", p->info.nrFelii);
		for (int i = 0; i < p->info.nrFelii; i++){
			printf("%5.2f, ", p->info.greutateFelii[i]);
		}
		printf("\n");
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

void main(){
	nod* lista = NULL;
	Portocala portocala = crearePortocala(4, new float[4]{20, 24, 19, 15});
	lista = inserareInceput(portocala, lista);
	portocala.greutateFelii[0] = 10;
	lista = inserareInceput(portocala, lista);
	portocala.greutateFelii[0] = 12;
	lista = inserareInceput(portocala, lista);

	afisareLista(lista);
	lista=stergereLista(lista);

	lista = inserareSfarsit(portocala, lista);
	portocala.greutateFelii[0] = 17;

	lista = inserareSfarsit(portocala, lista);
	portocala.greutateFelii[0] = 23;
	float greutate = greutateTotala(portocala);
	lista = inserareSfarsit(portocala, lista);
	printf("lista nou:\n");
	afisareLista(lista);

	portocala.greutateFelii[0] = 56;
	lista = inserareInainteDeNod(portocala, lista, greutate);

	printf("lista noua:\n");
	afisareLista(lista);
	lista = stergereLista(lista);

	free(portocala.greutateFelii);
}