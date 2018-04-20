#include<iostream>

struct Mesaj {
	int prioritate;
	char* destinatar;
};

Mesaj creareMesaj(int prioritate, char* destinatar) {
	Mesaj m;
	m.destinatar = (char*)malloc(sizeof(char)*(strlen(destinatar) + 1));
	strcpy(m.destinatar, destinatar);
	m.prioritate = prioritate;
	return m;
}

void afisareMesaj(Mesaj m) {
	printf("Mesajul de la %s are prioritatea %d\n", m.destinatar, m.prioritate);
}

struct HEAP {
	Mesaj* vector;
	int dim;
};

void filtrare(HEAP heap, int pozitie) {
	int fiuStanga = 2 * pozitie + 1;
	int fiuDreapta = 2 * pozitie + 2;
	int max = pozitie;
	if (fiuStanga<heap.dim && heap.vector[max].prioritate < heap.vector[fiuStanga].prioritate) {
		max = fiuStanga;
	}
	if (fiuDreapta<heap.dim && heap.vector[max].prioritate < heap.vector[fiuDreapta].prioritate) {
		max = fiuDreapta;
	}
	if (max != pozitie) {
		Mesaj aux = heap.vector[pozitie];
		heap.vector[pozitie] = heap.vector[max];
		heap.vector[max] = aux;
		if (max < (heap.dim - 1) / 2) {
			filtrare(heap, max);
		}
	}

}

void afisareHeap(HEAP heap) {
	for (int i = 0; i < heap.dim; i++) {
		afisareMesaj(heap.vector[i]);
	}
}

void inserareMesaj(HEAP *heap, Mesaj m) {
	Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(heap->dim + 1));
	for (int i = 0; i < heap->dim; i++) {
		temp[i] = heap->vector[i];
	}
	temp[heap->dim] = m;
	free(heap->vector);
	heap->vector = temp;
	heap->dim++;
	for (int i = (heap->dim - 1) / 2; i >= 0; i--) {
		filtrare(*heap, i);
	}
}

Mesaj extragereMesaj(HEAP *heap) {
	if (heap->vector) {
		Mesaj rezultat = heap->vector[0];
		Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(heap->dim - 1));
		for (int i = 0; i < heap->dim-1; i++) {
			temp[i] = heap->vector[i + 1];
		}

		free(heap->vector);
		heap->dim--;
		heap->vector = temp;
		for (int i = (heap->dim - 1) / 2; i >= 0; i--) {
			filtrare(*heap, i);
		}
		return rezultat;
	}
	else {
		Mesaj m;
		m.destinatar = (char*)malloc(sizeof(char));
		strcpy(m.destinatar, "");
		m.prioritate = -1;
		return m;
	}
}
void main() {
	HEAP heap;
	heap.dim = 6;
	heap.vector = (Mesaj*)malloc(sizeof(Mesaj)*heap.dim);
	heap.vector[0] = creareMesaj(5, "Popescu");
	heap.vector[1] = creareMesaj(8, "Ionescu");
	heap.vector[2] = creareMesaj(3, "Vasilescu");
	heap.vector[3] = creareMesaj(9, "Georgescu");
	heap.vector[4] = creareMesaj(4, "Gigel");
	heap.vector[5] = creareMesaj(2, "Gheorghe");

	afisareHeap(heap);
	for (int i = (heap.dim - 1) / 2; i >= 0; i--) {
		filtrare(heap, i);
	}
	printf("\n\n");
	afisareHeap(heap);

	inserareMesaj(&heap, creareMesaj(11, "Popescu Ion"));

	printf("\n\n");
	afisareHeap(heap);

	Mesaj m = extragereMesaj(&heap);

	printf("Mesaj: ");
	afisareMesaj(m);


	printf("\n\n");
	afisareHeap(heap);

}