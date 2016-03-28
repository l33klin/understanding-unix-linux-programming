/**
 * purpose : show answers to signal questions
 * questions1: does the handler stay in effect after a signal arrives?
 * questions2: what if a signalX arrives while handling signalX?
 * questions3: what if a signalY arrives while handling signalY?
 * questions4: what happens to read() when a signal arrives?
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define INPUTLEN 100

int main(int argc, char *argv[]) {
  void intHandler(int);
  void quitHandler(int);
  char input[INPUTLEN];
  int nchars;

  signal(SIGINT, intHandler);
  signal(SIGQUIT, quitHandler);

  do {
    printf("\nType a message\n");
    nchars = read(0, input, (INPUTLEN - 1));
    if (nchars == -1) {
      perror("read returned a error");
    } else {
      input[nchars] = '\0';
      printf("You typed: %s", input);
    }
  } while (strncmp(input, "quit", 4) != 0);

}

void intHandler(int s) {
  printf(" Received signal %d .. waiting\n", s);
  sleep(2);
  printf("Leaving intHandler\n");
}

void quitHandler(int s) {
  printf(" Received signal %d .. waiting\n", s);
  sleep(3);
  printf("Leaving quitHandler\n");
}
