#include "rational/rat_io.c"
#include <string.h>
int main() {
  char last[30];
  strcpy(last, "0");
  while (1) {
    inout(last);
  }
}
