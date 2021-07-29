#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int chave;
  int valor;
  int verificacao;
  struct hashElemento *prox;
} hashElemento;

int inserirHash(hashElemento *tabelaHash, int tamanho, int valor)
{
  hashElemento *pAux;
  if (tabelaHash[valor % tamanho].verificacao == 0)
  {
    tabelaHash[valor % tamanho].chave = valor % tamanho;
    tabelaHash[valor % tamanho].valor = valor;
    tabelaHash[valor % tamanho].verificacao = 1;
  }
  else
  {
    pAux = &tabelaHash[valor % tamanho];
    while (pAux->prox != NULL)
    {
      pAux = pAux->prox;
    }

    pAux->prox = (hashElemento *)malloc(sizeof(hashElemento));
    pAux = pAux->prox;
    pAux->valor = valor;
    pAux->chave = valor % tamanho;
    pAux->prox = NULL;
  }
}

int removeHash(hashElemento *tabelaHash, int valor, int tamanho, hashElemento *pRemover)
{

  hashElemento *pAux, *pAux2 = pRemover;
  if (pRemover->prox != NULL)
  {
    while (pRemover->prox != NULL)
    {
      pAux2 = pRemover;
      pAux = pRemover->prox;
      pRemover->valor = pAux->valor;
      pRemover = pRemover->prox;
    }

    pAux2->prox = NULL;
    pAux->valor = 0;
    free(pRemover);
  }
  else
  {
    pAux = &tabelaHash[valor % tamanho];
    if (tabelaHash[valor % tamanho].prox == NULL)
      pAux->verificacao = 0;
    else
    {
      while (pAux->prox != pRemover)
      {
        pAux = pAux->prox;
      }
      pAux->prox = NULL;
      free(pRemover);
    }
  }
}

int buscaHash(hashElemento *tabelaHash, int valor, int tamanho)
{
  hashElemento *pAux = &tabelaHash[valor % tamanho];
  if (tabelaHash[valor % tamanho].verificacao == 0)
  {
    return 1;
  }
  else
  {
    if (pAux->valor == valor)
    {
      removeHash(tabelaHash, valor, tamanho, pAux);

      return 0;
    }

    while (pAux != NULL)
    {
      if (pAux->valor == valor)
      {
        removeHash(tabelaHash, valor, tamanho, pAux);
        return 0;
      }
      pAux = pAux->prox;
    }
  }

  inserirHash(tabelaHash, tamanho, valor);
}

int imprimirHash(hashElemento *tabelaHash, int tamanho, int linhaExibida)
{
  int i;
  hashElemento *pAux;

  printf("[%d]", linhaExibida);
  if (tabelaHash[linhaExibida].verificacao != 0)
    printf(" %d", tabelaHash[linhaExibida].valor);
  pAux = &tabelaHash[linhaExibida];
  while (pAux->prox != NULL)
  {
    pAux = pAux->prox;

    printf(" %d", pAux->valor);
  }

  printf("\n");
}

int main()
{
  int tamanhoTabela, valorInserido, chavePesquisa, linhaExibida, i, valorEncontrado;
  hashElemento *tabelaHash, *pAux;

  scanf("%d", &tamanhoTabela);

  tabelaHash = (hashElemento *)malloc(tamanhoTabela * sizeof(hashElemento));

  for (i = 0; i < tamanhoTabela; i++)
  {
    tabelaHash[i].chave = i;
    tabelaHash[i].prox = NULL;
    tabelaHash[i].verificacao = 0;
  }

  while (valorInserido != -1)
  {
    scanf("%d", &valorInserido);
    if (valorInserido != -1)
      inserirHash(tabelaHash, tamanhoTabela, valorInserido);
  }

  scanf("%d", &chavePesquisa);
  if (buscaHash(tabelaHash, chavePesquisa, tamanhoTabela) == 1)
  {
    printf("Valor não encontrado");
  }
  scanf("%d", &linhaExibida);
  imprimirHash(tabelaHash, tamanhoTabela, linhaExibida);
}

//7 3 4 9 2 5 1 8 1 2 -1