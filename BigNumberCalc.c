#include <stdio.h>
#define MAX 100000

int size(char *ptr)
{
	int offset = 0;
	int count = 0;
	while (*(ptr + offset) != '\0')
	{
		++count;
		++offset;
	}
	return count;
}

void addn(char* value1, char* value2, FILE* ofp) {
	int size1 = size(value1);
	int size2 = size(value2);
	int max = 0;
	if (size1 > size2)
		max = size1;
	else
		max = size2;
	char* sum = malloc(sizeof(char)* max);
	int i = size1 - 1;
	int j = size2 - 1;
	int k = max - 1;
	int carry = 0;
	while (i >= 0 && j >= 0) {
		int s = value1[i--] - 96 + value2[j--] + carry;
		sum[k--] = s % 10 + 48;
		carry = (s > 10) ? 1 : 0;
	}
	if (i >= 0) {
		while (i >= 0) {
			int s = value1[i--] - 48 + carry;
			sum[k--] = s % 10 + 48;
			carry = (s > 10) ? 1 : 0;
		}
	}
	else if (j >= 0) {
		while (j >= 0) {
			int s = value2[j--] - 48 + carry;
			sum[k--] = s % 10 + 48;
			carry = (s > 10) ? 1 : 0;
		}
	}
	for (int i = 0; i < max - 1; i++)
		fprintf(ofp, "%c", sum[i]);
	fprintf(ofp, "%c\n", sum[max - 1]);
}

void sub(char* value1, char* value2, FILE* ofp) {
	int size1 = size(value1);
	int size2 = size(value2);
	int max = 0;
	if (size1 > size2)
		max = size1;
	else
		max = size2;
	char* sum = malloc(sizeof(char)* max);
	int i = size1 - 1;
	int j = size2 - 1;
	int k = max - 1;
	int carry = 0;
	while (i >= 0 && j >= 0) {
		int s = value1[i--] - value2[j--] - carry;
		carry = (s < 0) ? 1 : 0;
		if (s < 0)
			s += 10;
		sum[k--] = s+48;
	}
	if (i >= 0) {
		while (i >= 0) {
			int s = value1[i--] - 48 - carry;
			carry = (s < 0) ? 1 : 0;
			if (s < 0)
				s += 10;
			sum[k--] = s + 48;
		}
	}
	for (int i = 0; i < max - 1; i++)
		fprintf(ofp, "%c", sum[i]);
	fprintf(ofp, "%c\n", sum[max - 1]);
}

void abs(char* value1, FILE* ofp) {
	int size1 = size(value1);
	int size = size1 - 1;
	char* sum = malloc(sizeof(char)* (size));
	int i = size1 - 1;
	int k = size - 1;
	int carry = 0;
	while (i > 0) {
		sum[k--] = value1[i--];
	}
	for (int i = 0; i < size - 1; i++)
		fprintf(ofp, "%c", sum[i]);
	fprintf(ofp, "%c\n", sum[size - 1]);
}

void mult(char* value1, char* value2, FILE* ofp) {
	int size1 = size(value1);
	int size2 = size(value2);
	int max = size1 + size2;
	int k = max - 1;
	int carry = 0;
	char* sum = malloc(sizeof(char)* max);
	for (int i = size1 - 1; i >= 0; i--) {
		for (int j = size2 - 1; j >= 0; j--) {
			int s = (value1[i] - 48)*(value2[j] - 48) + carry;
			if (s >= 10) {
				s -= 10;
				carry = 1;
			}
			else
				carry = 0;
			sum[k--] = s + 48;
		}
	}
	sum[k--] = carry + 48;
	for (int i = 0; i < max - 1; i++)
		fprintf(ofp, "%c", sum[i]);
	fprintf(ofp, "%c\n", sum[max - 1]);
}


void calculate(FILE* ofp, char* function, char* value1, char* value2) {
	if (function[0] == 'A') {
		if (function[1] == 'D')
			addn(value1, value2, ofp);
		else if (function[1] == 'B')
			abs(value1, ofp);
	}
	else if (function[0] == 'S' && function[1] == 'U') {
		sub(value1, value2, ofp);
	}
	else if (function[0] == 'M' && function[1] == 'U') {
		mult(value1, value2, ofp);
	}
}

void main(void)
{
	FILE *ifp, *ofp;
	char *mode = "r";

	ifp = fopen("in.txt", mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in.txt!\n");
	}
	ofp = fopen("out.txt", "w");
	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", "out.txt");
	}

	char function[5];
	char value1[MAX];
	char value2[MAX];
	// TODO ABS will only take 2 inputs not 3
	while (fscanf(ifp, "%s %s %s", &function, &value1, &value2) != EOF) {
		calculate(ofp,&function,&value1,&value2);
	}
	fclose(ifp);
	fclose(ofp);
}