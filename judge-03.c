#include <stdio.h>

void InsertionSort(int i, int array[], int size, int pos)
{
  if (i < size)
  {
    int x;
    int temp = array[i];

    for (x = i; x > 0 && array[x - 1] > temp; x--)
    {
      array[x] = array[x - 1];
    }
    if (i != 0)
    {
      //printa o nivel de recursao
      printf("%d", pos - i);
      //printa o valor da chave
      printf(" %d ", temp);
      //printa a localização do elemento
      printf("%d\n", x);
    }

    array[x] = temp;

    InsertionSort(++i, array, size, pos);
  }
}

int main(void)
{
  int n, i;
  scanf("%d", &n);
  int arr[n];

  for (i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  InsertionSort(0, arr, n, n);
  for (i = 0; i < n; i++)
  {
    printf(" %d ", arr[i]);
  }
  printf("\n");

  return 0;
}