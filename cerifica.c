#include <stdio.h>
#include <string.h>

typedef struct
{
  int quantidade;
  char nome[50];
} Ingredientes;

typedef struct
{
  int quantidadeIngredientes;
  char nome[25];
  Ingredientes ingredientes[100];

} receitas;

int main(void)
{
  receitas Livro[50];
  strcpy(Livro[0].ingredientes[0].nome, "teste");
  return 0;
}