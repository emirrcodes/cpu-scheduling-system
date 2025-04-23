#include <stddef.h>
#include "../include/min_heap.h"
#include "../include/process.h"

int compare_vruntime(const void* a, const void* b) {
    const Process* p1 = (const Process*)a;
    const Process* p2 = (const Process*)b;

    if (p1->vruntime < p2->vruntime) return -1; // p1 is smallet
    if (p1->vruntime > p2->vruntime) return 1;  // p1 is greater
    return 0;                                   // equal
}

MinHeap* heap_create(size_t capacity, size_t element_size, int (*compare)(const void*, const void*)){
    MinHeap* new_heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (new_heap == NULL)
    {
        return NULL;
    }
    
    new_heap->capacity = capacity;
    new_heap->element_size = element_size;
    new_heap->size = 0;
    new_heap->data = malloc(capacity * element_size);
    if (new_heap->data == NULL) {
        free(new_heap);
        return NULL;
    }
    
    new_heap->compare = compare;

    return new_heap;
}

void heap_destroy(MinHeap* heap){
    free(heap->data);
    heap->data = NULL;
    free(heap);
}

int heap_insert(MinHeap* heap, const void* element){
    if(heap == NULL){
        return 0;
    }
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        void* new_data = realloc(heap->data, heap->capacity * heap->element_size);
        if (new_data == NULL) {
            return 0;
        }
        heap->data = new_data;
    }
    memcpy((char*)heap->data + heap->element_size * heap->size, element, heap->element_size);
    heap->size++;

    heapify_up(heap, heap->size - 1);
    return 1;
}

int heap_extract_min(MinHeap* heap, void* result){
    if(heap == NULL || heap->size <= 0){
        return 0;
    }

    memcpy(result, heap->data, heap->element_size);
    memcpy(heap->data, (char*)heap->data + heap->element_size * (heap->size - 1), heap->element_size);

    heap->size--;
    heapify_down(heap);

    return 1;
}

int heap_peek(const MinHeap* heap, void* result){
    if(heap == NULL || heap->size <= 0){
        return 0;
    }

    memcpy(result, heap->data, heap->element_size);

    return 1;
}

size_t heap_size(const MinHeap* heap){
    if (heap == NULL) {
        return 0;
    }
    return heap->size;
}

int heap_merge(MinHeap* heap1, const MinHeap* heap2){
    if(heap2->size == 0) return 1;

    if(heap1->element_size != heap2->element_size) return 0;
    
    while(heap1->capacity <= heap1->size + heap2->size){
        heap1->capacity *= 2;
        void* new_data = realloc(heap1->data, heap1->capacity * heap1->element_size);
        if (new_data == NULL) {
            return 0;
        }
        heap1->data = new_data;
    }

    for(size_t i = 0; i < heap2->size; i++){
        void* element = (char*)heap2->data + i * heap2->element_size;
        if(!heap_insert(heap1, element)){
            return 0;
        }
    }

    return 1;
}

void swap(void* a, void* b, size_t size){
    void* temp = malloc(size);
    if(temp == NULL){
        return;
    }
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);

    free(temp);
}

void heapify_up(MinHeap* heap, size_t index){
    while (index > 0){
        size_t parent_index = (index - 1)/2;
        if(heap->compare(
                (char*)heap->data + parent_index * heap->element_size,
                (char*)heap->data + index * heap->element_size) <= 0){
            break;
        }
        swap((char*)heap->data + parent_index * heap->element_size,
            (char*)heap->data + index * heap->element_size,
            heap->element_size
        );
        index = parent_index;
    }
}

void heapify_down(MinHeap* heap){
    int index = 0;
    while(index < heap->size){
        size_t left_child = index*2 + 1;
        size_t right_child = index*2 + 2;
        size_t child_min;

        if (left_child >= heap->size) {
            break;
        }
        if (right_child >= heap->size) {
            child_min = left_child;
        }else{
            if(heap->compare(
            (char*)heap->data + left_child * heap->element_size,
            (char*)heap->data + right_child * heap->element_size) <= 0){
                child_min = left_child;
            }else{
                child_min = right_child;
            }
        }

        if (heap->compare(
                (char*)heap->data + index * heap->element_size,
                (char*)heap->data + child_min * heap->element_size) <= 0) {
            break;
        }

        swap((char*)heap->data + index * heap->element_size,
            (char*)heap->data + child_min * heap->element_size,
            heap->element_size
        );

        index = child_min;
    }
}