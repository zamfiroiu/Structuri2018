#include<iostream>

struct test{
	char* materie;
	float notaMaxima;
};
struct nodSimplu{
	test info;
	nodSimplu* next;
};

struct nodDublu{
	test info;
	nodDublu* next;
	nodDublu* prev;
};

struct LDI{
	nodDublu* prim;
	nodDublu* ult;
};

test creareTest(char*materie, float nota){
	test t;
	t.materie = (char*)malloc(sizeof(char)*(strlen(materie) + 1));
	strcpy(t.materie, materie);
	t.notaMaxima = nota;
	return t;
}

nodDublu* creareNodDublu(test info, nodDublu* next, nodDublu* prev){
	nodDublu* nodNou = (nodDublu*)malloc(sizeof(nodDublu));
	nodNou->info = creareTest(info.materie,info.notaMaxima);
	nodNou->next = next;
	nodNou->prev = prev;
	return nodNou;
}

LDI inserareInceput(LDI lista, test info){
	nodDublu* nodNou = creareNodDublu(info, lista.prim, NULL);
	if (lista.prim){
		lista.prim->prev = nodNou;
		lista.prim = nodNou;
	}
	else{
		lista.prim = nodNou;
		lista.ult = nodNou;
	}
	return lista;
}

LDI inserareSfarsit(LDI lista, test info){
	nodDublu* nodNou = creareNodDublu(info, NULL, lista.ult);
	if (lista.ult){
		lista.ult->next = nodNou;
		lista.ult = nodNou;
	}
	else{
		lista.prim = nodNou;
		lista.ult = nodNou;
	}
	return lista;
}

void afisareTest(test t){
	printf("Testul la materia %s are nota maxima %5.2f\n", t.materie, t.notaMaxima);
}
void afisareCapCoada(LDI lista){
	nodDublu* p = lista.prim;
	while (p){
		afisareTest(p->info);
		p = p->next;
	}
}

void afisareCoadaCap(LDI lista){
	nodDublu* p = lista.ult;
	while (p){
		afisareTest(p->info);
		p = p->prev;
	}
}

void stergereLista(LDI* lista){
	while (lista->prim)
	{
		nodDublu* aux = lista->prim;
		lista->prim = lista->prim->next;
		free(aux->info.materie);
		free(aux);
	}
	lista->ult = NULL;
}

LDI inserarePePozitie(LDI lista, test info, int pozitie){
	if (lista.prim){
		int k = 1;
		nodDublu*p = lista.prim;
		while (p && k < pozitie){
			p = p->next;
			k++;
		}
		if (p){
			nodDublu* nodNou = creareNodDublu(info, p, p->prev);
			p->prev = nodNou;
			if (nodNou->prev){
				nodNou->prev->next = nodNou;
			}
			else{
				lista.prim = nodNou;
			}
		}
		else{
			lista = inserareSfarsit(lista, info);
		}
	}
	else{
		lista = inserareSfarsit(lista, info);
	}

	return lista;
}

nodSimplu* inserareInceput(nodSimplu* cap, test info){
	nodSimplu*nodNou = (nodSimplu*)malloc(sizeof(nodSimplu));
	nodNou->info = creareTest(info.materie, info.notaMaxima);
	nodNou->next = cap;
	return nodNou;
}

nodSimplu* ExtragereTeste(LDI lista, char* materieLimita){
	nodSimplu*cap = NULL;
	while (lista.prim){
		if (stricmp(lista.prim->info.materie, materieLimita) <= 0){
			cap = inserareInceput(cap, lista.prim->info);			
		}
		lista.prim = lista.prim->next;
	}
	return cap;
}

void main(){
	LDI lista;
	lista.prim = lista.ult = NULL;

	lista = inserarePePozitie(lista, creareTest("Structuri", 10),1);
	lista = inserarePePozitie(lista, creareTest("Statistica", 11),4);
	lista = inserarePePozitie(lista, creareTest("Java", 9),3);

	afisareCapCoada(lista);

	nodSimplu* cap = ExtragereTeste(lista, "Statistica");

	printf("\n");

	while (cap){
		afisareTest(cap->info);
		nodSimplu* aux = cap;
		cap = cap->next;
		free(aux->info.materie);
		free(aux);
	}


	stergereLista(&lista);
}