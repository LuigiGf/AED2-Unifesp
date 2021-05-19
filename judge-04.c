#include <stdio.h>
int counter = 0;

//função merge e mergesort utilizadas do site https://www.geeksforgeeks.org/merge-sort/
void merge(int arr[], int l, int m, int r, int data)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j] * data)
    {
      i++;
    }
    else
    {
      j++;
      counter = counter + (n1 - i);
    }
    k++;
  }

  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r, int k)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m, k);
    mergeSort(arr, m + 1, r, k);

    merge(arr, l, m, r, k);
  }
}
int main(void)
{
  int n, k, i;
  scanf("%d %d", &n, &k);

  int arr[n];
  for (i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  mergeSort(arr, 0, n - 1, k);

  printf("%d", counter);
  return 0;
}