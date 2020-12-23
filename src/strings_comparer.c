#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sortings.h"

char** loadFile(char* fileName, int* lineCount)
{
	char** lines = malloc(sizeof(char*));
	FILE* f = fopen(fileName, "r");
	char line[MAX_INPUT_STRING_SIZE];
	int spacePos = 0;
	*lineCount = 0;

	while (!feof(f))
	{
		fgets(line, MAX_INPUT_STRING_SIZE, f);
		spacePos = strcspn(line, "\n");
		line[spacePos] = '\0';
		lines[*lineCount] = malloc(sizeof(char) * strlen(line));
		strcpy(lines[*lineCount], line);
		if (f != EOF)
			lines = realloc(lines, sizeof(char*) * (*lineCount + 2));

		(*lineCount)++;
	}

	fclose(f);
	return lines;
}

void saveToFile(char* fileName, char** lines, int size)
{
	
}

int main(int argc, char* argv[])
{
	int i, error = 0;
	int lineCount = 0;
	char** lines;
	char sortType[16];
	char inputFileName[256];
	char outputFileName[256];
	int cmp = 0;
	int stringCount;

	stringCount = atoi(argv[1]);
	strcpy(inputFileName, argv[2]);
	strcpy(outputFileName, argv[3]);
	strcpy(sortType, argv[4]);
	if (strcmp(argv[5], "asc"))
		cmp = 1;
	else
		if (strcmp(argv[5], "des"))
			cmp = 0;
		else
			error += 1;
	if (error == 0)
	{
		lines = loadFile(inputFileName, &lineCount);

		if (strcmp(sortType, "bubble") == 0)
			bubbleSort(lines, stringCount, cmp);
		if (strcmp(sortType, "insertion") == 0)
			insertionSort(lines, stringCount, cmp);
		if (strcmp(sortType, "merge") == 0)
			mergeSort(lines, stringCount, cmp);
		if (strcmp(sortType, "quick") == 0)
			quickSort(lines, stringCount, cmp);

		saveToFile(outputFileName, lines, lineCount);
	}
	else
	{
		return -1;
	}

	for (i = 0; i < lineCount; i++)
		free(lines[i]);
	free(lines);
}