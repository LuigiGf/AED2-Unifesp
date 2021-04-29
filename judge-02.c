#include <stdio.h>

//GLOBAL VARIABLES
//v = quantity of tickets needed to earn a book
//books = result of how much books
int v = 0;
int calculaVales(int tickets)
{
  if (tickets >= v)
    return 1 + calculaVales(tickets - v + 1);
  else
    return 0;
}
//tentativa abaixo estava dando 2 erros
//recursion function to calculate books
// void bookCalculator(int tickets)
// {
//   int earnedBooks = tickets / v;
//   aux += tickets % v;
//   books += earnedBooks;
//   if (aux >= v)
//   {
//     books += aux / v;
//     aux /= v;
//   }
//   //verify to finish the recursive function
//   if (tickets < v)
//   {
//     return;
//   }
//   bookCalculator(earnedBooks);
//   return;
// }

int main(void)
{
  int money, price, tickets, n, i, books;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d %d %d", &money, &price, &v);
    //if (money > 0)
    //{
    tickets = money / price;
    books = tickets + calculaVales(tickets);
    //}
    printf("%d\n", books);
  }
  return 0;
}