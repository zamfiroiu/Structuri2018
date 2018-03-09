#include<iostream>

struct Pizza {
	char* denumire;
	float pret;
	int nr_ingrediente;
};

struct Meniu {
	int nrPizza;
	Pizza* vectorPizza;
};

Pizza citirePizza() {
	Pizza p;
	char buffer[20];
	printf("Denumire Pizza:");
	scanf("%s", buffer);
	//p.denumire = new char[strlen(buffer) + 1];
	p.denumire = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(p.denumire, buffer);
	printf("Pret Pizza:");
	scanf("%f", &p.pret);	
	printf("Numarul de ingrediente:");
	scanf("%d", &p.nr_ingrediente);
	return p;
}

void afisarePizza(Pizza pizza) {
	printf("Pizza %s costa %5.2f lei si are %d ingrediente\n",
		pizza.denumire, pizza.pret, pizza.nr_ingrediente);
}

Pizza copiere(Pizza pizza) {
	Pizza p;
	p.denumire = (char*)malloc(sizeof(char)*(strlen(pizza.denumire) + 1));
	strcpy(p.denumire, pizza.denumire);
	p.pret = pizza.pret;
	p.nr_ingrediente = pizza.nr_ingrediente;
	return p;
}

Pizza* pizzaIeftine(Meniu meniu, float prag, int *dim) {
	Pizza* v;
	int counter = 0;
	for (int i = 0; i < meniu.nrPizza; i++) {
		if (meniu.vectorPizza[i].pret <= prag) {
			counter++;
		}
	}
	v = (Pizza*)malloc(sizeof(Pizza)*counter);
	counter = 0;
	for (int i = 0; i < meniu.nrPizza; i++) {
		if (meniu.vectorPizza[i].pret <= prag) {
			v[counter++] = copiere(meniu.vectorPizza[i]);
		}
	}
	*dim = counter;
	return v;
}

void main() {
	Pizza pizza;
	pizza = citirePizza();
	afisarePizza(pizza);

	Meniu meniu;
	printf("Numarul de pizza:");
	scanf("%d", &meniu.nrPizza);
	meniu.vectorPizza = (Pizza*)malloc(sizeof(Pizza)*meniu.nrPizza);
	for (int i = 0; i < meniu.nrPizza; i++) {
		meniu.vectorPizza[i] = citirePizza();
	}
	//shallow copy
	//meniu.vectorPizza[0] = pizza;

	free(meniu.vectorPizza[0].denumire);
	meniu.vectorPizza[0] = copiere(pizza);

	printf("Avem %d pizza:\n", meniu.nrPizza);
	for (int i = 0; i < meniu.nrPizza; i++) {
		afisarePizza(meniu.vectorPizza[i]);
	}

	int lungime = 0;
	Pizza* vPizza = pizzaIeftine(meniu, 30, &lungime);

	for (int i = 0; i < lungime; i++) {
		free(vPizza[i].denumire);
	}
	free(vPizza);

	for (int i = 0; i < meniu.nrPizza; i++) {
		free(meniu.vectorPizza[i].denumire);
	}
	free(meniu.vectorPizza);

	free(pizza.denumire);
}