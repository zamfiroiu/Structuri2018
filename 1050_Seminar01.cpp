#include<iostream>

struct Inmate {
	int id;
	char* name;
	float sentence;
};

struct Prison {
	char * name;
	int nrInmates;
	Inmate * inmates;
};

Inmate readInmate() {
	Inmate inmate;
	printf("Id:");
	scanf("%d", &inmate.id);

	char buffer[20];
	printf("Name:");
	scanf("%s", buffer);
	inmate.name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(inmate.name, buffer);
	printf("Sentece:");
	scanf("%f", &inmate.sentence);

	return inmate;
}

Prison readPrison() {
	Prison prison;
	char buffer[20];
	printf("The name:");
	scanf("%s", buffer);

	//prison.name = new char[strlen(buffer) + 1];
	prison.name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(prison.name, buffer);
	printf("The number of inmates:");
	scanf("%d", &prison.nrInmates);
	prison.inmates = (Inmate*)malloc(prison.nrInmates * sizeof(Inmate));
	for (int i = 0; i < prison.nrInmates; i++) {
		prison.inmates[i] = readInmate();
	}
	return prison;
}

void printInmate(Inmate inmate) {
	printf("The inmate %s with the id: %d have %5.2f years to stay in prison\n",inmate.name, inmate.id, inmate.sentence);

}

void printPrison(Prison prison) {
	printf("Prison %s have %d inmates:\n", prison.name, prison.nrInmates);
	for (int index = 0; index < prison.nrInmates; index++) {
		printInmate(prison.inmates[index]);
	}
}

Inmate copyInmate(Inmate inmate) {
	Inmate inm;
	inm.name = (char*)malloc(sizeof(char)*(strlen(inmate.name) + 1));
	strcpy(inm.name, inmate.name);
	inm.id = inmate.id;
	inm.sentence = inmate.sentence;
	return inm;
}

float totalSentence(Prison prison) {
	float sum = 0;
	for (int i = 0; i < prison.nrInmates; i++) {
		sum += prison.inmates[i].sentence;
	}
	return sum;
}

Inmate* limitSentence(Prison prison, float limit, int *nrInamtes)
{
	Inmate* freeInmates;
	int k = 0;
	for (int i = 0; i < prison.nrInmates; i++) {
		if (prison.inmates[i].sentence <= limit) {
			k++;
		}
	}
	freeInmates = (Inmate*)malloc(k * sizeof(Inmate));
	k = 0;
	for (int i = 0; i < prison.nrInmates; i++) {
		if (prison.inmates[i].sentence <= limit) {
			freeInmates[k] = copyInmate(prison.inmates[i]);
			k++;
		}
	}
	*nrInamtes = k;
	return freeInmates;
}

void main() {
	Inmate inmate;

	inmate = readInmate();
	printInmate(inmate);

	
	Prison prison=readPrison();
	//shallow copy;
	//prison.inmates[0] = inmate;

	//deepcopy
	free(prison.inmates[0].name);
	prison.inmates[0] = copyInmate(inmate);
	printPrison(prison);

	printf("Total sentence: %5.2f\n", totalSentence(prison));

	free(prison.name);
	for (int i = 0; i < prison.nrInmates; i++) {
		free(prison.inmates[i].name);
	}
	free(prison.inmates);

	free(inmate.name);
}