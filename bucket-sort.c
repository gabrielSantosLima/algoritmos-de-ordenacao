/* ==================== Bucket Sort ==================== */
/* ==================== Requisitos para o código ==================== */
/* Codificação e avaliação com 100000 números:
- Vetor totalmente ordenado decrescentemente;
- Vetor totalmente ordenado crescentemente;
- Primeira metade ordenada crescente, segunda metade ordenada decrescentemente;
- Primeira metade ordenada decrescente, segunda metade ordenada crescentemente;
- Elementos totalmente desordenados.
*/

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
    int length;   // Tamanho atual do vetor
    int size;     // Tamanho máximo do vetor
    double *data; // Primeiro elemento do vetor
} ARRAY;

// Cria um novo vetor (ARRAY*)
ARRAY *new_array(int size)
{
    ARRAY *narray = (ARRAY *)malloc(sizeof(ARRAY));
    narray->length = 0;
    narray->size = size;
    narray->data = (double *)malloc(sizeof(double) * size); // Aloca um vetor de double de tamanho sizeof(double) * size
    return narray;
}

// Verifica se vetor está vazio
bool is_empty(ARRAY *array)
{
    return array == NULL ||
           (array != NULL && array->length == 0);
}

// Verifica se vetor está cheio
bool is_full(ARRAY *array)
{
    return array == NULL ||
           (array != NULL && array->length == array->size);
}

// Adiciona um elemento em um vetor
void add(ARRAY *array, double value)
{
    if (is_full(array))
        return;
    array->data[array->length] = value;
    array->length++;
}

// Exibe os elementos de uma vetor
void print_array(ARRAY *array)
{
    if (is_empty(array))
        return;
    for (int index = 0; index < array->length; index++)
        printf("%f ", array->data[index]);
}

// Concatena uma lista de vetores para um único vetor
ARRAY *concat(ARRAY *arrays[], int size)
{
    ARRAY *array = new_array(size);
    for (int index = 0; index < size; index++)
    {
        for (int element_index = 0; element_index < arrays[index]->length; element_index++)
            add(array, arrays[index]->data[element_index]);
    }
    return array;
}
// =====================================================

// ==================== Linked List ====================
typedef struct NODE
{
    double value;           // Valor do nó
    struct NODE *next_node; // NODE* que aponta para próximo nó da lista
} NODE;

typedef struct LIST
{
    int length; // Tamanho atual da lista
    NODE *data; // Primeiro elemento da lista
} LIST;

// Cria uma nova lista (LIST*)
LIST *new_list()
{
    LIST *nlist = (LIST *)malloc(sizeof(LIST));
    nlist->data = NULL;
    nlist->length = 0;
    return nlist;
}

// Cria um novo nó (NODE*)
NODE *create_node(double value)
{
    NODE *nnode = (NODE *)malloc(sizeof(NODE));
    nnode->value = value;
    nnode->next_node = NULL;
    return nnode;
}

// Adiciona um elemento em uma lista
void push(LIST *list, double value)
{
    if (list == NULL)
        return;
    if (list->length == 0)
    {
        list->data = create_node(value);
        list->length++;
        return;
    }
    NODE *auxNode = list->data;
    while (auxNode->next_node != NULL)
        auxNode = auxNode->next_node;
    auxNode->next_node = create_node(value);
    list->length++;
}

// Exibe os elementos de uma lista
void print_list(LIST *list)
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
        node = node->next_node;
    }
}

// =====================================================

/* ==================== Bucket Sort ==================== */
// Transforma uma lista em um vetor
ARRAY *list_2_array(LIST *list)
{
    if (list == NULL)
        return NULL;
    ARRAY *array = new_array(list->length);
    NODE *tmp_node = list->data;
    while (tmp_node != NULL)
    {
        add(array, tmp_node->value);
        tmp_node = tmp_node->next_node;
    }
    return array;
}

