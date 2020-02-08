#include <stdio.h>
#include <stdbool.h>
#define MAX 30000

int size(char *ptr){
	int offset = 0;
	int count = 0;
	while (*(ptr + offset) != '\0')
	{
		++count;
		++offset;
	}
	return count;
}

int* convert(char* c) {
	int len=strlen(c);
	int* ret = (int*)malloc(len*sizeof(int));
	for(int i=0; i<len; i++) {
		ret[i] =c[i] -48; 
	}
	return ret;
}

char* convert_s(int* c) {
	int len = sizeof(c)/sizeof(int);
	char* ret = malloc(sizeof(char) * len);
	for(int i=0; i<len; i++) {
		ret[i] =c[i] + 48; 
	}
	return ret;
}

int positionDecimal(char* c){
	int s = size(c);
	for(int i = s-1; i>0;i--){
		if(c[i] == 46)
			return i;
	}
	return 0;
}

bool negative(char* c){
	if(c[0] == 45)
		return true;
	else 
		return false;
}

char* removeNegative(char* c){
	int s = size(c);
	char* final = malloc(sizeof(char)*(s-1));
	for(int i = 1;i<s;i++){
		final[i-1] = c[i];
	}
	final[s-2] = '/0';
	return final;
}

char* removeDecimal(char* c){

}

char* addn(char* value1, char* value2, FILE* ofp) {
	int size1 = size(value1);
	int size2 = size(value2);
	int max = 0;
	if (size1 > size2)
		max = size1;
	else
		max = size2;
	char* sum = malloc(sizeof(char)* (max+1));
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
	sum[max] ='\0';
	return sum;
}

char* sub(char* value1, char* value2, FILE* ofp) {
	int size1 = size(value1);
	int size2 = size(value2);
	int max = 0;
	if (size1 > size2)
		max = size1;
	else
		max = size2;
	char* sum = malloc(sizeof(char)* (max+1));
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
	sum[max] = '\0';
	int zeros = 0;
	for(int i = 0;i<max;i++){
		if(sum[i] != 48)
			break;
		zeros++;
	}
	char* sum2 = malloc(sizeof(char)* (max+1-zeros));
	int k1 = 0;
	for(int i = zeros;i<max;i++){
		sum2[k1++] = sum[i];
	}
	sum2[max-zeros] = '\0';
	return sum2;
}

char* abs(char* value1, FILE* ofp) {
	int size1 = size(value1);
	int size = size1 - 1;
	char* sum = malloc(sizeof(char)* (size));
	int i = size1 - 1;
	int k = size - 1;
	int carry = 0;
	while (i > 0) {
		sum[k--] = value1[i--];
	}
	sum[size] ='\0';
	return sum;
}

void shift(char* sum){
	int s = size(sum);
	char* sum2 = malloc(sizeof(char)* (s+1));
	for(int i = 0; i<s;i++){
		sum2[i] = sum[i];
	}
	sum2[s] = 0;
	sum = sum2;
}


int* mult(char* value1, char* value2, FILE* ofp) {
	int size1 = size(value1);
	int size2 = size(value2);
	int max = size1 + size2;
	int k;
	int offset = 1;
	int carry = 0;
	int* sum = (int*)malloc((max+1)*sizeof(int));
	if(size2>size1){
		char* temp = value2;
		value2 = value1;
		value1 = temp;
		int size = size2;
		size2 = size1;
		size1 = size;
	}
	for (int j = size2 - 1; j >= 0; j--) {
		carry = 0;
		k = max - offset;
		for (int i = size1 - 1; i >= 0; i--) {
			int s = (value1[i] - 48)*(value2[j] - 48) + carry;
			s = sum[k]+s;
			if (s >= 10) {
				carry = s/10;
				s = s%10;
			}
			else
				carry = 0;
			sum[k] = s;
			k--;
		}
		sum[k--] = carry;
		offset++;
	}
	sum[k--] = carry;
	for(int l = 0; l<max;l++){
		fprintf(ofp,"%d",sum[l]);
	}
	fprintf(ofp,"\n");
	return sum;
}

