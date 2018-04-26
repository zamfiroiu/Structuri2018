//#include<iostream>
//
//struct ApelUrgenta {
//	int prioritate;
//	char* apelant;
//};
//
//struct HEAP {
//	int dim;
//	ApelUrgenta * vector;
//};
//
//ApelUrgenta citireApel(FILE*f) {
//	char buffer[20];
//	fgets(buffer, 19, f);
//	ApelUrgenta au;
//	au.prioritate = atoi(strchr(buffer, ',') + 1);
//	au.apelant = (char*)malloc(sizeof(char)*(strlen(buffer) - strlen(strchr(buffer, ',')) + 1));
//	strcpy(au.apelant, "");
//	strncat(au.apelant, buffer, strlen(buffer) - strlen(strchr(buffer, ',')));
//
//	return au;
//}
//
//void afisareHeap(HEAP heap, const char*numeFisier) {
//	FILE* f = fopen(numeFisier, "w");
//	if (f) {
//		for (int i = 0;i < heap.dim;i++) {
//			fprintf(f, "Apelul de la %s are prioritatea %d\n", heap.vector[i].apelant, heap.vector[i].prioritate);
//		}
//	}
//	fclose(f);
//}
//
//void filtrare(HEAP heap, int poz) {
//	int stanga = 2 * poz + 1;
//	int dreapta = 2 * poz + 2;
//	int pozitieMaxim;
//	if (dreapta<heap.dim && heap.vector[stanga].prioritate > heap.vector[dreapta].prioritate) {
//		pozitieMaxim = stanga;
//	}
//	else {
//		pozitieMaxim = dreapta;
//	}
//	if (heap.vector[pozitieMaxim].prioritate > heap.vector[poz].prioritate) {
//		ApelUrgenta aux = heap.vector[poz];
//		heap.vector[poz] = heap.vector[pozitieMaxim];
//		heap.vector[pozitieMaxim] = aux;
//		if (pozitieMaxim <= (heap.dim - 1) / 2) {
//			filtrare(heap, pozitieMaxim);
//		}
//	}
//}
//
//ApelUrgenta extragereApel(HEAP *heap) {
//	if (heap->dim > 0) {
//		ApelUrgenta aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->dim - 1];
//		heap->vector[heap->dim - 1] = aux;
//		heap->dim--;
//		for (int i = (heap->dim - 1) / 2;i >= 0;i--) {
//			filtrare(*heap, i);
//		}
//		return aux;
//	}
//}
//
//void main() {
//
//	//declarare heap
//	HEAP heap;
//
//
//	FILE* file = fopen("apeluri.txt", "r");
//	if (file) {
//		int nrApeluri;
//		char buffer[20];
//		fgets(buffer, 19, file);
//		nrApeluri = atoi(buffer);
//		heap.dim = nrApeluri;
//		heap.vector = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*nrApeluri);
//
//		for (int i = 0;i < nrApeluri;i++) {
//			heap.vector[i] = citireApel(file);
//		}
//
//		afisareHeap(heap, "HeapNefiltrat.txt");
//
//		for (int i = (heap.dim - 1) / 2;i >= 0;i--) {
//			filtrare(heap, i);
//		}
//
//		afisareHeap(heap, "HeapFiltrat.txt");
//
//		ApelUrgenta au = extragereApel(&heap);
//		printf( "Apelul de la %s are prioritatea %d\n", au.apelant, au.prioritate);
//
//
//		afisareHeap(heap, "HeapExtras.txt");
//	}
//}