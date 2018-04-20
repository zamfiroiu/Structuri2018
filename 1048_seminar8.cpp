#include<iostream>

struct Mesaj {
	int prioritate;
	char* expeditor;
};

Mesaj creareMesaj(char* exp, int pri) {
	Mesaj m;
	m.expeditor = (char*)malloc(sizeof(char)*(strlen(exp) + 1));
	strcpy(m.expeditor, exp);
	m.prioritate = pri;
	return m;
}

void afisareMesaj(Mesaj m) {
	printf("Mesajul de la %s are prioritatea %d\n", m.expeditor, m.prioritate);
}

struct CoadaPrioritate {
	Mesaj* vector;
	int dim;
};

void filtrare(CoadaPrioritate coada, int pozitia) {
	int fiuStanga = 2 * pozitia + 1;
	int fiuDreapta = 2 * pozitia + 2;
	int pozitiemaxim = pozitia;
	if (fiuStanga<coada.dim && coada.vector[pozitiemaxim].prioritate < coada.vector[fiuStanga].prioritate) {
		pozitiemaxim = fiuStanga;
	}
	if (fiuDreapta<coada.dim && coada.vector[pozitiemaxim].prioritate < coada.vector[fiuDreapta].prioritate) {
		pozitiemaxim = fiuDreapta;
	}

	if (pozitia != pozitiemaxim) {
		Mesaj aux = coada.vector[pozitia];
		coada.vector[pozitia] = coada.vector[pozitiemaxim];
		coada.vector[pozitiemaxim] = aux;
		if (pozitiemaxim < (coada.dim - 1) / 2) {
			filtrare(coada, pozitiemaxim);
		}
	}
}

void afisareCoadaPrioritati(CoadaPrioritate coada) {
	for (int i = 0; i < coada.dim; i++) {
		afisareMesaj(coada.vector[i]);
	}
}

void inserareMesaj(CoadaPrioritate* coada, Mesaj m) {
	Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(coada->dim + 1));
	for (int i = 0; i < coada->dim; i++) {
		temp[i] = coada->vector[i];
	}
	temp[coada->dim] = m;
	free(coada->vector);
	coada->dim++;
	coada->vector = temp;
	for (int i = (coada->dim - 1) / 2; i >= 0; i--) {
		filtrare(*coada, i);
	}
}

Mesaj extrageMesaj(CoadaPrioritate*coada) {
	Mesaj rezultat = coada->vector[0];
	Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(coada->dim - 1));
	for (int i = 0; i < coada->dim-1; i++) {
		temp[i] = coada->vector[i + 1];
	}
	coada->dim--;
	free(coada->vector);
	coada->vector = temp;
	for (int i = (coada->dim - 1) / 2; i >= 0; i--) {
		filtrare(*coada, i);
	}
	return rezultat;
}

void main() {
	CoadaPrioritate coada;
	coada.dim = 6;
	coada.vector = (Mesaj*)malloc(sizeof(Mesaj)*coada.dim);
	coada.vector[0] = creareMesaj("Popescu", 4);
	coada.vector[1] = creareMesaj("Ionescu", 5);
	coada.vector[2] = creareMesaj("Gigel", 7);
	coada.vector[3] = creareMesaj("Dumitru", 9);
	coada.vector[4] = creareMesaj("Gheorghe", 3);
	coada.vector[5] = creareMesaj("Vasilescu", 1);

	afisareCoadaPrioritati(coada);

	for (int i = (coada.dim - 1) / 2; i >= 0; i--) {
		filtrare(coada, i);
	}

	printf("\n");
	afisareCoadaPrioritati(coada);

	inserareMesaj(&coada, creareMesaj("fsdfsdf", 12));

	printf("\n");
	afisareCoadaPrioritati(coada);


	Mesaj m = extrageMesaj(&coada);

	printf("\n");
	afisareMesaj(m);

	printf("\n");
	afisareCoadaPrioritati(coada);

	for (int i = 0; i < coada.dim; i++) {
		free(coada.vector[i].expeditor);
	}
	free(coada.vector);
}