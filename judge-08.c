#include <stdio.h>
#include <stdlib.h>

//==============================TAD ARVORE=====================================
int altura = 0;
//struct arvore
typedef struct abb *Apontador;
typedef struct abb
{
  int valor;
  Apontador esq;
  Apontador dir;
  Apontador pai;
} ABB;

//inicia arvore
void iniciaArvore(ABB *arvore, int v)
{
  arvore->pai = NULL;
  arvore->dir = NULL;
  arvore->esq = NULL;
  arvore->valor = v;
}

//menor valor arvore
ABB *valorMin(ABB *arvore)
{
  while (arvore->esq != NULL)
    arvore = arvore->esq;
  return arvore;
}

//maior valor arvore
ABB *valorMax(ABB *arvore)
{
  while (arvore->dir != NULL)
    arvore = arvore->dir;
  return arvore;
}

//sucessor
ABB *sucessor(ABB *arvore)
{
  ABB *aux;
  if (arvore->dir != NULL)
    return valorMin(arvore->dir);
  aux = arvore->pai;
  while (aux != NULL && arvore == aux->dir)
  {
    arvore = aux;
    aux = aux->pai;
  }
  return aux;
}

//pesquisa arvore
ABB *pesquisaArvore(ABB *arvore, int v)
{
  if (arvore == NULL || v == arvore->valor)
    return arvore;

  if (v < arvore->valor)
    return pesquisaArvore(arvore->esq, v);
  else
    return pesquisaArvore(arvore->dir, v);

  return NULL;
}

//insere arvore
void insereElemento(ABB *arvore, int v)
{
  //criação do novo no
  ABB *novoNo;
  novoNo = (ABB *)malloc(sizeof(ABB));
  novoNo->dir = NULL;
  novoNo->esq = NULL;
  novoNo->valor = v;
  //fim criação

  ABB *aux;
  ABB *aux2;
  aux2 = NULL;
  aux = arvore;

  while (aux != NULL)
  {
    aux2 = aux;
    if (novoNo->valor < aux->valor)
      aux = aux->esq;
    else
      aux = aux->dir;
  }

  novoNo->pai = aux2;
  if (novoNo->valor < aux2->valor)
  {
    aux2->esq = novoNo;
  }
  else
  {
    aux2->dir = novoNo;
  }
}

//transplante
void transplante(ABB *arvore, ABB *u, ABB *v)
{
  if (u->pai == NULL)
  {
    arvore = v;
  }
  else if (u == u->pai->esq)
  {
    u->pai->esq = v;
  }
  else
  {
    u->pai->dir = v;
  }
  if (v != NULL)
  {
    v->pai = u->pai;
  }
}

//remove arvore
void removeNo(ABB *arvore, ABB *no)
{
  ABB *aux;
  if (no->esq == NULL)
  {
    transplante(arvore, no, no->dir);
  }
  else if (no->dir == NULL)
  {
    transplante(arvore, no, no->esq);
  }
  else
  {
    aux = valorMin(no->dir);
    if (aux->pai != no)
    {
      transplante(arvore, aux, aux->dir);
      aux->dir = no->dir;
      aux->dir->pai = aux;
    }
    transplante(arvore, no, aux);
    aux->esq = no->esq;
    aux->esq->pai = aux;
  }
}

//printar arvore
void imprimirArvore(ABB *arvore)
{
  ABB *aux;
  aux = arvore;
  if (arvore == NULL)
  {
    printf("Arvore nao existe");
  }
  printf("%d ", aux->valor);
  if (aux->esq != NULL)
  {
    imprimirArvore(aux->esq);
  }
  if (aux->dir != NULL)
  {
    imprimirArvore(aux->dir);
  }
}

int calculaAltura(ABB *arvore, int aux)
{
  if (arvore == NULL)
    return -1;

  if (arvore->esq != NULL)
    calculaAltura(arvore->esq, aux + 1);
  if (arvore->dir != NULL)
    calculaAltura(arvore->dir, aux + 1);
  if (aux >= altura)
  {
    altura = aux;
    return aux;
  }
}

void printaAltura(ABB *arvore)
{
  altura = 0;
  int h = 0, hd = 0, he = 0;
  h = calculaAltura(arvore, h);
  altura = 0;
  hd = calculaAltura(arvore->dir, hd);
  altura = 0;
  he = calculaAltura(arvore->esq, he);
  printf("%d,%d,%d\n", h, he + 1, hd + 1);
}
//==============================FIM DO TAD=====================================

int main(void)
{
  int entrada = 0, valor = 0;

  ABB arvore;
  ABB *aux;
  scanf("%d", &valor);
  iniciaArvore(&arvore, valor);
  while (valor > 0)
  {
    scanf("%d", &valor);
    if (valor < 0)
      break;
    insereElemento(&arvore, valor);
  }
  printaAltura(&arvore);
  scanf("%d", &valor);
  while (valor > 0)
  {
    aux = pesquisaArvore(&arvore, valor);
    if (aux != NULL)
    {
      removeNo(&arvore, aux);
    }
    else
    {
      insereElemento(&arvore, valor);
    }
    scanf("%d", &valor);
  }

  scanf("%d", &valor);
  if (pesquisaArvore(&arvore, valor) != NULL)
    printaAltura(pesquisaArvore(&arvore, valor));
  else
  {
    printf("Valor nao encontrado\n");
  }

  return 0;
}