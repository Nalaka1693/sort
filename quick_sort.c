#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000

void swap(int *var1, int *var2) {
	int temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

void choosePivot(int *array, int first, int last) {
	int middle = (first + last) / 2;

	if (array[first] < array[last]) {
		if (array[first] < array[middle] && array[middle] < array[last]) {
			swap(&array[first], &array[middle]);
		}
	}
	else {
		if (array[last] < array[middle] && array[middle] < array[first]) {
			swap(&array[first], &array[middle]);
		}
		else {
			swap(&array[first], &array[last]);
		}
	}
}

void partition(int *array, int first, int last, int *pivot) {
	choosePivot(array, first, last);

	*pivot = array[first];

	int last_sort = first;
	int unknown = first + 1;

	for (; unknown <= last; unknown++) {
		if (array[unknown] < *pivot) {
			last_sort++;
			swap(&array[unknown], &array[last_sort]);
		}
	}

	swap(&array[first], &array[last_sort]);
	*pivot = last_sort;
}

void quickSort(int *array, int first, int last) {
	int pivot_index;
	
	if (first < last) {
		partition(array, first, last, &pivot_index);
		quickSort(array, first, pivot_index - 1);
		quickSort(array, pivot_index + 1, last);
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
		 array[i] = rand() % 65535;
	}
}

int main() {
	int array[SIZE] = {};
	clock_t t1, t2;

	filltArray(array, sizeof(array) / sizeof(int));
	printf("Before sorting: \n");
	//printArray(array, sizeof(array)/sizeof(int));
	t1 = clock();
	quickSort(array, 0, sizeof(array) / sizeof(int)-1);
	t2 = clock();
	printf("\nAfter sorting: \n");
	//printArray(array, sizeof(array) / sizeof(int));

	float diff = ((float)(t2 - t1) / 1000000.0F ) * 1000;   
    printf("Time taken = %f",diff); 

	// #include <sys/time.h>

	// struct timeval stop, start;
	// gettimeofday(&start, NULL);
	// //do stuff
	// gettimeofday(&stop, NULL);
	// printf("took %lu\n", stop.tv_usec - start.tv_usec);

	return 0;
}

