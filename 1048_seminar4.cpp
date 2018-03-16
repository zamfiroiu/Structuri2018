#include<iostream>

struct Avion {
	char* model;
	int anFabricatie;
};

struct nodSimplu {
	Avion info;
	nodSimplu*next;
};

struct nodDublu {
	Avion info;
	nodDublu*next;
	nodDublu*prev;
};

struct LDI {
	nodDublu*prim;
	nodDublu*ult;
};


Avion creareAvion(char*model, int an) {
	Avion avion;
	avion.model = (char*)malloc(sizeof(char)*(strlen(model) + 1));
	strcpy_s(avion.model, strlen(model) + 1, model);
	avion.anFabricatie = an;
	return avion;
}

nodDublu* creareNod(Avion info, nodDublu*next, nodDublu*prev) {
	nodDublu* nodNou = (nodDublu*)malloc(sizeof(nodDublu));
	nodNou->info = creareAvion(info.model, info.anFabricatie);
	nodNou->next = next;
	nodNou->prev = prev;
	return nodNou;
}

nodSimplu* creareNod(Avion info, nodSimplu*next) {
	nodSimplu*nodNou = (nodSimplu*)malloc(sizeof(nodSimplu));
	nodNou->info = creareAvion(info.model, info.anFabricatie);
	nodNou->next = next;
	return nodNou;
}

nodSimplu*inserareSfarsit(nodSimplu* cap, Avion info) {
	if (cap) {
		nodSimplu*p = cap;
		while (p->next) {
			p = p->next;
		}
		nodSimplu* nodNou = creareNod(info, NULL);
		p->next = nodNou;
		return cap;
	}
	else {
		return creareNod(info, NULL);
	}
}

LDI inserareInceput(Avion info, LDI lista) {
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


LDI inserareSfarsit(Avion info, LDI lista) {
	nodDublu* nodNou = creareNod(info,NULL,lista.ult);
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

void afisareAvion(Avion a) {
	printf("Avionul %s a fost fabricat in anul %d\n", a.model, a.anFabricatie);
}

void afisareDeLaInceput(LDI lista) {
	while (lista.prim) {
		afisareAvion(lista.prim->info);
		lista.prim = lista.prim->next;
	}
}

void afisareDeLaSfarsit(LDI lista) {
	while (lista.ult) {
		afisareAvion(lista.ult->info);
		lista.ult = lista.ult->prev;
	}
}

LDI stergereLista(LDI lista) {
	while (lista.prim) {
		free(lista.prim->info.model);
		nodDublu*aux = lista.prim;
		lista.prim = lista.prim->next;
		free(aux);
	}
	lista.ult = NULL;
	return lista;
}

LDI inserarePePozitie(Avion info, LDI lista, int pozitie) {
	if (lista.prim) {
		nodDublu*p = lista.prim;
		while (p && pozitie > 1) {
			p = p->next;
			pozitie--;
		}
		if (p) {
			nodDublu*nodNou = creareNod(info, p, p->prev);
			p->prev = nodNou;
			if (nodNou->prev) {
				nodNou->prev->next = nodNou;
			}
			else {
				lista.prim = nodNou;
			}
		}
		else {
			//lista = inserareSfarsit(info, lista);
			nodDublu*nodNou = creareNod(info, NULL, lista.ult);
			
			lista.ult->next = nodNou;
			lista.ult = nodNou;
		}
	}
	else
	{
		nodDublu*nodNou = creareNod(info, NULL, NULL);
		lista.prim = lista.ult = nodNou;
	}
	return lista;
}

nodSimplu* filtrareAvioane(LDI lista, int anLimita) {
	nodSimplu*cap = NULL;
	if (lista.prim) {
		nodDublu* p = lista.prim;
		while (p) {
			if (p->info.anFabricatie >= anLimita) {
				cap = inserareSfarsit(cap, p->info);
			}
			p = p->next;
		}
	}

	return cap;
}

void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ult = NULL;

	lista = inserarePePozitie(creareAvion("B535", 2008), lista,1);
	lista = inserarePePozitie(creareAvion("B424", 2010), lista,1);
	lista = inserarePePozitie(creareAvion("B373", 2016), lista,2);
	
	afisareDeLaInceput(lista);


	nodSimplu* cap = filtrareAvioane(lista, 2011);

	printf("\n\n");
	while (cap) {
		afisareAvion(cap->info);
		
		nodSimplu*temp = cap;
		cap = cap->next;
		free(temp->info.model);
		free(temp);
	}

	lista = stergereLista(lista);
}