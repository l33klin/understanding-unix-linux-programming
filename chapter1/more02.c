/**
 * read and print 24 lines then pause for a few special commands
 * feature of version 0.2: reads from /dev/tty for commands
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGELEN 24
#define LINELEN 512
void do_more(FILE*);
int see_more(FILE*);

int main(int ac, char *av[]) {
  FILE* fp;
  if (ac == 1) {
    do_more(stdin);
  } else {
    while (--ac) {
      if ((fp = fopen(*++av, "r")) != NULL) {
        do_more(fp);
        fclose(fp);
      } else {
        exit(1);
      }
    }
  }
  return 0;
}

/**
 * read PAGELEN lines, then call see_more() for further instructions
 */
void do_more(FILE* fp) {
  char line[LINELEN];
  int num_of_lines = 0;
  int reply;

  FILE* fp_tty = fopen("/dev/tty", "r");
  if (fp_tty == NULL)
    exit(1);

  while (fgets(line, LINELEN, fp)) {
    if (num_of_lines == PAGELEN) {
      reply = see_more(fp_tty);
      if (reply == 0)
        break;
      num_of_lines -= reply;
    }
    if (fputs(line, stdout) == EOF)
      exit(1);
    num_of_lines++;
  }
}

/**
 * print message, wait for response, return # of lines to advance
 * q means no, space means yes, CR means one line
 */
int see_more(FILE* cmd) {
  int c;
  printf("\033[7m more? \033[m");
  while ((c = getc(cmd)) != EOF) {
    if (c == 'q')
      return 0;
    if (c == ' ')
      return PAGELEN;
    if (c == '\n')
      return 1;
  }
  return 0;
}
