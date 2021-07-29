/*  Programa: lab01
    Autor: Isabela Cristina Silva Pedro
    Versão: 1.0 - 27/05/2021
*/

// ##################### Bibliotecas Externas ##############################
#include <stdio.h>
#include <stdlib.h>
// ########################## TAD X.h ######################################
//struct arvore
typedef struct abb *Apontador;

typedef struct abb
{
  int valor;
  Apontador *esq, *dir;
} ABB;
//gera novo no
struct abb *novoNo(int valor)
{
  struct abb *temp = (struct abb *)malloc(sizeof(struct abb));
  temp->valor = valor;
  temp->esq = temp->dir = NULL;
  return temp;
}
//insere arvore
struct abb *insereElemento(struct abb *arvore, int valor)
{
  if (arvore == NULL)
    return novoNo(valor);

  if (valor < arvore->valor)
    arvore->esq = insereElemento(arvore->esq, valor);
  else
    arvore->dir = insereElemento(arvore->dir, valor);

  return arvore;
}
//menor valor arvore
struct abb *valorMin(struct abb *arvore)
{
  struct abb *current = arvore;

  while (current && current->esq != NULL)
    current = current->esq;

  return current;
}
//remove arvore
struct abb *removeNo(struct abb *arvore, int valor)
{
  // base case
  if (arvore == NULL)
    return arvore;

  if (valor < arvore->valor)
    arvore->esq = removeNo(arvore->esq, valor);
  else if (valor > arvore->valor)
    arvore->dir = removeNo(arvore->dir, valor);
  else
  {
    if (arvore->esq == NULL)
    {
      struct abb *temp = arvore->dir;
      free(arvore);
      return temp;
    }
    else if (arvore->dir == NULL)
    {
      struct abb *temp = arvore->esq;
      free(arvore);
      return temp;
    }
    struct abb *temp = valorMin(arvore->dir);

    arvore->valor = temp->valor;
    arvore->dir = removeNo(arvore->dir, temp->valor);
  }
  return arvore;
}
// ###################### Funcoes e Procedimentos do programa ##############
//printar arvore
void imprimirArvore(ABB *arvore)
{
  ABB *root;
  root = arvore;
  if (root != NULL)
  {
    imprimirArvore(root->esq);
    printf("%d ", root->valor);
    imprimirArvore(root->dir);
  }
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

// ############################ Principal ###################################
int main(void)
{
  int entrada, i, valor;
  int selecao;
  ABB *arvore = NULL;
  ABB *aux;
  scanf("%d", &entrada);

  for (i = 0; i < entrada + entrada; i++)
  {
    selecao = getchar();
    scanf("%d", &valor);
    switch (selecao)
    {
    //Inserção
    case 'I':
      arvore = insereElemento(arvore, valor);
      break;
    //Busca
    case 'B':
      if (pesquisaArvore(arvore, valor) != NULL)
        printf("S\n");
      else
        printf("N\n");
      break;
    //Impressão
    case 'M':
      imprimirArvore(arvore);
      printf("\n");
      break;
    //Remover
    case 'R':
      arvore = removeNo(arvore, valor);
      break;
    }
  }

  return 0;
}