char* mult2(char* value1, char* value2, FILE* ofp) {
	int size1 = size(value1);
	int size2 = size(value2);
	int max = size1 + size2;
	int k;
	int offset = 1;
	int carry = 0;
	char* sum = malloc((max+1)*sizeof(char));
	if(size2>size1){
		char* temp = value2;
		value2 = value1;
		value1 = temp;
		int size = size2;
		size2 = size1;
		size1 = size;
	}
	for(int i = 0; i<max;i++){
		sum[i] = 48;
	}
	for (int j = size2 - 1; j >= 0; j--) {
		carry = 0;
		k = max - offset;
		for (int i = size1 - 1; i >= 0; i--) {
			int s = (value1[i] - 48)*(value2[j] - 48) + carry;
			s = (sum[k]-48)+s;
			if (s >= 10) {
				carry = s/10;
				s = s%10;
			}
			else
				carry = 0;
			sum[k] = s +48;
			k--;
		}
		sum[k--] = carry+48;
		offset++;
	}
	sum[k--] = carry+48;
	return sum;
}

char* sqrt(char* value1, FILE* ofp) {
	return value1;
}

bool isGreater(char* value1,char* value2){
	int size1 = size(value1);
	int size2 = size(value2);
	if(size1>size2)
		return true;
	if(size1<size2)
		return false;
	for(int i = 0;i<size1;i++){
		if(value1[i] < value2[i])
			return false;
	}
	return true;
}

bool isZero(char* value1){
	int size1 = size(value1);
	for(int i = 0;i<size1;i++){
		if(value1[i] != 48)
			return false;
	}
	return true;
}

int divide(char* value1, char* value2,FILE* ofp){
	int size1 = size(value1);
	int size2 = size(value2);
	if(size2>size1){
		char* temp = value2;
		value2 = value1;
		value1 = temp;
		int size = size2;
		size2 = size1;
		size1 = size;
	}
	int a = 0;
	while(isGreater(value1,value2) && !isZero(value1)){
		value1 = sub(value1,value2,ofp);
		a++;
	}
	return a;
}

char* power(char* value, int pow ,FILE* ofp){
	char* naya = value;
	pow--;
	while(pow--){
		naya = mult2(value,naya,ofp);
		int zeros = 0;
		int max = size(naya);
		for(int i = 0;i<max;i++){
			if(naya[i] != 48)
				break;
			zeros++;
		}
		char* sum2 = malloc(sizeof(char)* (max+1-zeros));
		int k1 = 0;
		for(int i = zeros;i<max;i++){
			sum2[k1++] = naya[i];
		}
		sum2[max-zeros] = '\0';
		naya = sum2;
	}
	return naya;
}

void calculate(FILE* ofp, char* function, char* value1, char* value2,int pow) {
	char* answer;
	if (function[0] == 'A') {
		if (function[1] == 'D'){
			answer = removeNegative(value1);
			// answer = addn(value1, value2, ofp);
		}
		else if (function[1] == 'B')
			answer = abs(value1, ofp);
		fprintf(ofp,"%s\n",answer);
	}
	else if (function[0] == 'S'){
		if (function[1] == 'U')
			answer = sub(value1, value2, ofp);
		else
			answer = sqrt(value1, ofp);
		fprintf(ofp,"%s\n",answer);
	}
	else if (function[0] == 'M' && function[1] == 'U') {
		answer = mult2(value1, value2, ofp);
		fprintf(ofp,"%s\n",answer);
	}
	else if(function[0] == 'P'){
		//fprintf(ofp, "%d\n", pow);
		answer = power(value1, pow, ofp);
		fprintf(ofp,"%s\n",answer);
	}
	else if(function[0] == 'D'){
		int ans = divide(value1,value2,ofp);
		fprintf(ofp,"%d\n",ans);
	}
}

void main(void)
{
	FILE *ifp, *ofp;
	char *mode = "r";

	ifp = fopen("inp.txt", mode);
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
	int pow;
	while (1) {
		fscanf(ifp, "%s", &function);
		if ((function[0] == 'A'&& function[1] == 'B') || (function[0] == 'S'&& function[1] == 'Q')){
					if(fscanf(ifp,"%s",&value1) == EOF)
						return;
		}
		else if((function[0] == 'P'&& function[1] == 'O')){
			if(fscanf(ifp,"%s %d",&value1,&pow) == EOF)
				break;
			// fprintf(ofp, "%s\n", value1);
		}
		else if(fscanf(ifp, "%s %s", &value1, &value2) == EOF)
			return;
		calculate(ofp,&function,&value1,&value2,pow);
	}
	fclose(ifp);
	fclose(ofp);
}
