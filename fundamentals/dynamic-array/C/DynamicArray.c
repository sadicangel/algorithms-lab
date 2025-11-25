//
// Created by sadic on 25/11/2025.
//
#include "DynamicArray.h"

#include <stdio.h>
#include <stdlib.h>

const size_t DynamicArray_INITIAL_CAPACITY = 4;
const size_t DynamicArray_GROW_FACTOR = 2;

DynamicArray* DynamicArray_Create(size_t capacity) {
    int* elements = malloc(sizeof(int) * capacity);
    if (elements == NULL) {
        fprintf(stderr, "DynamicArray_Create(): Out of memory\n");
        exit(EXIT_FAILURE);
    }

    DynamicArray* array = malloc(sizeof(DynamicArray));
    if (array == NULL) {
        fprintf(stderr, "DynamicArray_Create(): Out of memory\n");
        exit(EXIT_FAILURE);
    }

    array->capacity = capacity;
    array->length = capacity;
    array->elements = elements;

    return array;
}

void DynamicArray_Destroy(DynamicArray* array) {
    free(array->elements);
    free(array);
}

void DynamicArray_Reserve(DynamicArray* array, const size_t new_capacity) {
    if (array->capacity >= new_capacity) {
        return;
    }

    array->capacity = new_capacity;

    int* elements = realloc(array->elements, sizeof(int) * array->capacity);
    if (elements == NULL) {
        fprintf(stderr, "DynamicArray_Reserve(): realloc failed\n");
        exit(EXIT_FAILURE);
    }
    array->elements = elements;
}

void DynamicArray_Push(DynamicArray* array, const int value) {
    if (array->length >= array->capacity) {
        DynamicArray_Reserve(array, array->capacity * DynamicArray_GROW_FACTOR);
    }
    array->elements[array->length] = value;
    array->length++;
}

int DynamicArray_Pop(DynamicArray* array) {
    if (array->length == 0) {
        fprintf(stderr, "DynamicArray_Pop(): array is empty\n");
        exit(EXIT_FAILURE);
    }

    array->length--;
    return array->elements[array->length];
}

void DynamicArray_InsertAt(DynamicArray* array, const size_t index, const int value) {
    if (index >= array->length) {
        fprintf(stderr, "DynamicArray_InsertAt(): index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    if (array->length + 1 >= array->capacity) {
        DynamicArray_Reserve(array, array->capacity * DynamicArray_GROW_FACTOR);
    }

    for (size_t i = index; i < array->length; ++i) {
        array->elements[i + 1] = array->elements[i];
    }

    array->elements[index] = value;
    array->length++;
}

int DynamicArray_RemoveAt(DynamicArray* array, const size_t index) {
    if (index >= array->length) {
        fprintf(stderr, "DynamicArray_RemoveAt(): index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    const int value = array->elements[index];

    for (size_t i = index; i < array->length - 1; ++i) {
        array->elements[i] = array->elements[i + 1];
    }

    array->length--;

    return value;
}