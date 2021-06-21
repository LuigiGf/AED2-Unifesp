#include <stdio.h>
#include <string.h>

//não correto.
void maiMinus(char arr[][21], int m)
{
  int i = 0, j = 0;
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < strlen(arr[i]); j++)
    {
      if (arr[i][j] < 91)
        arr[i][j] = arr[i][j] + 32;
    }
  }
}

void espacosAdicionar(char arr[][21], int m)
{
  int i = 0, j = 0;
  for (i = 0; i < m; i++)
  {
    for (j = strlen(arr[i]); j < 20; j++)
    {
      strcat(arr[i], " ");
    }
  }
}

int main(void)
{
  char palavra[21], maiorP[21];
  int entrada, i, m, p;

  scanf("%d", &entrada);
  char vetor[entrada][21];

  for (i = 0; i < entrada; i++)
  {
    scanf("%s", &palavra);
    strcpy(vetor[i], palavra);
  }
  radixsort(vetor, entrada);

  for (i = 0; i < entrada; i++)
  {
    printf("%s.\n", vetor[i]);
  }
  scanf("%d %d", &p, &m);
  p--;
  char vetorF[m][21];
  for (i = 0; i < m; i++)
  {
    strcpy(vetorF[i], vetor[p + i]);
  }

  printf("palavras\n");
  for (i = 0; i < m; i++)
  {
    printf("%s.\n", vetorF[i]);
  }

  return 0;
}