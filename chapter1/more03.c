/**
 * read and print 24 lines then pause for a few special commands
 * feature of version 0.2: reads from /dev/tty for commands
 *
 * Problem solved:
 * 1. Read char from stdin without press enter, more detail: https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar
 * 2. Get terminal size for show self-adaptive, more detail: https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
 */

#include <sys/ioctl.h>  //ioctl
#include <stdio.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include <stdlib.h>
#include <string.h>

int PAGELEN;
int LINELEN;
void do_more(FILE*);
int see_more(FILE*);

int main(int ac, char *av[]) {

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);  // Get terminal size for self-adaptive show
  PAGELEN = w.ws_row;
  LINELEN = w.ws_col;

  static struct termios oldt, newt;

  /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
  tcgetattr( STDIN_FILENO, &oldt);
  /*now the settings will be copied*/
  newt = oldt;

  /*ICANON normally takes care that one line at a time will be processed
  that means it will return if it sees a "\n" or an EOF or an EOL*/
  newt.c_lflag &= ~(ICANON);

  /*Those new settings will be set to STDIN
  TCSANOW tells tcsetattr to change attributes immediately. */
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);

  /* This is your part */
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

  /*restore the old settings*/
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

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
    short ret = -1;
    if (c == 'q')
      ret = 0;
    if (c == ' ') {
      ret = PAGELEN;
    }
    if (c == '\n') {
      ret = 1;
    }
    if (ret != -1) {
      printf("%c[2K", 27);
      return ret;
    }
  }
  return 0;
}
