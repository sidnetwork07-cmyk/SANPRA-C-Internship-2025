#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 2

typedef struct {
    int *data;      // pointer to the array
    int size;       // current number of elements
    int capacity;   // total allocated capacity
} DynamicArray;

void initArray(DynamicArray *arr);
void pushBack(DynamicArray *arr, int value);
void insertAt(DynamicArray *arr, int index, int value);
void deleteAt(DynamicArray *arr, int index);
int search(DynamicArray *arr, int value);
void display(DynamicArray *arr);
void resizeArray(DynamicArray *arr, int newCapacity);
void freeArray(DynamicArray *arr);

int main() {
    DynamicArray arr;
    int choice, value, index, result;

    initArray(&arr);

    do {
        printf("\n====== Dynamic Array Menu ======\n");
        printf("1. Insert at end (push back)\n");
        printf("2. Insert at a position\n");
        printf("3. Delete from a position\n");
        printf("4. Search an element\n");
        printf("5. Display array\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert at end: ");
            scanf("%d", &value);
            pushBack(&arr, value);
            break;

        case 2:
            printf("Enter index (0-based): ");
            scanf("%d", &index);
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insertAt(&arr, index, value);
            break;

        case 3:
            printf("Enter index (0-based) to delete: ");
            scanf("%d", &index);
            deleteAt(&arr, index);
            break;

        case 4:
            printf("Enter value to search: ");
            scanf("%d", &value);
            result = search(&arr, value);
            if (result == -1)
                printf("Value %d not found in array.\n", value);
            else
                printf("Value %d found at index %d.\n", value, result);
            break;

        case 5:
            display(&arr);
            break;

        case 6:
            printf("Exiting... freeing memory.\n");
            break;

        default:
            printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);

    freeArray(&arr);
    return 0;
}

void initArray(DynamicArray *arr) {
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->data = (int *)malloc(arr->capacity * sizeof(int));
    if (arr->data == NULL) {
        printf("Memory allocation failed! Exiting.\n");
        exit(1);
    }
}

void resizeArray(DynamicArray *arr, int newCapacity) {
    if (newCapacity < 1) return;

    int *temp = (int *)realloc(arr->data, newCapacity * sizeof(int));
    if (temp == NULL) {
        printf("Reallocation failed! Keeping old capacity.\n");
        return;
    }
    arr->data = temp;
    arr->capacity = newCapacity;
}

void pushBack(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        // Double the capacity
        resizeArray(arr, arr->capacity * 2);
    }
    arr->data[arr->size] = value;
    arr->size++;
    printf("Inserted %d at end. Size = %d, Capacity = %d\n",
           value, arr->size, arr->capacity);
}

void insertAt(DynamicArray *arr, int index, int value) {
    if (index < 0 || index > arr->size) {
        printf("Invalid index! Valid range: 0 to %d\n", arr->size);
        return;
    }

    if (arr->size == arr->capacity) {
        resizeArray(arr, arr->capacity * 2);
    }

    // Shift elements to right
    for (int i = arr->size - 1; i >= index; i--) {
        arr->data[i + 1] = arr->data[i];
    }

    arr->data[index] = value;
    arr->size++;

    printf("Inserted %d at index %d.\n", value, index);
}

void deleteAt(DynamicArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf("Invalid index! Valid range: 0 to %d\n", arr->size - 1);
        return;
    }

    int deletedValue = arr->data[index];

    // Shift elements to left
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;

    // Optional: shrink capacity if too empty
    if (arr->size > 0 && arr->size <= arr->capacity / 4) {
        resizeArray(arr, arr->capacity / 2);
    }

    printf("Deleted value %d from index %d. Size = %d, Capacity = %d\n",
           deletedValue, index, arr->size, arr->capacity);
}

int search(DynamicArray *arr, int value) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            return i;  // found
        }
    }
    return -1;  // not found
}

void display(DynamicArray *arr) {
    if (arr->size == 0) {
        printf("Array is empty.\n");
        return;
    }

    printf("Array elements (size = %d, capacity = %d):\n", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}
