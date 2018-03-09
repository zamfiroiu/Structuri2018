#include<iostream>

struct Telefon {
	char * marca;
	float pret;
	bool defect;
};

Telefon CitesteTelefon() {
	char buffer[30];
	printf("Marca:");
	scanf("%s", buffer);
	Telefon telefon;
	//telefon.marca = new char[strlen(buffer) + 1];
	telefon.marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(telefon.marca, buffer);
	printf("Pret:");
	scanf("%f", &telefon.pret);
	printf("Defect?");
	scanf("%d", &telefon.defect);
	return telefon;
}

void AfiseazaTelefon(Telefon tel) {
	printf("Telefonul %s costa %5.2f, %s", tel.marca, tel.pret, tel.defect ? "este defect" : "nu este defect");
}

struct Magazin {
	int nr_telefoane;
	Telefon* telefoane;
};

void CitesteMagazin(Magazin *magazin) {	
	printf("Numarul de telefoane:");
	scanf("%d", &magazin->nr_telefoane);
	magazin->telefoane = (Telefon*)malloc(magazin->nr_telefoane * sizeof(Telefon));
	for (int i = 0; i < magazin->nr_telefoane; i++)
	{
		magazin->telefoane[i] = CitesteTelefon();
	}
}

void AfiseazaMagazin(Magazin mag) {
	printf("Magazinul are %d telefoane\n", mag.nr_telefoane);
	for (int i = 0; i < mag.nr_telefoane; i++) {
		AfiseazaTelefon(mag.telefoane[i]);
		printf("\n");
	}
}

Telefon copiaza(Telefon tel) {
	Telefon t;
	t.marca = (char*)malloc((strlen(tel.marca) + 1) * sizeof(char));
	strcpy(t.marca, tel.marca);
	t.pret = tel.pret;
	t.defect = tel.defect;
	return t;
}

void main() {
	Telefon telefon;
	telefon = CitesteTelefon();
	AfiseazaTelefon(telefon);


	Magazin magazin;
	CitesteMagazin(&magazin);
	//shalow copy
	//magazin.telefoane[0] = telefon;
	
	//deepCopy
	free(magazin.telefoane[0].marca);
	magazin.telefoane[0] = copiaza(telefon);

	AfiseazaMagazin(magazin);

	for (int i = 0; i < magazin.nr_telefoane; i++)
	{
		free(magazin.telefoane[i].marca);
	}
	free(magazin.telefoane);

	free(telefon.marca);
}