#include <stdio.h>
#include "DynamicArray.h"

static void PrintArray(const char* label, const DynamicArray* array)
{
    printf("%s [len=%zu, cap=%zu]: ", label, array->length, array->capacity);
    for (size_t i = 0; i < array->length; i++) {
        printf("%d ", array->elements[i]);
    }
    printf("\n");
}

static void TestStack(void)
{
    printf("=== STACK TEST ===\n");

    DynamicArray* stack = DynamicArray_Create(DynamicArray_INITIAL_CAPACITY);

    // Push some values
    for (int i = 1; i <= 5; i++) {
        DynamicArray_Push(stack, i);
        PrintArray("After push", stack);
    }

    // Pop all values
    while (stack->length > 0) {
        int value = DynamicArray_Pop(stack);
        printf("Popped: %d\n", value);
        PrintArray("After pop", stack);
    }

    DynamicArray_Destroy(stack);
    printf("\n");
}

static void TestQueue(void)
{
    printf("=== QUEUE TEST ===\n");

    DynamicArray* queue = DynamicArray_Create(DynamicArray_INITIAL_CAPACITY);

    // Enqueue some values (push at end)
    for (int i = 10; i <= 50; i += 10) {
        DynamicArray_Push(queue, i);
        PrintArray("After enqueue", queue);
    }

    // Dequeue a couple of values (remove at index 0)
    while (queue->length > 0) {
        int value = DynamicArray_RemoveAt(queue, 0);
        printf("Dequeued: %d\n", value);
        PrintArray("After dequeue", queue);
    }

    DynamicArray_Destroy(queue);
    printf("\n");
}

static void TestInsertRemoveAt(void)
{
    printf("=== INSERT/REMOVE TEST ===\n");

    DynamicArray* arr = DynamicArray_Create(DynamicArray_INITIAL_CAPACITY);

    // Fill with some base values
    for (int i = 0; i < 5; i++) {
        DynamicArray_Push(arr, i * 10);  // 0, 10, 20, 30, 40
    }
    PrintArray("Initial", arr);

    // Insert in the middle
    DynamicArray_InsertAt(arr, 2, 999);  // at index 2
    PrintArray("After insert at index 2", arr);

    // Remove that element
    int removed = DynamicArray_RemoveAt(arr, 2);
    printf("Removed at index 2: %d\n", removed);
    PrintArray("After remove at index 2", arr);

    DynamicArray_Destroy(arr);
    printf("\n");
}

int main(void)
{
    TestStack();
    TestQueue();
    TestInsertRemoveAt();

    return 0;
}
