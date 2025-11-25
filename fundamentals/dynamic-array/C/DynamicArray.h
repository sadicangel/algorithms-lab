//
// Created by sadic on 25/11/2025.
//

#ifndef C_DYNAMICARRAY_H
#define C_DYNAMICARRAY_H
#include <stddef.h>

typedef struct {
  size_t capacity;
  size_t length;
  int* elements;
} DynamicArray;

extern const size_t DynamicArray_INITIAL_CAPACITY;
extern const size_t DynamicArray_GROW_FACTOR;

DynamicArray* DynamicArray_Create(size_t capacity);
void DynamicArray_Destroy(DynamicArray* array);

void DynamicArray_Reserve(DynamicArray* array, size_t new_capacity);

void DynamicArray_Push(DynamicArray* array, int value);
int DynamicArray_Pop(DynamicArray* array);

void DynamicArray_InsertAt(DynamicArray* array, size_t index, int value);
int DynamicArray_RemoveAt(DynamicArray* array, size_t index);

#endif //C_DYNAMICARRAY_H