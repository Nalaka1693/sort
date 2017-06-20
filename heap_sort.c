#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

typedef struct {
	int last;
	int size;
	int *array;
} Heap;

void swap(int *, int *);
void printArray(int *, int);
void filltArray(int *, int);

Heap *heapCreate() {
	Heap *heap = (Heap *)malloc(sizeof(Heap));

	heap->last = 0;
	heap->size = SIZE;
	heap->array = (int *)malloc(sizeof(int) * heap->size);

	return heap;
}

void heapDestroy(Heap *heap) {
	free(heap->array);
	heap = NULL;
}

void heapShiftUp(Heap *heap) {
	int child = heap->last - 1;
	int parent = (heap->last - 2) / 2;

	while (heap->array[child] > heap->array[parent]) {
		swap(&heap->array[child], &heap->array[parent]);
		child = parent;
		parent = (parent - 1) / 2;
	}
}

int heapInsert(Heap *heap, int data) {
	if (heap->last >= heap->size) {
		printf("Heap is full\n");
		return -1;
	}

	heap->array[heap->last++] = data;

	if (heap->last >= 2) {
		heapShiftUp(heap);
	}

	return 0;
}

Heap *heapify(int *array, int size) {
	Heap *heap = heapCreate();

	if (size > heap->size) {
		printf("Array is larger than maximum heap size\n");
		return NULL;
	}	

	int i = 0;
	for (; i < size; i++) {
		heapInsert(heap, array[i]);
	}

	return heap;
}

void heapShiftDown(Heap *heap) {
	int parent = 0;
	int child = 2 * parent + 1;

	while (heap->array[child] > heap->array[parent] && 2 * child + 1 < heap->size) {
		swap(&heap->array[child], &heap->array[parent]);
		parent = child;
		child = 2 * child + 1;
	}
}

int heapRemove(Heap *heap, int *data) {
	if (heap->array <= 0) {
		printf("Heap is empty\n");
		return -1;
	}

	swap(&heap->array[0], &heap->array[heap->last - 1]);
	*data = heap->array[heap->last - 1];
	heap->array[heap->last - 1] = NULL;
	heap->last--;
	heapShiftDown(heap);

	return 0;
}

void heapSort(int *array, int size) {
    Heap *heap = heapify(array, size);

    while (heap->last > 1) {
		printf("Before: ");
		printArray(heap->array, SIZE);
		swap(&heap->array[heap->last - 1], &heap->array[0]);
		heap->last--;
		heapShiftDown(heap);
		printf("After: ");
		printArray(heap->array, SIZE);
    }

	*array = *heap->array;
}

int main() {
	int array[SIZE] = { 8, 10, 15, 3, 30, 55, 2, 9, 41, 16 };

	/*filltArray(array, sizeof(array)/sizeof(int));

	printf("Before heapify: \n");
	printArray(array, sizeof(array) / sizeof(int));

	Heap* heap = heapify(array, sizeof(array) / sizeof(int));
	printf("\nAfter heapify: \n");
	printArray(heap->array, sizeof(array) / sizeof(int));*/

	printf("Before sort: \n");
	printArray(array, sizeof(array) / sizeof(int));

	heapSort(array, sizeof(array) / sizeof(int));
	printf("\nAfter sort: \n");
	printArray(array, sizeof(array) / sizeof(int));
	getchar();

	return 0;
}

void swap(int *var1, int *var2) {
	int temp = *var1;
	*var1 = *var2;
	*var2 = temp;
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

