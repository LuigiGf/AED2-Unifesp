#include <stdio.h>
#include <math.h>

int primeNumberCalculator(int entry)
{
  int i;
  //for(i = 2; i <= sqrt(entry); i++){}
  for (i = 2; i <= entry / 2; i++)
  {
    //se a entrada por i for igual a zero significa não primo
    if (entry % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  int value, i, count;
  scanf("%d", &count);
  for (i = 0; i < count; i++)
  {
    scanf("%d", &value);
    // if (primeNumberCalculator(value))
    // {
    //   printf("%d 1\n", value);
    // }
    // else
    // {
    //   printf("%d 0\n", value);
    // }
    printf("%d %d\n", value, primeNumberCalculator(value));
  }
  return 0;
}