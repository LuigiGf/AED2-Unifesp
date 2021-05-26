#include <stdio.h>
int k = 0;
void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int arr[], int low, int high)
{
  int pivot = arr[high]; // pivot
  int i = (low - 1);

  int j;
  for (j = low; j <= high - 1; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int pi = partition(arr, low, high);
    if (pi > k - 1)
    {
      return quickSort(arr, low, pi - 1);
    }
    if (pi < k - 1)
    {
      return quickSort(arr, pi + 1, high);
    }
    if (pi == k - 1)
    {
      return;
    }
  }
}

void printarFunc(int arr[], int end)
{
  printf("%do menor elemento eh o %d\n", k, arr[k - 1]);
  int i = 0;
  for (i = 0; i < end; i++)
  {
    printf("%d ", arr[i]);
  }
}

int main()
{
  int i = 0, n = 0;

  scanf("%d %d", &k, &n);
  int arr[n];

  for (i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }

  quickSort(arr, 0, n - 1);
  printarFunc(arr, n);

  return 0;
}