#include<iostream>

struct InstrumentMuzical {
	char* denumire;
	float greutate;
	int intensitate;
};

struct Formatie {
	int nrInstrumente;
	InstrumentMuzical * instrumente;
};


InstrumentMuzical* instrumenteUsoare(float prag, Formatie f,int* dim)
{
	InstrumentMuzical* v;
	int k = 0;
	for (int i = 0; i < f.nrInstrumente; i++) {
		if (f.instrumente[i].greutate <= prag) {
			k++;
		}
	}
	v = (InstrumentMuzical*)malloc(sizeof(InstrumentMuzical)*k);
	k = 0;
	for (int i = 0; i < f.nrInstrumente; i++) {
		if (f.instrumente[i].greutate <= prag) {
			//shallow copy
			//v[k++] = f.instrumente[i];
			
			//deepcopy
			v[k].denumire = (char*)malloc(sizeof(char)*(strlen(f.instrumente[i].denumire) + 1));
			strcpy(v[k].denumire, f.instrumente[i].denumire);
			v[k].greutate = f.instrumente[i].greutate;
			v[k].intensitate = f.instrumente[i].intensitate;
			k++;
		}
	}
	*dim = k;
	return v;
}

void citireInstrument(InstrumentMuzical * im) {
	printf("Denumire:");
	char buffer[20];
	scanf("%s", buffer);
	//im->denumire = new char[strlen(buffer) + 1];
	im->denumire = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(im->denumire, buffer);
	printf("Greutate:");
	scanf("%f", &im->greutate);
	printf("Intensitate:");
	scanf("%d", &im->intensitate);
}

Formatie citireFormatie() {
	Formatie f;

	printf("Numarul instrumente:");
	scanf("%d", &f.nrInstrumente);
	f.instrumente = (InstrumentMuzical*)malloc(sizeof(InstrumentMuzical)*f.nrInstrumente);
	for (int i = 0; i < f.nrInstrumente; i++) {
		citireInstrument(&f.instrumente[i]);
	}

	return f;
}

void afisareInstrument(InstrumentMuzical im) {
	printf("Instrumentul muzical %s are o greutate de %5.2f kg si o intensitate de %d dB\n",
		im.denumire, im.greutate, im.intensitate);
}

void afisareFormatie(Formatie f) {
	printf("Formatia are %d instrumente:\n",f.nrInstrumente);
	for (int i = 0; i < f.nrInstrumente; i++) {
		afisareInstrument(f.instrumente[i]);
	}
}

void main() {
	InstrumentMuzical im;
	citireInstrument(&im);
	afisareInstrument(im);
	Formatie f = citireFormatie();
	afisareFormatie(f);

	int dimensiune = 0;
	InstrumentMuzical* vector = instrumenteUsoare(3, f, &dimensiune);



	for (int i = 0; i < f.nrInstrumente; i++) {
		free(f.instrumente[i].denumire);
	}
	free(f.instrumente);
	
	free(im.denumire);
}