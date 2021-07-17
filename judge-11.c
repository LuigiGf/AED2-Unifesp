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

void remover(int valor)
{
  struct rubroNegraNo *pilha[98], *ptr, *xPtr, *yPtr;
  struct rubroNegraNo *pPtr, *qPtr, *rPtr;
  int dir[98], ht = 0, diff, i;
  enum corDoNo cor;

  if (!raiz)
  {
    printf("Arvore não disponivel\n");
    return;
  }

  ptr = raiz;
  while (ptr != NULL)
  {
    if ((valor - ptr->valor) == 0)
      break;
    diff = (valor - ptr->valor) > 0 ? 1 : 0;
    pilha[ht] = ptr;
    dir[ht++] = diff;
    ptr = ptr->lado[diff];
  }

  if (ptr->lado[1] == NULL)
  {
    if ((ptr == raiz) && (ptr->lado[0] == NULL))
    {
      free(ptr);
      raiz = NULL;
    }
    else if (ptr == raiz)
    {
      raiz = ptr->lado[0];
      free(ptr);
    }
    else
    {
      pilha[ht - 1]->lado[dir[ht - 1]] = ptr->lado[0];
    }
  }
  else
  {
    xPtr = ptr->lado[1];
    if (xPtr->lado[0] == NULL)
    {
      xPtr->lado[0] = ptr->lado[0];
      cor = xPtr->cor;
      xPtr->cor = ptr->cor;
      ptr->cor = cor;

      if (ptr == raiz)
      {
        raiz = xPtr;
      }
      else
      {
        pilha[ht - 1]->lado[dir[ht - 1]] = xPtr;
      }

      dir[ht] = 1;
      pilha[ht++] = xPtr;
    }
    else
    {
      i = ht++;
      while (1)
      {
        dir[ht] = 0;
        pilha[ht++] = xPtr;
        yPtr = xPtr->lado[0];
        if (!yPtr->lado[0])
          break;
        xPtr = yPtr;
      }

      dir[i] = 1;
      pilha[i] = yPtr;
      if (i > 0)
        pilha[i - 1]->lado[dir[i - 1]] = yPtr;

      yPtr->lado[0] = ptr->lado[0];

      xPtr->lado[0] = yPtr->lado[1];
      yPtr->lado[1] = ptr->lado[1];

      if (ptr == raiz)
      {
        raiz = yPtr;
      }

      cor = yPtr->cor;
      yPtr->cor = ptr->cor;
      ptr->cor = cor;
    }
  }

  if (ht < 1)
    return;

  if (ptr->cor == Preto)
  {
    while (1)
    {
      pPtr = pilha[ht - 1]->lado[dir[ht - 1]];
      if (pPtr && pPtr->cor == Vermelho)
      {
        pPtr->cor = Preto;
        break;
      }

      if (ht < 2)
        break;

      if (dir[ht - 2] == 0)
      {
        rPtr = pilha[ht - 1]->lado[1];

        if (!rPtr)
          break;

        if (rPtr->cor == Vermelho)
        {
          pilha[ht - 1]->cor = Vermelho;
          rPtr->cor = Preto;
          pilha[ht - 1]->lado[1] = rPtr->lado[0];
          rPtr->lado[0] = pilha[ht - 1];

          if (pilha[ht - 1] == raiz)
          {
            raiz = rPtr;
          }
          else
          {
            pilha[ht - 2]->lado[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 0;
          pilha[ht] = pilha[ht - 1];
          pilha[ht - 1] = rPtr;
          ht++;

          rPtr = pilha[ht - 1]->lado[1];
        }

        if ((!rPtr->lado[0] || rPtr->lado[0]->cor == Preto) &&
            (!rPtr->lado[1] || rPtr->lado[1]->cor == Preto))
        {
          rPtr->cor = Vermelho;
        }
        else
        {
          if (!rPtr->lado[1] || rPtr->lado[1]->cor == Preto)
          {
            qPtr = rPtr->lado[0];
            rPtr->cor = Vermelho;
            qPtr->cor = Preto;
            rPtr->lado[0] = qPtr->lado[1];
            qPtr->lado[1] = rPtr;
            rPtr = pilha[ht - 1]->lado[1] = qPtr;
          }
          rPtr->cor = pilha[ht - 1]->cor;
          pilha[ht - 1]->cor = Preto;
          rPtr->lado[1]->cor = Preto;
          pilha[ht - 1]->lado[1] = rPtr->lado[0];
          rPtr->lado[0] = pilha[ht - 1];
          if (pilha[ht - 1] == raiz)
          {
            raiz = rPtr;
          }
          else
          {
            pilha[ht - 2]->lado[dir[ht - 2]] = rPtr;
          }
          break;
        }
      }
      else
      {
        rPtr = pilha[ht - 1]->lado[0];
        if (!rPtr)
          break;

        if (rPtr->cor == Vermelho)
        {
          pilha[ht - 1]->cor = Vermelho;
          rPtr->cor = Preto;
          pilha[ht - 1]->lado[0] = rPtr->lado[1];
          rPtr->lado[1] = pilha[ht - 1];

          if (pilha[ht - 1] == raiz)
          {
            raiz = rPtr;
          }
          else
          {
            pilha[ht - 2]->lado[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 1;
          pilha[ht] = pilha[ht - 1];
          pilha[ht - 1] = rPtr;
          ht++;

          rPtr = pilha[ht - 1]->lado[0];
        }
        if ((!rPtr->lado[0] || rPtr->lado[0]->cor == Preto) &&
            (!rPtr->lado[1] || rPtr->lado[1]->cor == Preto))
        {
          rPtr->cor = Vermelho;
        }
        else
        {
          if (!rPtr->lado[0] || rPtr->lado[0]->cor == Preto)
          {
            qPtr = rPtr->lado[1];
            rPtr->cor = Vermelho;
            qPtr->cor = Preto;
            rPtr->lado[1] = qPtr->lado[0];
            qPtr->lado[0] = rPtr;
            rPtr = pilha[ht - 1]->lado[0] = qPtr;
          }
          rPtr->cor = pilha[ht - 1]->cor;
          pilha[ht - 1]->cor = Preto;
          rPtr->lado[0]->cor = Preto;
          pilha[ht - 1]->lado[0] = rPtr->lado[1];
          rPtr->lado[1] = pilha[ht - 1];
          if (pilha[ht - 1] == raiz)
          {
            raiz = rPtr;
          }
          else
          {
            pilha[ht - 2]->lado[dir[ht - 2]] = rPtr;
          }
          break;
        }
      }
      ht--;
    }
  }
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

void printaAltura(struct rubroNegraNo *auxRoot)
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

struct rubroNegraNo *pesquisaArvore(struct rubroNegraNo *auxRoot, int v)
{
  if (auxRoot == NULL || v == auxRoot->valor)
    return auxRoot;

  if (v < auxRoot->valor)
    return pesquisaArvore(auxRoot->lado[0], v);
  else
    return pesquisaArvore(auxRoot->lado[1], v);

  return NULL;
}

int EhVermelha(struct rubroNegraNo *No)
{
  return (No == NULL) || (No->cor == 0);
}

int CalculaAlturaVermelha(struct rubroNegraNo *H, int alturaAtual)
{
  if (H == NULL)
  {
    return 0;
  }
  int alt = 0;
  if (EhVermelha(H) == 1)
  {
    alt = 1;
  }

  return alt + CalculaAlturaVermelha(H->lado[0], alt);
}

void printaAlturaVermelha(struct rubroNegraNo *auxRoot)
{
  altura = 0;
  int h = 0;
  h = CalculaAlturaVermelha(auxRoot, h);
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
  printaAltura(raiz);
  scanf("%d", &valor);
  while (valor > 0)
  {
    aux = pesquisaArvore(raiz, valor);
    if (aux != NULL)
    {
      printaAltura(aux);
      remover(valor);
    }
    else
    {
      inserir(valor);
    }
    scanf("%d", &valor);
  }

  scanf("%d", &valor);
  if (pesquisaArvore(raiz, valor) != NULL)
    printaAlturaVermelha(pesquisaArvore(raiz, valor));
  else
  {
    printf("Valor nao encontrado\n");
  }
  return 0;
}