#include<iostream>


struct Hotel{
	char* denumire;
	char camereLibere;
	int nrCamere;
};

struct nod {
	Hotel info;
	nod* next;
};

Hotel citesteHotelDinFisier(FILE* f) {
	char  buffer[50];
	fgets(buffer, 49, f);
	Hotel h;
	h.denumire = (char*)malloc(sizeof(char)*(strlen(buffer) 
					- strlen(strchr(buffer, ',') + 1)));
	strcpy(h.denumire, "");
	strncat(h.denumire,buffer, strlen(buffer) - strlen(strchr(buffer, ',')));
	h.camereLibere = buffer[strlen(buffer) - strlen(strchr(buffer, ','))+1];
	h.nrCamere = atoi(strrchr(buffer, ',')+1);
	return h;
}

nod* inserareInListaCirculara(nod* cap, Hotel h) {
	nod* nodNou = (nod*)malloc(sizeof(nod));
	//shallow copy
	nodNou->info = h;
	if (cap) {
		nod* p = cap;
		while (p->next != cap) {
			p = p->next;
		}
		p->next = nodNou;
		nodNou->next = cap;
		return cap;
	}
	else {
		nodNou->next = nodNou;
		return nodNou;
	}
}

void salvareHotelInFisier(Hotel h, FILE* f) {
	fprintf(f, "hotelul %s are %d camere si disponibilitatea este %c\n", h.denumire, h.nrCamere, h.camereLibere);
}

void salvareListaInFisier(nod* cap, char* numeFisier) {
	FILE* f = fopen(numeFisier, "w");
	if (f) {
		if (cap) {
			nod* p = cap;
			do {
				salvareHotelInFisier(p->info, f);
				p = p->next;
			} while (p != cap);
		}
	}
	fclose(f);
}

void stergereListaCircualara(nod**cap) {
	if (*cap) {
		nod* p = (*cap)->next;
		while (p != (*cap)) {
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

void main() {
	nod* cap = NULL;
	FILE* file = fopen("hoteluri.txt", "r");
	if (file) {
		int nrHoteluri = 0;
		fscanf(file, "%d", &nrHoteluri);
		char buffer[3];
		fgets(buffer, 2, file);
		for (int i = 0; i < nrHoteluri; i++) {
			cap = inserareInListaCirculara(cap, citesteHotelDinFisier(file));
		}
		fclose(file);
	}
	salvareListaInFisier(cap, "HoteluriSalvate.txt");

	stergereListaCircualara(&cap);
}