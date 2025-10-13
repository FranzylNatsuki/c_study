#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 13

typedef struct {
	int data;
} INFO;

typedef struct  {
	INFO elements[MAX];
	int size;
} HEAP;

void swap(INFO *structt1, INFO *structt2) {
	INFO temp = *structt1;
	*structt1 = *structt2;
	*structt2 = temp;
	return;
}

void insert_min(INFO data, HEAP *heap) {
	//temporary place for the new element
	int i = ++(heap->size);

	// example we start at i = 2

	//percolate to maintain min or max relation
	
	while(heap->elements[i/2].data > data.data) {
		// move the parent to the current spot
		heap->elements[i] = heap->elements[i/2];
		// move to the parent
		i = i/2;
	}

	// since we have the correct spot, we place it
	heap->elements[i] = data;
	return;
}

void insert_max(INFO data, HEAP *heap) {
	//temporary place for the new element
	int i = ++(heap->size);

	//percolate to maintain min or max relation
	while(heap->elements[i/2].data < data.data) {
		// move the parent to the current spot
		heap->elements[i] = heap->elements[i/2];
		// move to the parent
		i = i/2;
	}

	// since we have the correct spot, we place it
	heap->elements[i] = data;
	return;
}

void min_heapify(int i, INFO elements[], int size) { // i generally = 1
	int l, r, smaller;

	// set the current node's children

	l = 2 * i; 
	r = 2 * i + 1;

	// if l isn't bigger than the array AND if l is smaller then i
	if ((l <= size) && (elements[l].data < elements[i].data)) {
		smaller = l; // then l is the smallest
	} else {
		smaller = i; // default behaviour
	}

	// if r is smaller than i, than r is the smallest
	if ((r <= size) && (elements[r].data < elements[i].data)) { 
		smaller = r;
	}

	// if the current node isn't the smallest, swap and recurse
	if (smaller != i) {
		swap(&elements[i], &elements[smaller]);
		min_heapify(smaller, elements, size);
	}
}

void max_heapify(int i, INFO elements[], int size) {
	int l, r, larger;

	l = 2 * i;
	r = 2 * i + 1;

	// logic follows but is inverted, if L is bigger than data
	if ((l <= size) && (elements[l].data > elements[i].data)) {
		larger = l;
	} else {
		larger = i;
	}

	if ((r <= size) && (elements[r].data > elements[i].data)) {
		larger = r;
	}

	if (larger != i) {
		swap(&elements[i], &elements[larger]);
		max_heapify(larger, elements, size);
	}
}

INFO delete_Min(HEAP *heap) {
	INFO min = heap->elements[1]; // get the root

	heap->elements[1] = heap->elements[heap->size--];
	min_heapify(1, heap->elements, heap->size);

	return min;
}

INFO delete_Max(HEAP *heap) {
	INFO max = heap->elements[1]; // get the root

	heap->elements[1] = heap->elements[heap->size--];
	max_heapify(1, heap->elements, heap->size);
	
	return max;
}

void build_min_heap(HEAP *heap) {
	for (int i = heap->size / 2; i >= 1; i--) { 
		min_heapify(i, heap->elements, heap->size);
	}
}

void build_max_heap(HEAP *heap) {
	for (int i = heap->size / 2; i >= 1; i--) {
		max_heapify(i, heap->elements, heap->size);
	}
}

void init(HEAP *heap) {
	heap->elements[0].data = 0;
	heap->size = 0;
}

int main() {
    HEAP heap;
    INFO data;
    heap.size = 0;
    heap.elements[0].data = -9999; // sentinel

    printf("=== TESTING MIN-HEAP ===\n");

    // Insert elements
    int values1[] = {50, 30, 20, 15, 10, 8, 16};
    int n1 = sizeof(values1)/sizeof(values1[0]);
    for (int i = 0; i < n1; i++) {
        data.data = values1[i];
        insert_min(data, &heap);
    }

    printf("Inserted elements (Min-Heap): ");
    for (int i = 1; i <= heap.size; i++) {
        printf("%d ", heap.elements[i].data);
    }
    printf("\n");

    // Build min-heap
    build_min_heap(&heap);
    printf("After build_min_heap: ");
    for (int i = 1; i <= heap.size; i++) {
        printf("%d ", heap.elements[i].data);
    }
    printf("\n");

    // Delete min
    INFO minVal = delete_Min(&heap);
    printf("Deleted min = %d\n", minVal.data);
    printf("Heap after delete_Min: ");
    for (int i = 1; i <= heap.size; i++) {
        printf("%d ", heap.elements[i].data);
    }
    printf("\n\n");

    // Reset heap for max test
    heap.size = 0;
    heap.elements[0].data = 9999;

    printf("=== TESTING MAX-HEAP ===\n");

    int values2[] = {10, 40, 30, 60, 90, 70, 20};
    int n2 = sizeof(values2)/sizeof(values2[0]);
    for (int i = 0; i < n2; i++) {
        data.data = values2[i];
        insert_max(data, &heap);
    }

    printf("Inserted elements (Max-Heap): ");
    for (int i = 1; i <= heap.size; i++) {
        printf("%d ", heap.elements[i].data);
    }
    printf("\n");

    // Build max-heap
    build_max_heap(&heap);
    printf("After build_max_heap: ");
    for (int i = 1; i <= heap.size; i++) {
        printf("%d ", heap.elements[i].data);
    }
    printf("\n");

    // Delete max
    INFO maxVal = delete_Max(&heap);
    printf("Deleted max = %d\n", maxVal.data);
    printf("Heap after delete_Max: ");
    for (int i = 1; i <= heap.size; i++) {
        printf("%d ", heap.elements[i].data);
    }
    printf("\n");

    return 0;
}
