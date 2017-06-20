#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void merge(int *array, int left, int right, int mid) {
	int tempArray[SIZE] = {};
	int pos = left;
	int lpos = left;
	int rpos = mid + 1;

	while (lpos <= mid && rpos <= right) {
		if (array[lpos] < array[rpos]) {
			tempArray[pos++] = array[lpos++];
		}
		else {
			tempArray[pos++] = array[rpos++];
		}
	}

	while (lpos <= mid) {
		tempArray[pos++] = array[lpos++];
	}
	while (rpos <= right) {
		tempArray[pos++] = array[rpos++];
	}

	int i = left;
	while (i <= right) {
		array[i] = tempArray[i++];
	}
}

void mergeSort(int *array, int left, int right) {
	if (left < right) {
		int mid = (left + right)/2;

		mergeSort(array, left, mid);
		mergeSort(array, mid + 1, right);

		merge(array, left, right, mid);
	}
}

void printArray(int *array, int size) {
	int i = 0;
	for (; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void filltArray(int *array, int size) {
	time_t t;
	srand((unsigned)time(&t));

	int i = 0;
	for (; i < size; i++) {
		array[i] = rand() % 100;
	}
}

int main() {
	int array[SIZE] = {};

	filltArray(array, sizeof(array)/sizeof(int));
	printf("Before sorting: \n");
	printArray(array, sizeof(array)/sizeof(int));

	mergeSort(array, 0, sizeof(array)/sizeof(int) - 1);
	printf("\nAfter sorting: \n");
	printArray(array, sizeof(array)/sizeof(int));
	getchar();

	return 0;
}
