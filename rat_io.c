#include "rat_math.c"
#include <stdio.h>
#include <string.h>

void checkNull(char *str);
void inout(char *last);
rational_t transform(char *arr);
void inout(char *last) {

  char str1[50];
  char firNum[50];
  char secNum[50];
  char sign;

  printf("Введите выражение с рациональными числами: ");
  
  fgets(str1, 50, stdin);

  sscanf(str1, "%s %c %s", firNum, &sign, secNum);

  rational_t firvar, secvar;

  if (strncmp(firNum, "last", 4) == 0) {
    firvar = transform(last);
  } else {
    firvar = transform(firNum);
  }

  if (strncmp(secNum, "last", 4) == 0) {
    secvar = transform(last);
  } else {
    secvar = transform(secNum);
  }

  oper(firvar, secvar, sign, last);

  if (transform(last).denom == 1)
    printf("%ld\n",transform(last).num);
  else printf("%s\n",last);

}

rational_t transform(char *arr) {
  long num, denom;
  sscanf(arr, "%d/%u", &num, &denom);
  if (strchr(arr, '/') == NULL)
    denom = 1;
  else if (strchr(arr, '/') != NULL && denom == 0) {
    num = 0;
    denom = 0;
  }
  rational_t result = rational(num, denom);
  return result;
}


void checkNull(char *str) {
  if (str == NULL) {
    printf("Ошибка в размещении строки");
    return;
  }
}
