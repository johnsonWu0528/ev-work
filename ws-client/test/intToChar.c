#include "stdio.h"

void int2str(int , char *);

int main() {
  int i = 123;
  char s[64];

  int2str(i, s);

  printf("%s\n", s);
}

void int2str(int i, char *s) {
  sprintf(s,"%d",i);
}