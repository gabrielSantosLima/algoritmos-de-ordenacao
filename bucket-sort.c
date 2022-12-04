#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <inttypes.h>

#define false 0
#define true 1

typedef int bool;

// ==================== Array ====================
typedef struct ARRAY
{
    int lenght;
    int maxLength;
    double *data;
} ARRAY;

ARRAY *newArray(int maxLength)
{
    ARRAY *newArray = (ARRAY *)malloc(sizeof(ARRAY));
    newArray->lenght = 0;
    newArray->maxLength = maxLength;
    newArray->data = (double *)malloc(sizeof(double) * maxLength);
    return newArray;
}

bool isEmpty(ARRAY *array)
{
    return array == NULL ||
           (array != NULL && array->lenght == 0);
}

bool isFull(ARRAY *array)
{
    return array == NULL ||
           (array != NULL && array->lenght == array->maxLength);
}

void add(ARRAY *array, double value)
{
    if (isFull(array))
        return;
    array->data[array->lenght] = value;
    array->lenght++;
}

void printArray(ARRAY *array)
{
    if (isEmpty(array))
        return;
    for (int index = 0; index < array->lenght; index++)
        printf("%f ", array->data[index]);
}

ARRAY *concat(ARRAY *arrays[], int maxLength)
{
    ARRAY *array = newArray(maxLength);
    for (int index = 0; index < maxLength; index++)
    {
        for (int elementIndex = 0; elementIndex < arrays[index]->lenght; elementIndex++)
        {
            add(array, arrays[index]->data[elementIndex]);
        }
    }
    return array;
}
// =====================================================

// ==================== Linked List ====================
typedef struct NODE
{
    double value;
    struct NODE *nextNode;
} NODE;

typedef struct LIST
{
    int length;
    NODE *data;
} LIST;

LIST *newList()
{
    LIST *newList = (LIST *)malloc(sizeof(LIST));
    newList->data = NULL;
    newList->length = 0;
    return newList;
}

NODE *createNode(double value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->value = value;
    newNode->nextNode = NULL;
    return newNode;
}

void push(LIST *list, double value)
{
    if (list == NULL)
        return;
    if (list->length == 0)
    {
        list->data = createNode(value);
        list->length++;
        return;
    }
    NODE *auxNode = list->data;
    while (auxNode->nextNode != NULL)
        auxNode = auxNode->nextNode;
    auxNode->nextNode = createNode(value);
    list->length++;
}

void printList(LIST *list)
{
    if (list == NULL || (list != NULL && list->length == 0))
    {
        printf("Lista vazia");
        return;
    }
    NODE *node = list->data;
    while (node != NULL)
    {
        printf("%f ", node->value);
        node = node->nextNode;
    }
}

// =====================================================

/* ==================== Bucket Sort ==================== */
ARRAY *listToArray(LIST *list)
{
    if (list == NULL)
        return NULL;
    ARRAY *array = newArray(list->length);
    NODE *auxNode = list->data;
    while (auxNode != NULL)
    {
        add(array, auxNode->value);
        auxNode = auxNode->nextNode;
    }
    return array;
}

void insertionSort(ARRAY *array)
{
    if (isEmpty(array) || (!isEmpty(array) && array->lenght == 1))
        return;
    for (int index = 1; index < array->lenght; index++)
    {
        double key = array->data[index];
        int i = index - 1;
        while (i >= 0 && array->data[i] > key)
        {
            array->data[i + 1] = array->data[i];
            i = i - 1;
        }
        array->data[i + 1] = key;
    }
}

void bucketSort(ARRAY *array, int maxLength)
{
    LIST *buckets[maxLength];
    for (int index = 0; index < maxLength; index++)
        buckets[index] = newList();
    for (int index = 0; index < maxLength; index++)
    {
        int position = floor(maxLength * array->data[index]);
        push(buckets[position], array->data[index]);
    }
    ARRAY *bucketsAsArray[maxLength];
    for (int index = 0; index < maxLength; index++)
    {
        ARRAY *bucketAsArray = listToArray(buckets[index]);
        insertionSort(bucketAsArray);
        bucketsAsArray[index] = bucketAsArray;
    }
    ARRAY *sortedArray = concat(bucketsAsArray, maxLength);
    for (int index = 0; index < sortedArray->lenght; index++)
        array->data[index] = sortedArray->data[index];
}
// =====================================================

