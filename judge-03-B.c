#include <stdio.h>

void recursiveInsertionSort(int arr[], int count, int pos)
{
  if (count <= 1)
  {
    return;
  }

  recursiveInsertionSort(arr, count - 1, pos);
  //printa a posição da chave
  printf("%d", pos - count);

  int last = arr[count - 1];
  int aux = count - 2;
  //printa o valor da chave
  printf(" %d ", arr[count - 1]);
  while (aux >= 0 && arr[aux] > last)
  {
    arr[aux + 1] = arr[aux];
    aux--;
  }
  //printa a localização da chave do vetor
  printf("%d\n", aux + 1);
  arr[aux + 1] = last;
}

int main()
{
  int n, i;
  scanf("%d", &n);
  int arr[n];

  for (i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  if (n <= 1)
  {
    printf("1 1 0\n1");
    return 0;
  }
  recursiveInsertionSort(arr, n, n + 1);
  for (i = 0; i < n; i++)
  {
    printf(" %d ", arr[i]);
  }

  return 0;
}