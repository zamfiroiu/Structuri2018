#include<iostream>
#pragma warning(disable:4996)

//prioritizare

struct Stone {
	float weight;
	char* color;
};

Stone createStone(char* color, float weight) {
	Stone stone;
	stone.weight = weight;
	stone.color = (char*)malloc(sizeof(char)*(strlen(color) + 1));
	strcpy(stone.color, color);
	return stone;
}

void printStone(Stone stone) {
	printf("The stone has the color %s and %5.2f kg", stone.color, stone.weight);
}

void readMatrix(int *nLines, int* *nColumns, Stone** *matrix) {
	printf("number of lines:");
	scanf("%d", nLines);

	*nColumns = (int*)malloc(sizeof(int)*(*nLines));
	*matrix = (Stone**)malloc(sizeof(Stone*)*(*nLines));
	
	for (int i = 0; i < *nLines; i++) {
		printf("number of columns for line:%d:", (i + 1));
		scanf("%d", &(*nColumns)[i]);

		(*matrix)[i] = (Stone*)malloc(sizeof(Stone)*(*nColumns)[i]);
		for (int j = 0; j < (*nColumns)[i]; j++) {
			(*matrix)[i][j] = createStone("Red", 10 + (i*j));
		}
	}
}

int getPositionOfMaximum(int* vector, int nr) {
	int maxim = vector[0];
	int position = 0;
	for (int i = 1; i < nr; i++) {
		if (vector[i] > maxim) {
			maxim = vector[i];
			position = i;
		}
	}
	return position;
}

Stone* getLongestLine(int nLines, int* nColumns, Stone** matrix, int *dimesion) {
	int position = getPositionOfMaximum(nColumns, nLines);
	int noElements = nColumns[position];
	Stone* result = (Stone*)malloc(sizeof(Stone)*noElements);
	for (int i = 0; i < noElements; i++) {
		result[i] = createStone(matrix[position][i].color, matrix[position][i].weight);
	}
	*dimesion = noElements;
	return result;
}

void main() {
	int nLines;
	Stone**matrix;
	int* nColumns;
	
	readMatrix(&nLines, &nColumns, &matrix);

	for (int i = 0; i < nLines; i++) {
		for (int j = 0; j < nColumns[i]; j++) {
			printStone(matrix[i][j]);
			printf("\n");
		}
		printf("\n");
	}

	int noElements = 0;
	Stone* longestLine = getLongestLine(nLines, nColumns, matrix, &noElements);

	for (int i = 0; i < noElements; i++) {
		printStone(longestLine[i]);
		printf("\n");
	}

	for (int i = 0; i < noElements; i++) {
		free(longestLine[i].color);
	}
	free(longestLine);


	for (int i = 0; i < nLines; i++) {
		for (int j = 0; j < nColumns[i]; j++) {
			free(matrix[i][j].color);
		}
		free(matrix[i]);
	}
	free(matrix);
	free(nColumns);

}