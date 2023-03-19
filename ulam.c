#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrime(int n);
void createDirection(char *direction, int size);
void showMatrix(int size, int matrix[size][size], char primes);
int getDigitCount(int n);
void createMatrix(int size, int matrix[size][size]);


int main(void){
	int size;
	printf("Specify an odd spiral edge size (25 recommended): ");
	scanf("%d", &size);
	// correction if number is odd or less than 3
	if (size < 3) { size = 3; }
	if (size%2 == 0) { size++; }
	char prime;
	while (prime != 'y' && prime != 'Y' && prime != 'n' && prime != 'N'){
		printf("\rShow ONLY prime numbers? Y/N: ");
		prime = getchar();
	}
	// initialize
	int matrix[size][size];
	createMatrix(size, matrix);
	showMatrix(size, matrix, prime);
}

void createDirection(char *direction, int size)
{
    // generator of directions. Return string where every single char define where spiral shoud go(r- right, u- up etc.)
	int count = 1;
	int idx = 0;
	int totalSize = (size*size);
	char direct = 'r';
	while (idx < totalSize-1){
		for (int i=0; i<2; i++){
			for (int j=0; j<count; j++){
				if (idx > totalSize-1 ) { break; }
				direction[idx] = direct;
				idx++;
			}
			if (direct == 'r') { direct = 'u'; }
			else if (direct == 'u') { direct = 'l'; }
			else if (direct == 'l') { direct = 'd'; }
			else if (direct == 'd') { direct = 'r'; }
		}
		count++;
	}
	direction[totalSize] = '\0';

}


void showMatrix(int size, int matrix[size][size], char primes){
	int maxLenght = getDigitCount(size*size);
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			for (int k=0; k<maxLenght-getDigitCount(matrix[i][j]); k++){
				printf(" ");
			}
            if (isPrime(matrix[i][j])){
                printf("%i ", matrix[i][j]);
            }
            else if (primes == 'y' || primes == 'Y'){
                for (int k=0; k<getDigitCount(matrix[i][j])+1; k++){
                    printf(" ");
                }
            }
            else{
                printf("%i ", matrix[i][j]);
            }
        }
		printf("\n");
    }
}


int getDigitCount(int n){
	// return count of digits. For example for 1000 it will be 4
	int count = 0;
	while (n != 0){
		n /= 10;
		count++;
	}
	return count;
}

void createMatrix(int size, int matrix[size][size]){
	int width = size/2;
	int height = size/2;
	char *direction = malloc(sizeof(char) * (size*size));
	createDirection(direction, size);
	
	for (int i=0; direction[i] != '\0'; i++){
		matrix[height][width] = i+1;
		if (direction[i] == 'r') { width++; }
		else if (direction[i] == 'u') { height--; }
		else if (direction[i] == 'l') { width--; }
		else if (direction[i] == 'd') { height++; }
	}
	free(direction);
}

bool isPrime(int n){
    if (n == 2) { return true; }
    if (n != 2 && n % 2 == 0) { return false; }
    if (n < 2) { return false; }
    for (int i=3; i<n/2; i+=2){
        if (n % i == 0) { return false; }
    }

    return true;
}
