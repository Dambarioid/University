#include "rational.c"
#include <stdio.h>

char oper(rational_t firstnum, rational_t secnum, char sign, char *last);
long max(long a, long b);
long min(long a, long b);
long KRAT(long fir, long sec);
void checkEd(long finum, long findenom, char *str);
void checkReap(long *fir, long *sec);

char oper(rational_t firstnum, rational_t secnum, char sign, char *last) {
  long findenom, finum;
  if (firstnum.denom == 0 || secnum.denom == 0) {
    printf("Stop trying to divine on 0\n");
    return 0;
  }

  switch (sign) {

  case '/':
    findenom = firstnum.denom * secnum.num;
    finum = firstnum.num * secnum.denom;
    break;

  case '*':
    findenom = firstnum.denom * secnum.denom;
    finum = firstnum.num * secnum.num;
    break;

  case '+':
    findenom = KRAT(firstnum.denom, secnum.denom);
    finum = firstnum.num * (findenom / firstnum.denom) + secnum.num * (findenom / secnum.denom);
    break;

  case '-':
    findenom = KRAT(firstnum.denom, secnum.denom);
    finum = firstnum.num * (findenom / firstnum.denom) - secnum.num * (findenom / secnum.denom);
    break;
  }
  checkReap(&finum,&findenom);
  checkEd(finum,findenom,last);

}
long KRAT(long fir, long sec) {
  long obsh = max(fir, sec);
  while (1) {
    if (obsh % fir == 0 && obsh % sec == 0)
      break;
    obsh += max(fir, sec);
  }
  return obsh;
}

long max(long a, long b) { return (a > b || a == b) ? a : b; }

void checkReap(long *fir, long *sec) {
  long div = 1;
  for (long i = 1; i <= min(*fir, *sec); i++) {
    if (*fir % i == 0 && *sec % i == 0)
      div = i;
  }
  *fir = *fir / div;
  *sec = *sec / div;
}

void checkEd(long finum, long findenom, char *str) {
  if (findenom == 0) {
    fprintf(stderr, "Stop trying to divine on 0\n");
  } else if (findenom == 1) {
    sprintf(str, "%ld/%ld", finum, findenom);
  } else if (findenom != 1 || findenom != 0) {
    sprintf(str, "%ld/%ld", finum, findenom);
  }
}

long min(long a, long b) { return (a < b || a == b) ? a : b; }

