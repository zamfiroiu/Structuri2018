#include<iostream>

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

void main() {
	int nLines;
	Stone**matrix;
	int* nColumns;

	printf("number of lines:");
	scanf("%d", &nLines);

	nColumns = (int*)malloc(sizeof(int)*nLines);
	matrix = (Stone**)malloc(sizeof(Stone*)*nLines);

	for (int i = 0; i < nLines; i++) {
		printf("number of columns for line:%d:",(i+1));
		scanf("%d", &nColumns[i]);

		matrix[i] = (Stone*)malloc(sizeof(Stone)*nColumns[i]);
		for (int j = 0; j < nColumns[i]; j++) {
			matrix[i][j] = createStone("Red", 10 + (i*j));
		}
	}

	for (int i = 0; i < nLines; i++) {
		for (int j = 0; j < nColumns[i]; j++) {
			printStone(matrix[i][j]);
			printf("\n");
		}
		printf("\n");
	}

	for (int i = 0; i < nLines; i++) {
		for (int j = 0; j < nColumns[i]; j++) {
			free(matrix[i][j].color);
		}
		free(matrix[i]);
	}
	free(matrix);
	free(nColumns);

}