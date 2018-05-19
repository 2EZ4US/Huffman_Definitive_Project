#ifndef HEAP_AHRT
#define HEAP_AHRT

typedef struct HEAP {
    GENERIC *array;
    INTEGER size;
} HEAP;

GENERIC HEAP_Create() {
    HEAP *new_heap = (HEAP*) malloc(sizeof(HEAP));
    new_heap->array = (GENERIC*) calloc(MAX_HEAP_SIZE, sizeof(GENERIC));
    new_heap->size = 0;
    return new_heap;
}

INTEGER HEAP_Get_Parent(INTEGER index) {
    return (index >> 1);
}

INTEGER HEAP_Get_Left_Child(INTEGER index) {
    return (index << 1);
}

INTEGER HEAP_Get_Right_Child(INTEGER index) {
    return ((index << 1) + 1);
}

void HEAP_Swap(HEAP *heap, INTEGER first_index, INTEGER second_index) {
    GENERIC aux = heap->array[first_index];
    heap->array[first_index] = heap->array[second_index];
    heap->array[second_index] = aux;
    return;
}

void HEAP_Enqueue(HEAP *heap, GENERIC data, bool (*Lambda)()) {
    heap->array[++heap->size] = data;
    INTEGER current = heap->size;
    INTEGER parent = HEAP_Get_Parent(current);

    while(parent >= 1 && Lambda(heap->array[current], heap->array[parent])) {
        HEAP_Swap(heap, current, parent);
        current = parent;
        parent = HEAP_Get_Parent(current);
    }
    return;
}

void HEAP_Heapify(HEAP *heap, INTEGER index, bool (*Lambda)()) {
    INTEGER least = index;
    INTEGER left = HEAP_Get_Left_Child(index);
    INTEGER right = HEAP_Get_Right_Child(index);

    if(left <= heap->size) {
        if(Lambda(heap->array[least], heap->array[left])) {
            least = left;
        }
    }
    if(right <= heap->size) {
        if(Lambda(heap->array[least], heap->array[right])) {
            least = right;
        }
    }
    if(least != index) {
        HEAP_Swap(heap, index, least);
        HEAP_Heapify(heap, least, Lambda);
    }
    return;
}

GENERIC HEAP_Dequeue(HEAP *heap, bool (*Lambda)()) {
    GENERIC save_first = heap->array[1];
    HEAP_Swap(heap, 1, heap->size--);
    HEAP_Heapify(heap, 1, Lambda);
    return save_first;
}

#endif