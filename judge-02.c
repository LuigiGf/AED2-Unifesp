#include <stdio.h>

//GLOBAL VARIABLES
//v = quantity of tickets needed to earn a book
//books = result of how much books
int v = 0, books = 0, aux = 0;

//recursion function to calculate books
void bookCalculator(int tickets)
{
  int earnedBooks = tickets / v;
  aux += tickets % v;
  books += earnedBooks;
  if (aux >= v)
  {
    books += aux / v;
    aux /= v;
  }
  //verify to finish the recursive function
  if (tickets < v)
  {
    return;
  }
  bookCalculator(earnedBooks);
  return;
}

int main(void)
{
  int money, price, tickets, n, i;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d %d %d", &money, &price, &v);
    if (money > 0)
    {
      tickets = money / price;
      books = tickets;
      bookCalculator(tickets);
    }
    printf("%d\n", books);
    books = 0;
    aux = 0;
  }
  return 0;
}