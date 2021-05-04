#include <stdio.h>

int count = 1;

//Código do bubble sort pego no site http://devfuria.com.br/logica-de-programacao/exemplos-na-linguagem-c-do-algoritmo-bubble-sort/
void bubble_sort(int vetor[], int n)
{
  int k, j, aux;

  for (k = 1; k < n; k++)
  {
    for (j = 0; j < n - k; j++)
    {
      if (vetor[j] > vetor[j + 1])
      {
        aux = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = aux;
        //contador adicionado para identificar qual dos dois ganhou
        count++;
      }
    }
  }
}

int main(void)
{
  int n, number, i;
  scanf("%d", &n);

  int vet[n];

  for (i = 0; i < n; i++)
  {
    scanf("%d", &number);
    vet[i] = number;
  }

  bubble_sort(vet, n);

  for (i = 0; i < n; i++)
  {
    printf("%d ", vet[i]);
  }
  //verifica o vencedor baseado no vencedor
  if (count % 2 == 0)
  {
    printf("\nMarcelo");
  }
  else
  {
    printf("\nCarlos");
  }

  return 0;
}