// Aplica a ordenação por inserção
void insertion_sort(ARRAY *array)
{
    if (is_empty(array) || (!is_empty(array) && array->length == 1))
        return;
    for (int index = 1; index < array->length; index++)
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

// Aplica a ordenação por baldes
void bucket_sort(ARRAY *array)
{
    if (array == NULL || is_empty(array))
        return;
    int size = array->size;
    LIST *buckets[size]; // Cria um vetor de tamanho array->size
    for (int index = 0; index < size; index++)
        buckets[index] = new_list(); // Faz com que cada posição seja inicializada com uma lista vazia
    for (int index = 0; index < size; index++)
    {
        int position = floor(size * array->data[index]); // Calcula a posição de cada elemento no vetor de listas
        push(buckets[position], array->data[index]);
    }
    ARRAY *buckets_as_array[size]; // Cria um vetor de vetores que será utilizado para a saída do algoritmo
    for (int index = 0; index < size; index++)
    {
        ARRAY *bucket_as_array = list_2_array(buckets[index]); // Para cada lista, transforma em um vetor para ser ordenado
        insertion_sort(bucket_as_array);                       // Aplica ordenação por inserção
        buckets_as_array[index] = bucket_as_array;             // Insere vetor no vetor de vetores
    }
    ARRAY *sorted_array = concat(buckets_as_array, size); // Concatena os vetores
    for (int index = 0; index < sorted_array->length; index++)
        array->data[index] = sorted_array->data[index]; // Reatribui os valores já ordenados para o vetor original
}
// =====================================================

/* ==================== Utilidades ==================== */
// Exibe um título
void print_title(char *text)
{
    char *divisor = "==================";
    printf("\n%s ", divisor);
    printf(text);
    printf(" %s\n", divisor);
}

// Exibe o tempo transcorrido
void print_time(double seconds)
{
    printf("\nFinalizado em %.2f segundos.\n", seconds);
}

typedef clock_t timestamp;

// Retorna o tempo atual
timestamp get_time()
{
    return clock();
}

// Dado um tempo inicial e um tempo final, calcula (em segundos) o tempo transcorrido
double calc_time(timestamp start, timestamp end)
{
    return ((double)end - start) / CLOCKS_PER_SEC;
}

// Conta (em segundos) o tempo de execução de uma função
void cout_time(void (*fn)())
{
    timestamp start = get_time();
    fn();
    timestamp end = get_time();
    print_time(calc_time(start, end)); // Exibe a quantidade de tempo calculada
}

// Retorna quantidade de casas a serem retiradas tal que 'value' seja um valor x, onde 0 <= x <= 1
double get_decimal(double value, int decimal)
{
    if (value < 10)
        return pow(10, decimal);
    return get_decimal(value / 10, decimal + 1);
}
// =====================================================

// Testa vetor de 100 mil números totalmente ordenado decrescentemente
void test_decrescent_numbers()
{
    ARRAY *array = new_array(100000);
    for (int index = 100000; index > 0; index--)
        add(array, index / get_decimal(index, 1));
    bucket_sort(array);
    // print_array(array); // Remover este comentário para ver a saída
}

// Testa vetor de 100 mil números totalmente ordenado crescentemente
void test_crescent_numbers()
{
    ARRAY *array = new_array(100000);
    for (int index = 1; index <= 100000; index++)
        add(array, index / get_decimal(index, 1));
    bucket_sort(array);
    // print_array(array); // Remover este comentário para ver a saída
}

// Testa vetor de 100 mil números com primeira metade ordenada crescentemente e segunda metade ordenada decrescentemente
void test_crescent_decrescent_numbers()
{
    ARRAY *array = new_array(100000);
    for (int index = 1; index <= 50000; index++)
        add(array, index / get_decimal(index, 1));
    for (int index = 100000; index >= 50001; index--)
        add(array, index / get_decimal(index, 1));
    bucket_sort(array);
    // print_array(array); // Remover este comentário para ver a saída
}

// Testa vetor de 100 mil números com primeira metade ordenada decrescentemente e segunda metade ordenada crescentemente
void test_decrescent_crescent_numbers()
{
    ARRAY *array = new_array(100000);
    for (int index = 50000; index >= 1; index--)
        add(array, index / get_decimal(index, 1));
    for (int index = 50001; index <= 100000; index++)
        add(array, index / get_decimal(index, 1));
    bucket_sort(array);
    // print_array(array); // Remover este comentário para ver a saída
}

// Testa vetor de 100 mil números com valores totalmente desordenados
void test_random_numbers()
{
    ARRAY *array = new_array(100000);
    for (int index = 0; index < 100000; index++)
    {
        uint64_t sorted_number;
        sorted_number = rand();
        sorted_number = (sorted_number << 32) | rand();
        sorted_number = (sorted_number % (999999999 - 100000000)) + 100000000;

        int number = sorted_number % 100001;
        add(array, number / get_decimal(number, 1));
    }
    bucket_sort(array);
    // printArray(array) // Remover este comentário para ver a saída
}

int main() // Função principal
{
    print_title("Números Decrescentes");
    cout_time(test_decrescent_numbers);

    print_title("Números Crescentes");
    cout_time(test_crescent_numbers);

    print_title("Números Crescente-Decrescente");
    cout_time(test_crescent_decrescent_numbers);

    print_title("Números Decrescente-Crescente");
    cout_time(test_decrescent_crescent_numbers);

    print_title("Números Aleatórios");
    cout_time(test_random_numbers);
    return 0;
}