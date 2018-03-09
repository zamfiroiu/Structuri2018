#include<iostream>


struct Library {
	char*name;
	int numberPublishingHouses;
};

Library createLibrary(char* name, int number) {
	Library library;
	library.name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	strcpy(library.name, name);
	library.numberPublishingHouses = number;
	return library;
}

void printLibrary(Library library) {
	printf("Library %s colraborates with %d Publishing houses.", library.name, library.numberPublishingHouses);
}

int getPositionOfMaximum(int* vector, int elements) {
	int maximum = vector[0];
	int position = 0;
	for (int i = 1; i < elements; i++) {
		if (maximum < vector[i]) {
			maximum = vector[i];
			position = i;
		}
	}
	return position;
}

Library* getlongestLine(Library**matrix, int*nColumns, int nLines, int*dim) {
	int position = getPositionOfMaximum(nColumns, nLines);
	*dim = nColumns[position];
	Library* result = (Library*)malloc(sizeof(Library)*(*dim));
	for (int i = 0; i < *dim; i++) {
		result[i] = createLibrary(matrix[position][i].name, matrix[position][i].numberPublishingHouses);
	}

	return result;
}

void readMatrix(Library** *m, int *nLines, int* *nColumns) {
	
	printf("Number of lines:");
	scanf("%d", nLines);
	(*m) = (Library**)malloc(sizeof(Library*)*(*nLines));
	(*nColumns) = (int*)malloc(sizeof(int)*(*nLines));

	for (int i = 0; i < (*nLines); i++) {
		printf("Number of columns for line:%d:", (i + 1));
		scanf("%d", &(*nColumns)[i]);
		(*m)[i] = (Library*)malloc(sizeof(Library)*(*nColumns)[i]);
		for (int j = 0; j < (*nColumns)[i]; j++) {
			(*m)[i][j] = createLibrary((char*)"National Library", 300 + (i*j));
		}
	}
}

void main() {

	Library**matrix;
	int nLines;
	int* nColumns;
	
	readMatrix(&matrix, &nLines, &nColumns);

	for (int i = 0; i < nLines; i++) {
		for (int j = 0; j < nColumns[i]; j++) {
			printLibrary(matrix[i][j]);
			printf("\n");
		}
		printf("\n");
	}

	int noElements = 0;
	Library* longhestLine = getlongestLine(matrix, nColumns, nLines, &noElements);

	printf("Longestline:\n");
	for (int i = 0; i < noElements; i++) {
		printLibrary(longhestLine[i]);
		printf("\n");
	}
	for (int i = 0; i < noElements; i++) {
		free(longhestLine[i].name);
	}
	free(longhestLine);


	for (int i = 0; i < nLines; i++) {
		for (int j = 0; j < nColumns[i]; j++) {
			free(matrix[i][j].name);
		}
		free(matrix[i]);
	}
	free(matrix);
	free(nColumns);

}