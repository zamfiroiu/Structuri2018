#include<iostream>

struct Mesaj {
	int priritate;
	char* text;
};

Mesaj creareMesaj(int pr, char* text) {
	Mesaj m;
	m.priritate = pr;
	m.text = (char*)malloc(sizeof(char)*(strlen(text) + 1));
	strcpy(m.text, text);
	return m;
}

void afisareMesaj(Mesaj m) {
	printf("Mesajul %s are prioritatea %d\n", m.text, m.priritate);
}

struct HEAP {
	Mesaj * vector;
	int dim;
};

void filtrare(HEAP heap, int pozitie) {
	if (heap.vector) {
		if (pozitie <= (heap.dim - 1) / 2) {
			int fiuStanga = 2 * pozitie + 1;
			int fiuDreapta = 2 * pozitie + 2;
			int pozitieMaxim = pozitie;
			if (fiuStanga<heap.dim && heap.vector[pozitieMaxim].priritate < heap.vector[fiuStanga].priritate) {
				pozitieMaxim = fiuStanga;
			}
			if (fiuDreapta<heap.dim && heap.vector[pozitieMaxim].priritate < heap.vector[fiuDreapta].priritate) {
				pozitieMaxim = fiuDreapta;
			}
			if (pozitie != pozitieMaxim) {
				Mesaj aux = heap.vector[pozitie];
				heap.vector[pozitie] = heap.vector[pozitieMaxim];
				heap.vector[pozitieMaxim] = aux;
				if (pozitieMaxim <= (heap.dim - 1) / 2) {
					filtrare(heap, pozitieMaxim);
				}
			}
		}
	}
}

void afisareHeap(HEAP heap) {
	for (int i = 0; i < heap.dim; i++) {
		afisareMesaj(heap.vector[i]);
	}
}

void inserareMesaj(HEAP* heap, Mesaj m) {
	Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(heap->dim + 1));
	for (int i = 0; i < heap->dim; i++) {
		temp[i] = heap->vector[i];
	}
	temp[heap->dim] = m;
	heap->dim++;
	free(heap->vector);
	heap->vector = temp;
	
	for (int i = (heap->dim - 1) / 2; i >= 0; i--) {
		filtrare(*heap, i);
	}
}

Mesaj extrageMesaj(HEAP *heap) {
	if (heap->dim>0) {
		Mesaj aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->dim - 1];
		heap->vector[heap->dim - 1] = aux;
		heap->dim--;
		for (int i = (heap->dim - 1) / 2; i >= 0; i--) {
			filtrare(*heap, i);
		}
		return aux;
	}
}

void main() {
	HEAP heap;
	heap.dim = 6;
	heap.vector = (Mesaj*)malloc(sizeof(Mesaj)*heap.dim);
	heap.vector[0] = creareMesaj(4, "Salut");
	heap.vector[1] = creareMesaj(8, "Alo");
	heap.vector[2] = creareMesaj(3, "ce faci?");
	heap.vector[3] = creareMesaj(5, "Licenta");
	heap.vector[4] = creareMesaj(9, "test SDD");
	heap.vector[5] = creareMesaj(6, "Obtin nota");

	afisareHeap(heap);
	
	for (int i = (heap.dim - 1) / 2; i >= 0; i--) {
		filtrare(heap, i);
	}

	printf("\n");
	afisareHeap(heap);

	inserareMesaj(&heap, creareMesaj(10, "Mesaj nou"));

	printf("\n");
	afisareHeap(heap);

	Mesaj m = extrageMesaj(&heap);

	printf("\n");
	afisareMesaj(m);

	printf("\n");
	afisareHeap(heap);

}