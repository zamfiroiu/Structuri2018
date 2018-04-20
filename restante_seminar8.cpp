#include<iostream>

struct Mesaj{
	char* destinatar;
	int prioritate;
};

Mesaj creareMesaj(char* des, int pr){
	Mesaj m;

	m.destinatar = (char*)malloc(sizeof(char)*(strlen(des) + 1));
	strcpy(m.destinatar, des);
	m.prioritate = pr;
	return m;


}

void afisareMesaj(Mesaj m){
	printf("Mesajul trimis catre %s are prioritatea %d\n", m.destinatar, m.prioritate);
}

struct HEAP{
	Mesaj * vector;
	int dim;
};

void filtrare(HEAP heap, int pozitie){
	if (heap.vector && pozitie < heap.dim){
		int fiuStanga = 2 * pozitie + 1;
		int fiuDreapta = 2 * pozitie + 2;
		int max = pozitie;
		if (fiuStanga<heap.dim && heap.vector[max].prioritate < heap.vector[fiuStanga].prioritate){
			max = fiuStanga;
		}
		if (fiuDreapta<heap.dim && heap.vector[max].prioritate < heap.vector[fiuDreapta].prioritate){
			max = fiuDreapta;
		}

		if (max != pozitie){
			Mesaj aux = heap.vector[max];
			heap.vector[max] = heap.vector[pozitie];
			heap.vector[pozitie] = aux;

			if (max < (heap.dim - 1) / 2){
				filtrare(heap, max);
			}
		}
	}
}

void afisareHeap(HEAP heap){
	for (int i = 0; i < heap.dim; i++){
		afisareMesaj(heap.vector[i]);
	}
}

Mesaj extrageMesaj(HEAP*heap){
	Mesaj rezultat = heap->vector[0];
	Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(heap->dim - 1));
	for (int i = 0; i < heap->dim-1; i++){
		temp[i] = heap->vector[i + 1];
	}
	free(heap->vector);
	heap->dim--;
	heap->vector = temp;

	for (int i = (heap->dim - 1) / 2; i >= 0; i--){
		filtrare(*heap, i);
	}

	return rezultat;

}

void inserareMesaj(HEAP* heap, Mesaj m){
	Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(heap->dim + 1));
	for (int i = 0; i < heap->dim; i++){
		temp[i] = heap->vector[i];

	}
	temp[heap->dim] = m;
	heap->dim++;
	free(heap->vector);
	heap->vector = temp;
	for (int i = (heap->dim - 1) / 2; i >= 0; i--){
		filtrare(*heap, i);
	}
}

void main(){
	HEAP heap;
	heap.dim = 6;
	heap.vector = (Mesaj*)malloc(sizeof(Mesaj)*heap.dim);
	heap.vector[0] = creareMesaj("popescu", 5);
	heap.vector[1] = creareMesaj("ionescu", 4);
	heap.vector[2] = creareMesaj("Vasilescu", 8);
	heap.vector[3] = creareMesaj("georgescu", 3);
	heap.vector[4] = creareMesaj("Gigel", 9);
	heap.vector[5] = creareMesaj("Dumitru", 2);

	afisareHeap(heap);

	for (int i = (heap.dim - 1) / 2; i >= 0; i--){
		filtrare(heap, i);
	}

	printf("\n\n");
	afisareHeap(heap);

	inserareMesaj(&heap, creareMesaj("Ionescu2", 10));


	printf("\n\n");
	afisareHeap(heap);
	
	
	for (int i = 0; i < heap.dim; i++){
		free(heap.vector[i].destinatar);
	}
	free(heap.vector);

}