/* ==================== Utilidades ==================== */
void printTitle(char *text)
{
    char *divisor = "==================";
    printf("\n%s ", divisor);
    printf(text);
    printf(" %s\n", divisor);
}

void printTime(double seconds)
{
    printf("\nFinalizado em %.2f segundos.\n", seconds);
}

typedef clock_t timestamp;

timestamp getTime()
{
    return clock();
}

double calcTime(timestamp start, timestamp end)
{
    return ((double)end - start) / CLOCKS_PER_SEC;
}

void countTimeOf(void (*fn)())
{
    timestamp start = getTime();
    fn();
    timestamp end = getTime();
    printTime(calcTime(start, end));
}

// 0 -> 0.0
// 11 (11/10 = 1) -> 0.11
// 101 (101/10 = 10) -> 0.101
// 1001 (1001/10 = 100) -> 0.1001
// 10001 (10001/10 = 1000) -> 0.10001
// 100001 (100001/10 = 10000) -> 0.100001
double getDecimalUnits(double value, int decimal)
{
    if (value < 10)
        return pow(10, decimal);
    return getDecimalUnits(value / 10, decimal + 1);
}
// =====================================================

/* ==================== Requisitos para o código ==================== */
/* Codificação e avaliação com 100000 números:
- Vetor totalmente ordenado decrescentemente;
- Vetor totalmente ordenado crescentemente;
- Primeira metade ordenada crescente, segunda metade ordenada decrescentemente;
- Primeira metade ordenada decrescente, segunda metade ordenada crescentemente;
- Elementos totalmente desordenados.
*/

void testDecrescentNumbers()
{
    ARRAY *array = newArray(100000);
    for (int index = 100000; index > 0; index--)
        add(array, index / getDecimalUnits(index, 1));
    bucketSort(array, array->maxLength);
    // printArray(array); // Remover este comentário para ver a saída
}

void testCrescentNumbers()
{
    ARRAY *array = newArray(100000);
    for (int index = 1; index <= 100000; index++)
        add(array, index / getDecimalUnits(index, 1));
    bucketSort(array, array->maxLength);
    // printArray(array); // Remover este comentário para ver a saída
}

void testCrescentDecrescentNumbers()
{
    ARRAY *array = newArray(100000);
    for (int index = 1; index <= 50000; index++)
        add(array, index / getDecimalUnits(index, 1));
    for (int index = 100000; index >= 50001; index--)
        add(array, index / getDecimalUnits(index, 1));
    bucketSort(array, array->maxLength);
    // printArray(array); // Remover este comentário para ver a saída
}

void testDecrescentCrescentNumbers()
{
    ARRAY *array = newArray(100000);
    for (int index = 50000; index >= 1; index--)
        add(array, index / getDecimalUnits(index, 1));
    for (int index = 50001; index <= 100000; index++)
        add(array, index / getDecimalUnits(index, 1));
    bucketSort(array, array->maxLength);
    // printArray(array); // Remover este comentário para ver a saída
}

void testRandomNumbers()
{
    ARRAY *array = newArray(100000);
    for (int index = 0; index < 100000; index++)
    {
        uint64_t sortedNumber;
        sortedNumber = rand();
        sortedNumber = (sortedNumber << 32) | rand();
        sortedNumber = (sortedNumber % (999999999 - 100000000)) + 100000000;

        int number = sortedNumber % 100001;
        add(array, number / getDecimalUnits(number, 1));
    }
    bucketSort(array, array->maxLength);
    // printArray(array) // Remover este comentário para ver a saída
}

int main()
{
    printTitle("Números Decrescentes");
    countTimeOf(testDecrescentNumbers);

    printTitle("Números Crescentes");
    countTimeOf(testCrescentNumbers);

    printTitle("Números Crescente-Decrescente");
    countTimeOf(testCrescentDecrescentNumbers);

    printTitle("Números Decrescente-Crescente");
    countTimeOf(testDecrescentCrescentNumbers);

    printTitle("Números Aleatórios");
    countTimeOf(testRandomNumbers);
    return 0;
}