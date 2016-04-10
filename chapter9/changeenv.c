/**
 * show how to change the environment
 * note: call "env" to display its new settings
 */
#include <stdio.h>
#include <unistd.h>

extern char ** environ;

int main() {
  char *table[3];

  table[0] = "TERM=vt100";
  table[1] = "HOME=/on/the/range";
  table[2] = NULL;

  environ = table;
  execlp("env", "env", NULL);

  return 0;
}
