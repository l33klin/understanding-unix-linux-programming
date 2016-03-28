/**
 * purpose: show use of sigaction()
 * feature: blocks ^\ while handling ^C
 *          does not reset ^C handler, so two kill
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#define INPUTLEN 100

int main() {
  struct sigaction new_hander;
  sigset_t blocked;
  void intHandler();
  char x[INPUTLEN];

  // load these two members first
  new_hander.sa_handler = intHandler;
  new_hander.sa_flags = SA_RESETHAND | SA_RESTART;

  // then build the list of blocked signals
  sigemptyset(&blocked);
  sigaddset(&blocked, SIGQUIT);
  new_hander.sa_mask = blocked;   // store blockmask

  if (sigaction(SIGINT, &new_hander, NULL) == -1)
    perror("sigaction");
  else
    while (1) {
      fgets(x, INPUTLEN, stdin);
      printf("input: %s", x);
    }
}

void intHandler(int s) {
  printf("Called with signal %d\n", s);
  sleep(s);
  printf("Done handling signal %d\n", s);
}
