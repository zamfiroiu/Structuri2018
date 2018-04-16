#include<iostream>

struct Prajitura{
	char* denumire;
	float gramaj;
};

struct nod{
	Prajitura info;
	nod*next;
};

Prajitura citirePrajituraDinFisier(FILE* f){
	Prajitura prajitura;
	char buffer[20];
	fgets(buffer, 19, f);
	prajitura.gramaj = atof(strchr(buffer, ',')+1);
	*strchr(buffer, ',') = '\0';

	prajitura.denumire = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(prajitura.denumire, buffer);
	return prajitura;
}

nod* inserareInListaCirculara(nod* cap, Prajitura prajitura){
	nod* nodNou = (nod*)malloc(sizeof(nod));
	//shallow copy
	nodNou->info = prajitura;
	if (cap){
		nod* p = cap;
		while (p->next != cap){
			p = p->next;
		}
		p->next = nodNou;
		nodNou->next = cap;
		return cap;
	}
	else{
		nodNou->next = nodNou;
		return nodNou;
	}
}

void salvarePrajituraInFisier(Prajitura prajitura, FILE* f){
	fprintf(f, "Prajitura %s are %5.2f grame.\n", prajitura.denumire, prajitura.gramaj);
}


void salvareListaInFisier(nod* cap, char* numeFisier){
	if (cap){
		FILE* f = fopen(numeFisier, "w");
		if (f){
			nod* p = cap;
			/*while (p->next != cap){
				salvarePrajituraInFisier(p->info, f);
				p = p->next;
			}
			salvarePrajituraInFisier(p->info, f);*/

			do{
				salvarePrajituraInFisier(p->info, f);
				p = p->next;
			} while (p != cap);

		}
		fclose(f);
	}
}

void stergereLista(nod** cap){
	if (*cap){
		nod*p = (*cap)->next;
		while (p != *cap){
			free(p->info.denumire);
			nod* aux = p;
			p = p->next;
			free(aux);
		}
		free(p->info.denumire);
		free(p);
		*cap = NULL;
	}
}

void main(){
	nod* cap = NULL;
	FILE* file = fopen("prajituri.txt", "r");
	int nrPrajituri;
	fscanf(file, "%d", &nrPrajituri);
	char buffer[3];
	fgets(buffer, 2, file);
	for (int i = 0; i < nrPrajituri; i++){
		cap=inserareInListaCirculara(cap, citirePrajituraDinFisier(file));
	}

	salvareListaInFisier(cap, "PrajituriSalvate.txt");
	stergereLista(&cap);

}