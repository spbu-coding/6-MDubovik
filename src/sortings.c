#include "sortings.h"

void bubbleSort(char** lines, int size, int cmp)
{
	int i, j;
	char tmp[MAX_INPUT_STRING_SIZE];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (strcmp(lines[j], lines[j + 1]) > 0 && cmp == 1 ||
				strcmp(lines[j], lines[j + 1]) < 0 && cmp == 0)
			{
				strcpy(tmp, lines[j]);
				strcpy(lines[j], lines[j + 1]);
				strcpy(lines[j + 1], tmp);
			}
		}
	}
}

void insertionSort(char** lines, int size, int cmp)
{
	int i, j;
	char tmp[MAX_INPUT_STRING_SIZE];
	for (i = 1; i < size; i++)
	{
		strcpy(tmp, lines[i]);
		j = i - 1;
		while (j >= 0 && (strcmp(lines[j], tmp) > 0 && cmp == 1 ||
			strcmp(lines[j], tmp) < 0 && cmp == 0))
		{
			strcpy(lines[j + 1], lines[j]);
			j--;
		}
		strcpy(lines[j + 1], tmp);
	}
}

void merge(char** lines, int left, int middle, int right, int cmp)
{
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	char** L = malloc(sizeof(char*) * n1);
	char** R = malloc(sizeof(char*) * n2);

	for (i = 0; i < n1; i++)
	{
		L[i] = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);
		strcpy(L[i], lines[left + i]);
	}
	for (i = 0; i < n2; i++)
	{
		R[i] = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);
		strcpy(R[i], lines[middle + i + 1]);
	}

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2)
	{
		if ((strcmp(L[i], R[j]) < 0 && cmp == 1 ||
			strcmp(L[i], R[j]) > 0 && cmp == 0))
		{
			strcpy(lines[k], L[i]);
			i++;
		}
		else
		{
			strcpy(lines[k], R[j]);
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		strcpy(lines[k], L[i]);
		i++;
		k++;
	}

	while (j < n2)
	{
		strcpy(lines[k], R[j]);
		j++;
		k++;
	}


	for (i = 0; i < n1; i++)
		free(L[i]);
	for (i = 0; i < n2; i++)
		free(R[i]);
	free(L);
	free(R);
}

void mSort(char** lines, int left, int right, int cmp)
{
	if (left >= right)
		return;
	int middle = (left + right - 1) / 2;
	mSort(lines, left, middle, cmp);
	mSort(lines, middle + 1, right, cmp);
	merge(lines, left, middle, right, cmp);
}

void mergeSort(char** lines, int size, int cmp)
{
	mSort(lines, 0, size - 1, cmp);
}

void quickSort(char** lines, int size, int cmp)
{
	int i, begin, end;
	char mid[MAX_INPUT_STRING_SIZE];
	char tmp[MAX_INPUT_STRING_SIZE];
	strcpy(mid, lines[size / 2]);

	if (size < 2)
		return;
	begin = 0;
	end = size - 1;
	while (begin <= end)
	{
		while ((strcmp(lines[begin], mid) < 0 && cmp == 1 ||
			strcmp(lines[begin], mid) > 0 && cmp == 0))
			begin++;
		while ((strcmp(lines[end], mid) > 0 && cmp == 1 ||
			strcmp(lines[end], mid) < 0 && cmp == 0))
			end--;
		if (begin <= end)
		{
			if (begin != end)
			{
				strcpy(tmp, lines[begin]);
				strcpy(lines[begin], lines[end]);
				strcpy(lines[end], tmp);
			}
			begin++;
			end--;
		}
	}
	quickSort(lines, end + 1, cmp);
	quickSort(lines + begin, size - begin, cmp);
	return 0;
}