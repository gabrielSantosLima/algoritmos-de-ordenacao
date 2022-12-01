#include <stdio.h>
#include <stdlib.h>
 
void merge(int vetor[], int inicio, int meio, int fim){
 
  // quantidade de elementos em cada parte do vetor
  int n1 = meio - inicio+1;
  int n2 = fim - meio;
 
  int aux1[n1], aux2[n2]; // criando os vetores auxiliares
 
  int i=0; //percorrerá o vetor aux1
  int j=0; //percorrerá o vetor aux2
  int k=inicio; //percorrerá o vetor original
 
 
  // colocando cada metade do vetor original em seu vetor auxiliar correspondente
  for(int i=0; i < n1; i++){
    aux1[i] = vetor[inicio+i];
  }
  for(int j=0; j < n2; j++){
    aux2[j] = vetor[meio+1 + j];
  }
 
 
  // Comparações serão feitas entre os vetores auxiliares e os menores elementos serão inseridos no vetor original
  while(i < n1 && j < n2){
    if(aux1[i] <= aux2[j]){
      vetor[k] = aux1[i];
      i++;
    }
    else {
      vetor[k] = aux2[j];
      j++;
    }
    k++;
  }
 
 
  //ainda há elementos no vetor aux1
  while(i < n1){
    vetor[k] = aux1[i];
    i++;
    k++;
  }
 
  //ainda há elementos no vetor aux2
  while(j < n2){
    vetor[k] = aux2[j];
    j++;
    k++;
  }
}
 
 
void mergeSort(int vetor[], int inicio, int fim){
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio); //ordena a primeira parte (início até o meio)
        mergeSort(vetor, meio+1, fim); //ordena a segunda parte (meio até o fim)
        merge(vetor, inicio, meio, fim); // combina as duas partes intercalando-as de maneira ordenada
    }
}
 
 
void printVetor(int vetor[], int tam){
  for(int i=0; i<tam; i++){
    printf("%d ", vetor[i]);
  }
  printf("\n");
}
 
 
int main(){
  int vetor[] = {29, 3, 1, 54, 23, 2, 7, 9, 2};
  printf("----- Vetor desordenado -----\n");
  printVetor(vetor, 9);
 
  mergeSort(vetor, 0, 9);
 
  printf("\n");
  printf("----- Vetor ordenado -----\n");
  printVetor(vetor, 9);
  return 0;
}

