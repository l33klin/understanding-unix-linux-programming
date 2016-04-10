#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  char *cp = getenv("LANG");
  if (cp)
    printf("%s\n", cp);
  else
    printf("he");
}
