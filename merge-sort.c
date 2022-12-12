/* ==================== Merge Sort ==================== */
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

// Exibe os elementos de um vetor
void print_array(ARRAY *array)
{
	if (is_empty(array))
		return;
	for (int index = 0; index < array->length; index++)
		printf("%f ", array->data[index]);
}

void merge(ARRAY *array, int inicio, int meio, int fim)
{

	// quantidade de elementos em cada parte do vetor
	int n1 = meio - inicio + 1;
	int n2 = fim - meio;

	ARRAY *aux1 = new_array(n1);
	ARRAY *aux2 = new_array(n2);
	//int aux1[n1], aux2[n2]; 
	// criando os vetores auxiliares
 
	int i = 0; //percorrerá o vetor aux1
	int j = 0; //percorrerá o vetor aux2
	int k = inicio; //percorrerá o vetor original
 
 
	// colocando cada metade do vetor original em seu vetor auxiliar correspondente
	for(int i = 0; i < n1; i++){
		aux1[i] = array[inicio+i];
	}
	for(int j=0; j < n2; j++){
		aux2[j] = array[meio+1 + j];
	}
 
 
	// Comparações serão feitas entre os vetores auxiliares e os menores elementos serão inseridos no vetor original
	while(i < n1 && j < n2){
		if (aux1->data[i] <= aux2->data[j])
		{

			array->data[k] = aux1->data[i];
			i++;
		}
		else {
			array->data[k] = aux2->data[j];
			j++;
		}
		k++;
	}
 
 
	//ainda há elementos no vetor aux1
	while(i < n1){
		array->data[k] = aux1->data[i];
		i++;
		k++;
	}
 
	//ainda há elementos no vetor aux2
	while(j < n2){
		array->data[k] = aux2->data[j];
		j++;
		k++;
	}
}

void merge_sort(ARRAY *array, int inicio, int fim)
{
	if (inicio < fim)
	{
		int meio = (inicio + fim) / 2;
		merge_sort(array, inicio, meio);	 // ordena a primeira parte (início até o meio)
		merge_sort(array, meio + 1, fim); // ordena a segunda parte (meio até o fim)
		merge(array, inicio, meio, fim); // combina as duas partes intercalando-as de maneira ordenada
	}
}


void printVetor(ARRAY * array, int tam)
{
	for (int i = 0; i < tam; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
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
void count_time(void (*fn)())
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
	merge_sort(array, 0, array->length);
	// print_array(array); // Remover este comentário para ver a saída
}

// Testa vetor de 100 mil números totalmente ordenado crescentemente
void test_crescent_numbers()
{
	ARRAY *array = new_array(100000);
	for (int index = 1; index <= 100000; index++)
		add(array, index / get_decimal(index, 1));
	merge_sort(array, 0, array->length);
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
	merge_sort(array, 0, array->length);
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
	merge_sort(array, 0, array->length);
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
	merge_sort(array, 0, array->length);
	// print_array(array) // Remover este comentário para ver a saída
}

int main() // Função principal
{
	print_title("Números Decrescentes");
	count_time(test_decrescent_numbers);

	print_title("Números Crescentes");
	count_time(test_crescent_numbers);

	print_title("Números Crescente-Decrescente");
	count_time(test_crescent_decrescent_numbers);

	print_title("Números Decrescente-Crescente");
	count_time(test_decrescent_crescent_numbers);

	print_title("Números Aleatórios");
	count_time(test_random_numbers);
	return 0;
}
