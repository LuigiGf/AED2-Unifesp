#include <stdio.h>
#include <stdlib.h>
int altura = 0;
enum corDoNo
{
  Vermelho,
  Preto
};

struct rubroNegraNo
{
  int valor, cor;
  struct rubroNegraNo *lado[2];
};

struct rubroNegraNo *raiz = NULL;

struct rubroNegraNo *criarNo(int valor)
{
  struct rubroNegraNo *novoNo;
  novoNo = (struct rubroNegraNo *)malloc(sizeof(struct rubroNegraNo));
  novoNo->valor = valor;
  novoNo->cor = Vermelho;
  novoNo->lado[0] = novoNo->lado[1] = NULL;
  return novoNo;
}

void inserir(int valor)
{
  struct rubroNegraNo *pilha[98], *ptr, *novoNo, *xPtr, *yPtr;
  int dir[98], ht = 0, indice;
  ptr = raiz;
  if (!raiz)
  {
    raiz = criarNo(valor);
    return;
  }

  pilha[ht] = raiz;
  dir[ht++] = 0;
  while (ptr != NULL)
  {
    if (ptr->valor == valor)
    {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    indice = (valor - ptr->valor) > 0 ? 1 : 0;
    pilha[ht] = ptr;
    ptr = ptr->lado[indice];
    dir[ht++] = indice;
  }
  pilha[ht - 1]->lado[indice] = novoNo = criarNo(valor);
  while ((ht >= 3) && (pilha[ht - 1]->cor == Vermelho))
  {
    if (dir[ht - 2] == 0)
    {
      yPtr = pilha[ht - 2]->lado[1];
      if (yPtr != NULL && yPtr->cor == Vermelho)
      {
        pilha[ht - 2]->cor = Vermelho;
        pilha[ht - 1]->cor = yPtr->cor = Preto;
        ht = ht - 2;
      }
      else
      {
        if (dir[ht - 1] == 0)
        {
          yPtr = pilha[ht - 1];
        }
        else
        {
          xPtr = pilha[ht - 1];
          yPtr = xPtr->lado[1];
          xPtr->lado[1] = yPtr->lado[0];
          yPtr->lado[0] = xPtr;
          pilha[ht - 2]->lado[0] = yPtr;
        }
        xPtr = pilha[ht - 2];
        xPtr->cor = Vermelho;
        yPtr->cor = Preto;
        xPtr->lado[0] = yPtr->lado[1];
        yPtr->lado[1] = xPtr;
        if (xPtr == raiz)
        {
          raiz = yPtr;
        }
        else
        {
          pilha[ht - 3]->lado[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
    else
    {
      yPtr = pilha[ht - 2]->lado[0];
      if ((yPtr != NULL) && (yPtr->cor == Vermelho))
      {
        pilha[ht - 2]->cor = Vermelho;
        pilha[ht - 1]->cor = yPtr->cor = Preto;
        ht = ht - 2;
      }
      else
      {
        if (dir[ht - 1] == 1)
        {
          yPtr = pilha[ht - 1];
        }
        else
        {
          xPtr = pilha[ht - 1];
          yPtr = xPtr->lado[0];
          xPtr->lado[0] = yPtr->lado[1];
          yPtr->lado[1] = xPtr;
          pilha[ht - 2]->lado[1] = yPtr;
        }
        xPtr = pilha[ht - 2];
        yPtr->cor = Preto;
        xPtr->cor = Vermelho;
        xPtr->lado[1] = yPtr->lado[0];
        yPtr->lado[0] = xPtr;
        if (xPtr == raiz)
        {
          raiz = yPtr;
        }
        else
        {
          pilha[ht - 3]->lado[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
  }
  raiz->cor = Preto;
}

void imprimirArvore(struct rubroNegraNo *arvore)
{
  struct rubroNegraNo *aux;
  aux = arvore;
  if (arvore == NULL)
  {
    printf("Arvore nao existe");
  }
  printf("%d ", aux->valor);
  if (aux->lado[0] != NULL)
  {
    imprimirArvore(aux->lado[0]);
  }
  if (aux->lado[1] != NULL)
  {
    imprimirArvore(aux->lado[1]);
  }
}

int calculaAltura(struct rubroNegraNo *auxRoot, int aux)
{
  if (auxRoot == NULL)
    return -1;

  if (auxRoot->lado[1] != NULL)
    calculaAltura(auxRoot->lado[1], aux + 1);
  if (auxRoot->lado[0] != NULL)
    calculaAltura(auxRoot->lado[0], aux + 1);
  if (aux >= altura)
  {
    altura = aux;
    return aux;
  }
}

void imprimirAltura(struct rubroNegraNo *auxRoot)
{
  altura = 0;
  int h = 0, hd = 0, he = 0;
  h = calculaAltura(auxRoot, h);
  altura = 0;
  hd = calculaAltura(auxRoot->lado[1], hd);
  altura = 0;
  he = calculaAltura(auxRoot->lado[0], he);
  printf("%d,%d,%d\n", h, he + 1, hd + 1);
}

struct rubroNegraNo *buscaArvore(struct rubroNegraNo *auxRoot, int v)
{
  if (auxRoot == NULL || v == auxRoot->valor)
    return auxRoot;

  if (v < auxRoot->valor)
    return buscaArvore(auxRoot->lado[0], v);
  else
    return buscaArvore(auxRoot->lado[1], v);

  return NULL;
}

int EhPreto(struct rubroNegraNo *No)
{
  return (No == NULL) || (No->cor == 1);
}

int CalculaAlturaPreta(struct rubroNegraNo *H, int alturaAtual)
{
  if (H == NULL)
  {
    return 0;
  }
  int alt = 0;
  if (EhPreto(H) == 1)
  {
    alt = 1;
  }

  return alt + CalculaAlturaPreta(H->lado[0], alt);
}

void PrintaAlturaPreta(struct rubroNegraNo *auxRoot)
{
  altura = 0;
  int h = 0;
  h = CalculaAlturaPreta(auxRoot, h);
  printf("%d\n", h);
}

int main()
{
  int entrada = 0, valor = 0;

  struct rubroNegraNo *aux;
  scanf("%d", &valor);
  inserir(valor);
  while (valor > 0)
  {
    scanf("%d", &valor);
    if (valor < 0)
      break;
    inserir(valor);
  }
  imprimirAltura(raiz);
  scanf("%d", &valor);
  while (valor > 0)
  {
    aux = buscaArvore(raiz, valor);
    if (aux != NULL)
    {
      imprimirAltura(aux);
    }
    else
    {
      inserir(valor);
    }
    scanf("%d", &valor);
  }

  scanf("%d", &valor);
  if (buscaArvore(raiz, valor) != NULL)
    PrintaAlturaPreta(buscaArvore(raiz, valor));
  else
  {
    printf("Valor nao encontrado\n");
  }
  return 0;
}