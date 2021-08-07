#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 4
#define MINIMO 2
int verificador = 0;
struct ArvoreBNo
{
  int valor[MAXIMO + 1], contador;
  struct ArvoreBNo *conexoes[MAXIMO + 1];
};

struct ArvoreBNo *raiz;

struct ArvoreBNo *criarNo(int valor, struct ArvoreBNo *crianca)
{
  struct ArvoreBNo *novoNo;
  novoNo = (struct ArvoreBNo *)malloc(sizeof(struct ArvoreBNo));
  novoNo->valor[1] = valor;
  novoNo->contador = 1;
  novoNo->conexoes[0] = raiz;
  novoNo->conexoes[1] = crianca;
  return novoNo;
}

void inserirNo(int valor, int posicao, struct ArvoreBNo *no,
               struct ArvoreBNo *crianca)
{
  int j = no->contador;
  while (j > posicao)
  {
    no->valor[j + 1] = no->valor[j];
    no->conexoes[j + 1] = no->conexoes[j];
    j--;
  }
  no->valor[j + 1] = valor;
  no->conexoes[j + 1] = crianca;
  no->contador++;
}

void dividirNo(int valor, int *pValor, int posicao, struct ArvoreBNo *no,
               struct ArvoreBNo *crianca, struct ArvoreBNo **novoNo)
{
  int meio, j;

  if (posicao > MINIMO)
    meio = MINIMO + 1;
  else
    meio = MINIMO;

  *novoNo = (struct ArvoreBNo *)malloc(sizeof(struct ArvoreBNo));
  j = meio + 1;
  while (j <= MAXIMO)
  {
    (*novoNo)->valor[j - meio] = no->valor[j];
    (*novoNo)->conexoes[j - meio] = no->conexoes[j];
    j++;
  }
  no->contador = meio;
  (*novoNo)->contador = MAXIMO - meio;

  if (posicao <= MINIMO)
  {
    inserirNo(valor, posicao, no, crianca);
  }
  else
  {
    inserirNo(valor, posicao - meio, *novoNo, crianca);
  }
  *pValor = no->valor[no->contador];
  (*novoNo)->conexoes[0] = no->conexoes[no->contador];
  no->contador--;
}

int setarValor(int valor, int *pValor,
               struct ArvoreBNo *no, struct ArvoreBNo **crianca)
{
  int posicao;
  if (!no)
  {
    *pValor = valor;
    *crianca = NULL;
    return 1;
  }

  if (valor < no->valor[1])
  {
    posicao = 0;
  }
  else
  {
    for (posicao = no->contador;
         (valor < no->valor[posicao] && posicao > 1); posicao--)
      ;
    if (valor == no->valor[posicao])
    {
      return 0;
    }
  }
  if (setarValor(valor, pValor, no->conexoes[posicao], crianca))
  {
    if (no->contador < MAXIMO)
    {
      inserirNo(*pValor, posicao, no, *crianca);
    }
    else
    {
      dividirNo(*pValor, pValor, posicao, no, *crianca, crianca);
      return 1;
    }
  }
  return 0;
}

void inserir(int valor)
{
  int flag, i;
  struct ArvoreBNo *crianca;

  flag = setarValor(valor, &i, raiz, &crianca);
  if (flag)
    raiz = criarNo(i, crianca);
}

void procurar(int valor, int *posicao, struct ArvoreBNo *myNode)
{
  if (!myNode)
  {
    return;
  }

  if (valor < myNode->valor[1])
  {
    *posicao = 0;
  }
  else
  {
    for (*posicao = myNode->contador;
         (valor < myNode->valor[*posicao] && *posicao > 1); (*posicao)--)
      ;
    if (valor == myNode->valor[*posicao])
    {
      printf("%d", myNode->contador);
      verificador = 1;
      return;
    }
  }
  procurar(valor, posicao, myNode->conexoes[*posicao]);

  return;
}

int main()
{
  int valor, ch;
  struct ArvoreBNo *aux;

  while (valor > 0)
  {
    scanf("%d", &valor);
    if (valor < 0)
      break;
    inserir(valor);
  }
  printf("%d\n", raiz->contador);
  scanf("%d", &valor);
  procurar(valor, &ch, raiz);
  if (verificador == 0)
    printf("Valor nao encontrado\n");
}