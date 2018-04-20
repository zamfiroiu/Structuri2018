#include<iostream>

struct Mesaj {
	int prioritate;
	char* text;
};

Mesaj creareMesaj(int prioritate, char* text) {
	Mesaj m;
	m.text = (char*)malloc(sizeof(char)*(strlen(text) + 1));
	strcpy(m.text, text);
	m.prioritate = prioritate;

	return m;
}

void afisareMesaj(Mesaj m) {
	printf("Mesajul % s are prioritatea %d\n", m.text, m.prioritate);
}

struct HEAP{
	int dim;
	Mesaj * vector;
};

void filtrare(HEAP heap, int poz) {
	if (heap.vector) {
		int fiuStanga = 2 * poz + 1;
		int fiuDreapta = 2 * poz + 2;
		int pozMax = poz;

		if (fiuStanga<heap.dim && heap.vector[pozMax].prioritate < heap.vector[fiuStanga].prioritate) {
			pozMax = fiuStanga;
		}

		if (fiuDreapta < heap.dim && heap.vector[pozMax].prioritate < heap.vector[fiuDreapta].prioritate) {
			pozMax = fiuDreapta;
		}
		if (poz != pozMax) {
			Mesaj aux = heap.vector[poz];
			heap.vector[poz] = heap.vector[pozMax];
			heap.vector[pozMax] = aux;
			if (pozMax < (heap.dim - 1) / 2) {
				filtrare(heap, pozMax);
			}
		}
	}
}

void afisareHeap(HEAP heap) {
	for (int i = 0; i < heap.dim; i++) {
		afisareMesaj(heap.vector[i]);
	}
}

void inserareMesaj(HEAP * heap, Mesaj m) {
	if (heap->vector) {
		Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(heap->dim + 1));
		for (int i = 0; i < heap->dim; i++) {
			temp[i] = creareMesaj(heap->vector[i].prioritate, heap->vector[i].text);
			free(heap->vector[i].text);
		}
		temp[heap->dim] = creareMesaj(m.prioritate, m.text);
		heap->dim++;
		free(heap->vector);
		heap->vector = temp;
	}
	for (int i = (heap->dim - 1) / 2; i >= 0; i--) {
		filtrare(*heap, i);
	}
}

void main() {
	HEAP heap;
	heap.dim = 5;
	heap.vector = (Mesaj*)malloc(sizeof(Mesaj)*heap.dim);
	heap.vector[0] = creareMesaj(3, "Salut");
	heap.vector[1] = creareMesaj(8, "La revedere");
	heap.vector[2] = creareMesaj(2, "Ce faci?");
	heap.vector[3] = creareMesaj(5, "Foarte bine!");
	heap.vector[4] = creareMesaj(4, "Restanta.");

	afisareHeap(heap);

	for (int i = (heap.dim - 1) / 2; i >= 0; i--) {
		filtrare(heap, i);
	}
	printf("\n");
	afisareHeap(heap);

	inserareMesaj(&heap, creareMesaj(10, "Noul mesaj"));
	printf("\n");
	afisareHeap(heap);
}