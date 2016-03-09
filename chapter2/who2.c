/**
 * open, read UTMP file, and show
 * suppresses empty records
 * formats time nicely
 */

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST
void show_time(long);
void show_info(struct utmp*);

int main() {
  struct utmp current_record;
  int utmpfd;
  int reclen = sizeof(current_record);

  if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
    perror(UTMP_FILE);
    exit(1);
  }

  while (read(utmpfd, &current_record, reclen) == reclen)
    show_info(&current_record);
  close(utmpfd);
  return 0;
}

/**
 * display cotents of the utmp struct in human readable form
 * *note* these sizes should not be hardwired
 */
void show_info(struct utmp* utbufp) {
  if (utbufp->ut_type != USER_PROCESS) // user only
    return;

  printf("%-8.8s", utbufp->ut_name);
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  show_time(utbufp->ut_time);
  #ifdef SHOWHOST
  if (utbufp->ut_host[0] != '\0')
    printf("(%s)", utbufp->ut_host);
  #endif
  printf("\n");
}

/**
 * display time in a format fit for human consumption
 * use ctime to build a string then picks pars out of it
 * Node: %12.12s prints a string 12 chars wide and LIMITS
 * it to 12 chars
 */
void show_time(long timeval) {
  char *cp;
  cp = ctime(&timeval); // looks like: Mon Feb 4 00:46:40 EST 1991
  printf("%12.12s", cp + 4);
}
